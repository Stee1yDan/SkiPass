#include "limited_ticket.hpp"

bool SkiPass::LimitedTicket::pass() {

}

bool SkiPass::LimitedTicket::can_pass() {
}

bool SkiPass::LimitedTicket::extend_ticket(extension_unit_t value) {
}

SkiPass::AbstractTicket::balance_unit_t SkiPass::LimitedTicket::get_balance() {
}

std::shared_ptr<SkiPass::AbstractTicket> SkiPass::LimitedTicket::clone() const {
}

SkiPass::LimitedTicket::~LimitedTicket() {
}
