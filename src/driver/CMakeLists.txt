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

