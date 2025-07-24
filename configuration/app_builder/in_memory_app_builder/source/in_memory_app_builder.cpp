#include "../include/in_memory_app_builder.hpp"
#include "in_memory_ticket_repository.hpp"
#include "in_memory_storage_unit_repository.hpp"
#include "ticket_service.hpp"
#include "cli_view.hpp"

namespace SkiPass {
    std::shared_ptr<IController> InMemoryAppBuilder::build_controller(std::shared_ptr<TicketService> ticket_service,
        std::shared_ptr<StorageService> storage_service, std::shared_ptr<TourniquetService> tourniquet_service,
        std::shared_ptr<IView> view) {
        return std::make_shared<CLIController>(ticket_service, storage_service, tourniquet_service, view);
    }

    std::shared_ptr<IView> InMemoryAppBuilder::build_view() {
        return std::make_shared<CLIView>();
    }

    std::shared_ptr<TicketService> InMemoryAppBuilder::build_ticket_service(
        std::shared_ptr<ITicketRepository> ticket_repository) {
        return std::make_shared<TicketService>(ticket_repository);
    }

    std::shared_ptr<StorageService> InMemoryAppBuilder::build_storage_service(
        std::shared_ptr<IStorageUnitRepository> ticket_repository) {
        return std::make_shared<StorageService>(ticket_repository);
    }

    std::shared_ptr<TourniquetService> InMemoryAppBuilder::build_tourniquet_service(
        std::shared_ptr<ITicketRepository> ticket_repository) {
        return std::make_shared<TourniquetService>(ticket_repository);
    }

    std::shared_ptr<ITicketRepository> InMemoryAppBuilder::build_ticket_repository() {
        return std::make_shared<InMemoryTicketRepository>();
    }

    std::shared_ptr<IStorageUnitRepository> InMemoryAppBuilder::build_storage_unit_repository() {
        return std::make_shared<InMemoryStorageUnitRepository>();
    }

    InMemoryAppBuilder::~InMemoryAppBuilder() = default;
}
