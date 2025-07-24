#include "tourniquet_service.hpp"

namespace SkiPass {
    TourniquetService::pass_operation_status TourniquetService::pass_through_tourniquet(AbstractTicket::ticket_id_t id,
        unsigned tourniquet_id) const {
        auto ticket = ticket_repository_->get_ticket(id);

        if (!ticket.has_value()) {
            return pass_operation_status::no_such_ticket_found;
        }

        if (!ticket->get()->can_pass(tourniquet_id)) {
            auto ticket_type = ticket->get()->get_ticket_type();
            if (ticket_type == AbstractTicket::TicketType::LIMITED)
                return pass_operation_status::no_passes_left;

            if (ticket_type == AbstractTicket::TicketType::TEMPORARY)
                return pass_operation_status::ticket_expired;

            if (ticket_type == AbstractTicket::TicketType::SERVICE)
                return pass_operation_status::wrong_tourniquet;
        }

        ticket->get()->pass(tourniquet_id);

        return pass_operation_status::success;
    }

    TourniquetService::pass_operation_status TourniquetService::can_pass_through_tourniquet(
        AbstractTicket::ticket_id_t id, unsigned tourniquet_id) const {
        auto ticket = ticket_repository_->get_ticket(id);

        if (!ticket.has_value()) {
            return pass_operation_status::no_such_ticket_found;
        }

        if (!ticket->get()->can_pass(tourniquet_id)) {
            auto ticket_type = ticket->get()->get_ticket_type();
            if (ticket_type == AbstractTicket::TicketType::LIMITED)
                return pass_operation_status::no_passes_left;

            if (ticket_type == AbstractTicket::TicketType::TEMPORARY)
                return pass_operation_status::ticket_expired;

            if (ticket_type == AbstractTicket::TicketType::SERVICE)
                return pass_operation_status::wrong_tourniquet;
        }

        if (ticket->get()->can_pass(tourniquet_id)) return pass_operation_status::success;

        return pass_operation_status::operation_declined;
    }
}
