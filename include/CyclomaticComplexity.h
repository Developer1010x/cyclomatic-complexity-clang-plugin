#ifndef CYCLOMATIC_COMPLEXITY_H
#define CYCLOMATIC_COMPLEXITY_H

// Include guards to prevent multiple inclusions of this header file
// CYCLOMATIC_COMPLEXITY_H is defined only if it hasn't been defined before
// This ensures the header is only included once per compilation unit

#include "clang/AST/ASTConsumer.h"  // Include the header for ASTConsumer, used for handling AST nodes
#include "clang/AST/RecursiveASTVisitor.h"  // Include the header for RecursiveASTVisitor, used for traversing the AST
#include "clang/Frontend/CompilerInstance.h"  // Include the header for CompilerInstance, which provides access to the Clang compiler
#include "clang/Frontend/FrontendAction.h"  // Include the header for FrontendAction, the base class for creating custom Clang actions
#include "clang/Tooling/Tooling.h"  // Include the header for Clang tooling, which provides utility functions for working with Clang

#include <map>  // Include the standard map container for storing key-value pairs
#include <string>  // Include the standard string class for handling text data

// Definition of the CyclomaticComplexityVisitor class
class CyclomaticComplexityVisitor : public clang::RecursiveASTVisitor<CyclomaticComplexityVisitor> {
private:
    clang::ASTContext *Context;  // Pointer to the ASTContext, which provides context for AST node processing
    std::map<std::string, int> ComplexityMap;  // Map to store the cyclomatic complexity of functions, keyed by function name

public:
    // Constructor that initializes the CyclomaticComplexityVisitor with a given ASTContext
    explicit CyclomaticComplexityVisitor(clang::ASTContext *Context);

    // Method to visit function declarations and compute cyclomatic complexity
    bool VisitFunctionDecl(clang::FunctionDecl *FD);

    // Method to count branching statements in a given statement
    int countBranchingStatements(clang::Stmt *S);

    // Method to print the computed cyclomatic complexity to standard output
    void printComplexity();
};

// Definition of the CyclomaticComplexityASTConsumer class
class CyclomaticComplexityASTConsumer : public clang::ASTConsumer {
private:
    CyclomaticComplexityVisitor Visitor;  // Instance of CyclomaticComplexityVisitor to process AST nodes

public:
    // Constructor that initializes the CyclomaticComplexityASTConsumer with a given ASTContext
    explicit CyclomaticComplexityASTConsumer(clang::ASTContext *Context);

    // Method to handle the translation unit, called once per source file
    void HandleTranslationUnit(clang::ASTContext &Context) override;
};

// Definition of the CyclomaticComplexityFrontendAction class
class CyclomaticComplexityFrontendAction : public clang::ASTFrontendAction {
public:
    // Method to create an ASTConsumer, which will be used to process the AST
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &CI, llvm::StringRef file) override;
};

#endif // CYCLOMATIC_COMPLEXITY_H
