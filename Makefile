# CMake project wrapper
# https://stackoverflow.com/questions/11143062/getting-cmake-to-build-out-of-source-without-wrapping-scripts

MKDIR := mkdir -p

all: ./build/Makefile
	@ $(MAKE) -C build

./build/Makefile: CMakeList.txt
	@ ($(MKDIR) build)
	(cd build && cmake ..)

.PHONY: clean
clean:
	rm -r build/CMake*
	rm -r build/cmake*

ifeq ($(findstring clean, $(MAKECMDGOALS)),)
$(MAKECMDGOALS): ./build/Makefile
	@ $(MAKE) -C build $(MAKECMDGOALS)
endif
