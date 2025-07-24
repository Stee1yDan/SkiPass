#pragma once
#include "abstract_ticket_repository.hpp"
#include "ticket_service.hpp"
#include "cli_controller.hpp"

namespace SkiPass {

class IAppBuilder {
public:
    virtual ~IAppBuilder() = default;

    virtual std::shared_ptr<IController> build_controller(std::shared_ptr<TicketService> ticket_service,
                                                            std::shared_ptr<StorageService> storage_service,
                                                            std::shared_ptr<TourniquetService> tourniquet_service,
                                                            std::shared_ptr<IView> view) = 0;
    virtual std::shared_ptr<TicketService> build_ticket_service(std::shared_ptr<ITicketRepository> ticket_repository) = 0;
    virtual std::shared_ptr<StorageService> build_storage_service(std::shared_ptr<IStorageUnitRepository> ticket_repository) = 0;
    virtual std::shared_ptr<TourniquetService> build_tourniquet_service(std::shared_ptr<ITicketRepository> ticket_repository) = 0;
    virtual std::shared_ptr<ITicketRepository> build_ticket_repository() = 0;
    virtual std::shared_ptr<IStorageUnitRepository> build_storage_unit_repository() = 0;
    virtual std::shared_ptr<IView> build_view() = 0;
};

} // namespace banking