#ifndef GPIO_H
#define GPIO_H
#include <string>

class GPIO
{
	private:
		std::string pin_number;

		int writeToFile(std::string, std::string);
		int readFromFile(std::string, std::string&);

		int exportPin();
		int unexportPin();

	public:
		GPIO();
		GPIO(std::string);

		int setPinNumber(int);


		int setPinDirection(std::string);

		int setPinValue(std::string);
		int getPinValue(std::string&);

		void set(void);
		void clear(void);
};

#endif /* GPIO_H */
