# Cyclomatic Complexity Tool



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

## License

This project is licensed under the [MIT License](LICENSE).
