#pragma once

#include "view.hpp"

namespace SkiPass {

    class CLIView : public IView{
    public:

        ~CLIView() override;

        void show_balance(std::shared_ptr<ITicket> ticket) override;

        void show_account_info(TicketService::TicketInfo ticket_info) override;

        void show_message(const std::string &message) override;

        void show_error(const std::string &error) override;

        void show_ticket_created(std::shared_ptr<ITicket> ticket) override;
    };

}
