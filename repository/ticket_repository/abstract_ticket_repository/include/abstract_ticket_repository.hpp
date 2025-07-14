#pragma once
#include <ticket.hpp>

#include <vector>
#include <memory>

namespace SkiPass {
    class ITicketRepository {
    public:

        using ticket_id_t = unsigned long long;

        virtual ticket_id_t increment_ticket_id() = 0;

        virtual std::vector<std::shared_ptr<ITicket>> get_all() = 0;

        virtual ticket_id_t add_ticket(std::shared_ptr<ITicket> account) = 0;

        ITicketRepository() = default;

        virtual ~ITicketRepository() = default;
    };
}