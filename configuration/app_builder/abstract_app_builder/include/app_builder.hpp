#pragma once
#include "abstract_ticket_repository.hpp"
#include "ticket_service.hpp"
#include "cli_controller.hpp"

namespace SkiPass {

class IAppBuilder {
public:
    virtual ~IAppBuilder() = default;

    virtual std::shared_ptr<CLIController> build_controller(std::shared_ptr<TicketService> service) = 0;
    virtual std::shared_ptr<TicketService> build_service(std::shared_ptr<ITicketRepository> repository) = 0;
    virtual std::shared_ptr<ITicketRepository> build_repository() = 0;
};

} // namespace banking