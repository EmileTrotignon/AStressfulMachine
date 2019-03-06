# CMake project wrapper
# https://stackoverflow.com/questions/11143062/getting-cmake-to-build-out-of-source-without-wrapping-scripts

MKDIR := mkdir -p
CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=Release

all: ./build/Makefile
	@ $(MAKE) -C build

./build/Makefile: CMakeLists.txt
	@ ($(MKDIR) build)
	(cd build && cmake $(CMAKE_FLAGS) ..)

.PHONY: clean
clean:
	rm -r build/CMake*
	rm -r build/cmake*

ifeq ($(findstring clean, $(MAKECMDGOALS)),)
$(MAKECMDGOALS): ./build/Makefile
	@ $(MAKE) -C build $(MAKECMDGOALS)
endif

doc: src/*.h
	@ ($(MKDIR) doc)
	@ (cd doc && doxygen doxyconfig)
	@ $(MAKE) -C doc/latex
