#include <stdexcept>
#include "Utils.h"
#include "WaLibc.h"


//https://stackoverflow.com/questions/18675364/c-tokenize-a-string-with-spaces-and-quotes
int Utils::split_in_args(std::vector<std::string>& qargs, std::string command) {
	int len = command.length();
	bool qot = false, sqot = false;
	int arglen;
	for(int i = 0; i < len; i++) {
		int start = i;
		if(command[i] == '\"') {
			qot = true;
		}
		else if(command[i] == '\'') sqot = true;

		if(qot) {
			i++;
			start++;
			while(i<len && command[i] != '\"')
				i++;
			if(i<len)
				qot = false;
			arglen = i-start;
			i++;
		}
		else if(sqot) {
			i++;
			while(i<len && command[i] != '\'')
				i++;
			if(i<len)
				sqot = false;
			arglen = i-start;
			i++;
		}
		else{
			while(i<len && command[i]!=' ')
				i++;
			arglen = i-start;
		}
		qargs.push_back(command.substr(start, arglen));
	}
	if(qot || sqot) return -1;
	return 0;
}

void * Utils::readFileToWaBuffer(std::string filename) {
	FILE * pf = fopen(filename.c_str(), "rb");
	if(!pf) throw std::runtime_error("Failed to load file: " + filename);

	fseek(pf, 0, SEEK_END);
	size_t filesize = ftell(pf);
	rewind(pf);
	void * buffer = WaLibc::waMalloc(filesize);
	if(!buffer) throw std::runtime_error("Failed to load filename: " + filename + " - Failed to allocate memory: " + std::to_string(filesize));
	size_t readsize = fread(buffer, 1, filesize,pf);
	if(readsize != filesize)
		throw std::runtime_error("Failed to read filename completely: filename: " + filename + " size: " + std::to_string(filesize) + " read: " + std::to_string(readsize));
	fclose(pf);

	return buffer;
}