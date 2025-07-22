#pragma once

#include "app_builder.hpp"

namespace SkiPass {
    class InMemoryAppBuilder : public IAppBuilder
    {
        public:
            InMemoryAppBuilder() = default;

            std::shared_ptr<IController> build_controller(std::shared_ptr<TicketService> service,
                                                            std::shared_ptr<IView> view) override;

            std::shared_ptr<IView> build_view() override;

            std::unique_ptr<TicketService> service_;

            std::unique_ptr<TicketService> view_;
            std::unique_ptr<ITicketRepository> ticket_repository_;
            std::unique_ptr<IStorageUnitRepository> storage_unit_repository_;

            std::shared_ptr<TicketService> build_service(std::shared_ptr<ITicketRepository> ticket_repository, std::shared_ptr<IStorageUnitRepository> storage_repository) override;

            std::shared_ptr<ITicketRepository> build_ticket_repository() override;
            std::shared_ptr<IStorageUnitRepository> build_storage_unit_repository() override;

            ~InMemoryAppBuilder() override;

        private:

    };
}
