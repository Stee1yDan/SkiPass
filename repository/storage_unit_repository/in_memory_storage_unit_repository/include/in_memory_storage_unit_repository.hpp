#pragma once

#include "abstract_storage_unit_repository.hpp"
#include "storage_unit.hpp"


namespace SkiPass {
    class StorageUnit;

    class InMemoryStorageUnitRepository : public IStorageUnitRepository {
    public:
        std::shared_ptr<StorageUnit> add_unit(std::shared_ptr<StorageUnit> unit) override;
        bool delete_unit(StorageUnit::unit_id_t id) override;
        std::optional<std::shared_ptr<StorageUnit>> get_unit(StorageUnit::unit_id_t id) const override;
        std::vector<std::shared_ptr<StorageUnit>> get_all() const override;

        std::optional<std::shared_ptr<StorageUnit>>
            get_unit_by_ticket(AbstractTicket::ticket_id_t ticket_id) const override;

        ~InMemoryStorageUnitRepository() override = default;

    private:
        std::unordered_map<StorageUnit::unit_id_t, std::shared_ptr<StorageUnit>> units_;
        std::unordered_map<AbstractTicket::ticket_id_t, std::shared_ptr<StorageUnit>> ticket_to_unit_;
        StorageUnit::unit_id_t next_id_ = 1;
    };

}
