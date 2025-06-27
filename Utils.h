#ifndef UTILS_H
#define UTILS_H

#include <string>

using namespace std;

class Utils {
public:
    static void printMessage(const std::string& message);
    static string getInput(const std::string& prompt);
    static int getIntInput(const std::string& prompt); 
    static double getDoubleInput(const std::string& prompt);

    static void printSuccess(const std::string& message);
    static void printError(const std::string& message);
};

#endif
