#include "abstract_ticket.hpp"

namespace SkiPass {
    AbstractTicket::~AbstractTicket() = default;

    std::ostream & operator<<(std::ostream &os, AbstractTicket::TicketType ticket_type) {
        switch (ticket_type) {
            case AbstractTicket::TicketType::LIMITED:       return os << "Limited";
            case AbstractTicket::TicketType::UNLIMITED:     return os << "Unlimited";
            case AbstractTicket::TicketType::SERVICE:       return os << "Service";
            case AbstractTicket::TicketType::TEMPORARY:     return os << "Temporary";
            default:                        return os << "Unknown";
        }
    }
}
