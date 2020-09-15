add_executable(scannerHMI scannerHMI.cpp)
target_compile_features(scannerHMI PRIVATE cxx_std_11)

target_link_libraries(scannerHMI PRIVATE scanner)

