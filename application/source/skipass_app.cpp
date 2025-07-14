#include "skipass_app.hpp"

#include <iostream>
#include <memory>
#include <bits/ostream.tcc>

#include "in_memory_ticket_repository.hpp"
#include "abstract_ticket.hpp"
#include "unlimited_ticket.hpp"


namespace SkiPass {
    int SkiPassApp::run(int argc, char const *argv[]) {
        auto builder = load(argc, argv);
        auto ticket_repository = builder->build_repository();
        auto ticket1 = std::make_shared<UnlimitedTicket>("fio",21,"M", AbstractTicket::TicketType::UNLIMITED);
        auto ticket2 = std::make_shared<UnlimitedTicket>("fio",22,"M", AbstractTicket::TicketType::UNLIMITED);
        ticket_repository->add_ticket(ticket1);
        ticket_repository->add_ticket(ticket2);
        std::cout << "SkiPassApp::run" << std::endl;
        std::cout << ticket_repository->increment_ticket_id() << std::endl;
        return 0;
    }

    std::unique_ptr<IAppBuilder> SkiPassApp::load(int argc, char const *argv[])
    {
        std::cout << "SkiPassApp::load" << std::endl;
        return std::make_unique<InMemoryAppBuilder>();
    }
}
