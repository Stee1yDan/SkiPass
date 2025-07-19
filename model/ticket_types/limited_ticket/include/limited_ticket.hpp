#pragma once
#include "abstract_ticket.hpp"


namespace SkiPass {
    class LimitedTicket : public AbstractTicket {
    public:
        bool pass() override;

        bool can_pass() override;

        LimitedTicket(ticket_id_t id,
                        const std::string &full_name,
                        unsigned age,
                        const gender_t &gender,
                        TicketType,
                        balance_unit_t balance)
            : LimitedTicket(id, full_name, age, gender, TicketType::LIMITED, balance) {}

        [[nodiscard]] bool extend_ticket(extension_unit_t value) override;

        [[nodiscard]] balance_unit_t get_balance() override;

        [[nodiscard]] std::shared_ptr<AbstractTicket> clone() const override;

        ~LimitedTicket() override;
    };
}
