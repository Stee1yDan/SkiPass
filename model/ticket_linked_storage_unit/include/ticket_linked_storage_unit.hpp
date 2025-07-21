#pragma once

#include "abstract_ticket.hpp"
#include "../../storage_unit/include/storage_unit.hpp"

namespace SkiPass {
    class TicketLinkedStorageUnit : IStorageUnit {
    public:
        TicketLinkedStorageUnit(bool is_locked, IStorageUnit::unit_id_t storage_unit_id,
            const AbstractTicket::ticket_id_t &linked_ticket_id)
            : is_locked_(is_locked),
              storage_unit_id_(storage_unit_id),
              linked_ticket_id_(linked_ticket_id) {
        }

        ~TicketLinkedStorageUnit() override;

        [[nodiscard]] unit_id_t get_storage_unit_id() const override;

        AbstractTicket::ticket_id_t get_linked_ticket_id() const;

        void lock_storage_unit() override;

        void open_storage_unit() override;

    private:
        bool is_locked_ = true;
        IStorageUnit::unit_id_t storage_unit_id_;
        AbstractTicket::ticket_id_t linked_ticket_id_;
    };
}
