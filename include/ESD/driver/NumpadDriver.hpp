#ifndef NUMPADDRIVER_H
#define NUMPADDRIVER_H

#include <array>
#include <GPIO.hpp>

class NumpadDriver
{
private:
	std::array<GPIO*,4> column;
	std::array<GPIO*,4> row;

	int getValue() ;
public:
	NumpadDriver();
	void init();
	int check() ;
//	virtual ~NumpadDriver();
};

#endif /* NUMPADDRIVER_H */
