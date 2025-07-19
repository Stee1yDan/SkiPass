#include "limited_ticket.hpp"

#include <format>

bool SkiPass::LimitedTicket::pass() {
    auto balance_unit = std::stoll(balance);
    balance = std::to_string(--balance_unit);
}

bool SkiPass::LimitedTicket::can_pass() {
    return std::stoll(balance) > 0;
}

bool SkiPass::LimitedTicket::extend_ticket(extension_unit_t value) {
    long long balance_unit = std::stoll(balance);
    balance_unit += value;
    balance = std::to_string(balance_unit);
}

SkiPass::AbstractTicket::balance_unit_t SkiPass::LimitedTicket::get_balance() {
    return std::format("Passes left - {}",balance);
}

std::shared_ptr<SkiPass::AbstractTicket> SkiPass::LimitedTicket::clone() const {
    auto new_ticket = std::make_shared<LimitedTicket>(id, full_name, age, gender, ticket_type, balance);
    return new_ticket;
}

SkiPass::LimitedTicket::~LimitedTicket() = default;
