#include "abstract_ticket.hpp"

namespace SkiPass {
    AbstractTicket::~AbstractTicket() = default;

    std::ostream & operator<<(std::ostream &os, AbstractTicket::TicketType ticket_type) {
        switch (ticket_type) {
            case AbstractTicket::TicketType::LIMITED:       return os << "LIMITED";
            case AbstractTicket::TicketType::UNLIMITED:     return os << "UNLIMITED";
            case AbstractTicket::TicketType::SERVICE:       return os << "SERVICE";
            case AbstractTicket::TicketType::TEMPORARY:     return os << "TEMPORARY";
            default:                        return os << "Unknown";
        }
    }


}
