#ifndef SYSINFO_H
#define SYSINFO_H

#include <string>

class SysInfo {
public:
    static std::string getVersion();
    static std::string getAuthor();
};

#endif // SYSINFO_H