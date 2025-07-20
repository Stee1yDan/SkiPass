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
        auto id = increment_ticket_id();
        ticket->id = id;
        tickets_.emplace(TicketKey{ticket->ticket_type, id}, ticket);
        id_to_ticket_.emplace(id, ticket);  // Maintain direct ID lookup
        return ticket;
    }

    bool InMemoryTicketRepository::delete_ticket(ticket_id_t id) {
        auto id_it = id_to_ticket_.find(id);
        if (id_it == id_to_ticket_.end()) {
            return false;
        }

        auto ticket = id_it->second;
        TicketKey key{ticket->ticket_type, id};

        auto range = tickets_.equal_range(key);
        for (auto it = range.first; it != range.second; ++it) {
            if (it->second->id == id) {
                tickets_.erase(it);
                break;
            }
        }
        id_to_ticket_.erase(id_it);

        return true;
    }

    std::optional<std::shared_ptr<AbstractTicket>> InMemoryTicketRepository::get_ticket(ticket_id_t id) {
        auto it = id_to_ticket_.find(id);
        if (it == id_to_ticket_.end()) {
            return std::nullopt;
        }
        return it->second;
    }

    std::vector<std::shared_ptr<AbstractTicket>> InMemoryTicketRepository::get_all() {
        std::vector<std::shared_ptr<AbstractTicket>> result;
        for (const auto& [key, ticket] : tickets_) {
            result.push_back(ticket);
        }
        return result;
    }

    std::ostream& operator<<(std::ostream& os, const ITicketRepository& repo) {
        os << std::format("{:<10} | {:<8} | {:<20} | {:<6} | {:<10}\n",
                         "ID", "Type", "Name", "Age", "Gender", "Balance");
        os << std::string(80, '-') << '\n';

        for (const auto& [key, ticket] : repo.tickets_) {
            os << std::format("{:<10} | {:<8} | {:<20} | {:<6} | {:<10}\n",
                             SkiPass::AbstractTicket::ticket_type_to_string(ticket->ticket_type),
                             ticket->id,
                             ticket->full_name,
                             ticket->age,
                             ticket->gender);
        }
        return os;
    }
}
