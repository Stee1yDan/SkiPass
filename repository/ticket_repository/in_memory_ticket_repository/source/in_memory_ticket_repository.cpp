#include "in_memory_ticket_repository.hpp"
#include <ranges>
#include <stdexcept>
#include <format>

namespace SkiPass {


    InMemoryTicketRepository::ticket_id_t InMemoryTicketRepository::increment_ticket_id() {
        ticket_id_t_++;
        return ticket_id_t_;
    }

    std::shared_ptr<AbstractTicket> InMemoryTicketRepository::add_ticket(std::shared_ptr<AbstractTicket> ticket) {
        auto id = ticket_id_t_++;
        ticket->id = id;
        tickets_[id] = ticket;
        return tickets_[id];
    }

    std::shared_ptr<AbstractTicket> InMemoryTicketRepository::get_ticket(ticket_id_t id) {
        return tickets_[id];
    }

    std::vector<std::shared_ptr<AbstractTicket>> InMemoryTicketRepository::get_all() {
        auto value_view = std::views::values(tickets_);
        return std::vector<std::shared_ptr<AbstractTicket>>{value_view.begin(), value_view.end()};
    }
}
