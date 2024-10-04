This is a graphical calculator that I have been able to create using the GTK4 api, most functions are pretty default, providing operations such as add, subtract, multiply, divide, and mod operator.

(I personally built and ran this in the VSCode text editor using CMake)

How to run : 

WINDOWS :

Before you begin, ensure you have met the following requirements:

Windows 10 or later
MSYS2 (provides a Unix-like environment on Windows)
CMake (for building the project)
Git (for cloning the repository)

Installation Steps

Install MSYS2:

Download the installer from MSYS2 website
Run the installer and follow the prompts

Set up MSYS2:

Open MSYS2 MinGW 64-bit from the Start menu
Update the package database and core system packages:

pacman -Syu

Close the terminal when prompted, then reopen it and run:

pacman -Su

Install required packages:

pacman -S mingw-w64-x86_64-gtk4 mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake make

Install CMake:

Download the latest CMake installer from the official CMake website
Run the installer
Choose the option to add CMake to the system PATH for all users or the current user
Complete the installation

Clone the repository:
git clone https://github.com/singH7775/My_C_GUI_Calculator.git
cd My_C_GUI_Calculator

Build the project:

mkdir build

cd build

cmake -G "MSYS Makefiles" ..

make

Running the Application
After building, you can run the application from the build directory:

./Calculator.exe

---------------------------------------------------------------------------------------------------

Mac : 

Before you begin, ensure you have met the following requirements:

macOS 10.15 (Catalina) or later
Xcode Command Line Tools
Homebrew (for installing dependencies)
Git (for cloning the repository)

Installation Steps

Install Xcode Command Line Tools:
Open Terminal and run:

xcode-select --install

Install Homebrew:
If you don't have Homebrew installed, run:

/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

Install required packages:
brew install gtk4
brew install cmake

Clone the repository:
git clone https://github.com/singH7775/My_C_GUI_Calculator.git
cd My_C_GUI_Calculator

Build the project:

mkdir build

cd build

cmake ..

make

After building, you can run the application from the build directory:
./Calculator

---------------------------------------------------------------------------------------------------

Linux (Ubuntu) : 

Before you begin, ensure you have met the following requirements:

Ubuntu 20.04 LTS or later
Terminal access
Sudo privileges

Installation Steps

Update your system:
sudo apt update
sudo apt upgrade

Install required packages:
sudo apt install build-essential git cmake

Install GTK4 development files:
sudo apt install libgtk-4-dev

Verify CMake installation:
cmake --version
If CMake is not installed or you need a newer version, you can install it via:
sudo apt install cmake

Clone the repository:
git clone https://github.com/singH7775/My_C_GUI_Calculator.git
cd My_C_GUI_Calculator

Build the project:

mkdir build

cd build

cmake ..

make

Running the Application
After building, you can run the application from the build directory:

./Calculator

---------------------------------------------------------------------------------------------------

Troubleshooting

- Ensure all GTK4 Packages are installed and your build path is finding them
- Ensure CMake is installed and configured correctly
- Ensure the tasks.json and properties.json are setup correctly to include the libraries needed to build the application


Windows : https://www.gtk.org/docs/installations/windows
Mac : https://www.gtk.org/docs/installations/macos
Linux : https://www.gtk.org/docs/installations/linux
