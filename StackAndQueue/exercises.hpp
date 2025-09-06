#include <iostream>

#include <stack>

string reverse_string(const std::string& str)
{   
    stack<char>st;

    std::string reversed = "";

    // for (std::string::iterator it = str.begin(); it != str.end(); ++it)
    // for (size_t i = 0; i < str.length(); ++i)
    for(char ch: str)
    {
        st.push(ch);
    }

    while(!st.empty())
    {
        reversed += st.top();
        st.pop();
    }

    return reversed;
}

bool is_balanced_parentheses(const std::string& parentheses)
{
    stack<char>st;

    if(parentheses == "") return false;

    // for (std::string::iterator it = parentheses.begin(); it != str.end(); ++it)
    // for (size_t i = 0; i < parentheses.length(); ++i)
    for(char ch: parentheses)
    {
        if(ch == '(') st.push(ch);
        else if(ch == ')')
        {
            if(st.empty() || st.top() != '(')
            {
                return false;
            }
            else
            {
                st.pop();
            }
        }
        
    }

    if(st.empty()) return true;

    return false;
}

void printStack(std::stack<int> s) {
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
}

void sortStack(stack<int>& inputStack) 
{
    stack<int> temp_stack;

    while(!inputStack.empty())
    {
       int temp = inputStack.top();
       inputStack.pop();

        while (!temp_stack.empty() && temp_stack.top() > temp) 
        {
            inputStack.push(temp_stack.top());
            temp_stack.pop();
        }

        temp_stack.push(temp);

    }

    while(!temp_stack.empty())
    {
        inputStack.push(temp_stack.top());
        temp_stack.pop();
    }
}