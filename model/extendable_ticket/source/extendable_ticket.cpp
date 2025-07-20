#include "extendable_ticket.hpp"

namespace SkiPass {
    ExtendableTicket::~ExtendableTicket() = default;

    ExtendableTicket & ExtendableTicket::operator+=(const extension_unit_t &amount) {
        return *this;
    };
}
