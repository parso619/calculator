#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string>
#include <tuple>
#include <queue>
#include <vector>
#include <regex>

/*
 * This file contains definitions for the data structures that are shared
 * between the parser and the evaluator.
 * 
 * This includes definitions about the different tokens.
 * The supported tokens are:
 *  > The operand keywords: "add", "subtract", "multiply", "print", "quit".
 *  > Registers: strings containing alphanumeric symbols (with at least one letter symbol)
 *  > Numbers: strings containing only digits
 * 
 * It also includes definitions about how the instructions are stored.
 * The instructions are stored in tuples with three values:
 *     <operand> <register> <value>
 * The value can be either a numeric value, or a register name.
 * The print instruction has no <value>, and the quit instruction has no <value> or
 * <register>. These fields will then be empty in the tuple.
 */


/* Static functions for identifying the different tokens. */
namespace Token {

/* Return true if the input token is a quit operand. */
static bool isQuitOperand(std::string &in) {
    return !in.compare("quit");
}

/* Return true if the input token is a print operand. */
static bool isPrintOperand(std::string &in) {
    return !in.compare("print");
}

/* Return true if the input token is a add operand. */
static bool isAddOperand(std::string &in) {
    return !in.compare("add");
}

/* Return true if the input token is a subtract operand. */
static bool isSubtractOperand(std::string &in) {
    return !in.compare("subtract");
}

/* Return true if the input token is a multiply operand. */
static bool isMultiplyOperand(std::string &in) {
    return !in.compare("multiply");
}

/* Return true if the input token is any of the keyword operands. */
static bool isKeyword(std::string &in) {
    return ( isQuitOperand(in)
             || isPrintOperand(in)
             || isAddOperand(in)
             || isSubtractOperand(in)
             || isMultiplyOperand(in) );
}

/* Return true if the input token is a number. */
static bool isNumber(std::string &in) {
    std::regex regularexpression("[0-9]*");
    return std::regex_match(in, regularexpression);
}

/* Return true if the input token is a register name. */
static bool isRegister(std::string &in) {
    std::regex regularexpression("[a-zA-Z0-9]*");
    return ( std::regex_match(in, regularexpression)
             && !isNumber(in) && !isKeyword(in) );
}

};


/* Definitions of the instructions. */

// The calculator should support operands for addition, subtraction and multiplication,
// plus printing the result and quitting the calculator.
enum Operand {ADD, SUBTRACT, MULTIPLY, PRINT, QUIT};

// Instructions consists of an operand, a register, and a value.
// Note that the print operation has no value, and the quit operation has no register or value.
typedef std::tuple<Operand, std::string, std::string> Instruction;
// The instructions are stored in a queue, since they will always be evaluated in
// the same order they are parsed.
typedef std::queue<Instruction> Instructions;


#endif // DEFINITIONS_H

