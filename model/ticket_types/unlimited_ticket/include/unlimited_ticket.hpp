#pragma once
#include "abstract_ticket.hpp"


namespace SkiPass {
    class UnlimitedTicket : public AbstractTicket {
    public:
        bool pass(unsigned tourniquet_id) override;

        bool can_pass(unsigned tourniquet_id) override;

        UnlimitedTicket(ticket_id_t id,
                        const std::string &full_name,
                        unsigned age,
                        const gender_t &gender,
                        TicketType)
            : AbstractTicket(id, full_name, age, gender, TicketType::UNLIMITED) {}

        [[nodiscard]] std::shared_ptr<AbstractTicket> clone() const override;

        ~UnlimitedTicket() override;
    };
}
