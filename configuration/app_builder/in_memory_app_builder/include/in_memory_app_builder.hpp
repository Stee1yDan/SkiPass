#pragma once

#include "app_builder.hpp"

namespace SkiPass {
    class InMemoryAppBuilder : public IAppBuilder
    {
        public:
            InMemoryAppBuilder() = default;

            std::shared_ptr<IController> build_controller(std::shared_ptr<TicketService> ticket_service,
                                                            std::shared_ptr<StorageService> storage_service,
                                                            std::shared_ptr<TourniquetService> tourniquet_service,
                                                            std::shared_ptr<IView> view) override;

            std::shared_ptr<IView> build_view() override;

            std::shared_ptr<TicketService> build_ticket_service(std::shared_ptr<ITicketRepository> ticket_repository) override;
            std::shared_ptr<StorageService> build_storage_service(std::shared_ptr<IStorageUnitRepository> ticket_repository) override;
            std::shared_ptr<TourniquetService> build_tourniquet_service(std::shared_ptr<ITicketRepository> ticket_repository) override;


            std::shared_ptr<ITicketRepository> build_ticket_repository() override;
            std::shared_ptr<IStorageUnitRepository> build_storage_unit_repository() override;

            ~InMemoryAppBuilder() override;

        private:
            std::unique_ptr<IView> view_;

            std::unique_ptr<TicketService> ticket_service_;
            std::unique_ptr<StorageService> storage_service_;
            std::unique_ptr<TourniquetService> tourniquet_service_;
            std::unique_ptr<ITicketRepository> ticket_repository_;
            std::unique_ptr<IStorageUnitRepository> storage_unit_repository_;

    };
}
