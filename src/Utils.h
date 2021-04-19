#ifndef WKJELLYWORM_UTILS_H
#define WKJELLYWORM_UTILS_H


#include <vector>
#include <string>

class Utils {
public:
	static int split_in_args(std::vector<std::string> &qargs, std::string command);
	static void * readFileToWaBuffer(std::string filename);
};


#endif //WKJELLYWORM_UTILS_H
