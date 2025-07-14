#include "ticket_service.hpp"

namespace SkiPass {
    TicketService::TicketService(std::shared_ptr<ITicketRepository> repository) {
        repository_ = repository;
    }

    std::optional<std::shared_ptr<ITicket>> TicketService::add_ticket(std::shared_ptr<ITicket> ticket) {
        repository_->add_ticket(ticket);
        return ticket;
    }
}
