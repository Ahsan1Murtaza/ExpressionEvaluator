#include<iostream>
#include<string>
#include<stack>
using namespace std;

int precedence(char op){
    if (op == '+' || op == '-'){
        return 1;
    }
    else if (op == '*' || op == '/')
    {
        return 2;
    }
    return 0;
}

int applyOp(int num1, int num2, char op){
    switch(op){
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num1 / num2;
    };
    return 0;
}

int evaluate(string expression){
    // stack to store integer values.
    stack <int> values;
     
    // stack to store operators.
    stack <char> ops;

    for (int i = 0; i < expression.length(); i++){

        if (expression[i] == ' '){ // Skip it if empty
            continue;
        }

        else if (isdigit(expression[i])){
            int val = 0;
            while (i < expression.length() && isdigit(expression[i])){ // Making a number
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            values.push(val);

            i--;
        }

        else if (expression[i] == '('){
            ops.push('(');
        }

        else if (expression[i] == ')'){
            while (!ops.empty() && ops.top() != '('){
                int val2 = values.top();
                values.pop();
                 
                int val1 = values.top();
                values.pop();
                 
                char op = ops.top();
                ops.pop();
                 
                values.push(applyOp(val1, val2, op));
            }

            // pop opening brace.
            if(!ops.empty())
               ops.pop();
            
        }

        else{ // it is an operator
            char thisOp = expression[i];
            while (!ops.empty() && precedence(ops.top()) >= precedence(thisOp)){

                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }
            ops.push(thisOp);
        }
    }

    while (!ops.empty())
    {
        int val2 = values.top();
        values.pop();

        int val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOp(val1, val2, op));
    }

    return values.top(); // It is final answer
    
}

int main()
{
    string expression = "1 + 2";
    expression = "100 * ( 2 + 12 ) / 14";
    cout << evaluate(expression) << endl;

    
    return 0;
}