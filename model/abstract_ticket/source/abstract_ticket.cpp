#include "abstract_ticket.hpp"

namespace SkiPass {
    AbstractTicket::~AbstractTicket() = default;

    std::ostream & AbstractTicket::operator<<(std::ostream &os, AbstractTicket::TicketType ticket_type) const {
        switch (ticket_type) {
            case TicketType::LIMITED:       return os << "Limited";
            case TicketType::UNLIMITED:     return os << "Unlimited";
            case TicketType::SERVICE:       return os << "Service";
            case TicketType::TEMPORARY:     return os << "Temporary";
            default:                        return os << "Unknown";
        }
    }
}
