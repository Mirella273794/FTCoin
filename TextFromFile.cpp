#include "TextFromFile.h"
#include <fstream>
#include <sstream>

using namespace std;

TextFromFile::TextFromFile(const string& filename) {
    ifstream file(filename);
    stringstream buffer;
    buffer << file.rdbuf();
    content = buffer.str();
}

string TextFromFile::getContent() const {
    return content;
}