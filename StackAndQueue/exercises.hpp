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
