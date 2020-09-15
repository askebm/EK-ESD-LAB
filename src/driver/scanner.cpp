#include <driver/scanner.hpp>

Scanner::Scanner(std::string device) : device(device) {
	try {
		ifs.open(device, std::ifstream::in);
	}catch(...) {
		std::cout << "Could not open devive: "
			<< device << std::endl;
	}
}

/*! \brief Brief function description here
 *
 *  Detailed description
 *
 * \return Return parameter description
 */
void Scanner::waitAndGetData(std::string& data) {
	std::string result;
	char c = ifs.get();

	while (ifs.good() && c != '\n') {
		result += c;
		c = ifs.get();
	}
}

/*! \brief Brief function description here
 *
 *  Detailed description
 *
 * \return Return parameter description
 */
Scanner::~Scanner() {
	ifs.close();
}
