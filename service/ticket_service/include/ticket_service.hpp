#pragma once

#include <abstract_ticket_repository.hpp>
#include <abstract_ticket.hpp>

#include <optional>
#include <random>
#include <map>
#include <limits>
#include <unordered_map>


namespace SkiPass
{
    class TicketService
    {
    public:
        explicit TicketService(std::shared_ptr<ITicketRepository> repository);
        using ticket_id_t = ITicketRepository::ticket_id_t;

        struct TicketInfo {
            std::string full_name;
            AbstractTicket::gender_t gender;
            unsigned age;
            AbstractTicket::ticket_id_t ticket_id;
            AbstractTicket::TicketType ticket_type;
            AbstractTicket::balance_unit_t balance;
        };


        enum class pass_operation_status {
            success,
            ticket_expired,
            no_passes_left,
            wrong_tourniquet,
            no_such_ticket_found,
            operation_declined
        };

        enum class ticket_management_operation_status {
            success,
            no_such_ticket_found
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
        [[nodiscard]] pass_operation_status pass_through_tourniquet(AbstractTicket::ticket_id_t id, unsigned tourniquet_id) const;
        [[nodiscard]] pass_operation_status can_pass_through_tourniquet(AbstractTicket::ticket_id_t id, unsigned tourniquet_id) const;
        [[nodiscard]] BalanceOperation extend_ticket(AbstractTicket::ticket_id_t id, int extension_units, int funds) const;
        [[nodiscard]] std::shared_ptr<ITicketRepository> get_repository();
        [[nodiscard]] static std::unordered_map<AbstractTicket::TicketType, unsigned> get_extension_prices() ;
        [[nodiscard]] static TicketInfo get_ticket_info_struct(const std::shared_ptr<AbstractTicket>& ticket);

    private:
        std::shared_ptr<ITicketRepository> repository_;
        static const std::unordered_map<AbstractTicket::TicketType, unsigned> ticket_extension_prices;
    };
}
