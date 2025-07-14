#include "../include/in_memory_app_builder.hpp"
#include "in_memory_ticket_repository.hpp"
#include "ticket_service.hpp"

namespace SkiPass {
    std::shared_ptr<CLIController> InMemoryAppBuilder::build_controller(std::shared_ptr<TicketService> service) {
        return std::make_shared<CLIController>(service);
    }

    std::shared_ptr<TicketService> InMemoryAppBuilder::build_service(std::shared_ptr<ITicketRepository> repository) {
        return std::make_shared<TicketService>(repository);
    }

    std::shared_ptr<ITicketRepository> InMemoryAppBuilder::build_repository() {
        return std::make_shared<InMemoryTicketRepository>();
    }

    InMemoryAppBuilder::~InMemoryAppBuilder() = default;
}
