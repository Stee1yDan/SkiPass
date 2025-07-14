#pragma once

#include "app_builder.hpp"

namespace SkiPass {
    class InMemoryAppBuilder : public IAppBuilder
    {
        public:
            InMemoryAppBuilder() = default;

            std::unique_ptr<TicketService> service_;
            std::unique_ptr<ITicketRepository> repository_;

            std::shared_ptr<CLIController> build_controller(std::shared_ptr<TicketService> service) override;

            std::shared_ptr<TicketService> build_service(std::shared_ptr<ITicketRepository> repository) override;

            std::shared_ptr<ITicketRepository> build_repository() override;

            ~InMemoryAppBuilder() override;

        private:

    };
}
