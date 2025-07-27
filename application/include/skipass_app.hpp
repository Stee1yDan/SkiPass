#pragma once
#include <in_memory_app_builder.hpp>

namespace SkiPass {
    class SkiPassApp {
    public:
        static int run(int argc, char const *argv[]);
        static void show_banner();

    private:
        static std::unique_ptr<IAppBuilder> load(int argc, char const *argv[]);
    };

}