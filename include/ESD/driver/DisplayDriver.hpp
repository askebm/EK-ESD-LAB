#ifndef DISPLAYDRIVER_H
#define DISPLAYDRIVER_H
#include <GPIO.hpp>
#include <array>
#include <string>
#include <bitset>

class DisplayDriver
{
public:
	typedef std::bitset<8> bitset;
	enum Bits { DB0=0,DB1,DB2,DB3,DB4,DB5,DB6,DB7};
	enum CMD {HOME,CLEAR,SHIFT_CURSOR_RIGHT,SET_FUNCTION,DISPLAY_ON,
	};

private:
	std::array<GPIO*,8> data_bit;
	GPIO* register_select;
	GPIO*	read_write;
	GPIO*	enable;

public:
	DisplayDriver();
	void init();
	void print(int,std::string);
	void clear();

private:
	void initGPIOs();
	void initDisplay();
	void setDataBits(std::string);
	void setDataBits(bitset);
	void pulseEnableSignal();
	void sendCommand(const CMD&);
	void sendData(std::string);
	void sendData(const char&);
};

#endif /* DISPLAYDRIVER_H */
