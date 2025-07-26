#include "extendable_ticket.hpp"

namespace SkiPass {
    ExtendableTicket::~ExtendableTicket() = default;

    ExtendableTicket & ExtendableTicket::operator+=(const extension_unit_t &amount) {
        return *this;
    };

    ExtendableTicket::balance_unit_t ExtendableTicket::get_balance() const {
        return this->balance_;
    }
}
