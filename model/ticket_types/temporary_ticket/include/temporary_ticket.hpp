#pragma once
#include <chrono>

#include "abstract_ticket.hpp"

namespace SkiPass {
    class TemporaryTicket : public AbstractTicket {
    public:
        bool pass(unsigned tourniquet_id) override;

        bool can_pass(unsigned tourniquet_id) override;

        TemporaryTicket(ticket_id_t id,
                        const std::string &full_name,
                        unsigned age,
                        const gender_t &gender,
                        TicketType,
                        balance_unit_t balance)
            : AbstractTicket(id, full_name, age, gender, TicketType::TEMPORARY, balance) {}

        [[nodiscard]] bool extend_ticket(extension_unit_t value) override;

        [[nodiscard]] balance_unit_t get_balance() override;

        [[nodiscard]] std::shared_ptr<AbstractTicket> clone() const override;

        ~TemporaryTicket() override;
    };
}
