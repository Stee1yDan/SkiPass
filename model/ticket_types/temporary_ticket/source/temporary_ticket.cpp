#include "temporary_ticket.hpp"

#include <chrono>

bool SkiPass::TemporaryTicket::pass() {
    return true;
}

bool SkiPass::TemporaryTicket::can_pass() {
    try {
        auto ticket_expiration_date = convert_string_to_date(balance);

        auto now = std::chrono::system_clock::now();
        auto today = std::chrono::floor<std::chrono::days>(now);

        return std::chrono::sys_days{ticket_expiration_date} >= today;
    }
    catch (...) {
        return false;
    }
}

bool SkiPass::TemporaryTicket::extend_ticket(extension_unit_t value) {
    try {
        auto ticket_expiration_date = convert_string_to_date(balance);
        auto ticket_new_expiration_date = std::chrono::sys_days{ticket_expiration_date} + std::chrono::days{value};
        balance = convert_date_to_string(ticket_new_expiration_date);
        return true;
    }
    catch (...) {
        return false;
    }
}

SkiPass::AbstractTicket::balance_unit_t SkiPass::TemporaryTicket::get_balance() {
    return std::format("Valid until {}",balance);
}

std::shared_ptr<SkiPass::AbstractTicket> SkiPass::TemporaryTicket::clone() const {
    auto new_ticket = std::make_shared<TemporaryTicket>(id, full_name, age, gender, ticket_type, balance);
    return new_ticket;
}

SkiPass::TemporaryTicket::~TemporaryTicket() {
}

std::string SkiPass::TemporaryTicket::convert_date_to_string(const std::chrono::year_month_day &date) {
    if (!date.ok()) {
        throw std::runtime_error("Invalid date");
    }

    return std::format("{}-{:02}-{:02}",
                      static_cast<int>(date.year()),
                      static_cast<unsigned>(date.month()),
                      static_cast<unsigned>(date.day()));
}

std::chrono::year_month_day SkiPass::TemporaryTicket::convert_string_to_date(const std::string &dateStr) {
    int year, month, day;
    char sep1, sep2;
    std::istringstream iss(dateStr);

    if (!(iss >> year >> sep1 >> month >> sep2 >> day) ||
        sep1 != '-' || sep2 != '-') {
        throw std::runtime_error("Invalid date format. Expected YYYY-MM-DD");
        }

    auto date = std::chrono::year{year}/month/day;
    if (!date.ok()) {
        throw std::runtime_error("Invalid calendar date");
    }

    return date;
}