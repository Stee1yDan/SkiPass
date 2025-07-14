#include <unordered_map>

#include "abstract_ticket_repository.hpp"

namespace SkiPass {
    class InMemoryTicketRepository : public ITicketRepository {
        public:
        using ticket_id_t = unsigned long long;
        InMemoryTicketRepository() = default;

        ~InMemoryTicketRepository() override = default;

        std::vector<std::shared_ptr<ITicket>> get_all() override;

        ticket_id_t add_ticket(std::shared_ptr<ITicket> account) override;

        ticket_id_t increment_ticket_id() override;

        std::unordered_map<ticket_id_t, std::shared_ptr<ITicket>> tickets_;

        ticket_id_t ticket_id_t_ = 0;
    };
}