#include "service_ticket.hpp"

bool SkiPass::ServiceTicket::pass(unsigned tourniquet_id) {
    return can_pass(tourniquet_id);
}

bool SkiPass::ServiceTicket::can_pass(unsigned tourniquet_id) {
    return tourniquet_exists(tourniquet_id) && is_service_tourniquet(tourniquet_id);
}

std::shared_ptr<SkiPass::AbstractTicket> SkiPass::ServiceTicket::clone() const {
    auto new_ticket = std::make_shared<ServiceTicket>(ticket_id_t_, full_name_, age_, gender_, ticket_type_);
    return new_ticket;
}
