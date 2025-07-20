#include "cli_controller.hpp"

#include <format>

#include "unlimited_ticket.hpp"
#include "limited_ticket.hpp"
#include "service_ticket.hpp"
#include "temporary_ticket.hpp"

#include <iostream>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

#include "time_utils.hpp"


namespace SkiPass {

    CLIController::CLIController(std::shared_ptr<TicketService> service, std::shared_ptr<IView> view) {
        service_ = service;
        view_ = view;
    };

    CLIController::~CLIController() = default;

    const std::unordered_map<std::string, std::function<std::shared_ptr<AbstractTicket>(CLIController&)>> CLIController::ticket_types {
        std::pair{std::string{"unlimited"}, std::function<std::shared_ptr<AbstractTicket>(CLIController&)>{[](CLIController& obj){ return obj.create_unlimited(); }}},
        std::pair{std::string{"limited"}, std::function<std::shared_ptr<AbstractTicket>(CLIController&)>{[](CLIController& obj){ return obj.create_limited(); }}},
        std::pair{std::string{"service"}, std::function<std::shared_ptr<AbstractTicket>(CLIController&)>{[](CLIController& obj){ return obj.create_service(); }}},
        std::pair{std::string{"temporary"}, std::function<std::shared_ptr<AbstractTicket>(CLIController&)>{[](CLIController& obj){ return obj.create_temporary(); }}}
    };

    void CLIController::run() {
        while (true) {
            std::cout << "\nBanking System Menu:\n"
                      << "1. Create Ticket\n"
                      << "2. Show Balance\n"
                      << "3. Extend Ticket Balance\n"
                      << "4. Show Ticket Info\n"
                      << "5. Pass Through Tourniquet\n"
                      << "6. Can I Pass Through Tourniquet?\n"
                      << "7. Show All Tickets\n"
                      << "8. Delete Ticket\n"
                      << "9. Exit\n";

            int choice = get_input<int>("Enter choice: ");

            switch (choice) {
                case 1: on_create_ticket(); break;
                case 2: on_check_balance(); break;
                case 3: on_extend_ticket(); break;
                case 4: on_show_ticket_info(); break;
                case 5: on_pass(); break;
                case 6: on_can_pass(); break;
                case 7: on_show_all_tickets(); break;
                case 8: on_delete_ticket(); break;
                case 9: return;
                default: view_->show_error("Invalid choice"); break;
            }
        }
    }


    void CLIController::on_show_all_tickets() {
        view_->show_all_tickets(service_->get_repository());
    }

    void CLIController::on_show_ticket_info() {
        try {
            auto id = get_input<AbstractTicket::ticket_id_t>("Enter ticket id: ");
            auto ticket = service_->get_ticket(id);
            if (ticket.has_value()) {
                view_->show_ticket_info(SkiPass::TicketService::get_ticket_info_struct(ticket.value()));
            }
            else {
                view_->show_message("No such ticket found!");
            }

        } catch (const std::exception& e) {
            view_->show_error(std::string("Error: ") + e.what());
        }
    }


    void CLIController::on_create_ticket() {
        try {
            auto ticket_type = get_input<std::string>("Enter ticket type: ");

            for (char &c : ticket_type) {
                c = std::tolower(c);
            }

            std::shared_ptr<AbstractTicket> ticket = ticket_types.at(ticket_type)(*this);
            view_->show_ticket_info(SkiPass::TicketService::get_ticket_info_struct(ticket));
            auto saved_ticket = service_->add_ticket(ticket);
            view_->show_ticket_info(SkiPass::TicketService::get_ticket_info_struct(saved_ticket));
        } catch (const std::exception& e) {
            view_->show_error(std::string("Error: ") + e.what());
        }
    }

    void CLIController::on_delete_ticket() {
        try {
            auto id = get_input<AbstractTicket::ticket_id_t>("Enter id of ticket to delete: ");
            auto operation_status = service_->delete_ticket(id);
            if (operation_status == TicketService::ticket_management_operation_status::success) {
                view_->show_message(std::format("The ticket with id {} is deleted", id));
            }
            else if (operation_status == TicketService::ticket_management_operation_status::no_such_ticket_found) {
                view_->show_message(std::format("The ticket with is not found", id));
            }
        }
        catch (const std::exception& e) {
            view_->show_error(std::string("Error: ") + e.what());
        }

    }

    void CLIController::on_check_balance() {
        try {
            auto ticket_id = get_input<TicketService::ticket_id_t>("Enter ticket ID: ");
            auto ticket = service_->get_ticket(ticket_id);

            if (!ticket.has_value()) {
                view_->show_message("No such ticket found!");
            }

            std::shared_ptr<ExtendableTicket> extendedTicket = std::dynamic_pointer_cast<ExtendableTicket>(ticket.value());

            if (extendedTicket) {
                 view_->show_balance(extendedTicket);
            }
            else {
                view_->show_message("This type of ticket has no balance!");
            }
        }
        catch (const std::exception& e) {
            view_->show_error(std::string("Error: ") + e.what());
        }
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
            view_->show_error("Invalid input, please try again");
        }
    }

    void CLIController::on_pass() {
        try {
            auto ticket_id = get_input<TicketService::ticket_id_t>("Enter ticket ID: ");
            auto tourniquet_id = get_input<unsigned>("Enter tourniquet number: ");

            auto pass_result = service_->pass_through_tourniquet(ticket_id, tourniquet_id);

            switch (pass_result) {
                case TicketService::pass_operation_status::no_such_ticket_found:
                    view_->show_message(std::format("No ticket with id {} is found", ticket_id));
                    break;

                case TicketService::pass_operation_status::success:
                    view_->show_message("Passed!");
                    break;

                case TicketService::pass_operation_status::no_passes_left:
                    view_->show_message("No passes left! Please extend your ticket!");
                    break;

                case TicketService::pass_operation_status::ticket_expired:
                    view_->show_message("Ticket is expired! Please extend your ticket!");
                    break;

                case TicketService::pass_operation_status::wrong_tourniquet:
                    view_->show_message("Service ticket can't be used here!");
                    break;

                default:
                    view_->show_message("Unknown pass result status!");
                    break;
            }
        } catch (const std::exception& e) {
            view_->show_error(std::string("Error: ") + e.what());
        }
    }

    void CLIController::on_can_pass() {
        try {
            auto ticket_id = get_input<TicketService::ticket_id_t>("Enter ticket ID: ");
            auto tourniquet_id = get_input<unsigned>("Enter tourniquet number: ");

            auto pass_result = service_->can_pass_through_tourniquet(ticket_id, tourniquet_id);

            switch (pass_result) {
                case TicketService::pass_operation_status::no_such_ticket_found:
                    view_->show_message(std::format("No ticket with id {} is found", ticket_id));
                    break;

                case TicketService::pass_operation_status::success:
                    view_->show_message("You can pass!");
                    break;

                case TicketService::pass_operation_status::no_passes_left:
                    view_->show_message("No passes left! Please extend your ticket!");
                    break;

                case TicketService::pass_operation_status::ticket_expired:
                    view_->show_message("Ticket is expired! Please extend your ticket!");
                    break;

                case TicketService::pass_operation_status::wrong_tourniquet:
                    view_->show_message("Service ticket can't be used here!");
                    break;

                default:
                    view_->show_message("Unknown pass result status!");
                    break;
            }
        } catch (const std::exception& e) {
            view_->show_error(std::string("Error: ") + e.what());
        }
    }

    void CLIController::on_extend_ticket() {
        try {
            view_->show_extension_prices(SkiPass::TicketService::get_extension_prices());
            auto ticket_id = get_input<TicketService::ticket_id_t>("Enter ticket ID: ");
            auto funds = get_input<TicketService::ticket_id_t>("Enter funds: ");
            auto extension_units = get_input<TicketService::ticket_id_t>("Enter number of days/passes needed: ");

            auto res = service_->extend_ticket(ticket_id, extension_units, funds);

            switch (res.status) {
                case TicketService::balance_operation_status::invalid_ticket_type:
                    view_->show_message("Can't extend this type of ticket!");
                    break;

                case TicketService::balance_operation_status::not_enough_money:
                    view_->show_message("Not enough money for the purchase!");
                    break;

                case TicketService::balance_operation_status::invalid_extension_unit:
                    view_->show_message("Invalid value for the purchase!");
                    break;

                case TicketService::balance_operation_status::success:
                    view_->show_message("Ticket was extended successfully!");
                    view_->show_message(std::format("Your change: {} RUB", res.change));
                    break;

                default:
                    view_->show_message("Unknown extension result status!");
                    break;
            }
        } catch (const std::exception& e) {
            view_->show_error(std::string("Error: ") + e.what());
        }
    }


    std::shared_ptr<AbstractTicket> CLIController::create_unlimited() {
        auto name = get_input<std::string>("Enter your name: ");
        auto age = get_input<unsigned>("Enter your age: ");
        auto gender = get_input<AbstractTicket::gender_t>("Enter your gender: ");
        return std::make_shared<UnlimitedTicket>(0,name,age,gender,AbstractTicket::TicketType::UNLIMITED);
    }

    std::shared_ptr<AbstractTicket> CLIController::create_limited() {
        auto name = get_input<std::string>("Enter your name: ");
        auto age = get_input<unsigned>("Enter your age: ");
        auto gender = get_input<AbstractTicket::gender_t>("Enter your gender: ");
        AbstractTicket::balance_unit_t balance = "0";
        return std::make_shared<LimitedTicket>(0,name,age,gender,AbstractTicket::TicketType::LIMITED, balance);
    }

    std::shared_ptr<AbstractTicket> CLIController::create_service() {
        auto name = get_input<std::string>("Enter your name: ");
        auto age = get_input<unsigned>("Enter your age: ");
        auto gender = get_input<AbstractTicket::gender_t>("Enter your gender: ");
        return std::make_shared<ServiceTicket>(0,name,age,gender,AbstractTicket::TicketType::SERVICE);
    }

    std::shared_ptr<AbstractTicket> CLIController::create_temporary() {
        auto name = get_input<std::string>("Enter your name: ");
        auto age = get_input<unsigned>("Enter your age: ");
        auto gender = get_input<AbstractTicket::gender_t>("Enter your gender: ");

        auto balance = TimeUtils::convert_date_to_string(TimeUtils::get_current_date());
        return std::make_shared<TemporaryTicket>(0,name,age,gender,AbstractTicket::TicketType::TEMPORARY, balance);
    }
}
