#include "ticket_service.hpp"

namespace SkiPass {
    const std::unordered_map<unsigned, bool> TicketService::service_tourniquet_registry {
        std::pair{0, false},
        std::pair{1, false},
        std::pair{2, false},
        std::pair{3, false},
        std::pair{4, false},
        std::pair{5, true}
    };

    const std::unordered_map<AbstractTicket::TicketType, unsigned> TicketService::ticket_extension_prices {
        std::pair{AbstractTicket::TicketType::LIMITED, 50},
        std::pair{AbstractTicket::TicketType::TEMPORARY, 200}
    };

    bool TicketService::is_service_tourniquet(unsigned tourniquet_id) {
        return service_tourniquet_registry.at(tourniquet_id);
    }

    TicketService::TicketService(std::shared_ptr<ITicketRepository> repository) {
        repository_ = repository;
    }

    std::shared_ptr<AbstractTicket> TicketService::add_ticket(std::shared_ptr<AbstractTicket> ticket) {
        return repository_->add_ticket(std::move(ticket));
    }

    std::optional<std::shared_ptr<AbstractTicket>> TicketService::get_ticket(AbstractTicket::ticket_id_t id) {
        return repository_->get_ticket(id);
    }

    TicketService::TicketInfo TicketService::get_ticket_info_struct(const std::shared_ptr<AbstractTicket>& ticket) {
        TicketInfo ticket_info;
        ticket_info.full_name = ticket->full_name;
        ticket_info.age = ticket->age;
        ticket_info.gender = ticket->gender;
        ticket_info.ticket_type = ticket->ticket_type;
        ticket_info.balance = ticket->get_balance();
        ticket_info.ticket_id = ticket->id;
        return ticket_info;
    }

    TicketService::TicketService(ITicketRepository &repository) {
    }

    TicketService::ticket_management_operation_status TicketService::delete_ticket(AbstractTicket::ticket_id_t id) {
        if (repository_->delete_ticket(id)) {
            return TicketService::ticket_management_operation_status::success;
        }
        return TicketService::ticket_management_operation_status::no_such_ticket_found;
    }

    TicketService::pass_operation_status TicketService::pass_through_tourniquet(AbstractTicket::ticket_id_t id, //add tourniquet check
        unsigned tourniquet_id) const {
        auto ticket = repository_->get_ticket(id);

        if (!ticket.has_value()) {
            return pass_operation_status::no_such_ticket_found;
        }

        if (!ticket->get()->can_pass()) {
            if (ticket->get()->ticket_type == AbstractTicket::TicketType::LIMITED)
                return pass_operation_status::no_passes_left;

            if (ticket->get()->ticket_type == AbstractTicket::TicketType::TEMPORARY)
                return pass_operation_status::ticket_expired;
        }

        if (!is_service_tourniquet(tourniquet_id) &&
            ticket->get()->ticket_type == AbstractTicket::TicketType::SERVICE) {
            return pass_operation_status::wrong_tourniquet;
        }

        ticket->get()->pass();

        return pass_operation_status::success;
    }

    TicketService::BalanceOperation TicketService::extend_ticket(AbstractTicket::ticket_id_t id,
        int extension_units,
        int funds) const {

        auto ticket = repository_->get_ticket(id);

        if (extension_units < 0) {
            return BalanceOperation(balance_operation_status::invalid_extension_unit, 0);
        }

        if (funds < 0) {
            return BalanceOperation(balance_operation_status::not_enough_money, 0);
        }

        if (!ticket.has_value()) {
            return BalanceOperation(balance_operation_status::no_such_ticket_found, 0);
        }



        auto ticket_type = ticket->get()->ticket_type;

        if (ticket_type == AbstractTicket::TicketType::SERVICE) {
            return BalanceOperation(balance_operation_status::invalid_ticket_type,0);
        }

        if (ticket_type == AbstractTicket::TicketType::UNLIMITED) {
            return BalanceOperation(balance_operation_status::invalid_ticket_type,0);
        }



        auto funds_needed = extension_units * ticket_extension_prices.at(ticket_type);

        if (funds_needed > funds) {
            return BalanceOperation(balance_operation_status::not_enough_money,0);
        }

        if (!ticket->get()->extend_ticket(extension_units)) {
            return BalanceOperation(balance_operation_status::operation_declined,0);
        }



        auto change = funds - funds_needed;
        return BalanceOperation(balance_operation_status::success,change);
    }

    std::unordered_map<AbstractTicket::TicketType, unsigned> TicketService::get_extension_prices() {
        return ticket_extension_prices;
    }
}
