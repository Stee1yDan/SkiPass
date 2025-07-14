#include "cli_controller.hpp"
#include "unlimited_ticket.hpp"

#include <iostream>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>


namespace SkiPass {

    CLIController::CLIController(std::shared_ptr<TicketService> service) {
        service_ = service;
    };

    CLIController::~CLIController() = default;

    const std::unordered_map<std::string, std::function<std::shared_ptr<ITicket>(CLIController&)>> CLIController::ticket_types {
        std::pair{std::string{"unlimited"}, std::function<std::shared_ptr<ITicket>(CLIController&)>{[](CLIController& obj){ return obj.create_unlimited(); }}}
    };


    void CLIController::run() {
        while (true) {
            std::cout << "\nBanking System Menu:\n"
                      << "1. Create Ticket\n"
                      << "7. Exit\n";

            int choice = get_input<int>("Enter choice: ");

            switch (choice) {
                case 1: on_create_ticket(); break;
                case 7: return;
                //default: view_.show_error("Invalid choice"); break;
            }
        }
    }

    void CLIController::on_create_ticket() {
        try {
            auto ticket_type = get_input<std::string>("Enter account type: ");
            auto ticket = ticket_types.at(ticket_type)(*this);

            service_->add_ticket(ticket);

            //auto account = account_types.at(account_type)(*this);
            //auto account_info = bank_.open_new_account(account);
            //cards_.emplace(account_info.account_id, account_info.card);
            //view_.show_account_created(account_info);
        } catch (const std::exception& e) {
            //view_.show_error(std::string("Error: ") + e.what());
        }
    }

    void CLIController::on_close_ticket() {
    }

    void CLIController::on_check_balance() {
    }

    template<typename T>T CLIController::get_input(const std::string &prompt) {
        T value;
        while (true) {
            std::cout << prompt;
            std::string input;
            std::getline(std::cin, input);

            if (std::cin.bad()) {
                throw std::runtime_error("Broken input");
            }

            if (std::cin.eof()) {
                throw std::runtime_error("EOF");
            }

            std::stringstream ss(input);
            if (ss >> value) {
                return value;
            }
            //view_.show_error("Invalid input, please try again");
        }
    }

    std::shared_ptr<ITicket> CLIController::create_unlimited() {
        auto name = get_input<std::string>("Enter your name: ");
        auto age = get_input<unsigned>("Enter your age: ");
        auto gender = get_input<AbstractTicket::gender_t>("Enter your gender: ");
        return std::make_shared<UnlimitedTicket>(name,age,gender,AbstractTicket::TicketType::UNLIMITED);
    }
}
