#pragma once

#include <chrono>
#include <functional>
#include <unordered_map>

#include "controller.hpp"
#include "view.hpp"
#include "abstract_ticket.hpp"
#include "ticket_service.hpp"


namespace SkiPass {

    class CLIController : public IController {
    public:
        CLIController(std::shared_ptr<TicketService> service, std::shared_ptr<IView> view);

        ~CLIController() override;


        void run() override;

        void on_create_ticket() override;

        void on_delete_ticket() override;

        void on_show_ticket_info() override;

        void on_show_linked_storage_unit() override;

        void on_open_storage_unit() override;

        void on_lock_storage_unit() override;

        void on_check_balance() override;

        void on_extend_ticket() override;

        void on_show_all_tickets() override;

        void on_change_owner() override;

        void on_can_pass() override;

        void on_pass() override;

        void on_show_all_storage_units() override;

    private:
        template<typename T>
        T get_input(const std::string& prompt);   
    
        std::shared_ptr<AbstractTicket> create_unlimited();
        std::shared_ptr<AbstractTicket> create_limited();
        std::shared_ptr<AbstractTicket> create_service();
        std::shared_ptr<AbstractTicket> create_temporary();

        static const std::unordered_map<std::string, std::function<std::shared_ptr<AbstractTicket>(CLIController&)>> ticket_types;

        std::shared_ptr<TicketService> service_;
        std::shared_ptr<IView> view_;
    };
}
