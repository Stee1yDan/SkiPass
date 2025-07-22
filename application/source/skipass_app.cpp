#include "skipass_app.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <bits/ostream.tcc>

#include "in_memory_ticket_repository.hpp"
#include "in_memory_storage_unit_repository.hpp"
#include "abstract_ticket.hpp"
#include "unlimited_ticket.hpp"


namespace SkiPass {
    int SkiPassApp::run(int argc, char const *argv[]) {
        show_banner();
        auto builder = load(argc, argv);
        std::shared_ptr<ITicketRepository> ticket_repository = builder->build_ticket_repository();
        std::shared_ptr<IStorageUnitRepository> storage_repository = builder->build_storage_unit_repository();
        std::shared_ptr<IView> view = builder->build_view();
        std::shared_ptr<TicketService> ticket_service = builder->build_service(ticket_repository, storage_repository);
        std::shared_ptr<IController> cli_controller = builder->build_controller(ticket_service,view);
        // auto ticket1 = std::make_shared<UnlimitedTicket>("fio",21,"M", AbstractTicket::TicketType::UNLIMITED);
        // auto ticket2 = std::make_shared<UnlimitedTicket>("fio",22,"M", AbstractTicket::TicketType::UNLIMITED);
        // ticket_service->add_ticket(ticket1);
        // ticket_service->add_ticket(ticket2);
        cli_controller->run();
        return 0;
    }

    std::unique_ptr<IAppBuilder> SkiPassApp::load(int argc, char const *argv[])
    {
        std::cout << "SkiPassApp::load" << std::endl;
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
