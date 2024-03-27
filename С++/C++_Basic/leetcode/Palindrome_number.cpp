class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }

        long temp = x;
        long rev = 0;

        while (temp != 0) {
            int num = temp % 10;
            rev = rev * 10 + num;
            temp /= 10;
        }

        return (rev == x);
    }
};
