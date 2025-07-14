#pragma once
#include "../../abstract_ticket/include/abstract_ticket.hpp"


namespace SkiPass {
    class UnlimitedTicket : public AbstractTicket {
    public:
        bool pass() override;

        bool can_pass() override;

        UnlimitedTicket(const std::string &full_name,
                        unsigned age,
                        const gender_t &gender,
                        ticket_type_t ticket_type)
            : AbstractTicket(full_name, age, gender, TicketType::UNLIMITED) {}

        [[nodiscard]] bool extend_ticket(extension_unit_t value) override;

        [[nodiscard]] std::string get_balance() override;

        [[nodiscard]] std::string get_info() const override;

        [[nodiscard]] std::shared_ptr<ITicket> clone() const override;

        ~UnlimitedTicket() override;
    };
}
