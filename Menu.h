#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

class Menu {
private:
    std::vector<std::string> items;
    std::string title;
    std::string message;
    
public:
    Menu(const std::vector<std::string>& items, 
         const std::string& title, 
         const std::string& message = "Choose: ");
    int getChoice() const;
};

#endif