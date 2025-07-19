#include "temporary_ticket.hpp"

#include <chrono>

bool SkiPass::TemporaryTicket::pass() {
    return true;
}

bool SkiPass::TemporaryTicket::can_pass() {
   auto today = std::chrono::system_clock::now();

}

bool SkiPass::TemporaryTicket::extend_ticket(extension_unit_t value) {
    try {
        int year, month, day;
        char sep;
        std::istringstream iss(balance);
        iss >> year >> sep >> month >> sep >> day;

        auto date = std::chrono::year{year}/month/day;
        auto new_date = std::chrono::sys_days{date} + std::chrono::days{value};
        auto ymd = std::chrono::year_month_day{new_date};

        balance = std::format("{}/{}/{}",
                                         static_cast<int>(ymd.year()),
                                         static_cast<unsigned>(ymd.month()),
                                         static_cast<unsigned>(ymd.day()));

        return true;
    }
    catch (...) {
        return false;
    }
}

SkiPass::AbstractTicket::balance_unit_t SkiPass::TemporaryTicket::get_balance() {
    return balance;
}

std::shared_ptr<SkiPass::AbstractTicket> SkiPass::TemporaryTicket::clone() const {
}

SkiPass::TemporaryTicket::~TemporaryTicket() {
}
