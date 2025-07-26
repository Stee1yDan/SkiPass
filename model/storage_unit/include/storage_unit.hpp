#pragma once
#include "abstract_ticket.hpp"

namespace SkiPass {
    class StorageUnit  {
    public:
        ~StorageUnit() = default;

        using unit_id_t = unsigned int;

        [[nodiscard]] AbstractTicket::ticket_id_t get_linked_ticket_id() const;

        [[nodiscard]] unit_id_t get_storage_unit_id() const;

        [[nodiscard]] bool is_locked() const;

        void lock_storage_unit();

        void open_storage_unit();

        StorageUnit(unit_id_t unit_id_t, AbstractTicket::ticket_id_t linked_ticket_id)
            : unit_id_t_(unit_id_t),
              linked_ticket_id_(linked_ticket_id) {
        }

    private:
        unit_id_t unit_id_t_;
        AbstractTicket::ticket_id_t linked_ticket_id_;
        bool is_locked_ = false;
    };
}
