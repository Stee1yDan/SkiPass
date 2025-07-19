#pragma once

#include <abstract_ticket_repository.hpp>
#include <abstract_ticket.hpp>

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
            operation_declined
        };

        enum class ticket_management_operation_status {
            success,
            invalid_extension_period,
            not_enough_money,
            operation_declined,
            invalid_id
        };

        struct pass_result {
            std::optional<std::unique_ptr<AbstractTicket::extension_unit_t>> balance;
            pass_operation_status status;
        };

        struct balance_operation_result {
            std::optional<std::unique_ptr<AbstractTicket::extension_unit_t>> balance;
            pass_operation_status status;
        };

        std::size_t ticket_id_{};

        explicit TicketService(ITicketRepository &repository);

        [[nodiscard]] std::shared_ptr<AbstractTicket> add_ticket(std::shared_ptr<AbstractTicket> ticket);
        [[nodiscard]] ticket_management_operation_status delete_ticket(AbstractTicket::ticket_id_t ticket);
        [[nodiscard]] std::optional<std::shared_ptr<AbstractTicket>> get_ticket(AbstractTicket::ticket_id_t id);
        [[nodiscard]] static TicketInfo get_ticket_info_struct(const std::shared_ptr<AbstractTicket>& ticket);


    private:
        std::shared_ptr<ITicketRepository> repository_;
    };
}
