#pragma once

#include <vector>
#include <memory>

namespace SkiPass {
    class ITicketRepository {
    public:

        using ticket_id_t = unsigned long long;

        virtual ticket_id_t increment_ticket_id() = 0;

        ITicketRepository() = default;

        virtual ~ITicketRepository() = default;
    };
}