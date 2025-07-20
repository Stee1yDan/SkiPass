#include "temporary_ticket.hpp"
#include "time_utils.hpp"

#include <chrono>

bool SkiPass::TemporaryTicket::pass(unsigned tourniquet_id) {
    return tourniquet_exists(tourniquet_id);
}

bool SkiPass::TemporaryTicket::can_pass(unsigned tourniquet_id) {
    try {
        auto ticket_expiration_date = TimeUtils::convert_string_to_date(balance);

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
        auto ticket_expiration_date = TimeUtils::convert_string_to_date(balance);
        auto ticket_new_expiration_date = std::chrono::sys_days{ticket_expiration_date} + std::chrono::days{value};
        balance = TimeUtils::convert_date_to_string(ticket_new_expiration_date);
        return true;
    }
    catch (...) {
        return false;
    }
}

SkiPass::AbstractTicket::balance_unit_t SkiPass::TemporaryTicket::get_balance() {
    return std::format("Valid until {} 00:00",balance);
}

std::shared_ptr<SkiPass::AbstractTicket> SkiPass::TemporaryTicket::clone() const {
    auto new_ticket = std::make_shared<TemporaryTicket>(id, full_name, age, gender, ticket_type, balance);
    return new_ticket;
}

SkiPass::TemporaryTicket::~TemporaryTicket() = default;