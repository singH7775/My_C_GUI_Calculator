cmake_minimum_required(VERSION 3.5)
project(GUI_Calculator)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Find GTK4 package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# Include directories
include_directories(${GTK4_INCLUDE_DIRS})

# Link directories
link_directories(${GTK4_LIBRARY_DIRS})

# Add definitions
add_definitions(${GTK4_CFLAGS_OTHER})

# Add executable with all the source files
add_executable(Calculator calculator.c)

# Link the GTK4 libraries and math library
target_link_libraries(Calculator ${GTK4_LIBRARIES} m)