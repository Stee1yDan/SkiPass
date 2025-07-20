#pragma once
#include <abstract_ticket.hpp>
#include <map>

#include <vector>
#include <memory>
#include <optional>

namespace SkiPass {
    class ITicketRepository {
    public:

        using ticket_id_t = unsigned long long;
        using TicketKey = std::pair<AbstractTicket::TicketType, ticket_id_t>;

        virtual ticket_id_t increment_ticket_id() = 0;

        virtual std::vector<std::shared_ptr<AbstractTicket>> get_all() = 0;

        virtual std::shared_ptr<AbstractTicket> add_ticket(std::shared_ptr<AbstractTicket> ticket) = 0;

        virtual std::optional<std::shared_ptr<AbstractTicket>> get_ticket(ticket_id_t id) = 0;

        virtual bool delete_ticket(ticket_id_t id) = 0;

        ITicketRepository() = default;

        virtual ~ITicketRepository() = default;

        std::multimap<TicketKey, std::shared_ptr<AbstractTicket>> tickets_;
    };
}
