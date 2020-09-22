#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Scanner
{
private:
	std::string device;
	std::ifstream ifs;

public:
	Scanner(std::string device);

	void waitAndGetData(std::string& data);


	~Scanner();
};

#endif /* SCANNER_H */
