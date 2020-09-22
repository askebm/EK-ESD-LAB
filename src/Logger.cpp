#include <ESD/Logger.hpp>

Logger::Logger(std::string c, std::string fileName) : context(c) {
	if (!this->file.is_open()) 
		this->file.open(fileName);
	++Logger::cnt;
}


Logger::~Logger() {
	if (--Logger::cnt == 0) {
		while(!this->mutex.try_lock()); // Finish wrting to log file
		this->file.close();
		this->mutex.unlock();
	}
}

void Logger::log(const std::string& msg) {
	std::time_t result = std::time(nullptr);
	std::string timeStamp = std::asctime(std::localtime(&result));
	while(!this->mutex.try_lock()); // Might not be a good idea
	// context (timeStamp): msg
	this->file << context << " (" << timeStamp << "): " << msg << std::endl;
	this->mutex.unlock();
}

unsigned int Logger::cnt= 0;
std::ofstream Logger::file;
std::mutex Logger::mutex;
