#pragma once

#include "../include/in_memory_app_builder.hpp"
#include "in_memory_ticket_repository.hpp"

namespace SkiPass {

    std::unique_ptr<ITicketRepository> InMemoryAppBuilder::build_repository() {
        repository_ = std::make_unique<InMemoryTicketRepository>();
        return std::move(repository_);
    }
}
