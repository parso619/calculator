#include <iostream>
#include <fstream>

#include "parser.h"
#include "evaluator.h"

/* 
 * This is the main file for the calculator, which handles
 * the different steps of the interpretaion process.
 * 
 * The calculator is implemented in two steps, the parser
 * and the evaluator. Both of them are implemented as
 * separate classes. The main loop loops over each line
 * that the user puts in, via the console.
 *   The parser reads from an input stream and converts it to
 * a list of instructions. It reads the input as tokens,
 * where each token is separated by a space. Each token
 * is then identified (being an operation keyword, a
 * number, or a register name). And the order of the
 * tokens is analysed to determine what instruction the
 * user has put in. The instructions are stored in a
 * shared list, which is then passed to the evaluator.
 *   The evaluator takes the list of instructions and 
 * executes them. The instructions are now of three
 * types: arithmetic instruction (add, subtract, multiply),
 * print instruction, or quit instruction.
 *   The quit instruction immediately quits the program.
 * The print instruction evaluates a register expression
 * and prints it. And the arithmetic instruction adds
 * an arithmetic operation to the register it is
 * performed on (the expression is not evaluated
 * until a print is called).
 * 
 * Common definitions, about how tokens are defined,
 * and how instructions are defined and stored are
 * defined in a seaprate header, "definitions.h".
 * 
 * 
 * # Syntax
 * 
 * If an argument is passed to the program, this
 * will be treated as an input file. If no argument
 * is given, the input will be taken from the
 * console instead. (If the file could not be read,
 * the program will exit.)
 * 
 * The calculator can handle three types of input:
 * arithmetic operations on a register, printing a
 * register, and quitting.
 *   The syntax for the arithemtic operations is
 * as follows:
 *       <register> <operation> <value>
 * The register is a name identifier, consisting of
 * alphanumeric symbols (with at least one letter).
 * The operations is one of: 'add', 'subtract', 'multiply'.
 * And the value is either a numeric value, or the name
 * of a register. The name of the register does not have
 * to be defined before being used in an arithmetic
 * operation, but it has to be defined before it is needed
 * in a print operation.
 *   The syntax for a print operation is as follows:
 *       print <register>
 * The register (and all other registers that are needed
 * in the calculation if the register) needs to be defined
 * when trying to printing it.
 *   The syntax for the quit operation is:
 *       quit
 * 
 * Expressions are not evaluated until the user calls
 * a print operation, which is why registers do not have
 * to be defined until they are needed in a print statement.
 *   So, for example, the following is allowed (even though
 * b is not defined when used on the first line, it is
 * defined at the time of the print statement):
 *       a add b
 *       b add 1
 *       print a
 * 
 * When the input is taken from the user via the concole,
 * it is read one line at the time. This means that each
 * operation has to be finished by the end of the line.
 * This is not the case when reading from file (the whole
 * file is read in one go, so it does not matter where
 * there are line breaks).
 *   So you can't for example type:
 *       print
 *       a
 *   You would have to finish the operation on the same line:
 *       print a
 *   Though, it is possible to have several operations on
 * the same line, for example (this will print '5'):
 *       a add 5 print a
 * When using the quit operation, anything that appears after
 * the quit operation on the same line will be ignored.
 * 
 */
int main(int argc, char *argv[]) {

    // Class for parsing instructions from the command line
    Parser parser;

    // Class for evaluating loaded instructions
    Evaluator evaluator;

    // List of stored instructions, passed from the parser to the evaluator
    Instructions instructions;

    // Determine if there was any input file passed to the calculator
    // The first argument is the name of the executable
    // If there are any passed argument it 
    bool readFromFile = (argc >= 2);
    std::ifstream filestream;
    if (readFromFile) {
        std::string filename = argv[1];
        filestream.open(filename);
        // If the file could not be opened, exit the program
        if (filestream.fail()) {
            std::cout << "Could not open file: " << filename << std::endl;
            return 0;
        }
        std::cout << "Reading from file: " << filename << std::endl;
    }

    // Start a loop for reading the input lines
    // A flag signifying when
    bool running = true;
    while (running) {

        // Parse the input
        // Read from file or from the console
        if (readFromFile) {
            // Read the whole file, and parse it.
            // Since the program should quit after reading
            // the file, the running-flag is set to false.
            parser.parse(instructions, filestream);
            running = false;
        } else {
            // Read a line from console, and parse it.
            // We cannot send std::cin straight to the parser since std::cin waits
            // for more input. We want to evaluate the instructions after each line.
            // Since we want to read tokens from this line, we need it as a stream.
            std::string line;
            std::getline(std::cin, line);
            std::istringstream inputstream(line);
            parser.parse(instructions, inputstream);
        }

        // Execute the parsed instructions
        // If the running flag is already set to false, it should remain false
        running &= evaluator.execute(instructions);
    }

    return 0;
}

