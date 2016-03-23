
//
//  eval.cpp
//  CS32Homework2
//
//  Created by Monil Patel on 1/28/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <cctype>
#include <stack>
#include "Map.h"
using namespace std;
bool inFixIsValid(string infix);
bool isInfixContainedInValues(string infix, const Map& values);
void convertInfixToPostFix(string infix, string& px);
int evaluatePostFix(string postfix, const Map& values,bool doesDivideByZero);

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
    bool doesDivZero=false;
    if (!inFixIsValid(infix))
    {
        return 1;
    }
    else
    {
        convertInfixToPostFix(infix, postfix);
    }
    if(!isInfixContainedInValues(infix, values))
    {
        return 2;
    }
    
    int a=evaluatePostFix(postfix,values,doesDivZero);
    if (doesDivZero)
    {
        return 3;
    }
    result=a;
    return 0;
}
void convertInfixToPostFix(string infix, string postfix)
{
    postfix="";
    stack<char> st;     // declare a stack of characters
    for (int i=0; i<infix.length(); i++)
    {
        char ch=infix[i];
        switch (ch)
        {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                postfix+=ch;
                break;
            case '(':
                st.push(ch);
                break;
            case ')':
                while (st.top()!='(')
                {
                    postfix+=st.top();
                    st.pop();
                }
                st.pop();
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                while (!st.empty() && st.top()!='(' && ch<=st.top())
                {
                    postfix+=st.top();
                    st.pop();
                }
                st.push(ch);
                break;
                // is this supposed to go here?
            default:
                while (!st.empty())
                {
                    postfix+=st.top();
                    st.pop();
                }
                break;
        }
    }
}
int evaluatePostFix(string postfix, const Map& values,bool doesDivideByZero)
{
    stack<int> st;     // declare a stack of ints
    for (int i=0; i<postfix.length(); i++)
    {
        char ch=postfix[i];
        int value=0;
        if (isalpha(ch))
        {
           values.get(ch,value);
            st.push(value);
        }
        else
        {
            int op2=st.top();
            st.pop();
            int op1=st.top();
            st.pop();
            int res=0;
            
            if (ch=='+')
            {
                 res=op1+op2;
            }
            else if (ch=='-')
            {
                 res=op1-op2;
            }
            else if (ch=='*')
            {
                 res=op1*op2;
            }
            else if (ch=='/')
            {
                if (op2!=0)
                {
                   res=op1/op2;
                }
                doesDivideByZero=true;
                return -1;
            }
            st.push(res);
        }
    }
    int result=st.top();
    return result;
}
bool inFixIsValid(string infix)
{
    string result="";
    stack<char> st;     // declare a stack of characters
    for (int i=0; i<infix.length(); i++)
    {
        char ch=infix[i];
        if (isalpha(ch))
        {
            st.push(ch);
        }
    }
    return true;
}
bool isInfixContainedInValues(string infix, const Map& values)
{
    for (int i=0; i<infix.size(); i++)
    {
        if (isalpha(infix[i]) && !values.contains(infix[i]))
        {
            return false;
        }
    }
    return true;
}
int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    string a="aeiouy";
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
    {
        m.insert(vars[k], vals[k]);
    }
    if (isInfixContainedInValues(a, m))
    {
        cout<<"Passed Test 1";
    }
    cout<<"Failed Test 1";
}
/*
 Implement this function that evaluates an infix integer arithmetic expression that consists of the binary operators +, -, *, and /, parentheses, and operands (with blanks allowed for readability). The / operator denotes integer division (with truncation), so that the value of eight divided by five is 1, not 1.6. Operators have their conventional precedence and associativity. Multiplication must be explicitly indicated with the * operator.
 
 The operands in the expression are single lower case letters. Along with the expression string, you will pass the function a Map with key type char and value type int. Each letter character in the expression represents the integer value in the map that is paired with that letter key. For example, if the map maps a to 3, c to 5, l to 2, and u to 11, then the expression u-c+l*a would evaluate to 12.
 
 Here is the function:
 
	int evaluate(string infix, const Map& values, string& postfix, int& result);
 // Evaluates an integer arithmetic expression
 // Precondition: infix is an infix integer arithmetic
 //   expression consisting of single lower case letter operands,
 //   parentheses, and the operators +, -, *, /, with embedded blanks
 //   allowed for readability.
 // Postcondition: If infix is a syntactically valid infix integer
 //   expression whose only operands are single lower case letters
 //   (whether or not they appear in the values map), then postfix is
 //   set to the postfix form of the expression; 
 otherwise postfix may
 //   or may not be changed, result is unchanged, and the function
 //   returns 1.  
 If infix is syntactically valid but contains at
 //   least one lower case letter operand that does not appear in the
 //   values map, then result is unchanged and the function returns 2.
 
 //   If infix is syntactically valid and all its lower case operand
 //   letters appear in the values map, then if evaluating the
 //   expression (using for each letter in the expression the value in
 //   the map that corresponds to it) attempts to divide by zero, then
 //   result is unchanged and the function returns 3; 
    otherwise,
 //   result is set to the value of the expression and the function
 //   returns 0.
 Adapt the algorithms presented on pp. 205-209 of the textbook to convert the infix expression to postfix, then evaluate the postfix form of the expression. The algorithms use stacks. Rather than implementing the stack types yourself, you must use the stack class template from the Standard C++ library. You may not assume that the infix string passed to the function is syntactically valid; you'll have to detect whether it is or not.
 (Tips: In case you didn't already know it, you can append a character c to a string s by saying s += c. You'll have to adapt the code from the book, since it doesn't do any error checking. It's possible to do the error checking as you do the infix-to-postfix conversion instead of in a separate step before that; as you go through the infix string, almost all syntax errors can be detected by noting whether it is legal for the current nonblank character to follow the nearest nonblank character before it.
*/