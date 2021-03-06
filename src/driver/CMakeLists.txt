set(HEADER_LIST "${ESD_SOURCE_DIR}/include/ESD/driver/scanner.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(scanner scanner.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(scanner PUBLIC ../../include)

# All users of this library will need at least C++11
target_compile_features(scanner PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})

add_library(GPIO GPIO.cpp)
target_include_directories(GPIO
	PUBLIC
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/include/ESD/driver)
target_compile_features(GPIO PRIVATE cxx_std_11)

add_library(NumpadDriver NumpadDriver.cpp)
target_include_directories(NumpadDriver PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(NumpadDriver PRIVATE cxx_std_11)
target_link_libraries(NumpadDriver PUBLIC GPIO)

add_library(DisplayDriver DisplayDriver.cpp)
target_include_directories(DisplayDriver PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(DisplayDriver PRIVATE cxx_std_11)
target_link_libraries(DisplayDriver  PUBLIC GPIO)
