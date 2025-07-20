#pragma once
#include "abstract_ticket.hpp"

namespace SkiPass {
    class TransferableTicket : public AbstractTicket {
    public:
        TransferableTicket(ticket_id_t id, const std::string &full_name, unsigned age, const gender_t &gender,
            TicketType ticket_type)
            : AbstractTicket(id, full_name, age, gender, ticket_type) {
        }

        bool change_owner(const std::string &new_owner);
        void operator()(const std::string& new_owner);

        ~TransferableTicket() override;

    };
}
