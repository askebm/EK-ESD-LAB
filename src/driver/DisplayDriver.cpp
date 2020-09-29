#include <ESD/driver/DisplayDriver.hpp>
#include <unistd.h>

const DisplayDriver::cmd DisplayDriver::CLEAR_DISPLAY;
const DisplayDriver::cmd DisplayDriver::RETURN_HOME;
const DisplayDriver::cmd DisplayDriver::ENTRY_MODE_SHIFT_CURSOR_RIGHT;
const DisplayDriver::cmd DisplayDriver::DISPLAY_ON;
const DisplayDriver::cmd DisplayDriver::DISPLAY_OFF;
const DisplayDriver::cmd DisplayDriver::FUNCTION_SET;

DisplayDriver::DisplayDriver() {

}

DisplayDriver::~DisplayDriver(){
	delete register_select;
	delete read_write;
	delete enable;
	for (auto io : data_bit) {
		delete io;
	}
}

void DisplayDriver::init() {
	this->initGPIOs();
	usleep(30000);
	this->initDisplay();
}

void DisplayDriver::print(cmd_in n,std::string s) {
	int top = 0x00;
	int bottom = 0x40;
	if (n < 16) {
		setDDRAMAddress(n);
	} else {
		setDDRAMAddress(bottom+n);
	}
	sendData(s);
}

void DisplayDriver::clear() {
	sendCommand(CLEAR_DISPLAY);
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
	sendCommand(FUNCTION_SET);
	sendCommand(DISPLAY_ON);
	sendCommand(CLEAR_DISPLAY);
	usleep(5000);
}

void DisplayDriver::setDataBits(std::string s) {
	cmd command = 0;
	int i = s.size();
	for (const auto& c : s) {
		command |= ((c=='0'?0:1) << --i);
	}
	setDataBits(command);
}

void DisplayDriver::setDataBits(cmd_in bits){
	for (int i = 0; i < 8; ++i) {
		data_bit[i]->setPinValue( ( ( bits & (1<<i) )?"1":"0" ) );
	}
}

void DisplayDriver::sendCommand(cmd_in c){
	register_select->clear();
	read_write->clear();
	setDataBits(c);
	pulseEnableSignal();
}

void DisplayDriver::pulseEnableSignal() {
	enable->setPinValue("1");
	usleep(1000);
	enable->setPinValue("0");
	usleep(1000);
}

void DisplayDriver::sendData(std::string s) {
	for (const auto& c : s) {
		this->sendData(c);
	}	
}

void DisplayDriver::sendData(const char& c) {
	register_select->set();
	read_write->clear();
	setDataBits(c);
	pulseEnableSignal();
}

void DisplayDriver::setDDRAMAddress(cmd_in addr){
	sendCommand( addr | (1 << 7));
}
