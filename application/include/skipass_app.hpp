#pragma once
#include <in_memory_app_builder.hpp>

namespace SkiPass {
    class IAppBuilder;

    class SkiPassApp {
    public:
        static int run(int argc, char const *argv[]);

    private:
        static std::unique_ptr<IAppBuilder> load(int argc, char const *argv[]);

    };

}