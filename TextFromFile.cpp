#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "TextFromFile.h"
#include "Utils.h"

TextFromFile::TextFromFile(string fileName) :
		fileName(fileName)
	{
	fileContent = "";
	try
		{
		ifstream inputFile(fileName);
		stringstream buffer;

		if (!inputFile.is_open())
			{
			throw runtime_error("Failed to open the file: " + fileName);
			}

		buffer << inputFile.rdbuf(); // Read entire file into the buffer
		inputFile.close();
		fileContent = buffer.str();
		}
	catch (const exception &myException)
		{
		Utils::printMessage("Unexpected problem: " + string(myException.what()));
		}
	}

string& TextFromFile::getFileContent()
	{
	return fileContent;
	}

string& TextFromFile::getFileName()
	{
	return fileName;
	}

TextFromFile::~TextFromFile()
	{
	}