# TP1: Stack Data Structure

This C programming practical exercise focuses on implementing a **stack data structure** for integers and using it to **evaluate postfix expressions**.

## Objectives:

*   Implement an integer stack (`stack.c/.h`).
*   Write a variadic function (`fill_stack`) for adding multiple values to the stack.
*   Evaluate postfix expressions using the stack (`evaluation.c/.h`, `evaluationString.c`).
*   Use **function pointers** for operator management.
*   Learn the `static` keyword and practice basic unit testing (`test.c/.h`).
*   Automate compilation with a `Makefile`.

## Tasks:

1. **Stack Implementation:** Write and test the integer stack and the `fill_stack` function.
2. **Postfix Evaluation:** Implement postfix expression evaluation, and test it with operators like `+`, `-`, `*`, `/`.
3. **Function Pointers:** Implement `binary_operator_pf` to apply operations dynamically.
4. **Evaluate from String:** Add string-based postfix evaluation with function pointers for operators.
5. **Optional:** Add unary operators (square root and cube), and link the math library.

This exercise introduces stacks, function pointers, variable arguments, and automating testing with `make`.
