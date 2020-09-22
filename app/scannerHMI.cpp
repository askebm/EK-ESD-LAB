#include <ESD/driver/scanner.hpp>
#include <ESD/Logger.hpp>
#include <ctime>

// Returns true if given card number is valid
bool checkLuhn(const std::string& cardNo) {
    int nDigits = cardNo.length();

    int nSum = 0, isSecond = false;
    for (int i = nDigits - 1; i >= 0; i--) {

        int d = cardNo[i] - '0';

        if (isSecond == true)
            d = d * 2;

        // We add two digits to handle
        // cases that make two digits after
        // doubling
        nSum += d / 10;
        nSum += d % 10;

        isSecond = !isSecond;
    }
    return (nSum % 10 == 0);
}

bool checkPin(const std::string& pin){
	return true;
}

bool checkAmount(const int& amount){
	return true;
}

enum State {idle=0,input_pin,approve_amount,transaction};



int main(int argc, char *argv[])
{
	int amount = 5000;
	Scanner scanner{"swipe"};
	State state = idle;
	auto prevState = state;
	Logger hmiLog("Scanner HMI","/tmp/esd.log");

	while(true){
		std::string data;
		std::string msg;

		switch (state) {
			case idle:
				scanner.waitAndGetData(data);
				msg = "checkLuhn( " + data + " ) returned ";
				if (checkLuhn(data)) {
					state = input_pin;
					std::cout << "Validated by Luhn: " << data << std::endl;
					msg += "True";
				} else {
					msg += "False";
				}

				break;

			case input_pin:
				static int pin_cnt = 0;
				static std::string pin;
				std::cin >> pin;
				if (checkPin(pin)) {
					pin_cnt = 0;
					state=approve_amount;
				} else {
					++pin_cnt;
					if (pin_cnt >= 3) {
						state=idle;
						pin_cnt=0;
					}
				}

				break;
			case approve_amount:
				if (checkAmount(amount)) {
					state = transaction;
				} else {
					state = idle;
				}

				break;
			case transaction:
				state = idle;
				break;

			default:
				break;
		}
		if (state != prevState) {
			static std::string stateString[] ={"idle","input_pin","approve_amount","transaction"};
			hmiLog.log("State changed ( " + stateString[prevState] + " => " + stateString[state] + " )");
			prevState = state;
		}
	}
	
	return 0;
}
