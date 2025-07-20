#include "transferable_ticket.hpp"

namespace SkiPass {
    bool TransferableTicket::change_owner(std::string &new_owner) {
        full_name = new_owner;
        return true;
    }

    TransferableTicket::~TransferableTicket() = default;
}
