#include "unlimited_ticket.hpp"

namespace SkiPass {
    bool UnlimitedTicket::pass(unsigned tourniquet_id) {
        return can_pass(tourniquet_id);
    }

    bool UnlimitedTicket::can_pass(unsigned tourniquet_id) {
        return tourniquet_exists(tourniquet_id);
    }

    std::shared_ptr<AbstractTicket> UnlimitedTicket::clone() const {
        auto new_ticket = std::make_shared<UnlimitedTicket>(ticket_id_t_, full_name_, age_, gender_, ticket_type_);
        return new_ticket;
    }

    UnlimitedTicket::~UnlimitedTicket() = default;
}
