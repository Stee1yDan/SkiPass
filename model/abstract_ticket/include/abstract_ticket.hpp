#pragma once
#include <iostream>
#include <memory>
#include <utility>

namespace SkiPass {
    class AbstractTicket {
    public:

    enum class TicketType {
        UNLIMITED,
        TEMPORARY,
        LIMITED,
        SERVICE};

    using gender_t = std::string;
    using extension_unit_t = long long;
    using balance_unit_t = std::string;
    using ticket_id_t = unsigned int;

    AbstractTicket(ticket_id_t id,const std::string &full_name, unsigned age, const gender_t &gender, TicketType ticket_type, balance_unit_t balance)
        : id(id),
          full_name(full_name),
          age(age),
          gender(gender),
          ticket_type(ticket_type),
          balance(balance){
    }

    AbstractTicket(ticket_id_t id, const std::string & string, unsigned age, const gender_t & gender, TicketType ticket);

    virtual bool pass() = 0;
    virtual bool can_pass() = 0;
    [[nodiscard]] virtual bool extend_ticket(extension_unit_t value) = 0;
    [[nodiscard]] virtual balance_unit_t get_balance() = 0;
    [[nodiscard]] virtual balance_unit_t get_info() const = 0;
    [[nodiscard]] virtual std::shared_ptr<AbstractTicket> clone() const = 0;

    virtual ~AbstractTicket();

    ticket_id_t id;
        std::string full_name;
        unsigned age;
        gender_t gender;
        TicketType ticket_type;
        balance_unit_t balance;
    };
    std::ostream& operator<<(std::ostream& os, AbstractTicket::TicketType ticket);
}