#include "FileSplitter.h"

using namespace udpninja;

FileSplitter::FileSplitter() {
	tmp = new File( (char *)TMP_FILENAME, FILE_MODE);
	startTime = 0;
}

FileSplitter::~FileSplitter() {
}

int FileSplitter::close() {
	return tmp->close();
}

int FileSplitter::isOpen() {
	return tmp->isOpen();
}

int FileSplitter::write(const void * data, size_t size){
	return tmp->write(data, size);
}

void FileSplitter::checkForNewFile() {
	if (startTime == 0) {
		updateStartTime();
	} else {
		
		if (difftime(time(NULL), startTime) > FIVE_MIN) {
			createNewFile(startTime + FIVE_MIN);
			updateStartTime();
		}
	}
}

void FileSplitter::createNewFile(time_t timestamp) {
	if (tmp->isEmpty()) {
		return;	//	no need for empty file
	}
	
	tm * timeInfo = localtime(&timestamp);
	
	timeInfo->tm_min = (timeInfo->tm_min / 5) * 5;
	// filename format is: udp_2016_03_27_12_55.ninja
	const int fileNameLen = 27;
	char * fileName = new char[fileNameLen];
	
	strftime(fileName, fileNameLen, "udp_%Y_%m_%d_%H_%M.ninja", timeInfo);
	tmp->renameFile(fileName, 0);
	
	delete tmp;
	
	tmp = new File((char *)TMP_FILENAME, FILE_MODE);
}

void FileSplitter::updateStartTime() {
	time(&startTime);
	tm * timeInfo = localtime(&startTime);
	timeInfo->tm_min = (timeInfo->tm_min / 5) * 5; //	round to 5 min
	startTime = mktime(timeInfo);
}
