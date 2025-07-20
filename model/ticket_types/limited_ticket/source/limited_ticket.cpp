#include "limited_ticket.hpp"

#include <format>

bool SkiPass::LimitedTicket::pass(unsigned tourniquet_id) {
    try {
        auto balance_unit = std::stoll(balance);
        balance = std::to_string(--balance_unit);
        return tourniquet_exists(tourniquet_id);
    }
    catch (const std::exception& e) {
        return false;
    }
}

bool SkiPass::LimitedTicket::can_pass(unsigned tourniquet_id) {
    return std::stoll(balance) > 0 && AbstractTicket::tourniquet_exists(tourniquet_id);;
}

bool SkiPass::LimitedTicket::extend_ticket(extension_unit_t value) {
    try {
        long long balance_unit = std::stoll(balance);
        balance_unit += value;
        balance = std::to_string(balance_unit);
        return true;
    }
    catch (const std::exception& e) {
        return false;
    }

}

SkiPass::ExtendableTicket & SkiPass::LimitedTicket::operator+=(const extension_unit_t &amount) {
    extend_ticket(amount);
    return *this;
}

SkiPass::AbstractTicket::balance_unit_t SkiPass::LimitedTicket::get_balance() {
    return std::format("Passes left - {}",balance);
}

std::shared_ptr<SkiPass::AbstractTicket> SkiPass::LimitedTicket::clone() const {
    auto new_ticket = std::make_shared<LimitedTicket>(id, full_name, age, gender, ticket_type, balance);
    return new_ticket;
}

SkiPass::LimitedTicket::~LimitedTicket() = default;
