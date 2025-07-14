#pragma once

#include "ticket.hpp"

namespace SkiPass {
    class UnlimitedTicket : public ITicket {
    public:
        bool pass() override;

        bool can_pass() override;

        UnlimitedTicket(const std::string &full_name, unsigned age, const gender_t &gender, ticket_type_t ticket_type)
            : full_name(full_name),
              age(age),
              gender(gender),
              ticket_type(ticket_type) {
        }

        [[nodiscard]] bool extend_ticket(extension_unit_t value) override;

        [[nodiscard]] std::string get_balance() override;

        [[nodiscard]] std::string get_info() const override;

        [[nodiscard]] std::shared_ptr<ITicket> clone() const override;

        ~UnlimitedTicket() override;

    private:
        std::string full_name;
        unsigned age;
        gender_t gender;
        ticket_type_t ticket_type = TicketType::UNLIMITED;

    };
}
