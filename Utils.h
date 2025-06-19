#ifndef UTILS_H
#define UTILS_H

#include <string>

using namespace std;

class Utils {
public:
    static void printMessage(const std::string& message);
    static string getInput(const std::string& prompt);
    static int getIntInput(const std::string& prompt); 
};

#endif