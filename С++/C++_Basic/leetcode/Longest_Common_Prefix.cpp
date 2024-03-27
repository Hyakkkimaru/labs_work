#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
std::string longestCommonPrefix(const std::vector<std::string>& strs) {
    if (strs.empty()) {
        return "";
    }

    std::string prefix = strs[0];
    for (const std::string& str : strs) {
        while (str.find(prefix) != 0) {
            prefix = prefix.substr(0, prefix.size() - 1);
            if (prefix.empty()) {
                return "";
            }
        }
    }

    return prefix;
}
};
