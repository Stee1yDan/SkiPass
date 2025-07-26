#include "cli_view.hpp"

#include <format>

#include "abstract_ticket.hpp"
#include "extendable_ticket.hpp"
#include "in_memory_ticket_repository.hpp"

#include <iostream>

#include "../../../repository/storage_unit_repository/in_memory_storage_unit_repository/include/in_memory_storage_unit_repository.hpp"


namespace SkiPass {
    CLIView::~CLIView() = default;

    void CLIView::show_balance(std::shared_ptr<ExtendableTicket> ticket) {
        std::cout << "Current balance: " << ticket->get_balance() << std::endl;
    }

    void CLIView::show_ticket_info(std::shared_ptr<AbstractTicket> ticket) {
        std::cout << std::endl;
        std::cout << "+-----Owner Info------" <<  std::endl;
        std::cout << "|Full Name: " << ticket->get_full_name() << std::endl;
        std::cout << "|Gender: " << ticket->get_gender() << std::endl;
        std::cout << "|Age: " << ticket->get_age() << std::endl;
        std::cout << "+-----Ticket Info-----" <<  std::endl;
        std::cout << "|Ticket Id: " << ticket->get_id() << std::endl;
        std::cout << "|Ticket Type: " << ticket->get_ticket_type() << std::endl;
        std::cout << "+----------------------" <<  std::endl;
        std::cout << std::endl;
    }

    void CLIView::show_extension_prices(std::unordered_map<AbstractTicket::TicketType, unsigned> map) {
        std::cout << std::endl;
        std::cout << "Price of one pass for LIMITED ticket: \t" << map.at(AbstractTicket::TicketType::LIMITED) <<  std::endl;
        std::cout << "Price of one day for TEMPORARY ticket: \t " << map.at(AbstractTicket::TicketType::TEMPORARY) <<  std::endl;
        std::cout << std::endl;
    }

    void CLIView::show_message(const std::string& message) {
        std::cout << message << std::endl;
    }

    void CLIView::show_error(const std::string& error) {
        std::cerr << "Error: " << error << std::endl;
    }

    void CLIView::show_storage_unit(std::shared_ptr<StorageUnit> unit) {
        std::cout << "+-----Storage Info------" <<  std::endl;
        std::cout << "|Storage unit id: " << unit->get_storage_unit_id() << std::endl;
        std::cout << "|Linked ticket id: " << unit->get_linked_ticket_id() << std::endl;
        std::cout << "|Status: " << (unit->is_locked() ? "Locked" : "Open") << std::endl;
        std::cout << "+-----------------------" <<  std::endl;
    }

    void CLIView::show_all_storage_units(std::shared_ptr<IStorageUnitRepository> repository) {
        if (auto repo = dynamic_cast<InMemoryStorageUnitRepository*>(repository.get())) {
            std::cout << *repo << std::endl;
        } else {
            std::cout << "Unsupported repository type" << std::endl;
        }
    }

    void CLIView::show_ticket_created(std::shared_ptr<AbstractTicket> ticket) {
        std::cout << "Ticket Created! Its id is: " << ticket->get_id() << std::endl;
    }

    void CLIView::show_all_tickets(std::shared_ptr<ITicketRepository> repository) {
        if (auto repo = dynamic_cast<InMemoryTicketRepository*>(repository.get())) {
            std::cout << *repo << std::endl;
        } else {
            std::cout << "Unsupported repository type" << std::endl;
        }
    }
}
