#include "in_memory_ticket_repository.hpp"
#include <ranges>
#include <stdexcept>
#include <format>

namespace SkiPass {

    InMemoryTicketRepository::ticket_id_t InMemoryTicketRepository::increment_ticket_id() {
        ticket_id_t_++;
        return ticket_id_t_;
    }

    InMemoryTicketRepository::ticket_id_t InMemoryTicketRepository::add_ticket(std::shared_ptr<ITicket> ticket) {
        auto id = ticket_id_t_++;
        tickets_[ticket_id_t_] = ticket;
        return ticket_id_t_;
    }

    std::vector<std::shared_ptr<ITicket>> InMemoryTicketRepository::get_all() {
        auto value_view = std::views::values(tickets_);
        return std::vector<std::shared_ptr<ITicket>>{value_view.begin(), value_view.end()};
    }
}
