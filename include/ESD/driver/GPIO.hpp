#ifndef GPIO_H
#define GPIO_H
#include <string>
#include <map>

class GPIO
{
	private:
		std::string pin_number;

		int writeToFile(const std::string&, const std::string&);
		int readFromFile(const std::string&, std::string&);
		void changePin(const std::string&);

		void lock();
		bool testLock();
		void unlock();


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
		void configure(const std::string&, const std::string&);
		void disable();
		void accesPinValue(std::string&);
		void mutatePinValue(const std::string&);

	private:
		// TODO maybe a template?
		std::string marshall(const int&);

		//Helpers
		bool isInitialised();
		bool isValidPin(const std::string&);

};

#endif /* GPIO_H */
