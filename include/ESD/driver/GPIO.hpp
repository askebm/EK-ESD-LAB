#ifndef GPIO_H
#define GPIO_H
#include <string>

class GPIO
{
	private:
		std::string pin_number;


		int writeToFile(const std::string&, const std::string&);
		int readFromFile(const std::string&, std::string&);


	public:
		GPIO();
		GPIO(const std::string&);
		~GPIO();

    int setPinNumber(const int&);

		int exportPin();
		int unexportPin();

		int setPinDirection(const std::string&);
		int setPinValue(const std::string&);
		int getPinValue(std::string&);

		void set(void);
		void clear(void);


		// Hardware proxy methods
		void initialise();
		void configure(const std::string&, const std::string&, const std::string&);
		void disable();
		void acces(std::string&);
		void mutate(const std::string&);

	private:
		// TODO maybe a template?
		std::string marshall(const int&);

		//Helpers
		bool isInitialised();
		bool hasValidPin();

};

#endif /* GPIO_H */
