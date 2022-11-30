#include <fstream>

#include "DirChecker.h"

constexpr const size_t BUF_LEN = 2048;

DirChecker::DirChecker(const std::string& path) : fd_(0), cwd_(path)
{
    if (cwd_.back() != '/') cwd_ += "/";

    fd_ = inotify_init1(0);
    if (fd_ == -1)
    {
        std::cerr << "Cannot init inotify" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    wd_ = inotify_add_watch(fd_, cwd_.c_str(), IN_CLOSE);
    if (fd_ == -1)
    {
        std::cerr << "Cannot init inotify" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void DirChecker::check()
{
    char buf[BUF_LEN] = {0};

    size_t len = read(fd_, buf, BUF_LEN);
    for (size_t i = 0; i < len && !sig_exit;)
    {
        inotify_event* event = (inotify_event*)&buf[i];
        if (event->len > 0)
        {
            std::string   name_with_path(cwd_ + event->name);
            std::ifstream in_file(name_with_path);

            if (in_file)
            {
                size_t      cnt = 0;
                std::string line;
                while (std::getline(in_file, line))
                {
                    ++cnt;
                }

                std::cout << "File: " << event->name << " has " << cnt << " lines was ";
                std::cout << (remove((cwd_ + event->name).c_str()) == 0 ? "removed" : "NOT removed")
                          << std::endl;
            }
        }

        i += sizeof(inotify_event) + event->len;
    }
}
