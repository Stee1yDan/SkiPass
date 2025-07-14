#include "app_builder.hpp"

namespace SkiPass {
    class InMemoryAppBuilder : public IAppBuilder
    {
        public:
            InMemoryAppBuilder() = default;

            std::unique_ptr<ITicketRepository> repository_;

            std::unique_ptr<ITicketRepository> build_repository() override;

        private:

    };
}
