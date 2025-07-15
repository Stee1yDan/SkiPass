#include "../include/in_memory_app_builder.hpp"
#include "in_memory_ticket_repository.hpp"
#include "ticket_service.hpp"
#include "cli_view.hpp"

namespace SkiPass {
    std::shared_ptr<IController> InMemoryAppBuilder::build_controller(
        std::shared_ptr<TicketService> service,
        std::shared_ptr<IView> view)
    {
        return std::make_shared<CLIController>(service, view);
    }

    std::shared_ptr<IView> InMemoryAppBuilder::build_view() {
        return std::make_shared<CLIView>();
    }

    std::shared_ptr<TicketService> InMemoryAppBuilder::build_service(std::shared_ptr<ITicketRepository> repository) {
        return std::make_shared<TicketService>(repository);
    }

    std::shared_ptr<ITicketRepository> InMemoryAppBuilder::build_repository() {
        return std::make_shared<InMemoryTicketRepository>();
    }

    InMemoryAppBuilder::~InMemoryAppBuilder() = default;
}
