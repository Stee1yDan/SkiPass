#include "skipass_app.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <bits/ostream.tcc>

#include "in_memory_ticket_repository.hpp"
#include "in_memory_storage_unit_repository.hpp"

namespace SkiPass {
    int SkiPassApp::run(int argc, char const *argv[]) {
        show_banner();
        auto builder = load(argc, argv);
        std::shared_ptr<ITicketRepository> ticket_repository = builder->build_ticket_repository();
        std::shared_ptr<IStorageUnitRepository> storage_repository = builder->build_storage_unit_repository();
        std::shared_ptr<IView> view = builder->build_view();
        std::shared_ptr<TicketService> ticket_service = builder->build_ticket_service(ticket_repository);
        std::shared_ptr<StorageService> storage_service = builder->build_storage_service(storage_repository);
        std::shared_ptr<TourniquetService> tourniquet_service = builder->build_tourniquet_service(ticket_repository);
        std::shared_ptr<IController> cli_controller = builder->build_controller(ticket_service,storage_service,tourniquet_service,view);
        cli_controller->run();
        return 0;
    }

    std::unique_ptr<IAppBuilder> SkiPassApp::load(int argc, char const *argv[])
    {
        return std::make_unique<InMemoryAppBuilder>();
    }

    void SkiPassApp::show_banner() {
        std::ifstream file("../application/banner.txt");

        if (!file.is_open()) {
            std::cerr << "Error: couldn't show banner\n";
        }

        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << '\n';
        }

        file.close();
    }
}
