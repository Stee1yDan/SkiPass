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

    CLIController::~CLIController() = default;

    const std::unordered_map<std::string, std::function<std::shared_ptr<AbstractTicket>(CLIController&)>> CLIController::ticket_types {
        std::pair{std::string{"unlimited"}, std::function<std::shared_ptr<AbstractTicket>(CLIController&)>{[](CLIController& obj){ return obj.create_unlimited(); }}},
        std::pair{std::string{"limited"}, std::function<std::shared_ptr<AbstractTicket>(CLIController&)>{[](CLIController& obj){ return obj.create_limited(); }}},
        std::pair{std::string{"service"}, std::function<std::shared_ptr<AbstractTicket>(CLIController&)>{[](CLIController& obj){ return obj.create_service(); }}},
        std::pair{std::string{"temporary"}, std::function<std::shared_ptr<AbstractTicket>(CLIController&)>{[](CLIController& obj){ return obj.create_temporary(); }}}
    };

    void CLIController::run() {
        while (true) {
            std::cout << "\nSkiPass System Menu:\n"
                      << "1. Create Ticket\n"
                      << "2. Show Balance\n"
                      << "3. Extend Ticket\n"
                      << "4. Change Ticket Owner\n"
                      << "5. Show Ticket Info\n"
                      << "6. Pass Through Tourniquet\n"
                      << "7. Can I Pass Through Tourniquet?\n"
                      << "8. Show All Tickets\n"
                      << "9. Show Storage Unit\n"
                      << "A. Open Storage Unit\n"
                      << "B. Close Storage Unit\n"
                      << "C. Show All Storage Units\n"
                      << "D. Delete Ticket\n"
                      << "E. Exit\n";

            int choice = get_input<char>("Enter choice: ");

            switch (choice) {
                case '1': on_create_ticket(); break;
                case '2': on_check_balance(); break;
                case '3': on_extend_ticket(); break;
                case '4': on_change_owner(); break;
                case '5': on_show_ticket_info(); break;
                case '6': on_pass(); break;
                case '7': on_can_pass(); break;
                case '8': on_show_all_tickets(); break;
                case '9': on_show_linked_storage_unit(); break;
                case 'A': on_open_storage_unit(); break;
                case 'B': on_lock_storage_unit(); break;
                case 'C': on_show_all_storage_units(); break;
                case 'D': on_delete_ticket(); break;
                case 'E': return;
                default: view_->show_error("Invalid choice"); break;
            }
        }
    }


    void CLIController::on_show_all_tickets() {
        view_->show_all_tickets(ticket_service_->get_ticket_repository());
    }

    void CLIController::on_show_all_storage_units() {
        view_->show_all_storage_units(storage_service_->get_storage_unit_repository());
    }

    void CLIController::on_show_ticket_info() {
        try {
            auto id = get_input<AbstractTicket::ticket_id_t>("Enter ticket id: ");
            auto ticket = ticket_service_->get_ticket(id);
            if (ticket.has_value()) {
                view_->show_ticket_info(ticket.value());
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
            auto saved_ticket = ticket_service_->add_ticket(ticket);

            if (saved_ticket->get_ticket_type() != AbstractTicket::TicketType::SERVICE) {
                auto storage_unit = std::make_shared<StorageUnit>(0, saved_ticket->get_id());
                auto saved_storage_unit = storage_service_->add_storage_unit(storage_unit);
            }

            view_->show_ticket_info(saved_ticket);
        } catch (const std::exception& e) {
            view_->show_error(std::string("Error: ") + e.what());
        }
    }

    void CLIController::on_delete_ticket() {
        try {
            auto id = get_input<AbstractTicket::ticket_id_t>("Enter id of ticket to delete: ");
            auto operation_status = ticket_service_->delete_ticket(id);

            if (operation_status == TicketService::ticket_management_operation_status::no_such_ticket_found) {
                view_->show_message(std::format("The ticket with is not found", id));
            }

            auto storage_operation = storage_service_->get_linked_storage_unit(id);

            storage_service_->delete_storage_unit(storage_operation.unit->get_storage_unit_id());

            if (storage_operation.status == StorageService::storage_management_operation_status::no_storage_unit_found) {
                view_->show_message(std::format("The storage unit with id {} is deleted", storage_operation.unit->get_storage_unit_id()));
            }

            if (operation_status == TicketService::ticket_management_operation_status::success) {
                view_->show_message(std::format("The ticket with id {} is deleted", id));
            }

        }
        catch (const std::exception& e) {
            view_->show_error(std::string("Error: ") + e.what());
        }

    }

    void CLIController::on_check_balance() {
        try {
            auto ticket_id = get_input<TicketService::ticket_id_t>("Enter ticket ID: ");
            auto ticket = ticket_service_->get_ticket(ticket_id);

            if (!ticket.has_value()) {
                view_->show_message("No such ticket found!");
                return;
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

    void CLIController::on_show_linked_storage_unit() {
        try {
            auto ticket_id = get_input<TicketService::ticket_id_t>("Enter ticket ID: ");
            auto operation_status = storage_service_->get_linked_storage_unit(ticket_id);

            if (operation_status.status == StorageService::storage_management_operation_status::no_storage_unit_found) {
                view_->show_message(std::format("No storage for ticket with id {} is found!", ticket_id));
            }
            else if (operation_status.status == StorageService::storage_management_operation_status::success) {
                view_->show_storage_unit(operation_status.unit);
            }
        } catch (const std::exception& e) {
            view_->show_error(std::string("Error: ") + e.what());
        }
    }

    void CLIController::on_open_storage_unit() {
        try {
            auto ticket_id = get_input<TicketService::ticket_id_t>("Enter ticket ID: ");
            auto operation_status = storage_service_->open_storage_unit(ticket_id);

            if (operation_status.status == StorageService::storage_management_operation_status::no_storage_unit_found) {
                view_->show_message(std::format("No storage for ticket with id {} is found!", ticket_id));
            }
            if (operation_status.status == StorageService::storage_management_operation_status::storage_unit_is_already_opened) {
                view_->show_message("The storage unit is opened already!");
            }
            else if (operation_status.status == StorageService::storage_management_operation_status::success) {
                view_->show_message("The storage unit was opened successfully!");
                view_->show_storage_unit(operation_status.unit);
            }

        } catch (const std::exception& e) {
            view_->show_error(std::string("Error: ") + e.what());
        }
    }

    void CLIController::on_lock_storage_unit() {
        try {
            auto ticket_id = get_input<TicketService::ticket_id_t>("Enter ticket ID: ");
            auto operation_status = storage_service_->lock_storage_unit(ticket_id);

            if (operation_status.status == StorageService::storage_management_operation_status::no_storage_unit_found) {
                view_->show_message(std::format("No storage for ticket with id {} is found!", ticket_id));
            }
            if (operation_status.status == StorageService::storage_management_operation_status::storage_unit_is_already_locked) {
                view_->show_message("The storage unit is locked already!");
            }
            else if (operation_status.status == StorageService::storage_management_operation_status::success) {
                view_->show_message("The storage unit was closed successfully!");
                view_->show_storage_unit(operation_status.unit);
            }

        } catch (const std::exception& e) {
            view_->show_error(std::string("Error: ") + e.what());
        }
    }

    void CLIController::on_pass() {
        try {
            auto ticket_id = get_input<TicketService::ticket_id_t>("Enter ticket ID: ");
            auto tourniquet_id = get_input<unsigned>("Enter tourniquet  (1-5): ");

            auto pass_result = tourniquet_service_->pass_through_tourniquet(ticket_id, tourniquet_id);

            switch (pass_result) {
                case TourniquetService::pass_operation_status::no_such_ticket_found:
                    view_->show_message(std::format("No ticket with id {} is found", ticket_id));
                    break;

                case TourniquetService::pass_operation_status::success:
                    view_->show_message("Passed!");
                    break;

                case TourniquetService::pass_operation_status::no_passes_left:
                    view_->show_message("No passes left! Please extend your ticket!");
                    break;

                case TourniquetService::pass_operation_status::ticket_expired:
                    view_->show_message("Ticket is expired! Please extend your ticket!");
                    break;

                case TourniquetService::pass_operation_status::wrong_tourniquet:
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

            auto pass_result = tourniquet_service_->can_pass_through_tourniquet(ticket_id, tourniquet_id);

            switch (pass_result) {
                case TourniquetService::pass_operation_status::no_such_ticket_found:
                    view_->show_message(std::format("No ticket with id {} is found", ticket_id));
                    break;

                case TourniquetService::pass_operation_status::success:
                    view_->show_message("You can pass!");
                    break;

                case TourniquetService::pass_operation_status::no_passes_left:
                    view_->show_message("No passes left! Please extend your ticket!");
                    break;

                case TourniquetService::pass_operation_status::ticket_expired:
                    view_->show_message("Ticket is expired! Please extend your ticket!");
                    break;

                case TourniquetService::pass_operation_status::wrong_tourniquet:
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

            auto res = ticket_service_->extend_ticket(ticket_id, extension_units, funds);

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

                case TicketService::balance_operation_status::no_such_ticket_found:
                    view_->show_message("No such ticket found!");
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

    void CLIController::on_change_owner() {
        try {
            auto ticket_id = get_input<TicketService::ticket_id_t>("Enter ticket ID: ");
            auto funds = get_input<std::string>("Enter new owner name: ");

            auto res = ticket_service_->change_owner(ticket_id, funds);

            switch (res) {
                case TicketService::ticket_management_operation_status::no_such_ticket_found:
                    view_->show_message("No such ticket found!");
                    break;

                case TicketService::ticket_management_operation_status::wrong_type_of_ticket:
                    view_->show_message("Can't change owner for this type of ticket");
                    break;

                case TicketService::ticket_management_operation_status::success:
                    view_->show_message("Owner changed successfully!");
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
        auto gender = get_input<AbstractTicket::gender>("Enter your gender: ");
        return std::make_shared<UnlimitedTicket>(0,name,age,gender,AbstractTicket::TicketType::UNLIMITED);
    }

    std::shared_ptr<AbstractTicket> CLIController::create_limited() {
        auto name = get_input<std::string>("Enter your name: ");
        auto age = get_input<unsigned>("Enter your age: ");
        auto gender = get_input<AbstractTicket::gender>("Enter your gender: ");
        AbstractTicket::balance_unit_t balance = "0";
        return std::make_shared<LimitedTicket>(0,name,age,gender,AbstractTicket::TicketType::LIMITED, balance);
    }

    std::shared_ptr<AbstractTicket> CLIController::create_service() {
        auto name = get_input<std::string>("Enter your name: ");
        auto age = get_input<unsigned>("Enter your age: ");
        auto gender = get_input<AbstractTicket::gender>("Enter your gender: ");
        return std::make_shared<ServiceTicket>(0,name,age,gender,AbstractTicket::TicketType::SERVICE);
    }

    std::shared_ptr<AbstractTicket> CLIController::create_temporary() {
        auto name = get_input<std::string>("Enter your name: ");
        auto age = get_input<unsigned>("Enter your age: ");
        auto gender = get_input<AbstractTicket::gender>("Enter your gender: ");

        auto balance = TimeUtils::convert_date_to_string(TimeUtils::get_current_date());
        return std::make_shared<TemporaryTicket>(0,name,age,gender,AbstractTicket::TicketType::TEMPORARY, balance);
    }
}
