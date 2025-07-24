#pragma once
#include "abstract_ticket.hpp"

namespace SkiPass {
    class ExtendableTicket : public AbstractTicket {
    public:
        ExtendableTicket(ticket_id_t id, const std::string &full_name, unsigned age, const gender_t &gender,
            TicketType ticket_type, const balance_unit_t& balance)
            : AbstractTicket(id, full_name, age, gender, ticket_type), balance(balance) {
        }

        using balance_unit_t = std::string;

        virtual bool extend_ticket(extension_unit_t value) = 0;

        virtual balance_unit_t get_balance() = 0;

        [[nodiscard]] balance_unit_t get_balance() const;
        void set_balance(const balance_unit_t &balance);

        virtual ExtendableTicket& operator+=(const extension_unit_t& amount);

        ~ExtendableTicket() override;

        ExtendableTicket(const ExtendableTicket &other)
            : AbstractTicket(other),
              balance(other.balance) {
        }

        ExtendableTicket(ExtendableTicket &&other) noexcept
            : AbstractTicket(other),
              balance(std::move(other.balance)) {
        }

        ExtendableTicket & operator=(const ExtendableTicket &other) {
            if (this == &other)
                return *this;
            AbstractTicket::operator =(other);
            balance = other.balance;
            return *this;
        }

        ExtendableTicket & operator=(ExtendableTicket &&other) noexcept {
            if (this == &other)
                return *this;
            AbstractTicket::operator =(other);
            balance = std::move(other.balance);
            return *this;
        }

    protected:
        balance_unit_t balance;

    };
}
