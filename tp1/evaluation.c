/*!
 * \file  evaluation.c
 * \brief  Definition of functions to process a stack of int as a post-fix expression
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "application.h"
#include "evaluation.h"
#include "stack.h"
#include "test.h"


//static Boolean binary_operator(Stack *s, int operation){
//
//  int op1,op2; /*the operands*/
//  int res; /*the result*/
//
//  if (isEmpty(s)){
//    fprintf(stderr,"Empty stack : can not proceed to the binary operation\n");
//    return(FALSE);
//  }
//  op1=pop(s);
//
//  if (isEmpty(s)){
//    fprintf(stderr,"Empty stack : can not proceed to the binary operation\n");
//    return(FALSE);
//  }
//  op2=pop(s);
//
//  /* computation*/
//  switch(operation){
//      case ADD:
//        res = op1 + op2;
//        break;
//      case SUBSTRACT:
//        res = op2 - op1;
//        break;
//      case MULTIPLY:
//        res = op1 * op2;
//        break;
//      case DIVIDE:
//        if (op1 == 0) {
//          fprintf(stderr, "Error: Division by zero\n");
//          return FALSE;
//        }
//        res = op2 / op1;
//        break;
//      default:
//        fprintf(stderr,"Unknown operator\n");
//        return(FALSE);
//  }
//
//  /* Put the result in the stack */
//  push(s,res);
//
//  return(TRUE);
//}


static int add_pre(int a, int b) {
  return a + b;
}

static int substract_pre(int a, int b) {
  return a - b;
}

static int multiply_pre(int a, int b) {
  return a * b;
}

static int divide_pre(int a, int b) {
  return a/b;
}


static Boolean binary_operator_pf(Stack *s, int (*op)(int,int)){
  int op1,op2; /*the operands*/
  int res; /*the result*/

  if (isEmpty(s)){
    fprintf(stderr,"Empty stack : can not proceed to the binary operation\n");
    return(FALSE);
  }
  op2=pop(s);

  if (isEmpty(s)){
    fprintf(stderr,"Empty stack : can not proceed to the binary operation\n");
    return(FALSE);
  }
  op1=pop(s);

  res = (*op)(op1,op2);
  push(s,res);
  return(TRUE);
}

Boolean add(Stack *s){
  return binary_operator_pf(s, &add_pre);
}

Boolean substract(Stack *s){
  return binary_operator_pf(s, &substract_pre);
}

Boolean multiply(Stack *s){
  return binary_operator_pf(s, &multiply_pre);
}

Boolean divide(Stack *s){
  return binary_operator_pf(s, &divide_pre);
}

/*!
 * \fn int test_eval(void)
 * Tests evaluation of postfix expressions
 * \return EXIT_SUCCESS if everything is ok
 */
int test_eval(void){

    Stack s;
    init_stack(&s);
    push(&s,1);
    push(&s,2);
    substract(&s);
    display_test_int("Test substract()",-1,pop(&s)); push(&s,-1); /*the push is to put back the popped value for the test*/
    push(&s,3);
    add(&s);
    display_test_int("Test add()",2,pop(&s)); push(&s,2); /*the push is to put back the popped value for the test*/
    push(&s,4);
    push(&s,5);
    add(&s);
    add(&s);

    display_test_check_by_user("Test substract() and add() : (display stack should be 0 11)");
    display_stack(&s);

    /* to be completed when multiply is implemented*/
    Stack p;
    init_stack(&p);
    push(&p,3);
    push(&p,2);
    multiply(&p);
    display_test_int("Test multiply()",6,pop(&p)); push(&p,6);
    display_test_check_by_user("Test multiply() : (display stack should be 0 6)");
    display_stack(&p);

    /* to be completed when divide is implemented*/
    Stack q;
    init_stack(&q);
    push(&q,10);
    push(&q,5);
    divide(&q);
    display_test_int("Test divide()",2,pop(&q)); push(&q,2);
    display_test_check_by_user("Test divide() : (display stack should be 0 2)");
    display_stack(&q);

    /* Test the 3 9 3 - 4 * 3 / + expression*/
    Stack r;
    init_stack(&r);
    push(&r,3);
    push(&r,9);
    push(&r,3);
    substract(&r);
    display_test_int("Test substract()",6,pop(&r)); push(&r,6);
    push(&r,4);
    multiply(&r);
    display_test_int("Test multiply()",24,pop(&r)); push(&r,24);
    push(&r,3);
    divide(&r);
    display_test_int("Test division()",8,pop(&r)); push(&r,8);
    add(&r);
    display_test_int("Test add()",11,pop(&r)); push(&r,11);

    display_test_check_by_user("Test substract(), multiply(), division() and add() : (display stack should be 0 11)");
    display_stack(&s);

    return(EXIT_SUCCESS);
}

