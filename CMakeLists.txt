cmake_minimum_required(VERSION 3.10)

# Enable vcpkg integration
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(AuthServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Add source files
file(GLOB SOURCES 
    src/*.cpp
    src/include/*.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${OPENSSL_INCLUDE_DIR}
    src/include
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${OPENSSL_LIBRARIES}
)

# Add SQLite3 static library
add_library(sqlite3 STATIC 
    extern/sqlite/sqlite3.c
)

target_include_directories(sqlite3 PUBLIC 
    extern/sqlite
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
    sqlite3
)