#include <unordered_map>

#include "abstract_ticket_repository.hpp"
#include <abstract_ticket.hpp>

namespace SkiPass {
    class InMemoryTicketRepository : public ITicketRepository {
        public:
        using ticket_id_t = unsigned long long;
        InMemoryTicketRepository() = default;

        ~InMemoryTicketRepository() override = default;

        std::vector<std::shared_ptr<AbstractTicket>> get_all() override;

        std::shared_ptr<AbstractTicket> add_ticket(std::shared_ptr<AbstractTicket> account) override;

        bool delete_ticket(ticket_id_t id) override;

        std::optional<std::shared_ptr<AbstractTicket>> get_ticket(ticket_id_t id) override;

        ticket_id_t increment_ticket_id() override;

        std::unordered_map<ticket_id_t, std::shared_ptr<AbstractTicket>> tickets_;

        ticket_id_t ticket_id_t_ = 0;
    };
}