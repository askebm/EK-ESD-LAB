#ifndef DISPLAYDRIVER_H
#define DISPLAYDRIVER_H
#include <GPIO.hpp>
#include <array>
#include <string>
#include <bitset>

class DisplayDriver
{
private:
	typedef unsigned char cmd;
	typedef const cmd& cmd_in;

	static const cmd CLEAR_DISPLAY = 0b1;
	static const cmd RETURN_HOME = 0b10;
	static const cmd ENTRY_MODE_SHIFT_CURSOR_RIGHT = 0b110;
	static const cmd DISPLAY_ON = 0b1100;
	static const cmd DISPLAY_OFF = 0b100;
	static const cmd FUNCTION_SET = 0b111000;
public:

private:
	std::array<GPIO*,8> data_bit;
	GPIO* register_select;
	GPIO*	read_write;
	GPIO*	enable;

public:
	DisplayDriver();
	~DisplayDriver();
	void init();
	void print(cmd_in,std::string);
	void clear();

private:
	void initGPIOs();
	void initDisplay();
	void setDataBits(std::string);
	void setDataBits(cmd_in);
	void sendCommand(cmd_in);
	void pulseEnableSignal();
	void sendData(std::string);
	void sendData(const char&);
	void setDDRAMAddress(cmd_in);
};

#endif /* DISPLAYDRIVER_H */
