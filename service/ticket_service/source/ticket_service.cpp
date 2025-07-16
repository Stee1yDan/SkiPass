#include "ticket_service.hpp"

namespace SkiPass {
    TicketService::TicketService(std::shared_ptr<ITicketRepository> repository) {
        repository_ = repository;
    }

    std::shared_ptr<AbstractTicket> TicketService::add_ticket(std::shared_ptr<AbstractTicket> ticket) {
        return repository_->add_ticket(ticket);
    }

    std::optional<std::shared_ptr<AbstractTicket>> TicketService::get_ticket(AbstractTicket::ticket_id_t id) {
        return repository_->get_ticket(id);
    }

    TicketService::TicketInfo TicketService::get_ticket_info_struct(std::shared_ptr<AbstractTicket> ticket) {
        TicketInfo ticket_info;
        ticket_info.full_name = ticket->full_name;
        ticket_info.age = ticket->age;
        ticket_info.gender = ticket->gender;
        ticket_info.ticket_id = ticket->id;
        ticket_info.balance = ticket->balance;
        ticket_info.ticket_id = ticket->id;
        return ticket_info;
    }
}
