#include <ESD/driver/DisplayDriver.hpp>

int main(int argc, char *argv[])
{
	DisplayDriver dd;

	dd.init();

	dd.print(0,"Hello World");
	

	
	return 0;
}
