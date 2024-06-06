cmake_minimum_required(VERSION 3.5)
project(GUI_Calculator)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Set the include and library directories for GTK3 (assuming you meant GTK3, as you used 'gtk4')
set(GTK3_INCLUDE_DIRS "C:/msys64/mingw64/include/")
set(GTK3_LIBRARY_DIRS "C:/msys64/mingw64/lib")
set(ENV{PKG_CONFIG_PATH} "C:/msys64/mingw64/lib/pkgconfig")

# Find GTK4 package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# Include directories
include_directories(${GTK4_INCLUDE_DIRS} "C:/MyProjects/Calculator")

# Link directories
link_directories(${GTK4_LIBRARY_DIRS})

# Add definitions
add_definitions(${GTK4_CFLAGS_OTHER})

# Add executable with all the source files
add_executable(Calculator calculator.c)

# Set properties for the executable (optional: if you don't want the console to appear with your .exe)
set_target_properties(Calculator PROPERTIES WIN32_EXECUTABLE true)

# Link the GTK4 libraries
target_link_libraries(Calculator ${GTK4_LIBRARIES})