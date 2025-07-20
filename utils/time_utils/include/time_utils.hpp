#pragma once

#include <chrono>

namespace SkiPass {
    class TimeUtils {
    public:
        static std::string convert_date_to_string(const std::chrono::year_month_day& date);
        static std::chrono::year_month_day convert_string_to_date(const std::string& dateStr);
        static std::chrono::year_month_day get_current_date();
    };
}
