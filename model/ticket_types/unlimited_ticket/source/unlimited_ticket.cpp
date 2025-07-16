#include "unlimited_ticket.hpp"

namespace SkiPass {
    bool UnlimitedTicket::pass() {
        return true;
    }

    bool UnlimitedTicket::can_pass() {
        return true;
    }

    bool UnlimitedTicket::extend_ticket(extension_unit_t value) {
        return true;
    }

    std::string UnlimitedTicket::get_balance() {
        return "Unlimited";
    }

    std::string UnlimitedTicket::get_info() const {
        return "Unlimited";
    }

    std::shared_ptr<ITicket> UnlimitedTicket::clone() const {
        auto new_ticket = std::make_shared<UnlimitedTicket>(id, full_name, age, gender, ticket_type, balance);
        return new_ticket;
    }

    UnlimitedTicket::~UnlimitedTicket() {};
}
