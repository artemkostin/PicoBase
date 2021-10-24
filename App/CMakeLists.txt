add_subdirectory(CLI)
add_subdirectory(MODBUS)
target_include_directories(PicoBase PUBLIC CLI PUBLIC MODBUS)