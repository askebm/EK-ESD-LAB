#include <ESD/driver/GPIO.hpp>
#include <fstream>
#include <iostream>

int GPIO::writeToFile(const std::string& file,const std::string& data) {
	std::ofstream f;
	f.open(file);
	for (const char& i : data) {
		f << i;
	}
	f.close();
	return 0;
}

int GPIO::readFromFile(const std::string& file, std::string& data) {
	std::ifstream f(file);
	data.clear();
	char c;
	while (f.get(c)) {
		if (c != '\n') {
			data += c;
		}
	}
	f.close();
	return 0;
}
int GPIO::exportPin(){
	static const std::string file = "/sys/class/gpio/export";
	writeToFile(file,pin_number);
	return 0;
}

int GPIO::unexportPin(){
	static const std::string file = "/sys/class/gpio/unexport";
	writeToFile(file,pin_number);
	return 0;
}

GPIO::GPIO(const std::string& pin) : pin_number(pin){
	//exportPin();
}

GPIO::~GPIO() {
//	unexportPin();
}

int GPIO::setPinDirection(const std::string& dir){
	std::string file = "/sys/class/gpio/gpio";
	file += pin_number;
	file += "/direction";
	return writeToFile(file,dir);
}

int GPIO::setPinValue(const std::string& val){
	std::string file = "/sys/class/gpio/gpio";
	file += pin_number;
	file += "/value";
	return writeToFile(file,val);
}

int GPIO::getPinValue(std::string& val){
	std::string file = "/sys/class/gpio/gpio";
	file += pin_number;
	file += "/value";
	return readFromFile(file,val);
}

void GPIO::set(void){
	setPinValue("1");
}

void GPIO::clear(void){
	setPinValue("0");
}
