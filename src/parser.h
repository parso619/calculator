#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <sstream>
#include <algorithm>

#include "definitions.h"

/*
 * This class represents a parser for parsing the calculator
 * input, and creating a list of instructions.
 * 
 * The parser will read from the input stream, and divide
 * it into tokens (separated by spaces or linebreaks).
 *   The parser acts as a very simple state machine, and
 * since there are very few instructions to take care of,
 * this state machine can be implemented as else-if-statements.
 * 
 * There are three types of tokens: keywords (quit, print,
 * add, subtract, multiply), numbers (string of digits),
 * and register names (string of alphanumeric symbols).
 * 
 * There are only three different types of operations the input
 * can consist of: arthmetic operations, printing operations
 * and a quitting operation. All of them can be identified
 * by their first token.
 *   The quit operation only consists of the token 'quit' (keyword).
 *   The print operation starts with the token 'print' (keyword),
 * and must be followed by a register name.
 *   The arithmetic operations start with a register name,
 * followed by an arithpetic operand ('add', 'subtract', 'multiply'),
 * and lastly a value (another register name, or a numeric value).
 *   All other syntaxes will lead to an error message written
 * to the console.
 * 
 * The instructions are stored as tuples with three values:
 * operand, register, value. The quit instruction has empty
 * register and value fileds, and the print instruction has
 * an empty value field.
 */
class Parser {

public:

    /* This method is the interface for using the parser.
     * It will read from a stream, and parse it
     * to create a list of instructions. The instructions
     * are stored sequentially in the given instruction
     * list.
     *   There are three kind of operations that are supported.
     * These consists of tokens as follows:
     *    > arithmetic operations
     *        <register> <operand> <value>
     *    > printing operations
     *        print <register>
     *    > quit operations
     *        quit
     * 
     * The <register> is a register name token. The <value>
     * is either a register name token or a numeric token.
     * 'quit' and 'print' are keywords, and <operand> is
     * any one of the three keywords: 'add', 'subtract', 'multiply'.
     * 
     * The parser will read one token at a time (no look-ahead
     * is needed, since there is no ambiguity about the instruction
     * prefixes). If the token is 'exit' an exit instruction is
     * added to the instruction list. If the token is 'print',
     * the next token is read and checked to be a register, and
     * then a print instruction is added to the list. If the
     * token is a register name, the two following tokens are read,
     * and assumed to be an operand and a value. An arithmetic
     * operation is then added to the instruction list.
     * If the syntax is not followed, an error message will be
     * written to the console, and no errenous instruction will
     * be added to the instruction list. */
    void parse(Instructions &instructions, std::istream &inputstream);

private:

    /* Helper functions for parsing the second token, for when a
     * print instruction has been encounterd. */
    void parsePrintInstruction(Instructions &instructions, std::istream &inputstream);

    /* Helper functions for parsing the second and third tokens,
     * for when an arithmetic instruction has been encounterd. */
    void parseArithmeticInstruction(Instructions &instructions, std::istream &inputstream, std::string reg);

    /* Read the next token, and return true if successful,
     * otherwise return false. */
    bool readToken(std::istream &inputstream, std::string &out);

    /* Read the next token, and return true if it is a quit token,
     * otherwise return false. */
    bool readQuitOperand(std::istream &inputstream);

    /* Read the next token, and return true if it is a print token,
     * otherwise return false. */
    bool readPrintOperand(std::istream &inputstream);

    /* Read the next token, and return true if it is an arithmetic
     * operation token, otherwise return false.
     * The given output value will contain which token was read
     * (and will be unaltered if no arithmetic operation was read). */
    bool readArithmeticOperand(std::istream &inputstream, Operand &out);

    /* Read the next token, and return true if it is a register name token,
     * otherwise return false.
     * The given output value will contain the read token
     * (and will be unaltered if no register name token was read). */
    bool readRegister(std::istream &inputstream, std::string &out);

    /* Read the next token, and return true if it is a value token,
     * otherwise return false.
     * (A value token can be either a number, or a register name.)
     * The given output value will contain the read token
     * (and will be unaltered if no value token was read). */
    bool readValue(std::istream &inputstream, std::string &out);

    /* Adds an instruction to the list of instruction, with the
     * given tuple values. */
    void addInstruction(Instructions &instructions,
                        Operand op, std::string reg = "", std::string val = "");

};

#endif // PARSER_H

