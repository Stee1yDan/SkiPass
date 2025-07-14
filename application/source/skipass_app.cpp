#include "skipass_app.hpp"

#include <iostream>
#include <memory>
#include <bits/ostream.tcc>

#include "in_memory_ticket_repository.hpp"

namespace SkiPass {
    int SkiPassApp::run(int argc, char const *argv[]) {
        auto builder = load(argc, argv);
        auto ticket_repository = builder->build_repository();
        ticket_repository->increment_ticket_id();
        ticket_repository->increment_ticket_id();
        ticket_repository->increment_ticket_id();
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
