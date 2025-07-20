#include "abstract_ticket.hpp"


namespace SkiPass {
    const std::unordered_map<unsigned, bool> AbstractTicket::service_tourniquet_registry {
        std::pair{0, false},
        std::pair{1, false},
        std::pair{2, false},
        std::pair{3, false},
        std::pair{4, false},
        std::pair{5, true}
    };


    AbstractTicket::AbstractTicket(ticket_id_t id, const std::string &string, unsigned age, const gender_t &gender,
        TicketType ticket) {
    }

    std::string AbstractTicket::ticket_type_to_string(AbstractTicket::TicketType type) {
        switch(type) {
            case AbstractTicket::TicketType::LIMITED:   return "LIMITED";
            case AbstractTicket::TicketType::UNLIMITED: return "UNLIMITED";
            case AbstractTicket::TicketType::SERVICE:   return "SERVICE";
            case AbstractTicket::TicketType::TEMPORARY: return "TEMPORARY";
            default:                                    return "UNKNOWN";
        }
    }

    std::ostream & operator<<(std::ostream &os, AbstractTicket::TicketType ticket_type) {
        return os << AbstractTicket::ticket_type_to_string(ticket_type);
    }

    bool AbstractTicket::tourniquet_exists(unsigned tourniquet_id) {
        return AbstractTicket::service_tourniquet_registry.contains(tourniquet_id);
    }

    bool AbstractTicket::is_service_tourniquet(unsigned tourniquet_id) {
        return AbstractTicket::service_tourniquet_registry.at(tourniquet_id);
    }
}
