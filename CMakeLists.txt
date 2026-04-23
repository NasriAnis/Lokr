cmake_minimum_required(VERSION 3.14)
project(MyProject C)

# 1. Dependency Management (No Global Install)
include(FetchContent)

# Fetch libsodium
FetchContent_Declare(
    libsodium
    GIT_REPOSITORY https://github.com/robinlinden/libsodium-cmake.git
    GIT_TAG        cfebfd3da486d5a86c644c8b47067e5411c7599c  # pinned commit
)

# Fetch Argon2
FetchContent_Declare(
    Argon2
    GIT_REPOSITORY https://github.com/P-H-C/phc-winner-argon2
    GIT_TAG        20190702  # latest stable release tag, not master
)

FetchContent_MakeAvailable(libsodium Argon2)

# 2. System-only: GTK4 (cannot be bundled, must be system)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

# 3. Project Configuration
set(CMAKE_C_STANDARD 11)
include_directories(include)

# 4. Source groups
file(GLOB COMMON_SRCS "src/*.c")
file(GLOB CLI_SRCS    "cli/*.c")
file(GLOB GUI_SRCS    "gui/*.c" "gui/windows/*.c")

# 5. Target: CLI (Default)
add_executable(lokr ${COMMON_SRCS} ${CLI_SRCS})
target_link_libraries(lokr PRIVATE sodium argon2)

# 6. Target: GUI
add_executable(lokr_gui ${COMMON_SRCS} ${GUI_SRCS})
target_link_libraries(lokr_gui PRIVATE sodium argon2 PkgConfig::GTK4)
