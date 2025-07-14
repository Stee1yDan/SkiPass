#include "abstract_ticket_repository.hpp"

namespace SkiPass {
    class InMemoryTicketRepository : public ITicketRepository {
        public:
        using ticket_id_t = unsigned long long;
        InMemoryTicketRepository() = default;

        ~InMemoryTicketRepository() override = default;

        ticket_id_t increment_ticket_id() override;

        ticket_id_t ticket_id_t_ = 0;
    };
}