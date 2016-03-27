#include "File.h"
#include <cstring>

#include <iostream>

using namespace udpninja;

File::File(char * fileName, const char * options) {
	this->fileName = new char [strlen(fileName) + 1];
	strcpy(this->fileName, fileName);

	this->options = new char [strlen(options) + 1];
	strcpy(this->options, options);
	file = fopen(fileName, options);
}

File::~File() {
	delete fileName;
	delete options;
}

int File::close() {
	flush();
	return fclose(file);
}

int File::isOpen() {
	return file != NULL;
}

int File::write(const void * data, size_t size) {
	return fwrite(data, size, 1, file) == 1;
}

void File::flush() {
	fflush(file);
}

int File::isEmpty() {
	fseek(file, 0L, SEEK_END);
	return ftell(file) == 0;
}

int File::renameFile(char * newName, int openAgain) {
	std::cout << newName << "\n";
	std::cout << strlen(newName) << "\n";
	close();
	if (rename(fileName, newName) != 0) {
		return -1;
	}
	delete fileName;
	fileName = new char [strlen(newName) + 1];
	fileName = strcpy(fileName, newName);
	if (openAgain) {
		file = fopen(fileName, options);
	} else {
		file = NULL;
	}
	return 0;
}