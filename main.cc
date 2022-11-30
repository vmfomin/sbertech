#include "src/DirChecker.h"

#include <csignal>

volatile int32_t sig_exit = 0;

void quit(int32_t signal) { sig_exit = signal; }

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: not enough args" << std::endl;
        return 1;
    }

    std::signal(SIGTERM, quit);
    std::signal(SIGINT, quit);
    std::signal(SIGABRT, quit);
    std::signal(SIGUSR1, quit);

    DirChecker checker(argv[1]);

    while (!sig_exit)
    {
        checker.check();
        ::usleep(100);
    }
}
