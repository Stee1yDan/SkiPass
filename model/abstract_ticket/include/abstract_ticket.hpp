#pragma once
#include "ticket.hpp"

namespace SkiPass {
    class AbstractTicket : public ITicket {
    public:

    enum class TicketType {
        UNLIMITED,
        TEMPORARY,
        LIMITED,
        SERVICE};

    using ticket_type_t = TicketType;

    AbstractTicket(const std::string &full_name, unsigned age, const gender_t &gender, ticket_type_t ticket_type)
        : full_name(full_name),
          age(age),
          gender(gender),
          ticket_type(ticket_type) {
    }

    ~AbstractTicket() override;

        std::string full_name;
        unsigned age;
        gender_t gender;
        ticket_type_t ticket_type;
    };
}