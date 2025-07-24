#pragma once

#include <abstract_ticket_repository.hpp>
#include <abstract_ticket.hpp>

#include <optional>
#include <random>
#include <map>
#include <limits>
#include <unordered_map>

#include "storage_unit.hpp"


namespace SkiPass
{
    class IStorageUnitRepository;

    class TicketService
    {
    public:
        explicit TicketService(const std::shared_ptr<ITicketRepository> &ticket_repository)
            : ticket_repository_(ticket_repository) {
        }

        using ticket_id_t = ITicketRepository::ticket_id_t;

        struct TicketInfo {
            std::string full_name;
            AbstractTicket::gender_t gender;
            unsigned age;
            AbstractTicket::ticket_id_t ticket_id;
            AbstractTicket::TicketType ticket_type;
            AbstractTicket::balance_unit_t balance;
        };

        enum class ticket_management_operation_status {
            success,
            wrong_type_of_ticket,
            no_such_ticket_found,
            operation_declined
        };


        enum class balance_operation_status {
            success,
            invalid_extension_unit,
            invalid_ticket_type,
            not_enough_money,
            no_such_ticket_found,
            operation_declined
        };

        struct BalanceOperation {
            balance_operation_status status;
            unsigned change;
        };


        std::size_t ticket_id_{};

        explicit TicketService(ITicketRepository &repository);

        [[nodiscard]] std::shared_ptr<AbstractTicket> add_ticket(std::shared_ptr<AbstractTicket> ticket);
        [[nodiscard]] ticket_management_operation_status delete_ticket(AbstractTicket::ticket_id_t ticket);
        [[nodiscard]] std::optional<std::shared_ptr<AbstractTicket>> get_ticket(AbstractTicket::ticket_id_t id);
        [[nodiscard]] ticket_management_operation_status change_owner(AbstractTicket::ticket_id_t id, std::string new_name) const;
        [[nodiscard]] BalanceOperation extend_ticket(AbstractTicket::ticket_id_t id, int extension_units, int funds) const;
        [[nodiscard]] static std::unordered_map<AbstractTicket::TicketType, unsigned> get_extension_prices();
        [[nodiscard]] static TicketInfo get_ticket_info_struct(const std::shared_ptr<AbstractTicket>& ticket);

        [[nodiscard]] std::shared_ptr<ITicketRepository> get_ticket_repository();

    private:
        std::shared_ptr<ITicketRepository> ticket_repository_;
        static const std::unordered_map<AbstractTicket::TicketType, unsigned> ticket_extension_prices_;
    };
}
