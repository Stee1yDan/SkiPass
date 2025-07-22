#pragma once
#include "abstract_ticket_repository.hpp"
#include "ticket_service.hpp"
#include "cli_controller.hpp"

namespace SkiPass {

class IAppBuilder {
public:
    virtual ~IAppBuilder() = default;

    virtual std::shared_ptr<IController> build_controller(std::shared_ptr<TicketService> service, std::shared_ptr<IView> view) = 0;
    virtual std::shared_ptr<TicketService> build_service(std::shared_ptr<ITicketRepository> ticket_repository, std::shared_ptr<IStorageUnitRepository> storage_repository) = 0;
    virtual std::shared_ptr<ITicketRepository> build_ticket_repository() = 0;
    virtual std::shared_ptr<IStorageUnitRepository> build_storage_unit_repository() = 0;
    virtual std::shared_ptr<IView> build_view() = 0;
};

} // namespace banking