#pragma once
#include <chrono>

#include "abstract_ticket.hpp"


namespace SkiPass {
    class TemporaryTicket : public AbstractTicket {
    public:
        bool pass() override;

        bool can_pass() override;

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

        std::string convert_date_to_string(const std::chrono::year_month_day& date);
        std::chrono::year_month_day convert_string_to_date(const std::string& dateStr);
    };
}
