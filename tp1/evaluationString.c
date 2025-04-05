/*!
 * \file  evaluationString.c
 * \brief  Definition of functions to process a stack of int as a post-fix expression
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "application.h"
#include "evaluation.h"
#include "stack.h"
#include "test.h"

//operators and their corresponding functions are mapped
Map_element operator_map[] = {
    {'+', &add},
    {'-', &substract},
    {'*', &multiply},
    {'/', &divide}
};


static int isANumber(char c)
{
    return (c>='0') && (c <= '9');
}

/*!
* Handle a stack to evaluate a postfix expression
* \param[in] str the postfix expression to be evaluated
* \return int the result of the evaluation
*/
int evaluateExpression(char *str){

  Stack s;
  int i;

  init_stack(&s);
  i=0;
  while(str[i] != '\0')
  {
    if(isANumber(str[i]))
        push(&s, str[i] - '0');
    else
    {
        switch(str[i])
        {
            case '+' : add(&s); break;
            case '-' : substract(&s); break;
            case '*' : multiply(&s); break;
            case '/' : divide(&s); break;
            default : fprintf(stderr,"unknown operator\n"); return 0;
        }
    }
    ++i;
  }
  return pop(&s);
}

int evaluateExpression_pf(char *str){
  Stack s;
  int i;
  init_stack(&s);
  i=0;
  while(str[i] != '\0')
  {
    if(isANumber(str[i]))
      push(&s, str[i] - '0');
    else
    {
      int found = 0;
      for(int j=0; j < (int)(sizeof(operator_map)/sizeof(Map_element)); j++){
        if(str[i] == operator_map[j].c){
          (operator_map[j].act)(&s);
          found = 1;
          break;
        }
      }
      if(!found){
      fprintf(stderr,"unknown operator\n"); return 0;
      }
    }
    ++i;
  }
  return pop(&s);
}

/*!
 * \fn int test_evalString(void)
 * Tests evaluation of postfix expressions from strings
 * \return EXIT_SUCCESS if everything is ok
 */
int test_evalString(void){

    char * expr1 = "393-4*3/+";

    /* With binary operators only*/
    display_test_int("Test evaluateExpression() for binary operators",11,evaluateExpression(expr1));
    /* Uncomment when function evaluateExpression_pf() is implemented*/

    display_test_int("Test evaluateExpression_pf()  for binary operators",11,evaluateExpression_pf(expr1));

    /* With binary + unary operators */
    /* Uncomment when function evaluateExpression_pf() + unary operators are implemented*/
    /*
    display_test_int("Test evaluateExpression_pf() for binary+unary operators",64,evaluateExpression_pf(expr2));
    */

  return(EXIT_SUCCESS);
}

