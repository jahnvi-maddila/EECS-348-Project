#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Function to determine the precedence of operators
int precedence(char c)
{
    switch (c)
    {
    case '!':
        return 5;
    case '&':
        return 4;
    case '@':
        return 3;
    case '$':
        return 2;
    case '|':
        return 1;
    default:
        return -1;
    }
}

// Function to check if a character is an operator
bool isOperator(char c)
{
    return c == '!' || c == '&' || c == '@' || c == '$' || c == '|';
}

// Function to check if a character is an operand
bool isOperand(char c)
{
    return c == 'T' || c == 'F' || c == 't' || c == 'f';
}

// Function to convert an infix expression to postfix notation
string infixToPostfix(string expression)
{
    stack<char> postfixStack;
    string postfix = "";

    for (char ch : expression)
    {
        if (isOperand(ch)) // Directly add operands to the output
        {
            postfix += ch;
        }
        else if (ch == '(') // Push '(' to stack
        {
            postfixStack.push(ch);
        }
        else if (ch == ')') // Pop and output from stack until '(' is encountered
        {
            while (!postfixStack.empty() && postfixStack.top() != '(')
            {
                postfix += postfixStack.top();
                postfixStack.pop();
            }
            if (!postfixStack.empty())
                postfixStack.pop(); // Remove '(' from the stack
        }
        else if (isOperator(ch)) // Handle operators based on precedence
        {
            while (!postfixStack.empty() && precedence(ch) <= precedence(postfixStack.top()))
            {
                postfix += postfixStack.top();
                postfixStack.pop();
            }
            postfixStack.push(ch);
        }
    }

    // Pop all the remaining elements in the stack
    while (!postfixStack.empty())
    {
        postfix += postfixStack.top();
        postfixStack.pop();
    }

    return postfix;
}

// Function to evaluate a postfix expression
bool evaluation(string postfix)
{
    stack<bool> evalStack;
    for (char ch : postfix)
    {
        if (isOperand(ch)) // Push the boolean equivalent of the operand
        {
            evalStack.push(ch == 'T' || ch == 't');
        }
        else if (isOperator(ch))
        {
            bool op1 = false;
            if (!evalStack.empty())
            {
                op1 = evalStack.top();
                evalStack.pop();
            }
            if (ch == '!') // Unary operator
            {
                evalStack.push(!op1);
            }
            else // Binary operators
            {
                bool op2 = false;
                if (!evalStack.empty())
                {
                    op2 = evalStack.top();
                    evalStack.pop();
                }
                switch (ch)
                {
                case '&':
                    evalStack.push(op1 && op2);
                    break;
                case '@':
                    evalStack.push(!(op1 && op2));
                    break;
                case '$':
                    evalStack.push(op1 != op2);
                    break;
                case '|':
                    evalStack.push(op1 || op2);
                    break;
                }
            }
        }
    }
    return evalStack.top();
}

// Function to validate the syntax of the expression
bool validateExpression(const string &expression)
{
    stack<char> validStack;
    bool lastWasOp = true;     // Assume starting with an operator or '(' is valid
    bool lastWasClose = false; // to handle cases like () or T()

    for (char c : expression)
    {
        if (c == ' ' || c == '\n')
            continue;

        if (isOperand(c)) // Validate operands
        {
            if (!lastWasOp && !lastWasClose)
            {
                cout << "Error: Two consecutive operands or invalid placement ('" << c << "')" << endl;
                return false;
            }
            lastWasOp = false;
            lastWasClose = false;
        }
        else if (isOperator(c)) // Validate operators
        {
            if (lastWasOp && c != '!')
            {
                cout << "Error: Misplaced operator '" << c << "'" << endl;
                return false;
            }
            lastWasOp = true;
            lastWasClose = false;
        }
        else if (c == '(') // Validate open parenthesis
        {
            if (!lastWasOp && !validStack.empty())
            {
                cout << "Error: Misplaced '(' after operand" << endl;
                return false;
            }
            validStack.push(c);
            lastWasOp = true;
            lastWasClose = false;
        }
        else if (c == ')') // Validate close parenthesis
        {
            if (validStack.empty() || validStack.top() != '(' || lastWasOp)
            {
                cout << "Error: Mismatched or misplaced ')'" << endl;
                return false;
            }
            validStack.pop();
            lastWasOp = false;
            lastWasClose = true;
        }
        else // Handle unknown characters
        {
            cout << "Error: Unknown character '" << c << "'" << endl;
            return false;
        }
    }

    if (!validStack.empty() || lastWasOp && !lastWasClose)
    {
        cout << "Error: Mismatched parentheses or incomplete expression" << endl;
        return false;
    }

    return true;
}

// Main function to run the expression evaluation
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <expression>" << endl;
        return 1;
    }

    string expression = argv[1];
    if (!validateExpression(expression))
    {
        cout << "Invalid expression!" << endl;
        return 1;
    }

    string postfix = infixToPostfix(expression);
    bool result = evaluation(postfix);
    cout << (result ? "True" : "False") << endl;

    return 0;
}
