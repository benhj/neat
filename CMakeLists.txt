cmake_minimum_required (VERSION 3.1)
project (neat)

# put all source code in one place for convenience
file(GLOB_RECURSE neat neat/src/*.cpp neat/include/*.hpp)

# ensure headers in the src folder are compiler-found
include_directories(neat/include)

# break above sub-folders into individual libraries
add_library(neat_lib ${neat})

# compile options. Lots of redundancy here. Can prob clean up.
set(COMP_FLAGS -std=c++14 -O3 -ffast-math -funroll-loops -Wno-ctor-dtor-privacy -fno-pic)
target_compile_options(neat_lib PUBLIC ${COMP_FLAGS})
