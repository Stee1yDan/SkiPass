#pragma once

#include <memory>

namespace SkiPass {

    class ITicket {
    public:

        using gender_t = std::string;

        using extension_unit_t = long long;

        using balance_unit_t = std::string;

        using ticket_id_t = unsigned int;

        virtual bool pass() = 0;
        virtual bool can_pass() = 0;

        [[nodiscard]] virtual bool extend_ticket(extension_unit_t value) = 0;

        [[nodiscard]] virtual balance_unit_t get_balance() = 0;

        [[nodiscard]] virtual balance_unit_t get_info() const = 0;

        [[nodiscard]] virtual std::shared_ptr<ITicket> clone() const = 0;

        virtual ~ITicket() = default;
    };

}