#ifndef OPENENGINE_CALCULATIONS_H
#define OPENENGINE_CALCULATIONS_H

//! Calculator namespace that provides some simple calculation operations.
//!
//! @version 1.0.0
//! @pre Understand math and templates.
//! @bug There are *no* bugs!
//! @copyright GNU Public License
//! @date 1989-2018
//! @author jyates
//!
namespace Calculator {

//! Add two numbers together and get a result.
//!
//! @tparam U Type for left hand operand.
//! @tparam V Type for right hand operand.
//!
//! @param operandA Value for left hand operand.
//! @param operandB Value for right hand operand.
//!
//! @return Result of adding two operands together.
//!
template<typename U, typename V>
U add(U operandA, V operandB) {
    return operandA + operandB;
}

//! Subtract two numbers together and get a result.
//!
//! @tparam U Type for left hand operand.
//! @tparam V Type for right hand operand.
//!
//! @param operandA Value for left hand operand.
//! @param operandB Value for right hand operand.
//!
//! @return Result of performing subtraction on two operands.
//!
template<typename U, typename V>
U sub(U operandA, V operandB) {
    return operandA - operandB;
}

};

#endif //OPENENGINE_CALCULATIONS_H
