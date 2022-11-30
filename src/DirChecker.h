#pragma once

#include <iostream>
#include <sys/inotify.h>
#include <unistd.h>

extern volatile int32_t sig_exit;

class DirChecker
{
public:
    DirChecker(const std::string& path);

    ~DirChecker()
    {
        inotify_rm_watch(fd_, wd_);
        close(fd_);
    }

    void check();

private:
    int32_t     fd_;
    int32_t     wd_;
    std::string cwd_;
};
