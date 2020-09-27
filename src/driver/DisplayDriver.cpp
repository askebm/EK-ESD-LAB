#include <ESD/driver/DisplayDriver.hpp>
#include <unistd.h>


DisplayDriver::DisplayDriver() {

}

void DisplayDriver::init() {
	this->initGPIOs();
	usleep(30000);
	this->initDisplay();

}

void DisplayDriver::print(int n,std::string s) {
	this->sendCommand(DisplayDriver::CMD::CLEAR);
	this->sendCommand(DisplayDriver::CMD::HOME);
	sendData(s);
}

void DisplayDriver::clear() {
	DisplayDriver::bitset b(0);
	b[DB0] = 1;
	setDataBits(b);
}

void DisplayDriver::initGPIOs() {
	static const std::string db[] = {"1016","1017","1018","1019","1020","1021","1022","1023"};
	static const std::string j2[] = {"1012","1013","1014","1015"};
	for (int i = 0; i < data_bit.size(); ++i) {
		auto& g = data_bit[i];
		g = new GPIO(db[i]);
		g->exportPin();
		g->setPinDirection("out");
	}
	register_select = new GPIO(j2[0]);
	register_select->setPinDirection("out");
	read_write = new GPIO(j2[1]);
	read_write->setPinDirection("out");
	enable = new GPIO(j2[2]);
	enable->setPinDirection("out");
}

void DisplayDriver::initDisplay() {
	DisplayDriver::bitset b(0);
	b[DB5] = 1;
	b[DB4] = 1;
	b[DB3] = 1;

	register_select->setPinValue("0");
	read_write->setPinValue("0");
	setDataBits(b);
	this->pulseEnableSignal();
	
	b[DB2] = 1;
	b[DB4] = 0;
	b[DB5] = 0;
	
	setDataBits(b);
	this->pulseEnableSignal();

	this->clear();
	usleep(5000);

	b.reset();
	b[DB2] = 1;
	b[DB0] = 0; // Don't shift display
	b[DB1] = 1; // Shift cursor right on DDRAM increment

	setDataBits(b);
	this->pulseEnableSignal();

}

void DisplayDriver::setDataBits(std::string s) {
	
}

void DisplayDriver::setDataBits(DisplayDriver::bitset b) {
	for (int i = 0; i < b.size(); ++i) {
		data_bit[i]->setPinValue(b[i]?"1":"0");
	}
}

void DisplayDriver::pulseEnableSignal() {
	enable->setPinValue("1");
	usleep(1000);
	enable->setPinValue("0");
	usleep(1000);
}

void DisplayDriver::sendCommand(const DisplayDriver::CMD& cmd) {
	register_select->setPinValue("0");
	read_write->setPinValue("0");
	DisplayDriver::bitset b(0);
	switch (cmd) {
		case DisplayDriver::CMD::HOME :
			b[DB1] = 1;
			break;
		case DisplayDriver::CMD::CLEAR :
			this->clear();
			break;
		case DisplayDriver::CMD::SHIFT_CURSOR_RIGHT :
			b[DB4] = 1;
			b[DB2] = 1;
			break;
		default:
			;
	}
	setDataBits(b);
	pulseEnableSignal();
}

void DisplayDriver::sendData(std::string s) {
	for (const auto& c : s) {
		this->sendData(c);
		this->sendCommand(DisplayDriver::CMD::SHIFT_CURSOR_RIGHT);
	}	
}

void DisplayDriver::sendData(const char& c) {
	register_select->setPinValue("1");
	read_write->setPinValue("0");
	DisplayDriver::bitset b(c);
	this->setDataBits(b);
	this->pulseEnableSignal();
}
