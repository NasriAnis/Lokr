cmake_minimum_required(VERSION 3.14)
project(MyProject C)

# 1. Dependency Management (No Global Install)
include(FetchContent)

# Fetch libsodium
FetchContent_Declare(
  libsodium
  GIT_REPOSITORY https://github.com/robinlinden/libsodium-cmake.git
  GIT_TAG        cfebfd3da486d5a86c644c8b47067e5411c7599c
)

# Fetch Argon2 (using a CMake-compatible wrapper)
FetchContent_Declare(
  Argon2
  GIT_REPOSITORY https://github.com
  GIT_TAG        main
)

FetchContent_MakeAvailable(libsodium Argon2)

# 2. External Tools (GTK4)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

# 3. Project Configuration
set(CMAKE_C_STANDARD 11)
include_directories(include)

# Define source groups based on your DIRS
file(GLOB COMMON_SRCS "src/*.c")
file(GLOB CLI_SRCS "cli/*.c")
file(GLOB GUI_SRCS "gui/*.c" "gui/windows/*.c")

# 4. Target: CLI (Default)
add_executable(myprog ${COMMON_SRCS} ${CLI_SRCS})
target_link_libraries(myprog PRIVATE sodium Argon2)

# 5. Target: GUI
add_executable(myprog_gui ${COMMON_SRCS} ${GUI_SRCS})
target_link_libraries(myprog_gui PRIVATE sodium Argon2 PkgConfig::GTK4)

