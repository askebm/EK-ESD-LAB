add_subdirectory(driver)

add_library(logger Logger.cpp)
target_include_directories(logger PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(logger PUBLIC cxx_std_11)
