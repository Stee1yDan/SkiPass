#include "service_ticket.hpp"

bool SkiPass::ServiceTicket::pass() {
    return true;
}

bool SkiPass::ServiceTicket::can_pass() {
    return true;
}

bool SkiPass::ServiceTicket::extend_ticket(extension_unit_t value) {
    return true;
}

SkiPass::AbstractTicket::balance_unit_t SkiPass::ServiceTicket::get_balance() {
    return balance;
}

std::shared_ptr<SkiPass::AbstractTicket> SkiPass::ServiceTicket::clone() const {
    auto new_ticket = std::make_shared<ServiceTicket>(id, full_name, age, gender, ticket_type, balance);
    return new_ticket;
}

SkiPass::ServiceTicket::~ServiceTicket() {
}
