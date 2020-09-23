add_library(GPIO SHARED IMPORTED)
set_target_properties(GPIO PROPERTIES IMPORTED_LOCATION  ${PROJECT_SOURCE_DIR}/extern/lib_example/libGPIO.so)
target_include_directories(GPIO INTERFACE ${PROJECT_SOURCE_DIR}/extern/lib_example)
