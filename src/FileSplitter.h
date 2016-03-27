#pragma once
#include "File.h"
#include <time.h>

#define FIVE_MIN 300
#define TMP_FILENAME "tmp.ninja"
#define FILE_MODE "wb"

namespace udpninja
{

class FileSplitter
{
public:
	FileSplitter();
	~FileSplitter();

	int isOpen();
	int close();
	int write(const void * data, size_t size);
	void checkForNewFile();
private:
	void updateStartTime();
	void createNewFile(time_t timestamp);

	File * tmpFile;
	time_t startTime;
};

}

