_PROJECT=lib_example
_SOURCES=lib_example.cpp
_CFLAGS=-std=c++1y

all: $(_PROJECT)

$(_PROJECT): libGPIO.so
	g++ $(_CFLAGS) -o $(_PROJECT) $(_SOURCES) -L . -l GPIO

