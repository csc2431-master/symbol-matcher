

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Stack {
public:
    Stack() { _count = 0; }
    bool empty() { return _count == 0; }
    void push(char symbol) {
        _array[_count++] = symbol;
    }
    char top() {
        return _array[_count-1];
    }
    void pop() { _count--;  }

private:
    char _array[100];
    int _count;
};

int main(int argc, char* argv[]) {
    ifstream fin;
    string line;
    unsigned lineNumber = 1;

    Stack symbols;

    if (argc != 2) {
        cout << "Usage: SyntaxChecker <file-name>" << endl;
        exit(1);
    }
    fin.open(argv[1]);
    if (!fin.is_open()) {
        cerr << "Could not open '" << argv[1] << "'" << endl;
        return 1;
    }

    while (getline(fin, line)) {
        for (int charPosition = 0; charPosition < line.length(); charPosition++) {
            if (line[charPosition] == '{' || line[charPosition] == '(' || line[charPosition] == '[') {
                symbols.push(line[charPosition]);
            }
            else if (line[charPosition] == '}' || line[charPosition] == ')' || line[charPosition] == ']') {
                if (symbols.empty()
                    || (line[charPosition] == '}' && symbols.top()  != '{')
                    || (line[charPosition] == ')' && symbols.top()  != '(')
                    || (line[charPosition] == ']' && symbols.top() != '[') ) {
                    fin.close();
                    cout << "Unmatched '" << line[charPosition] << "' at lineNumber " << lineNumber << ", position " << (charPosition+1) << endl;
                    exit(0);
                }
                else {
                    symbols.pop();
                }
            }
        }
        lineNumber ++;
    }
    if (!symbols.empty()) {
        cout << "Unmatched '" << symbols.top() << " at the end of the file" << endl;
    }
    else {
        cout << "No syntax errors found" << endl;
    }
    fin.close();
    return 0;
};