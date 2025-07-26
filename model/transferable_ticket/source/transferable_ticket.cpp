#include "transferable_ticket.hpp"

namespace SkiPass {
    bool TransferableTicket::change_owner(const std::string &new_owner) {
        this->full_name_ = new_owner;
        return true;
    }

    void TransferableTicket::operator()(const std::string &new_owner) {
        this->full_name_ = new_owner;
    }

    TransferableTicket::~TransferableTicket() = default;
}
