# AStressfulMachine

A Stressful Machine is a programming game where the player has to write programs to solve challenges using the game's particularly arduous programming language.

The langage syntax is inspired by brainfuck's syntax (https://en.wikipedia.org/wiki/Brainfuck), it is however made higher level.

There is also a standalone interpreter for the game langage provided.

## The GUI executable

### Compilation and running

This is a C++17/Qt5 project, that was built to be as crossplatform as possible.
It was tested on both Linux (Ubuntu/Kubuntu) and Windows 10.

Please note that the data folder needs to be in the parent folder of the executable for it to properly work.
On Linux you just have to run it from its build folder, but on Windows you may need to move a few files around.

#### Linux

In order to compile it you need :
  - gcc-8
  - cmake >= 3.8
  - Qt5

On Ubuntu, you can use the apt install command and install the following packages: gcc-8, cmake, qt5-default, qtmultimedia5-dev.

You may also need: libqt5multimedia5-plugins.

To compile on linux, use command: "make a_stressful_machine_gui"

Afterwards, you can run the program by running 2 commands: 

cd build

./a_stressful_machine_gui

#### Windows

On Windows, you will need the Visual Studio 2019 compiler (older versions were not tested but may work)

Visual Studio / cmake should do the linking for you, but you should add your Qt's version bin and include folders to the PATH environment variable.

We tested with Qt 5.12.2 MSVC2017.
We had issues with the auto linker picking the wrong version of Qt when both x84 and x64 versions were installed, and we fixed it be deinstalling one of them. 

## The interpreter executable

The interpreter is an interpreter of the game's langage

### Compiling and running

The interpreter executable just needs C++17 (mostly for the filesystem lib).

The console executable needs at least one argument : the program to run.

You can add 

#### Linux

In order to compile it you need :
  - gcc-8
  - cmake >= 3.8

On Ubuntu, you can use the apt install command and install the following packages: gcc-8, cmake.

Then use command "make interpreter"

#### Windows

The VisualStudio compiler should be enough, however this executable was not tested on Windows (most of the code is shared with the GUI, and it does compile, so if it does not work it should be pretty easy to fix)

## Authors

Emile Trotignon - 11719286

Kader Askia - 11609837

Abdoul Rahime Barry - 11712599

Marcel Fodor - 11719949

## Credits

Icons are from https://icons8.com

Songs are from https://freesound.org/

The idea for the langage design is from https://en.wikipedia.org/wiki/Brainfuck

The gameplay idea is from https://tomorrowcorporation.com/humanresourcemachine
