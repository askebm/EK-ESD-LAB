add_executable(scannerHMI scannerHMI.cpp)
target_compile_features(scannerHMI PRIVATE cxx_std_11)
target_link_libraries(scannerHMI scanner logger)

add_executable(gpioExample gpioExample.cpp)
#target_compile_features(gpioExample PRIVATE cxx_std_14)
target_link_libraries(gpioExample GPIO)
