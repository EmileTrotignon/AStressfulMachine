# AStressfulMachine

A Stressful Machine is a programming game where the player has to write programs to solve challenges using the game's particularly arduous programming language.

## The GUI executable

### Compilation

This is a C++17/Qt5 project, that was built to be as crossplatform as possible.
It was tested on both Linux (Ubuntu/Kubuntu) and Windows 10.

#### Linux

In order to compile it you need :
  - gcc-8
  - cmake >= 3.8
  - Qt5

On Ubuntu, you can use the apt install command and install the following packages: gcc-8, cmake, qt5-default, qtmultimedia5-dev.

You may also need: libqt5multimedia5-plugins.

To compile on linux, use command: make a_stressful_machine_gui

Afterwards, you can run the program by running 2 commands: 

cd build

./a_stressful_machine_gui

#### Windows

On Windows, you will need the Visual Studio 2019 compiler (older versions were not tested but may work)

Visual Studio / cmake should do the linking for you, but you should add your Qt's version bin and include folders to the PATH environment variable.

We tested with Qt 5.12.2 MSVC2017.
We had issues with the auto linker picking the wrong version of Qt when both x84 and x64 versions were installed, and we fixed it be deinstalling one of them. 

##

## Authors

Emile Trotignon - 11719286

Kader Askia - 11609837

Abdoul Rahime Barry - 11712599

Marcel Fodor - 11719949

## Credits

Icons are from icons8.com

Songs are from https://freesound.org/
