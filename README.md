 -- Compiler
VS code

 -- setups
cmake
mingw

 -- Add mingw path to system
C:\mingw32\bin (path) Starting address can vary PC to PC

Steps:
1. (Open) Edit System Environment variables
2. (Select) Environment variable
3. (In) System Variables (Add) C:\mingw32\bin 

 -- Packages
mingw32-base (bin)
mingw32-gcc-g++ (bin)
mingw32-gcc (bin)

 -- Verify installation and setting of Packages by typing these commands in VS terminal or cmd
cmake --version
g++ --version

 -- Run Commands in VS terminal or cmd to compile the project and make an exe file of project
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
.\MiniUber.exe