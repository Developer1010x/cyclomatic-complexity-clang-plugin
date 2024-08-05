cmake_minimum_required(VERSION 3.10)
project(CyclomaticComplexityAnalysis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set LLVM and Clang directories
# These paths may vary depending on your system and installation method

# On Ubuntu, you may need to install the following packages:
# sudo apt update
# sudo apt install -y build-essential cmake llvm clang libclang-dev

# On macOS, you can use Homebrew to install the following:
# brew update
# brew install cmake llvm

# Set LLVM and Clang directories. Update these paths if necessary
# For Ubuntu or other systems, adjust accordingly.
set(LLVM_DIR "/usr/local/opt/llvm/lib/cmake/llvm")
set(Clang_DIR "/usr/local/opt/llvm/lib/cmake/clang")

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_definitions(${LLVM_DEFINITIONS})

add_library(CyclomaticComplexity SHARED
    src/CyclomaticComplexity.cpp
)

target_link_libraries(CyclomaticComplexity
    PRIVATE
    clang-cpp
    LLVM
)
