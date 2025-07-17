#pragma once
#include "../../abstract_ticket/include/abstract_ticket.hpp"


namespace SkiPass {
    class UnlimitedTicket : public AbstractTicket {
    public:
        bool pass() override;

        bool can_pass() override;

        UnlimitedTicket(ticket_id_t id,
                        const std::string &full_name,
                        unsigned age,
                        const gender_t &gender,
                        TicketType ticket_type,
                        balance_unit_t balance)
            : AbstractTicket(id, full_name, age, gender, TicketType::UNLIMITED, balance) {}

        [[nodiscard]] bool extend_ticket(extension_unit_t value) override;

        [[nodiscard]] balance_unit_t get_balance() override;

        [[nodiscard]] balance_unit_t get_info() const override;

        [[nodiscard]] std::shared_ptr<AbstractTicket> clone() const override;

        ~UnlimitedTicket() override;
    };
}
