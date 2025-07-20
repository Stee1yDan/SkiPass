#include "cli_view.hpp"

#include <format>

#include "abstract_ticket.hpp"
#include "in_memory_ticket_repository.hpp"

#include <iostream>

namespace SkiPass {
    CLIView::~CLIView() = default;

    void CLIView::show_balance(std::shared_ptr<AbstractTicket> ticket) {
        std::cout << "Current balance: " << ticket->get_balance() << std::endl;
    }

    void CLIView::show_ticket_info(TicketService::TicketInfo ticket_info) {
        std::cout << std::endl;
        std::cout << "+-----Owner Info------" <<  std::endl;
        std::cout << "|Full Name: " << ticket_info.full_name << std::endl;
        std::cout << "|Gender: " << ticket_info.gender << std::endl;
        std::cout << "|Age: " << ticket_info.age << std::endl;
        std::cout << "+-----Ticket Info-----" <<  std::endl;
        std::cout << "|Ticket Id: " << ticket_info.ticket_id << std::endl;
        std::cout << "|Ticket Type: " << ticket_info.ticket_type << std::endl;
        std::cout << "|Balance: " << ticket_info.balance<< std::endl;
        std::cout << "+----------------------" <<  std::endl;
        std::cout << std::endl;
    }

    void CLIView::show_extension_prices(std::unordered_map<AbstractTicket::TicketType, unsigned> map) {
        std::cout << std::endl;
        std::cout << "Price of one pass for LIMITED ticket " << map.at(AbstractTicket::TicketType::LIMITED) <<  std::endl;
        std::cout << "Price of one day for TEMPORARY ticket " << map.at(AbstractTicket::TicketType::TEMPORARY) <<  std::endl;
        std::cout << std::endl;
    }

    void CLIView::show_message(const std::string& message) {
        std::cout << message << std::endl;
    }

    void CLIView::show_error(const std::string& error) {
        std::cerr << "Error: " << error << std::endl;
    }

    void CLIView::show_ticket_created(std::shared_ptr<AbstractTicket> ticket) {
        std::cout << "Ticket Created! Its id is: " << ticket->id << std::endl;
    }

    void CLIView::show_all_tickets(std::shared_ptr<ITicketRepository> repository) {
        if (auto repo = dynamic_cast<InMemoryTicketRepository*>(repository.get())) {
            std::cout << *repo << std::endl;
        } else {
            std::cout << "Unsupported repository type" << std::endl;
        }
    }
}
