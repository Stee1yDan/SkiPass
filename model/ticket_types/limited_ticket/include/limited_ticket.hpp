#pragma once
#include <utility>

#include "abstract_ticket.hpp"
#include "extendable_ticket.hpp"


namespace SkiPass {
    class LimitedTicket : public ExtendableTicket{
    public:
        bool pass(unsigned tourniquet_id) override;

        bool can_pass(unsigned tourniquet_id) override;

        LimitedTicket(ticket_id_t id,
                        const std::string &full_name,
                        unsigned age,
                        const gender &gender,
                        TicketType,
                        const balance_unit_t& balance)
            :  ExtendableTicket(id, full_name, age, gender, TicketType::LIMITED, balance) {
        }

        [[nodiscard]] bool extend_ticket(extension_unit_t value) override;

        [[nodiscard]] balance_unit_t get_balance() override;

        [[nodiscard]] std::shared_ptr<AbstractTicket> clone() const override;

        ~LimitedTicket() override;

        ExtendableTicket & operator+=(const extension_unit_t &amount) override;

        LimitedTicket(const LimitedTicket &other)
            : ExtendableTicket(other) {
        }


        LimitedTicket(LimitedTicket &&other) noexcept
            : ExtendableTicket(std::move(other)) {
        }

        LimitedTicket & operator=(const LimitedTicket &other) {
            if (this == &other)
                return *this;
            ExtendableTicket::operator =(other);
            return *this;
        }

        LimitedTicket & operator=(LimitedTicket &&other) noexcept {
            if (this == &other)
                return *this;
            ExtendableTicket::operator =(std::move(other));
            return *this;
        }
    };
}
