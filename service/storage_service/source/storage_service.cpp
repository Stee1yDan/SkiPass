#include "storage_service.hpp"

#include <utility>

namespace SkiPass {
    StorageService::StorageOperation StorageService::get_linked_storage_unit(AbstractTicket::ticket_id_t ticket_id) {
        auto storage_unit = storage_unit_repository_->get_unit_by_ticket(ticket_id);
        if (!storage_unit) {
            return StorageOperation(storage_management_operation_status::no_storage_unit_found, std::shared_ptr<StorageUnit>(nullptr));
        }

        if (storage_unit->get()->is_locked()) {
            return  StorageOperation(storage_management_operation_status::storage_unit_is_already_locked, storage_unit.value());;
        }

        storage_unit->get()->lock_storage_unit();

        return  StorageOperation(storage_management_operation_status::success, storage_unit.value());;
    }

    StorageService::StorageOperation StorageService::lock_storage_unit(AbstractTicket::ticket_id_t ticket_id) {
        auto storage_unit = storage_unit_repository_->get_unit_by_ticket(ticket_id);
        if (!storage_unit) {
            return StorageOperation(storage_management_operation_status::no_storage_unit_found, std::shared_ptr<StorageUnit>(nullptr));
        }

        if (storage_unit->get()->is_locked()) {
            return  StorageOperation(storage_management_operation_status::storage_unit_is_already_locked, storage_unit.value());;
        }

        storage_unit->get()->lock_storage_unit();

        return  StorageOperation(storage_management_operation_status::success, storage_unit.value());;
    }

    StorageService::StorageOperation StorageService::open_storage_unit(AbstractTicket::ticket_id_t ticket_id) {
        auto storage_unit = storage_unit_repository_->get_unit_by_ticket(ticket_id);
        if (!storage_unit) {
            return StorageOperation(storage_management_operation_status::no_storage_unit_found, std::shared_ptr<StorageUnit>(nullptr));
        }

        if (!storage_unit->get()->is_locked()) {
            return  StorageOperation(storage_management_operation_status::storage_unit_is_already_opened, storage_unit.value());;
        }

        storage_unit->get()->open_storage_unit();

        return  StorageOperation(storage_management_operation_status::success, storage_unit.value());;
    }

    std::shared_ptr<StorageUnit> StorageService::add_storage_unit(std::shared_ptr<StorageUnit> unit) {
        return storage_unit_repository_->add_unit(std::move(unit));
    }

    StorageService::StorageOperation StorageService::delete_storage_unit(StorageUnit::unit_id_t id) {
        auto storage_unit = storage_unit_repository_->get_unit(id);
        if (!storage_unit.has_value()) {
            return StorageOperation(storage_management_operation_status::no_storage_unit_found, nullptr);
        }
        storage_unit_repository_->delete_unit(id);
        return StorageOperation(storage_management_operation_status::success, storage_unit.value());;
    }

    std::optional<std::shared_ptr<StorageUnit>> StorageService::get_storage_unit_by_ticket(
        AbstractTicket::ticket_id_t ticket_id) const {
        return storage_unit_repository_->get_unit_by_ticket(ticket_id);
    }

    std::shared_ptr<IStorageUnitRepository> StorageService::get_storage_unit_repository() {
        return storage_unit_repository_;
    }
}
