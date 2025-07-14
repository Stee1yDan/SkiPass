#pragma once

#include <functional>
#include <unordered_map>

#include "controller.hpp"
#include "ticket.hpp"
#include "abstract_ticket.hpp"
#include "ticket_service.hpp"


namespace SkiPass {

    class CLIController : public IController {
    public:
        CLIController(std::shared_ptr<TicketService> service);

        ~CLIController() override;

        void run() override;

        void on_create_ticket() override;

        void on_close_ticket() override;

        void on_check_balance() override;

    private:
        template<typename T>
        T get_input(const std::string& prompt);   
    
        std::shared_ptr<ITicket> create_unlimited();

        static const std::unordered_map<std::string, std::function<std::shared_ptr<ITicket>(CLIController&)>> ticket_types;

        std::shared_ptr<TicketService> service_;

    };
}
