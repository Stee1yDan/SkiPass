#pragma once
#include <chrono>

#include "abstract_ticket.hpp"
#include "extendable_ticket.hpp"

namespace SkiPass {
    class TemporaryTicket : public ExtendableTicket {
    public:
        bool pass(unsigned tourniquet_id) override;

        bool can_pass(unsigned tourniquet_id) override;

        TemporaryTicket(ticket_id_t id,
                        const std::string &full_name,
                        unsigned age,
                        const gender &gender,
                        TicketType,
                        const balance_unit_t& balance)
            : ExtendableTicket(id, full_name, age, gender, TicketType::TEMPORARY, balance) {}

        [[nodiscard]] bool extend_ticket(extension_unit_t value) override;

        [[nodiscard]] balance_unit_t get_balance() override;

        [[nodiscard]] std::shared_ptr<AbstractTicket> clone() const override;

        ExtendableTicket & operator+=(const extension_unit_t &amount) override;

        ~TemporaryTicket() override;

        TemporaryTicket(const TemporaryTicket &other)
            : ExtendableTicket(other) {
        }

        TemporaryTicket(TemporaryTicket &&other) noexcept
            : ExtendableTicket(std::move(other)) {
        }

        TemporaryTicket & operator=(const TemporaryTicket &other) {
            if (this == &other)
                return *this;
            ExtendableTicket::operator =(other);
            return *this;
        }

        TemporaryTicket & operator=(TemporaryTicket &&other) noexcept {
            if (this == &other)
                return *this;
            ExtendableTicket::operator =(std::move(other));
            return *this;
        }
    };
}
