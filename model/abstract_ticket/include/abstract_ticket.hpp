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
    using ticket_id_t = unsigned int;

    AbstractTicket(ticket_id_t id,const std::string &full_name, unsigned age, const gender_t &gender, ticket_type_t ticket_type)
        : id(id),
          full_name(full_name),
          age(age),
          gender(gender),
          ticket_type(ticket_type) {
    }

    ~AbstractTicket() override;
        ticket_id_t id;
        std::string full_name;
        unsigned age;
        gender_t gender;
        ticket_type_t ticket_type;
    };
}