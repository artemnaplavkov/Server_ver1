﻿# CMakeList.txt : CMake project for server, include source and define
# project specific logic here.
#

include_directories("../../")

# Add source to this project's executable.
add_executable (server "server.cpp" "../../socket.h" "../../socket.cpp" "../../store.h" "../../store.cpp" "../../menu.h" "../../menu.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET server PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
