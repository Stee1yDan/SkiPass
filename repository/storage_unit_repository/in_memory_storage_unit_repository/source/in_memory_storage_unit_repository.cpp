#include "in_memory_storage_unit_repository.hpp"

#include <format>

#include "storage_unit.hpp"

namespace SkiPass {
    std::shared_ptr<StorageUnit> InMemoryStorageUnitRepository::add_unit(std::shared_ptr<StorageUnit> unit) {
        if (!unit) {
            throw std::invalid_argument("Cannot add null storage unit");
        }

        if (ticket_to_unit_.contains(unit->get_linked_ticket_id())) {
            throw std::runtime_error(
                std::format("Ticket {} already has a storage unit",
                           unit->get_linked_ticket_id()));
        }

        if (unit->get_storage_unit_id() == 0) {
            unit = std::make_shared<StorageUnit>(next_id_++, unit->get_linked_ticket_id());
        }

        units_.emplace(unit->get_storage_unit_id(), unit);
        ticket_to_unit_.emplace(unit->get_linked_ticket_id(), unit);

        return unit;
    }

    bool InMemoryStorageUnitRepository::delete_unit(StorageUnit::unit_id_t id) {
        auto it = units_.find(id);
        if (it == units_.end()) {
            return false;
        }

        ticket_to_unit_.erase(it->second->get_linked_ticket_id());
        units_.erase(it);

        return true;
    }

    std::optional<std::shared_ptr<StorageUnit>> InMemoryStorageUnitRepository::get_unit(StorageUnit::unit_id_t id) const {
        auto it = units_.find(id);
        if (it == units_.end()) {
            return std::nullopt;
        }
        return it->second;
    }

    std::vector<std::shared_ptr<StorageUnit>> InMemoryStorageUnitRepository::get_all() const {
        std::vector<std::shared_ptr<StorageUnit>> result;
        for (const auto& [id, unit] : units_) {
            result.push_back(unit);
        }
        return result;
    }

    std::optional<std::shared_ptr<StorageUnit>> InMemoryStorageUnitRepository::get_unit_by_ticket(
        AbstractTicket::ticket_id_t ticket_id) const {
        auto it = ticket_to_unit_.find(ticket_id);
        if (it == ticket_to_unit_.end()) {
            return std::nullopt;
        }
        return it->second;
    }

    std::ostream& operator<<(std::ostream& os, const IStorageUnitRepository& repo) {
        os << std::format("{:<10} | {:<15} | {:<10}\n",
                         "Unit ID", "Linked Ticket", "Status");
        os << std::string(45, '-') << '\n';

        for (const auto& unit : repo.get_all()) {
            os << std::format("{:<10} | {:<15} | {:<10}\n",
                             unit->get_storage_unit_id(),
                             unit->get_linked_ticket_id(),
                             unit->is_locked() ? "Locked" : "Unlocked");
        }
        return os;
    }
}
