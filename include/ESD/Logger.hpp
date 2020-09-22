#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <mutex>
#include <iostream>

class Logger
{
private:
	std::string context;
	static unsigned int cnt;
	static std::ofstream file;
	static std::mutex mutex;

public:
	Logger(std::string, std::string);
	~Logger();
	void log(const std::string& msg);
};

#endif /* LOGGER_H */
