#include <Logger.hpp>

Logger::Logger(std::string context, std::string file) : context(context) {
	if (!this->file.is_open()) {
		Logger::cnt = 0;
		this->file.open(file);
	}

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

