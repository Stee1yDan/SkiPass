#pragma once

#include <memory>

#include <abstract_ticket.hpp>

namespace SkiPass {

    class IController {
    public:
        virtual ~IController() = default;

        virtual void run() = 0;
        virtual void on_create_ticket() = 0;
        virtual void on_delete_ticket() = 0;
        virtual void on_check_balance() = 0;
        virtual void on_show_ticket_info() = 0;
        virtual void on_pass() = 0;
    };

} // namespace banking