#pragma once
#include "abstract_ticket.hpp"


namespace SkiPass {
    class ServiceTicket : public AbstractTicket {
    public:
        bool pass(unsigned tourniquet_id) override;

        bool can_pass(unsigned tourniquet_id) override;

        ServiceTicket(ticket_id_t id,
                        const std::string &full_name,
                        unsigned age,
                        const gender_t &gender,
                        TicketType,
                        balance_unit_t balance)
            : AbstractTicket(id, full_name, age, gender, TicketType::SERVICE, balance) {}

        [[nodiscard]] bool extend_ticket(extension_unit_t value) override;

        [[nodiscard]] balance_unit_t get_balance() override;

        [[nodiscard]] std::shared_ptr<AbstractTicket> clone() const override;

        ~ServiceTicket() override;
    };
}
