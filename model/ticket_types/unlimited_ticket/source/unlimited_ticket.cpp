#include "unlimited_ticket.hpp"

namespace SkiPass {
    bool UnlimitedTicket::pass(unsigned tourniquet_id) {
        return tourniquet_exists(tourniquet_id);
    }

    bool UnlimitedTicket::can_pass(unsigned tourniquet_id) {
        return tourniquet_exists(tourniquet_id);
    }

    std::shared_ptr<AbstractTicket> UnlimitedTicket::clone() const {
        auto new_ticket = std::make_shared<UnlimitedTicket>(id, full_name, age, gender, ticket_type);
        return new_ticket;
    }

    UnlimitedTicket::~UnlimitedTicket() = default;
}
