#include "abstract_storage_unit_repository.hpp"
#include "storage_unit.hpp"


namespace SkiPass {
    class StorageService {
        public:
        explicit StorageService(const std::shared_ptr<IStorageUnitRepository> &storage_unit_repository)
            : storage_unit_repository_(storage_unit_repository) {
        }

        ~StorageService() = default;


        enum class storage_management_operation_status {
            success,
            no_such_ticket_found,
            no_storage_unit_found,
            storage_unit_is_already_locked,
            storage_unit_is_already_opened,
            operation_declined
        };

        struct StorageOperation {
            storage_management_operation_status status;
            std::shared_ptr<StorageUnit> unit;
        };

        [[nodiscard]] StorageOperation get_linked_storage_unit(AbstractTicket::ticket_id_t ticket);
        [[nodiscard]] StorageOperation lock_storage_unit(AbstractTicket::ticket_id_t ticket);
        [[nodiscard]] StorageOperation open_storage_unit(AbstractTicket::ticket_id_t ticket);
        [[nodiscard]] std::shared_ptr<StorageUnit> add_storage_unit(std::shared_ptr<StorageUnit> unit);
        [[nodiscard]] StorageService::StorageOperation delete_storage_unit(StorageUnit::unit_id_t id);
        [[nodiscard]] std::optional<std::shared_ptr<StorageUnit>>get_storage_unit_by_ticket(AbstractTicket::ticket_id_t ticket_id) const;
        [[nodiscard]] std::shared_ptr<IStorageUnitRepository> get_storage_unit_repository();

        private:
            std::shared_ptr<IStorageUnitRepository> storage_unit_repository_;

        StorageService(const StorageService &other)
            : storage_unit_repository_(other.storage_unit_repository_) {
        }

        StorageService(StorageService &&other) noexcept
            : storage_unit_repository_(std::move(other.storage_unit_repository_)) {
        }

        StorageService & operator=(const StorageService &other) {
            if (this == &other)
                return *this;
            storage_unit_repository_ = other.storage_unit_repository_;
            return *this;
        }

        StorageService & operator=(StorageService &&other) noexcept {
            if (this == &other)
                return *this;
            storage_unit_repository_ = std::move(other.storage_unit_repository_);
            return *this;
        }
    };
}
