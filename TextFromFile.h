#ifndef TEXTFROMFILE_H_
#define TEXTFROMFILE_H_

#include <string>
using namespace std;

class TextFromFile final
	{
	private:
		string fileName;
		string fileContent;

	public:
		TextFromFile(string fileName);
		virtual ~TextFromFile();
		string& getFileContent();
		string& getFileName();
	};

#endif /* TEXTFROMFILE_H_ */