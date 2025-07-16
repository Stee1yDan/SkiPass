#pragma once
#include "ticket.hpp"
#include <iostream>
#include <utility>

namespace SkiPass {
    class AbstractTicket : public ITicket {
    public:

    enum class TicketType {
        UNLIMITED,
        TEMPORARY,
        LIMITED,
        SERVICE};

    AbstractTicket(ticket_id_t id,const std::string &full_name, unsigned age, const gender_t &gender, TicketType ticket_type, balance_unit_t balance)
        : id(id),
          full_name(full_name),
          age(age),
          gender(gender),
          ticket_type(ticket_type),
          balance(balance){
    }

    AbstractTicket(ticket_id_t id, const std::string & string, unsigned age, const gender_t & gender, TicketType ticket);
    ~AbstractTicket() override;

    ticket_id_t id;
        std::string full_name;
        unsigned age;
        gender_t gender;
        TicketType ticket_type;
        balance_unit_t balance;
    };
    std::ostream& operator<<(std::ostream& os, AbstractTicket::TicketType ticket);
}