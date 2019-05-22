#include "evaluator.h"

bool Evaluator::execute(Instructions &instructions) {
    // Go through all instructions sequentially,
    // and determine which operation should be
    // performed.
    //   (The executed instructions should be removed
    // from the instruction list.)
    while ( !instructions.empty() ) {
        // Get instruction
        Instruction intructions = instructions.front();
        instructions.pop(); // Remove instruction

        // Get the fields of the instruction tuple
        Operand op = std::get<0>(intructions);
        std::string reg   = std::get<1>(intructions);
        std::string value = std::get<2>(intructions);

        // Determine which operation to execute
        switch (op) {
            case QUIT:
                return false;
                break;
            case PRINT:
                printRegister(reg);
                break;
            case ADD:
            case SUBTRACT:
            case MULTIPLY:
                addArithmeticOperation(op, reg, value);
                break;
        }

    }
    return true;
}

void Evaluator::addArithmeticOperation(Operand &op, std::string &reg, std::string &value) {
    // Add the given operand and value to the
    // symbol table entry for the given register.
    // If the register is not in the symbol table,
    // it should be added.
    Operations operations = registers[reg];
    Operation operation = std::make_tuple(op, value);
    operations.push_back(operation);
    registers[reg] = operations;
}

void Evaluator::printRegister(std::string &reg) {
    // Evaluate what the value of the register is
    // and, if successful, print the value.
    long value;
    if (evaluateValue(reg, value)) {
        std::cout << value << std::endl;
    }
}

bool Evaluator::evaluateValue(std::string &value, long &outvalue) {

    // If the value is a number, set the output and return.
    if (Token::isNumber(value)) {
        outvalue = std::stol(value);
        return true;
    }
    // If it's not a number, it has to be a register.
    // If there is no register with the given name in
    // the symbol table, return failure.
    if (registers.find(value) == registers.end()) {
        std::cout << "Lookup Error: No register named '" << value << "'." << std::endl;
        return false;
    }
    // If the register is defined in the symbol table,
    // then retrieve it and go through the operations that
    // are associated with it.
    long res = 0;
    Operations operations = registers[value];
    for (Operation operation : operations) {
        // Retrieve the operand and value of the operation
        Operand operand   = std::get<0>(operation);
        std::string operandvalue = std::get<1>(operation);

        // Recursively evaluate the value
        long val;
        if (!evaluateValue(operandvalue, val)) return false;
        // If the evaluation was successful, perform the operation
        switch (operand) {
            case ADD:
                res += val;
                break;
            case SUBTRACT:
                res -= val;
                break;
            case MULTIPLY:
                res *= val;
                break;
        }
    }

    outvalue = res;
    return true;
}

