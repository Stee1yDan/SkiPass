#include "ticket_service.hpp"

namespace SkiPass {
    TicketService::TicketService(std::shared_ptr<ITicketRepository> repository) {
        repository_ = repository;
    }

    std::optional<std::shared_ptr<ITicket>> TicketService::add_ticket(std::shared_ptr<ITicket> ticket) {
        repository_->add_ticket(ticket);
        return ticket;
    }


    std::optional<std::shared_ptr<ITicket>> TicketService::get_ticket(AbstractTicket::ticket_id_t id) {
        return repository_->get_ticket(id);
    }
}
