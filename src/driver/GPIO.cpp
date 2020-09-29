#include <ESD/driver/GPIO.hpp>
#include <fstream>
#include <iostream>


static const std::string PATH = "/sys/class/gpio/";

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
	auto result = f.good();
	data.clear();
	char c;
	while (f.get(c)) {
		if (c != '\n') {
			data += c;
		}
	}
	f.close();
	return result;
}

void GPIO::changePin(const std::string& pin){
	if (isValidPin(this->pin_number)) {
		unexportPin();
	}
	if (isValidPin(pin)) {
		this->pin_number = pin;
	} else {
		std::cerr << "Can't change pin. " << pin << " is not a valid pin." << std::endl;
	}
}


int GPIO::exportPin(){
	static const std::string file = "/sys/class/gpio/export";
	if (isValidPin(this->pin_number)) {
		writeToFile(file,pin_number);
		return 1;
	}
	return 0;
}

int GPIO::unexportPin(){
	static const std::string file = "/sys/class/gpio/unexport";
	writeToFile(file,pin_number);
	return 0;
}

GPIO::GPIO(){
}

GPIO::GPIO(const std::string& pin)  {
	changePin(pin);
}

GPIO::~GPIO() {
}

int GPIO::setPinNumber(const int& pin){
	changePin( marshall(pin) );
	return 0;
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

void GPIO::initialise() {
	exportPin();
}

void GPIO::configure( const std::string& direction, const std::string& value){
	setPinDirection(direction);
	setPinValue(value);
}

void GPIO::disable(){
	unexportPin();
}

void GPIO::accesPinValue(std::string& value){
	getPinValue(value);
}

void GPIO::mutatePinValue(const std::string& value){
	setPinValue(value);
}

std::string GPIO::marshall(const int& in){
	return std::to_string(in);
}

bool GPIO::isInitialised(){
	auto result = isValidPin(this->pin_number);
	if (result) {
		std::string tmp;
		result = bool(getPinValue(tmp));
	}
	return result;
}

bool GPIO::isValidPin(const std::string& pin) {
	bool result;
	if (pin.size()) {
		result = true;
		for (const auto& c : pin) {
			result &= ( ( '0' <= c ) && ( c <= '9' ) );
		}
	} else {
		result = false;
	}
	return result;
}

