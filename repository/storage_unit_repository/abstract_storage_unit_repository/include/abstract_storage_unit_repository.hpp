#pragma once
#include <memory>
#include <optional>
#include <vector>

#include <abstract_ticket.hpp>
#include <storage_unit.hpp>

namespace SkiPass {

    class IStorageUnitRepository {
    public:
        virtual ~IStorageUnitRepository() = default;

        virtual std::shared_ptr<StorageUnit> add_unit(std::shared_ptr<StorageUnit> unit) = 0;
        virtual bool delete_unit(StorageUnit::unit_id_t id) = 0;
        [[nodiscard]] virtual std::optional<std::shared_ptr<StorageUnit>> get_unit(StorageUnit::unit_id_t id) const = 0;
        [[nodiscard]] virtual std::vector<std::shared_ptr<StorageUnit>> get_all() const = 0;

        [[nodiscard]] virtual std::optional<std::shared_ptr<StorageUnit>>
            get_unit_by_ticket(AbstractTicket::ticket_id_t ticket_id) const = 0;

        friend std::ostream& operator<<(std::ostream& os, const IStorageUnitRepository& repo);
    };

} // namespace SkiPass