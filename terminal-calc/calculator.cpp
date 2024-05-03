#include <iostream>
#include <stack>
#include <string>

using namespace std;

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

bool isOperator(char c)
{
    return c == '!' || c == '&' || c == '@' || c == '$' || c == '|';
}

bool isOperand(char c)
{
    return c == 'T' || c == 'F' || c == 't' || c == 'f';
}

string infixToPostfix(string expression)
{
    stack<char> postfixStack;
    string postfix = "";

    for (char ch : expression)
    {
        if (isOperand(ch))
        {
            postfix += ch;
        }
        else if (ch == '(')
        {
            postfixStack.push(ch);
        }
        else if (ch == ')')
        {
            while (!postfixStack.empty() && postfixStack.top() != '(')
            {
                postfix += postfixStack.top();
                postfixStack.pop();
            }
            if (!postfixStack.empty())
                postfixStack.pop(); // Pop the '(' from the stack
        }
        else if (isOperator(ch))
        {
            while (!postfixStack.empty() && precedence(ch) <= precedence(postfixStack.top()))
            {
                postfix += postfixStack.top();
                postfixStack.pop();
            }
            postfixStack.push(ch);
        }
    }

    while (!postfixStack.empty())
    {
        postfix += postfixStack.top();
        postfixStack.pop();
    }

    return postfix;
}

bool evaluation(string postfix)
{
    stack<bool> evalStack;
    for (char ch : postfix)
    {
        if (isOperand(ch))
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
            if (ch == '!')
            {
                evalStack.push(!op1);
            }
            else
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

bool validateExpression(const string &expression)
{
    stack<char> validStack;
    bool lastWasOp = true;     // Assume starting with an operator or '(' is valid
    bool lastWasClose = false; // to handle cases like () or T()

    for (char c : expression)
    {
        if (c == ' ' || c == '\n')
            continue;

        if (isOperand(c))
        {
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
            if (lastWasOp && c != '!')
            { // allow unary '!' after operators or open parenthesis
                cout << "Error: Misplaced operator '" << c << "'" << endl;
                return false;
            }
            lastWasOp = true;
            lastWasClose = false;
        }
        else if (c == '(')
        {
            if (!lastWasOp && !validStack.empty())
            {
                cout << "Error: Misplaced '(' after operand" << endl;
                return false;
            }
            validStack.push(c);
            lastWasOp = true; // After '(', expecting an operand or unary operator
            lastWasClose = false;
        }
        else if (c == ')')
        {
            if (validStack.empty() || validStack.top() != '(' || lastWasOp)
            {
                cout << "Error: Mismatched or misplaced ')'" << endl;
                return false;
            }
            validStack.pop();
            lastWasOp = false;
            lastWasClose = true; // just closed a pair, expecting operator or closing another pair
        }
        else
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

int main()
{
    cout << "Enter the expression: ";
    string expression;
    getline(cin, expression);

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