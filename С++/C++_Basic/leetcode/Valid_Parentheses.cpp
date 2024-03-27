#include <iostream>
#include <stack>
#include <string>

class Solution {
public:
    bool isValid(const std::string& s) {
        std::stack<char> stack;
        for (char c : s) {
            if (c == '(' || c == '{' || c == '[') {
                stack.push(c);
            } else {
                if (stack.empty()) {
                    return false;
                }
                char open = stack.top();
                stack.pop();
                if ((c == ')' && open != '(') || (c == '}' && open != '{') || (c == ']' && open != '[')) {
                    return false;
                }
            }
        }
        return stack.empty();
    }
};
