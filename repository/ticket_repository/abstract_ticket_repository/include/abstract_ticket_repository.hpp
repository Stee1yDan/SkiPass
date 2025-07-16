#pragma once
#include <ticket.hpp>
#include <abstract_ticket.hpp>

#include <vector>
#include <memory>

namespace SkiPass {
    class ITicketRepository {
    public:

        using ticket_id_t = unsigned long long;

        virtual ticket_id_t increment_ticket_id() = 0;

        virtual std::vector<std::shared_ptr<AbstractTicket>> get_all() = 0;

        virtual std::shared_ptr<AbstractTicket> add_ticket(std::shared_ptr<AbstractTicket> ticket) = 0;

        virtual std::shared_ptr<AbstractTicket> get_ticket(ticket_id_t id) = 0;

        ITicketRepository() = default;

        virtual ~ITicketRepository() = default;
    };
}