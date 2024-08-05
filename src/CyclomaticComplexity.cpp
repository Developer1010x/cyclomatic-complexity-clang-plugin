#include <llvm/Support/CommandLine.h>
#include <llvm/Support/Debug.h>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream> // Include fstream for file operations

#include "clang/AST/Expr.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/FileManager.h"
#include "clang/Frontend/CompilerInstance.h"
#include "llvm/Support/raw_ostream.h"

#include <map>
#include <string>

using namespace clang;

// Define a visitor class to traverse the AST nodes
class CyclomaticComplexityVisitor : public RecursiveASTVisitor<CyclomaticComplexityVisitor> {
private:
    ASTContext *context; // Pointer to the AST context
    CompilerInstance& instance; // Reference to the CompilerInstance
    DiagnosticsEngine& d; // Reference to DiagnosticsEngine for reporting issues
    unsigned int remarkID; // ID for custom diagnostic remarks
    std::map<std::string, int> ComplexityMap; // Map to store function names and their complexities

    // Check if a declaration is in a header file
    bool isInHeader(Decl *decl) {
        auto loc = decl->getLocation(); // Get the location of the declaration
        auto floc = context->getFullLoc(loc); // Get the full location information
        if (floc.isInSystemHeader()) return true; // Check if it's in a system header
        auto entry = floc.getFileEntry()->getName(); // Get the file name
        if (entry.ends_with(".h") || entry.ends_with(".hpp")) {
            return true; // Check if the file has a header extension
        }
        return false;
    }

    // Report the cyclomatic complexity of a function
    void reportCyclomaticComplexity(FunctionDecl *func, int complexity) {
        auto loc = context->getFullLoc(func->getLocation()); // Get the full location of the function
        d.Report(loc, remarkID) << complexity; // Report the complexity with a custom diagnostic
    }

    // Calculate cyclomatic complexity of a statement
    int calculateCyclomaticComplexity(const Stmt *stmt) {
        if (!stmt) {
            std::cout << "Null statement encountered!\n";
            return 0;
        }
        int complexity = 1; // Start with 1 for the function itself
        complexity += countBranchingStatements(stmt); // Add complexity based on branching statements
        return complexity;
    }

    // Count branching statements in a statement
    int countBranchingStatements(const Stmt *stmt) {
        int count = 0;
        if (isa<IfStmt>(stmt) || isa<SwitchStmt>(stmt) || isa<ForStmt>(stmt) ||
            isa<WhileStmt>(stmt) || isa<DoStmt>(stmt) || isa<ConditionalOperator>(stmt)) {
            count++; // Increment count for each branching statement
        }
        for (auto child : stmt->children()) {
            if (child) {
                count += countBranchingStatements(child); // Recursively count branching statements in child nodes
            }
        }
        return count;
    }

public:
    // Constructor for CyclomaticComplexityVisitor
    explicit CyclomaticComplexityVisitor(ASTContext *context, CompilerInstance& instance)
        : context(context), instance(instance), d(instance.getDiagnostics()) {
        remarkID = d.getCustomDiagID(DiagnosticsEngine::Remark, "Cyclomatic Complexity: %0");
    }

    // Visit each function declaration in the AST
    virtual bool VisitFunctionDecl(FunctionDecl *func) {
        if (isInHeader(func))
            return true; // Skip header files

        if (func->hasBody()) {
            int complexity = calculateCyclomaticComplexity(func->getBody()); // Calculate complexity
            ComplexityMap[func->getNameAsString()] = complexity; // Store complexity in the map
            reportCyclomaticComplexity(func, complexity); // Report the complexity
        }
        return true;
    }

    // Write cyclomatic complexity results to a file
    void writeComplexityToFile(const std::string &filename) {
        std::ofstream outFile(filename); // Open the file for writing
        if (!outFile.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        for (const auto &entry : ComplexityMap) {
            outFile << "Function: " << entry.first << ", Cyclomatic Complexity: " << entry.second << std::endl;
        }
        outFile.close(); // Close the file after writing
    }
};

// Define a consumer class to handle the translation unit
class CyclomaticComplexityConsumer : public ASTConsumer {
    CompilerInstance& instance; // Reference to the CompilerInstance
    CyclomaticComplexityVisitor visitor; // CyclomaticComplexityVisitor instance

public:
    // Constructor for CyclomaticComplexityConsumer
    CyclomaticComplexityConsumer(CompilerInstance& instance)
        : instance(instance), visitor(&instance.getASTContext(), instance) {}

    // Handle the translation unit
    virtual void HandleTranslationUnit(ASTContext &context) override {
        visitor.TraverseDecl(context.getTranslationUnitDecl()); // Traverse the AST
        visitor.writeComplexityToFile("results.cy"); // Write results to a file
    }
};

// Define the plugin action class
class CyclomaticComplexityAction : public PluginASTAction {
protected:
    // Create an ASTConsumer for the plugin
    virtual std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance& instance, llvm::StringRef) override {
        return std::make_unique<CyclomaticComplexityConsumer>(instance);
    }

    // Parse arguments for the plugin
    virtual bool ParseArgs(const CompilerInstance&, const std::vector<std::string>&) override {
        return true;
    }

    // Define the action type for the plugin
    virtual PluginASTAction::ActionType getActionType() override {
        return PluginASTAction::AddAfterMainAction;
    }
};

// Register the plugin with Clang
static FrontendPluginRegistry::Add<CyclomaticComplexityAction> X("cyclomatic-complexity", "Calculate cyclomatic complexity of functions");
