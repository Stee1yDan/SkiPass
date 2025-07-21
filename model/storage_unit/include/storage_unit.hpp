#pragma once

namespace SkiPass {
    class IStorageUnit  {
    public:
        virtual ~IStorageUnit() = default;

        using unit_id_t = unsigned int;

        [[nodiscard]] virtual unit_id_t get_storage_unit_id() const = 0;

        virtual void lock_storage_unit() = 0;

        virtual void open_storage_unit() = 0;
    };
}
