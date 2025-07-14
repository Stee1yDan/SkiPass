#pragma once
#include "abstract_ticket_repository.hpp"

namespace SkiPass {

class IAppBuilder {
public:
    virtual ~IAppBuilder() = default;

    virtual std::unique_ptr<ITicketRepository> build_repository() = 0;
};

} // namespace banking