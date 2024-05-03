#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Function to determine the precedence of logical operators
int precedence(char c)
{
    switch (c)
    {
    case '!': // Highest precedence
        return 5;
    case '&':
        return 4;
    case '@':
        return 3;
    case '$':
        return 2;
    case '|': // Lowest precedence
        return 1;
    default:
        return -1; // Not an operator
    }
}

// Function to check if a character is a logical operator
bool isOperator(char c)
{
    return c == '!' || c == '&' || c == '@' || c == '$' || c == '|';
}

// Function to check if a character is an operand (True or False)
bool isOperand(char c)
{
    return c == 'T' || c == 'F' || c == 't' || c == 'f';
}

// Function to convert an infix expression to postfix notation using a stack
string infixToPostfix(string expression)
{
    stack<char> postfixStack;
    string postfix = "";

    // Iterate through each character in the input expression
    for (char ch : expression)
    {
        if (isOperand(ch))
        {
            // Directly add operands to the postfix expression
            postfix += ch;
        }
        else if (ch == '(')
        {
            // Push '(' onto stack to handle precedence
            postfixStack.push(ch);
        }
        else if (ch == ')')
        {
            // Pop stack to the corresponding '(' and add to postfix expression
            while (!postfixStack.empty() && postfixStack.top() != '(')
            {
                postfix += postfixStack.top();
                postfixStack.pop();
            }
            postfixStack.pop(); // Remove '(' from stack
        }
        else if (isOperator(ch))
        {
            // Pop higher or equal precedence operators from the stack before pushing current operator
            while (!postfixStack.empty() && precedence(ch) <= precedence(postfixStack.top()))
            {
                postfix += postfixStack.top();
                postfixStack.pop();
            }
            postfixStack.push(ch);
        }
    }

    // Pop all remaining operators in the stack
    while (!postfixStack.empty())
    {
        postfix += postfixStack.top();
        postfixStack.pop();
    }

    return postfix;
}

// Function to evaluate a postfix logical expression
bool evaluation(string postfix)
{
    stack<bool> evalStack;

    // Evaluate the postfix expression using a stack
    for (char ch : postfix)
    {
        if (isOperand(ch))
        {
            // Convert operand to boolean and push to stack
            evalStack.push(ch == 'T' || ch == 't');
        }
        else if (isOperator(ch))
        {
            bool op1 = false, op2 = false;

            // Unary operator '!'
            if (ch == '!')
            {
                op1 = evalStack.top();
                evalStack.pop();
                evalStack.push(!op1);
            }
            else
            {
                // Binary operators
                if (!evalStack.empty())
                {
                    op2 = evalStack.top();
                    evalStack.pop();
                }
                if (!evalStack.empty())
                {
                    op1 = evalStack.top();
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
    return evalStack.top(); // Return the result of the expression
}

// Function to validate the syntactical correctness of the expression
bool validateExpression(const string &expression)
{
    stack<char> validStack;
    bool lastWasOp = true;     // Start assuming an operator or '(' is valid
    bool lastWasClose = false; // Track if the last character was a closing parenthesis

    for (char c : expression)
    {
        if (c == ' ' || c == '\n')
            continue;

        if (isOperand(c))
        {
            // Check for consecutive operands without an operator
            if (!lastWasOp && !lastWasClose)
            {
                cout << "Error: Two consecutive operands or invalid placement ('" << c << "')" << endl;
                return false;
            }
            lastWasOp = false;
            lastWasClose = false;
        }
        else if (isOperator(c))
        {
            // Check for misplaced operators
            if (lastWasOp && c != '!')
            {
                cout << "Error: Misplaced operator '" << c << "'" << endl;
                return false;
            }
            lastWasOp = true;
            lastWasClose = false;
        }
        else if (c == '(')
        {
            // Check for misplaced '('
            if (!lastWasOp && !validStack.empty())
            {
                cout << "Error: Misplaced '(' after operand" << endl;
                return false;
            }
            validStack.push(c);
            lastWasOp = true;
            lastWasClose = false;
        }
        else if (c == ')')
        {
            // Check for mismatched ')'
            if (validStack.empty() || validStack.top() != '(' || lastWasOp)
            {
                cout << "Error: Mismatched or misplaced ')'" << endl;
                return false;
            }
            validStack.pop();
            lastWasOp = false;
            lastWasClose = true;
        }
        else
        {
            // Handle unknown characters
            cout << "Error: Unknown character '" << c << "'" << endl;
            return false;
        }
    }

    // Final check for unmatched parentheses or incomplete expressions
    if (!validStack.empty() || (lastWasOp && !lastWasClose))
    {
        cout << "Error: Mismatched parentheses or incomplete expression" << endl;
        return false;
    }

    return true;
}

int main()
{
    cout << "Enter the expression: ";
    string expression;
    getline(cin, expression);

    // Validate, convert, and evaluate the expression
    if (!validateExpression(expression))
    {
        cout << "Invalid expression!" << endl;
        return 1;
    }

    string postfix = infixToPostfix(expression);
    cout << "Postfix expression: " << postfix << endl;

    bool result = evaluation(postfix);
    cout << "Result: " << (result ? "True" : "False") << endl;

    return 0;
}