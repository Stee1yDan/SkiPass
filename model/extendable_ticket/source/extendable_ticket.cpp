#include "extendable_ticket.hpp"

namespace SkiPass {
    ExtendableTicket::~ExtendableTicket() = default;

    ExtendableTicket & ExtendableTicket::operator+=(const extension_unit_t &amount) {
        return *this;
    };

    ExtendableTicket::balance ExtendableTicket::get_balance() const {
        return this->balance_;
    }

    void ExtendableTicket::set_balance(const balance &balance) {
        this->balance_ = balance;
    }
}
