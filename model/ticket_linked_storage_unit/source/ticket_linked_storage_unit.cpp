#include "ticket_linked_storage_unit.hpp"

namespace SkiPass {
    TicketLinkedStorageUnit::~TicketLinkedStorageUnit() = default;

    IStorageUnit::unit_id_t TicketLinkedStorageUnit::get_storage_unit_id() const {
        return storage_unit_id_;
    }

    AbstractTicket::ticket_id_t TicketLinkedStorageUnit::get_linked_ticket_id() const {
        return linked_ticket_id_;
    }

    void TicketLinkedStorageUnit::lock_storage_unit() {
        this->is_locked_ = true;
    }

    void TicketLinkedStorageUnit::open_storage_unit() {
        this->is_locked_ = false;
    }
}
