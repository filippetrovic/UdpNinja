#include "FileSplitter.h"
#include <cstring>

using namespace udpninja;

FileSplitter::FileSplitter(char * dir) {
	// Does slash exists: /tmp/ or /tmp
	int slashNotExists = dir[strlen(dir) - 1] != '/';
	
	outputDir = new char [strlen(dir) + 1 + slashNotExists];
	strcpy(outputDir, dir);
	if (slashNotExists) {
		outputDir[strlen(outputDir)] = '/';
		outputDir[strlen(outputDir) + 1] = '\0';
	}

	tempFilename = new char [strlen(outputDir) + strlen(TMP_FILENAME) + 1];
	strcpy(tempFilename, outputDir);
	strncat(tempFilename, TMP_FILENAME, strlen(TMP_FILENAME));

	tmpFile = new File(tempFilename, FILE_MODE);
	startTime = 0;
}

FileSplitter::~FileSplitter() {
	delete tmpFile;
	delete tempFilename;
	delete outputDir;
}

int FileSplitter::close() {
	return tmpFile->close();
}

int FileSplitter::isOpen() {
	return tmpFile->isOpen();
}

int FileSplitter::write(const void * data, size_t size){
	return tmpFile->write(data, size);
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
	if (tmpFile->isEmpty()) {
		return;	//	no need for empty file
	}
	
	tm * timeInfo = localtime(&timestamp);
	
	timeInfo->tm_min = (timeInfo->tm_min / 5) * 5;
	// filename format is: udp_2016_03_27_12_55.ninja
	const int fileNameLen = 27; // including terminal char
	char * fileName = new char[fileNameLen];
	
	strftime(fileName, fileNameLen, "udp_%Y_%m_%d_%H_%M.ninja", timeInfo);
	
	char * fullFileName = new char [strlen(outputDir) + fileNameLen];
	strcpy(fullFileName, outputDir);
	strncat(fullFileName, fileName, fileNameLen);
	tmpFile->renameFile(fullFileName, 0);
	
	delete fileName;
	delete fullFileName;
	delete tmpFile;
	
	tmpFile = new File(tempFilename, FILE_MODE);
}

void FileSplitter::updateStartTime() {
	time(&startTime);
	tm * timeInfo = localtime(&startTime);
	timeInfo->tm_min = (timeInfo->tm_min / 5) * 5; // round to 5 min
	timeInfo->tm_sec = 0;	// round to 5 min
	startTime = mktime(timeInfo);
}
char* FileSplitter::getOutputDir() {
	return outputDir;
}
