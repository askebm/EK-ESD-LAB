#include <ESD/driver/NumpadDriver.hpp>
#include <iostream>

/*			col1 col2 col3 col4
 * row1 1    2    3    A
 * row2 4    5    6    B
 * row3 7    8    9    C
 * row4 0    F    E    D
 */
NumpadDriver::NumpadDriver() {
	
}

void NumpadDriver::init() {
	static const std::string r[] = {"996","997","998","999"};
	static const std::string c[] = {"992","993","994","995"};
	for (int i = 0; i < this->column.size(); ++i) {
		auto& g =  column[i];
		g = new GPIO(c[i]);
		g->exportPin();
		g->setPinDirection("out");
		g->setPinValue("0");
	}
	for (int i = 0; i < this->row.size(); ++i) {
		auto& g =  row[i];
		g = new GPIO(r[i]);
		g->exportPin();
		g->setPinDirection("in");
	}
}

int NumpadDriver::getValue() {
	int result = -1;
	std::string value;
	for (int i = 0; i < this->row.size(); ++i) {
		this->row[i]->getPinValue(value);
		if (value == "0" ) {
			for (int j = 0; j < this->column.size(); ++j) {
				this->column[j]->setPinDirection("in");
				this->column[j]->getPinValue(value);
				this->column[j]->setPinDirection("out");
				if (value == "1") {
					static const int tab[4][4] = {
						{1,2,3,'A'},
						{4,5,6,'B'},
						{7,8,9,'C'},
						{0,'F','E','D'}};
					result = tab[3-i][3-j];
					break;
				}
			}
			break;
		}
	}

	return result;
}

int NumpadDriver::check()  {
	return this->getValue();
}

