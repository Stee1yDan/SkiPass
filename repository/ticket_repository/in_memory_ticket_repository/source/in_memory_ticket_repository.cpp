#include "in_memory_ticket_repository.hpp"

namespace SkiPass {

    InMemoryTicketRepository::ticket_id_t InMemoryTicketRepository::increment_ticket_id() {
        ticket_id_t_++;
        return ticket_id_t_;
    }
}
