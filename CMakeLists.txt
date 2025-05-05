cmake_minimum_required(VERSION 3.10)
project(Counter17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenSSL for password hashing
find_package(OpenSSL REQUIRED)

# Main executable
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

# Test executable
add_executable(Counter17Tests
    tests/TestMain.cpp
    tests/GunTests.cpp
    tests/UnitTests.cpp
    tests/IntegrationTests.cpp
    tests/PerformanceTests.cpp
    src/Gun.cpp
    src/Player.cpp
    src/Terrorist.cpp
    src/CT.cpp
    src/GameMap.cpp
    src/GameManager.cpp
    src/User.cpp
    src/AuthSystem.cpp
)

# Link OpenSSL to both executables
target_link_libraries(Counter17 PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(Counter17Tests PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Create directories for main executable
add_custom_command(TARGET Counter17 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Counter17>/users
    COMMENT "Creating users directory"
)

# Create directories for test executable
add_custom_command(TARGET Counter17Tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Counter17Tests>/users
    COMMENT "Creating users directory for tests"
)

enable_testing()
add_test(NAME Counter17Tests COMMAND Counter17Tests)