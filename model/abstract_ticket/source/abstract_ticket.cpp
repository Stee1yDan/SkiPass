#include "abstract_ticket.hpp"


namespace SkiPass {
    AbstractTicket::~AbstractTicket() = default;

    const std::unordered_map<unsigned, bool> AbstractTicket::service_tourniquet_registry {
        std::pair{0, false},
        std::pair{1, false},
        std::pair{2, false},
        std::pair{3, false},
        std::pair{4, false},
        std::pair{5, true}
    };

    std::ostream & operator<<(std::ostream &os, AbstractTicket::TicketType ticket_type) {
        switch (ticket_type) {
            case AbstractTicket::TicketType::LIMITED:       return os << "LIMITED";
            case AbstractTicket::TicketType::UNLIMITED:     return os << "UNLIMITED";
            case AbstractTicket::TicketType::SERVICE:       return os << "SERVICE";
            case AbstractTicket::TicketType::TEMPORARY:     return os << "TEMPORARY";
            default:                        return os << "Unknown";
        }
    }

    AbstractTicket::AbstractTicket(ticket_id_t id, const std::string &string, unsigned age, const gender_t &gender,
        TicketType ticket) {
    }

    bool AbstractTicket::tourniquet_exists(unsigned tourniquet_id) {
        return AbstractTicket::service_tourniquet_registry.contains(tourniquet_id);
    }

    bool AbstractTicket::is_service_tourniquet(unsigned tourniquet_id) {
        return AbstractTicket::service_tourniquet_registry.at(tourniquet_id);
    }
}
