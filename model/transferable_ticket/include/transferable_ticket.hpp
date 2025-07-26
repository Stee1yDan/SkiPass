#pragma once
#include "abstract_ticket.hpp"

namespace SkiPass {
    class TransferableTicket : public AbstractTicket {
    public:
        TransferableTicket(const ticket_id_t id, const std::string &full_name, unsigned age, const gender &gender,
            TicketType ticket_type)
            : AbstractTicket(id, full_name, age, gender, ticket_type) {
        }

        bool change_owner(const std::string &new_owner);
        void operator()(const std::string& new_owner);

        ~TransferableTicket() override;

        TransferableTicket(const TransferableTicket &other)
            : AbstractTicket(other) {
        }

        TransferableTicket(TransferableTicket &&other) noexcept
            : AbstractTicket(other) {
        }

        TransferableTicket & operator=(const TransferableTicket &other) {
            if (this == &other)
                return *this;
            AbstractTicket::operator =(other);
            return *this;
        }

        TransferableTicket & operator=(TransferableTicket &&other) noexcept {
            if (this == &other)
                return *this;
            AbstractTicket::operator =(other);
            return *this;
        }
    };
}
