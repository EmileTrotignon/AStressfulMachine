# CMake project wrapper
# https://stackoverflow.com/questions/11143062/getting-cmake-to-build-out-of-source-without-wrapping-scripts

COMPILER := g++-8
MKDIR := mkdir -p
CMAKE_FLAGS := -D CMAKE_BUILD_TYPE=Debug -D CMAKE_CXX_COMPILER=$(COMPILER)

all: ./build/Makefile
	@ $(MAKE) -C build

./build/Makefile: CMakeLists.txt
	@ ($(MKDIR) build)
	(cd build && cmake $(CMAKE_FLAGS) ..)

.PHONY: clean
clean:
	rm -r build/CMake*
	rm -r build/cmake*

.PHONY: superclean
superclean:
	rm -r build
	rm -r cmake-build-debug

ifeq ($(findstring clean, $(MAKECMDGOALS)),)
ifeq ($(findstring doc, $(MAKECMDGOALS)),)
$(MAKECMDGOALS): ./build/Makefile
	@ $(MAKE) -C build $(MAKECMDGOALS)
endif
endif

doc: src/*.h
	@ ($(MKDIR) doc)
	@ (cd doc && doxygen doxyconfig)
	@ $(MAKE) -C doc/latex
