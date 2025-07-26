#pragma once
#include <utility>

#include "abstract_ticket.hpp"

namespace SkiPass {
    class ExtendableTicket : public AbstractTicket {
    public:
        ExtendableTicket(ticket_id_t id, const std::string &full_name, unsigned age, const gender &gender,
            TicketType ticket_type, balance_unit_t  balance)
            : AbstractTicket(id, full_name, age, gender, ticket_type), balance_(std::move(balance)) {
        }

        using balance = std::string;

        virtual bool extend_ticket(extension_unit_t value) = 0;

        virtual balance get_balance() = 0;

        [[nodiscard]] balance get_balance() const;
        void set_balance(const balance &balance);

        virtual ExtendableTicket& operator+=(const extension_unit_t& amount);

        ~ExtendableTicket() override;

        ExtendableTicket(const ExtendableTicket &other)
            : AbstractTicket(other),
              balance_(other.balance_) {
        }

        ExtendableTicket(ExtendableTicket &&other) noexcept
            : AbstractTicket(other),
              balance_(std::move(other.balance_)) {
        }

        ExtendableTicket & operator=(const ExtendableTicket &other) {
            if (this == &other)
                return *this;
            AbstractTicket::operator =(other);
            balance_ = other.balance_;
            return *this;
        }

        ExtendableTicket & operator=(ExtendableTicket &&other) noexcept {
            if (this == &other)
                return *this;
            AbstractTicket::operator =(other);
            balance_ = std::move(other.balance_);
            return *this;
        }

    protected:
        balance balance_;

    };
}
