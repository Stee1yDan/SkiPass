#pragma once
#include "abstract_ticket.hpp"

namespace SkiPass {
    class ExtendableTicket : public AbstractTicket {
    public:
        ExtendableTicket(ticket_id_t id, const std::string &full_name, unsigned age, const gender_t &gender,
            TicketType ticket_type, const balance_unit_t& balance)
            : AbstractTicket(id, full_name, age, gender, ticket_type) {
        }

        using balance_unit_t = std::string;
        balance_unit_t balance;

        virtual bool extend_ticket(extension_unit_t value);

        virtual balance_unit_t get_balance();

        ~ExtendableTicket() override;

    };
}
