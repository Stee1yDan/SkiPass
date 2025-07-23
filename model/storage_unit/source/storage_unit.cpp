

#include "storage_unit.hpp"

namespace SkiPass {
    AbstractTicket::ticket_id_t StorageUnit::get_linked_ticket_id() const {
        return linked_ticket_id_;
    }

    StorageUnit::unit_id_t StorageUnit::get_storage_unit_id() const {
        return unit_id_t_;
    }

    bool StorageUnit::is_locked() const {
        return this->is_locked_;
    }

    void StorageUnit::lock_storage_unit() {
        this->is_locked_ = true;
    }

    void StorageUnit::open_storage_unit() {
        this->is_locked_ = false;
    }
}
