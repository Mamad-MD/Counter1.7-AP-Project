cmake_minimum_required(VERSION 3.10)
project(Counter17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenSSL for password hashing
find_package(OpenSSL REQUIRED)

# Add executable
add_executable(Counter17
    src/main.cpp
    src/Gun.cpp
    src/Player.cpp
    src/Terrorist.cpp
    src/CT.cpp
    src/GameMap.cpp
    src/GameManager.cpp
    src/User.cpp
    src/AuthSystem.cpp
    src/MenuSystem.cpp
)

# Link OpenSSL
target_link_libraries(Counter17 PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Copy assets and create directories
add_custom_command(TARGET Counter17 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Counter17>/users
    COMMENT "Creating users directory"
)