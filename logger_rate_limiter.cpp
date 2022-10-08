//Date: 08-10-22 //Author: Rishabh Paul
//Problem Statement Link: https://tenderleo.gitbooks.io/leetcode-solutions-/content/GoogleEasy/359.html

#include<bits/stdc++.h>
using namespace std;
const int INTERVAL = 10;

struct Logger {

    map<string, int> last_printed;
    
    Logger() {//default constructor

    }
    bool should_print(string &msg, int timestamp) {
        if (last_printed.find(msg) == last_printed.end()) {
            last_printed[msg] = timestamp;
            return true;
        }
        int last_print_time = last_printed[msg];
        last_printed[msg] = timestamp;
        return timestamp - last_print_time > INTERVAL;
    }
};

int main () {
    Logger logger;
    string s = "foo";
    string b = "bar";
    cout << logger.should_print(s, 1) << '\n';
    cout << logger.should_print(s, 2) << '\n';
    cout << logger.should_print(b, 3) << '\n';
    cout << logger.should_print(s, 3) << '\n';
    cout << logger.should_print(s, 50) << '\n';
    cout << logger.should_print(b, 30) << '\n';
    return 0;
}
