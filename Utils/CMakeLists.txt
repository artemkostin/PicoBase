add_subdirectory(Heartbeat)
target_include_directories(PicoBase PUBLIC Heartbeat)

add_subdirectory(DevInfo)
target_include_directories(PicoBase PUBLIC DevInfo)
