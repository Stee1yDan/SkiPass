#include "ticket_service.hpp"

#include <utility>

#include "abstract_storage_unit_repository.hpp"
#include "storage_unit.hpp"
#include "extendable_ticket.hpp"
#include "../../../model/transferable_ticket/include/transferable_ticket.hpp"

namespace SkiPass {
    const std::unordered_map<AbstractTicket::TicketType, unsigned> TicketService::ticket_extension_prices_{
        std::pair{AbstractTicket::TicketType::LIMITED, 50},
        std::pair{AbstractTicket::TicketType::TEMPORARY, 200}
    };

    TicketService::TicketService(std::shared_ptr<ITicketRepository> repository, const std::shared_ptr<IStorageUnitRepository> &unit_repository) {
        ticket_repository_ = repository;
        storage_unit_repository_ = unit_repository;
    }

    std::shared_ptr<AbstractTicket> TicketService::add_ticket(std::shared_ptr<AbstractTicket> ticket) {
        auto new_ticket  = ticket_repository_->add_ticket(std::move(ticket));

        if (new_ticket.get()->ticket_type != AbstractTicket::TicketType::SERVICE) {
            auto storage_unit = std::make_shared<StorageUnit>(0, new_ticket->id);
            storage_unit_repository_.get()->add_unit(storage_unit);
        }

        return new_ticket;
    }

    std::optional<std::shared_ptr<AbstractTicket> > TicketService::get_ticket(AbstractTicket::ticket_id_t id) {
        return ticket_repository_->get_ticket(id);
    }

    TicketService::TicketInfo TicketService::get_ticket_info_struct(const std::shared_ptr<AbstractTicket> &ticket) {
        TicketInfo ticket_info;
        ticket_info.full_name = ticket->full_name;
        ticket_info.age = ticket->age;
        ticket_info.gender = ticket->gender;
        ticket_info.ticket_type = ticket->ticket_type;
        ticket_info.ticket_id = ticket->id;
        return ticket_info;
    }

    TicketService::TicketService(ITicketRepository &repository) {
    }

    TicketService::ticket_management_operation_status TicketService::delete_ticket(AbstractTicket::ticket_id_t id) {
        if (ticket_repository_->delete_ticket(id)) {
            storage_unit_repository_.get()->delete_unit(id); // delete unit by ticket id
            return TicketService::ticket_management_operation_status::success;
        }
        return TicketService::ticket_management_operation_status::no_such_ticket_found;
    }

    TicketService::pass_operation_status TicketService::pass_through_tourniquet(
        AbstractTicket::ticket_id_t id, //add tourniquet check
        unsigned tourniquet_id) const {
        auto ticket = ticket_repository_->get_ticket(id);

        if (!ticket.has_value()) {
            return pass_operation_status::no_such_ticket_found;
        }

        if (!ticket->get()->can_pass(tourniquet_id)) {
            auto ticket_type = ticket->get()->ticket_type;
            if (ticket_type == AbstractTicket::TicketType::LIMITED)
                return pass_operation_status::no_passes_left;

            if (ticket_type == AbstractTicket::TicketType::TEMPORARY)
                return pass_operation_status::ticket_expired;

            if (ticket_type == AbstractTicket::TicketType::SERVICE)
                return pass_operation_status::wrong_tourniquet;
        }

        ticket->get()->pass(tourniquet_id);

        return pass_operation_status::success;
    }

    TicketService::BalanceOperation TicketService::extend_ticket(AbstractTicket::ticket_id_t id,
                                                                 int extension_units,
                                                                 int funds) const {
        auto ticket = ticket_repository_->get_ticket(id);

        if (extension_units < 0) {
            return BalanceOperation(balance_operation_status::invalid_extension_unit, 0);
        }

        if (funds < 0) {
            return BalanceOperation(balance_operation_status::not_enough_money, 0);
        }

        if (!ticket.has_value()) {
            return BalanceOperation(balance_operation_status::no_such_ticket_found, 0);
        }

        auto funds_needed = 0;

        if (ticket_extension_prices_.contains(ticket->get()->ticket_type)) {
            funds_needed = extension_units * ticket_extension_prices_.at(ticket->get()->ticket_type);
        } else {
            return BalanceOperation(balance_operation_status::invalid_ticket_type, 0);
        }

        if (funds_needed > funds) {
            return BalanceOperation(balance_operation_status::not_enough_money, 0);
        }

        auto change = funds - funds_needed;

        std::shared_ptr<ExtendableTicket> extendable_ticket = std::dynamic_pointer_cast<ExtendableTicket>(ticket.value());

        if (extendable_ticket) {
            *extendable_ticket += extension_units;
            return BalanceOperation(balance_operation_status::success, change);
        }

        return BalanceOperation(balance_operation_status::operation_declined, 0);
    }

    TicketService::pass_operation_status TicketService::can_pass_through_tourniquet(AbstractTicket::ticket_id_t id,
        unsigned tourniquet_id) const {
        auto ticket = ticket_repository_->get_ticket(id);

        if (!ticket.has_value()) {
            return pass_operation_status::no_such_ticket_found;
        }

        if (!ticket->get()->can_pass(tourniquet_id)) {
            auto ticket_type = ticket->get()->ticket_type;
            if (ticket_type == AbstractTicket::TicketType::LIMITED)
                return pass_operation_status::no_passes_left;

            if (ticket_type == AbstractTicket::TicketType::TEMPORARY)
                return pass_operation_status::ticket_expired;

            if (ticket_type == AbstractTicket::TicketType::SERVICE)
                return pass_operation_status::wrong_tourniquet;
        }

        if (ticket->get()->can_pass(tourniquet_id)) return pass_operation_status::success;

        return pass_operation_status::operation_declined;
    }

    std::unordered_map<AbstractTicket::TicketType, unsigned> TicketService::get_extension_prices() {
        return ticket_extension_prices_;
    }

    std::shared_ptr<ITicketRepository> TicketService::get_repository() {
        return ticket_repository_;
    }

    TicketService::ticket_management_operation_status TicketService::change_owner(AbstractTicket::ticket_id_t id,
        std::string new_name) const {
        auto ticket = ticket_repository_->get_ticket(id);
        std::shared_ptr<TransferableTicket> transferable_ticket = std::dynamic_pointer_cast<TransferableTicket>(ticket.value());

        if (!ticket.has_value()) {
            return ticket_management_operation_status::no_such_ticket_found;
        }

        if (!transferable_ticket) {
            return ticket_management_operation_status::wrong_type_of_ticket;
        }

        (*transferable_ticket)(new_name);

        return ticket_management_operation_status::success;

    }
}
