#ifndef GPIO_H
#define GPIO_H
#include <string>

class GPIO
{
	private:
		std::string pin_number;

		int writeToFile(const std::string&, const std::string&);
		int readFromFile(const std::string&, std::string&);

		int exportPin();
		int unexportPin();

	public:
		GPIO(const std::string&);

		int setPinDirection(const std::string&);
		int setPinValue(const std::string&);
		int getPinValue(std::string&);

		void set(void);
		void clear(void);
};

#endif /* GPIO_H */
