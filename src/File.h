#pragma once
#include <stdio.h>

namespace udpninja
{

class File
{
public:
	File(char * fileName, const char * options);
	~File();
	void flush();
	int isOpen();
	int isEmpty();
	int close();
	int renameFile(char * newName, int openAgain);
	int write(const void * data, size_t size);
	int read(void * data, size_t size);
private:
	FILE * file;
	char * fileName;
	char * options;
};

}

