#include <ESD/driver/NumpadDriver.hpp>
#include <unistd.h>
#include <iostream>

int main(int argc, char *argv[])
{
	NumpadDriver npd;
	npd.init();

	while (true) {
		std::cout << npd.check() << std::endl;
		usleep(10000);
	}

	return 0;
}
