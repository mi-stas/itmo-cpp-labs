#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <random>

using namespace std;

struct Expression
{
    vector<string> types;
    vector<string> operations;
};

static const unordered_set<string> operations = {
        "+", "-", "/", "*"
};

static const unordered_set<string> types = {
        "int", "unsigned int", "float", "double", "char", "unsigned char", "long", "unsigned long"
};

Expression parseConfigExpression(ifstream& fin)
{
    Expression expression;
    string line;

    while (getline(fin, line)) {
        if (types.find(line) != types.end()) {
            expression.types.push_back(line);
        } else if (operations.find(line) != operations.end()) {
            expression.operations.push_back(line);
        } else {
            cout << "Wrong config file value: " << line << "!" << "\n";
            return Expression{};
        }
    }

    return expression;
}

int main(){
    ifstream fin("task_1/config.txt");
    ofstream fout("task_1/func_1.cpp");

    Expression expression = parseConfigExpression(fin);

    fout << "#include <iostream>" << "\n\n";
    fout << "int f(void) {"<< endl;

    for (int i = 0; i < expression.types.size(); ++i) {
        fout << "    " << expression.types[i] << " var" << i + 1;
        int value = random() % numeric_limits<char>::max();
        if (i % 2 == 0) {
            fout << " = " << value << ";" << "\n";
        } else {
            fout << "{" << value << "};" << "\n";
        }
    }

    fout << "    std::cout << var1";
    for (int i = 1; i < expression.types.size(); ++i) {
        fout << " " << expression.operations[i - 1] << " var" << i + 1;
    }
    fout << ";" << "\n";
    fout << "    return 0;" << "\n";
    fout << "}" << "\n\n";
    fout << "int main() {" << "\n";
    fout << "    f();" << "\n";
    fout << "}";

    fout.close();
    fin.close();
    return 0;
}
