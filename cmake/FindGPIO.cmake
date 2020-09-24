add_library(GPIO INTERFACE)
target_include_directories(GPIO INTERFACE ${PROJECT_SOURCE_DIR}/extern/lib_example)
target_link_directories(GPIO INTERFACE ${PROJECT_SOURCE_DIR}/extern/lib_example)
target_link_options(GPIO INTERFACE -lGPIO)
