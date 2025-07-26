#include "limited_ticket.hpp"

#include <format>

bool SkiPass::LimitedTicket::pass(unsigned tourniquet_id) {
    try {
        auto balance_unit = std::stoll(balance_);
        balance_ = std::to_string(--balance_unit);
        return tourniquet_exists(tourniquet_id);
    }
    catch (const std::exception& e) {
        return false;
    }
}

bool SkiPass::LimitedTicket::can_pass(unsigned tourniquet_id) {
    return std::stoll(balance_) > 0 && AbstractTicket::tourniquet_exists(tourniquet_id);;
}

bool SkiPass::LimitedTicket::extend_ticket(extension_unit_t value) {
    try {
        long long balance_unit = std::stoll(balance_);
        balance_unit += value;
        balance_ = std::to_string(balance_unit);
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
    return std::format("Passes left - {}",balance_);
}

std::shared_ptr<SkiPass::AbstractTicket> SkiPass::LimitedTicket::clone() const {
    auto new_ticket = std::make_shared<LimitedTicket>(ticket_id_t_, full_name_, age_, gender_, ticket_type_, balance_);
    return new_ticket;
}

SkiPass::LimitedTicket::~LimitedTicket() = default;
