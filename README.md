# Cyclomatic Complexity Tool

# Cyclomatic Complexity Clang Plugin

## Overview

This project demonstrates how to create a Clang plugin for calculating cyclomatic complexity. It provides step-by-step instructions for setting up the project, building it, and testing it on macOS.

## Prerequisites

- macOS
- Clang and LLVM installed via Homebrew
- CMake
- Git

## Overview

The Cyclomatic Complexity Tool traverses the Abstract Syntax Tree (AST) of C++ code to calculate and report the cyclomatic complexity of each function. Cyclomatic complexity is a software metric used to indicate the complexity of a program by counting the number of linearly independent paths through its source code. This metric helps in understanding the intricacy of a function and, consequently, the overall complexity of the program.

## Features

- **AST Traversal**: Uses a `RecursiveASTVisitor` to traverse the AST of the C++ code.
- **Complexity Calculation**: Computes the cyclomatic complexity of each function by counting decision points (branching statements).
- **Reporting**: Outputs the cyclomatic complexity as a remark within the code.
- **File Output**: Writes the cyclomatic complexity of each function to a file for easy access and review.

## Usage

1. **Compile the Tool**: Follow the instructions in the `CMakeLists.txt` to compile the plugin.
2. **Run the Tool**: Use `clang++` to run the tool and analyze your C++ code.
3. **Review the Output**: Check the output file to review the cyclomatic complexity of each function.

## Credits

This tool was created with considerable effort by [Krishnatejaswi S](https://www.github.com/KTS-o7). If you find this code useful, please consider giving credit and starring the repository on GitHub.


Feel free to fork this repository, improve it, and submit a pull request. For any questions or contributions, you can reach out via:

- [Email](mailto:shentharkrishnatejaswi@gmail.com)
- [LinkedIn](https://www.linkedin.com/in/krishnatejaswi-shenthar/)
- [GitHub](https://www.github.com/KTS-o7)


I @developer1010x have editted the code for macos based complier(darwin) most codelines of .cpp and .h will remain same

## License

This project is licensed under the [MIT License](LICENSE).

## Setup Instructions

 ```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
xcode-select --install
clang --version
brew install llvm
export PATH="/usr/local/opt/llvm/bin:$PATH"
export LDFLAGS="-L/usr/local/opt/llvm/lib"
export CPPFLAGS="-I/usr/local/opt/llvm/include"
source ~/.zshrc
# or
source ~/.bash_profile
llvm-config --version
sw_vers

1. Clone the Repository

cd ~/Desktop
mkdir CyclomaticComplexityPlugin
cd CyclomaticComplexityPlugin
git clone https://github.com/KTS-o7/cyclomatic-complexity-clang-plugin.git
(MacOSX < x > MacOS 13.02)
or
https://github.com/Developer1010x/cyclomatic-complexity-clang-plugin.git
(MacOS 12 =< )
cd cyclomatic-complexity-clang-plugin
mkdir build
cd build
export LLVM_DIR=/usr/local/opt/llvm/lib/cmake/llvm
export CLANG_DIR=/usr/local/opt/llvm/lib/cmake/clang
cmake ..
mkdir -p ../test
cd ../test
cd /Users/sprajwalln/Desktop/<dir name>/cyclomatic-complexity-clang-plugin

cd test
/usr/local/opt/llvm/bin/clang++ -fplugin=/Users/<dir name>/ cyclomatic-complexity-clang-plugin/build/libCyclomaticComplexity.dylib -o sample sample.cpp

or

/usr/local/opt/llvm/bin/clang++ -fplugin=/Users/<dir name>/ cyclomatic-complexity-clang-plugin/build/libCyclomaticComplexity.so -o sample sample.cpp

cat result.cy
```

