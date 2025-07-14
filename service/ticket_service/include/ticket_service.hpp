#pragma once

#include <abstract_ticket_repository.hpp>
#include <ticket.hpp>

#include <optional>
#include <random>
#include <map>
#include <limits>


namespace SkiPass
{
    class TicketService
    {
    public:
        explicit TicketService(std::shared_ptr<ITicketRepository> repository);

        using ticket_id_t = ITicketRepository::ticket_id_t;

        enum class pass_operation_status {
            success,
            ticket_expired,
            no_passes_left,
            wrong_tourniquet,
            operation_declined
        };

        enum class balance_operation_status {
            success,
            invalid_extension_period,
            not_enough_money,
            operation_declined
        };

        enum class opening_ticket_operation_status {
            success,
            not_enough_money,
            invalid_ticket_type,
            operation_declined
        };

        struct pass_result {
            std::optional<std::unique_ptr<ITicket::extension_unit_t>> balance;
            pass_operation_status status;
        };

        struct balance_operation_result {
            std::optional<std::unique_ptr<ITicket::extension_unit_t>> balance;
            pass_operation_status status;
        };

        struct opening_ticket_operation_result {
            std::optional<std::optional<std::unique_ptr<ITicket::extension_unit_t>>> ticket;
            opening_ticket_operation_status status;
        };

        std::size_t ticket_id_{};

        TicketService(ITicketRepository &repository);

        [[nodiscard]] std::optional<std::shared_ptr<ITicket>> add_ticket(std::shared_ptr<ITicket> ticket);


    private:
        std::shared_ptr<ITicketRepository> repository_;
    };
}
