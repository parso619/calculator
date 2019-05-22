#include "parser.h"

void Parser::parse(Instructions &instructions, std::istream &inputstream) {

    // Read all tokens in the input
    std::string input;
    while ( readToken(inputstream, input) ) {

        // Determine which type of expression, there are three types:
        //  * Quit ('quit' keyword)
        //  * Print ('print' keyword followed by register)
        //  * Operation on a register (register followed by operand and value)
        if (Token::isQuitOperand(input)) {
            addInstruction(instructions, QUIT);
        } else if (Token::isPrintOperand(input)) {
            parsePrintInstruction(instructions, inputstream);
        } else if (Token::isRegister(input)) {
            parseArithmeticInstruction(instructions, inputstream, input);
        } else {
            std::cout << "Syntax Error: '" << input << "' is an invalid start of expression." << std::endl;
        }
    }
}

void Parser::parsePrintInstruction(Instructions &instructions, std::istream &inputstream) {
    // Read the second token, the register name, and add the instruction
    std::string reg;
    if ( readRegister(inputstream, reg) ) {
        addInstruction(instructions, PRINT, reg);
    } else {
        std::cout << "Syntax Error: 'print' must be followed by a register." << std::endl;
    }
}

void Parser::parseArithmeticInstruction(Instructions &instructions, std::istream &inputstream, std::string reg) {
    // Read the next two tokens (always read both of them).
    // If successful, add the instruction, else print error messages.

    Operand op;
    bool readOperandSucess = readArithmeticOperand(inputstream, op);

    std::string value;
    bool readValueSuccess = readValue(inputstream, value);

    if (readOperandSucess && readValueSuccess) {
        addInstruction(instructions, op, reg, value);
    }

    if (!readOperandSucess) {
        std::cout << "Syntax Error: Missing or invalid operand after register '" << reg << "'." << std::endl;
    }
    if (!readValueSuccess) {
        std::cout << "Syntax Error: Missing or invalid value after operand." << std::endl;
    }
}

bool Parser::readToken(std::istream &inputstream, std::string &out) {
    // Read a token and return if it is was successful or not.
    std::string token;
    if ( inputstream >> token ) {
        // The syntax is case insensitive, so change to lower case
        std::transform(token.begin(), token.end(), token.begin(), ::tolower);
        out = token;
        return true;
    }
    return false;
}

bool Parser::readQuitOperand(std::istream &inputstream) {
    // Read a token and return if it is a quit token or not.
    std::string op;
    return ( readToken(inputstream, op) && Token::isQuitOperand(op) );
}

bool Parser::readPrintOperand(std::istream &inputstream) {
    // Read a token and return if it is a print token or not.
    std::string op;
    return ( readToken(inputstream, op) && Token::isPrintOperand(op) );
}

bool Parser::readArithmeticOperand(std::istream &inputstream, Operand &out) {
    // Read a token and return if it is an arithmetic operation or not.
    // Also set the output value to the read operation.
    std::string op;
    if ( readToken(inputstream, op) ) {
        if ( Token::isAddOperand(op) ) {
            out = ADD;
            return true;
        } else if ( Token::isSubtractOperand(op) ) {
            out = SUBTRACT;
            return true;
        } else if ( Token::isMultiplyOperand(op) ) {
            out = MULTIPLY;
            return true;
        }
    }
    return false;
}

bool Parser::readRegister(std::istream &inputstream, std::string &out) {
    // Read a token and return if it is a register name or not.
    // Also set the output value to the read register name.
    std::string reg;
    if ( readToken(inputstream, reg) && Token::isRegister(reg) ) {
        out = reg;
        return true;
    }
    return false;
}

bool Parser::readValue(std::istream &inputstream, std::string &out) {
    // Read a token and return if it is a value token (a register name
    // or a number) or not.
    // Also set the output value to the read value token.
    std::string val;
    if ( readToken(inputstream, val) && ( Token::isNumber(val) || Token::isRegister(val) ) ) {
        out = val;
        return true;
    }
    return false;
}

void Parser::addInstruction(Instructions &instructions, Operand op, std::string reg, std::string val) {
    Instruction ins = std::make_tuple(op, reg, val);
    instructions.push(ins);
}

