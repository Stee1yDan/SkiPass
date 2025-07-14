#pragma once

#include <memory>

namespace SkiPass {

    class IController {
    public:
        virtual ~IController() = default;

        virtual void run() = 0;
        virtual void on_create_ticket() = 0;
        virtual void on_close_ticket() = 0;
        virtual void on_check_balance() = 0;
    };

} // namespace banking