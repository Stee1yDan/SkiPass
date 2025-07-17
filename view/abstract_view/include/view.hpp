#pragma once

#include <memory>
#include <string>

#include "abstract_ticket.hpp"
#include "ticket_service.hpp"

namespace SkiPass {
    class IView {
    public:
        virtual ~IView() = default;

        virtual void show_balance(std::shared_ptr<AbstractTicket> ticket) = 0;
        virtual void show_ticket_info(TicketService::TicketInfo ticket_info) = 0;
        virtual void show_message(const std::string& message) = 0;
        virtual void show_error(const std::string& error) = 0;
        virtual void show_ticket_created(std::shared_ptr<AbstractTicket> ticket) = 0;
    };

} // namespace banking