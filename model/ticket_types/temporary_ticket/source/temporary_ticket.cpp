#include "temporary_ticket.hpp"
#include "time_utils.hpp"

#include <chrono>

bool SkiPass::TemporaryTicket::pass(unsigned tourniquet_id) {
    return tourniquet_exists(tourniquet_id);
}

bool SkiPass::TemporaryTicket::can_pass(unsigned tourniquet_id) {
    try {
        auto ticket_expiration_date = TimeUtils::convert_string_to_date(balance_);

        auto now = std::chrono::system_clock::now();
        auto today = std::chrono::floor<std::chrono::days>(now);

        return std::chrono::sys_days{ticket_expiration_date} >= today && tourniquet_exists(tourniquet_id);
    }
    catch (...) {
        return false;
    }
}

bool SkiPass::TemporaryTicket::extend_ticket(extension_unit_t value) {
    try {
        auto ticket_expiration_date = TimeUtils::convert_string_to_date(balance_);
        auto ticket_new_expiration_date = std::chrono::sys_days{ticket_expiration_date} + std::chrono::days{value};
        balance_ = TimeUtils::convert_date_to_string(ticket_new_expiration_date);
        return true;
    }
    catch (...) {
        return false;
    }
}

SkiPass::AbstractTicket::balance_unit_t SkiPass::TemporaryTicket::get_balance() {
    return std::format("Expires at {} 00:00",balance_);
}

std::shared_ptr<SkiPass::AbstractTicket> SkiPass::TemporaryTicket::clone() const {
    auto new_ticket = std::make_shared<TemporaryTicket>(ticket_id_t_, full_name_, age_, gender_, ticket_type_, balance_);
    return new_ticket;
}

SkiPass::ExtendableTicket & SkiPass::TemporaryTicket::operator+=(const extension_unit_t &amount) {
    extend_ticket(amount);
    return *this;
}

SkiPass::TemporaryTicket::~TemporaryTicket() = default;
