#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <iostream>
#include <unordered_map>

#include "definitions.h"

/*
 * This class represents an evaluator for the calculator.
 * It has one public method, execute(), which will execute
 * the instructions in the given list of instructions. This
 * method will return if it encountered a quit operation or
 * not.
 * 
 * The class uses a symbol table to keep track of the used
 * registers. This symbol table contains entries for all
 * previously used registers. Each entry is associated with
 * a list of the operations performed on the register, in
 * sequential order.
 *   This way of storing the instructions,
 * rather than just updating a stored value, is necessary
 * to support functionality for using a registry before it
 * is defined.
 *   For example, the following should print "1", but at the
 * time of adding b to a, the value (1) is still not known:
 *     a add b
 *     b add 1
 *     print a
 * 
 * The evaluator reads the instructions one by one, and
 * performs the necessary actions. If the instruction is a
 * quit instruction, a false value will be returned immediately.
 * If a print operation is encountered, the register value
 * will be evaluated and printed to the console. If an
 * arithmetic operation is encountered, it will be added
 * in the symbol table, to the register it was performed on.
 */
class Evaluator {

private:

    /* Definitions for how the register values are stored. */

    // The list of operations on a register consists of pairs of operands and values.
    typedef std::tuple<Operand, std::string> Operation;
    typedef std::vector<Operation> Operations;

    // The symbol table is implemented as a hash map, containing the stored registers (symbols)
    // and a list of the operands used on the register.
    typedef std::unordered_map<std::string, Operations> SymbolTable;

    // Symbol table holding all information about the used registers
    SymbolTable registers;

public:

    /* This method is the interface for using the evaluator.
     * It takes a list of instructions, and will execute them,
     * sequentially.
     *   This method can handle operations: print, quit, and
     * arithmetic operations (add, subtract, multiply).
     *   This method will remove all the instructions that
     * are executed.
     *   The return value is a boolean signifying if a quit
     * operation was encountered or not.
     *   And if a quit operation is encountered, this method
     * will return immediately, without executing any further
     * instructions. */
    bool execute(Instructions &instructions);

private:

    /* This method adds an operation to the given register.
     * The operation will contain the given operand and the
     * given value. */
    void addArithmeticOperation(Operand &op, std::string &reg, std::string &value);

    /* This method will evaluate the value of the given
     * register, and print it to the console.
     *   The value will only be printed if the evaluation
     * was successful. */
    void printRegister(std::string &reg);

    /* This method evaluates the numeric value of a string
     * represented value.
     *   This string can be either a numeric value (only digits),
     * or the name of a register (alphanumeric symbols).
     *   The resulting value will be stored in the given output
     * parameter 'outvalue'.
     *   If the value is a register name, it has to be a
     * previously defined one, otherwise it's an error.
     *   The method returns if the evaluation was successful
     * or not. If it wasn't successful, the 'outvalue' will
     * be unaltered, and an error message will be printed to
     * console. */
    bool evaluateValue(std::string &value, long &outvalue);

};

#endif // EVALUATOR_H

