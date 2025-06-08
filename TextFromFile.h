#ifndef TEXTFROMFILE_H
#define TEXTFROMFILE_H

#include <string>

using namespace std;

class TextFromFile {
private:
    string content;
    
public:
    TextFromFile(const string& filename);
    string getContent() const;
};

#endif