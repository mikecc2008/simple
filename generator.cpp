#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class Generator {
	vector<string> procedures;
	vector<string> variables;
	vector<string> operators;
	int procNum, programSize, openBracket, nestedLevel;
	public:
		Generator(int pn, int ps, int nl) {
			procNum = pn;
			programSize = ps;
			nestedLevel = nl;
			openBracket = 0;

			operators.push_back("+");

			srand ( time(NULL) );
		}
		void generate() {
			cout << getProc() << endl;
			while(programSize) {
				int stmtType = getInt(3, 0);
				
				if(variables.size() == 0 || openBracket > nestedLevel)
					cout << getAssign() << endl;
				else {
					if(stmtType == 0)
						cout << getAssign() << endl;
					else if(stmtType == 1)
						cout << getWhile() << endl;
					else
						cout << getIf() << endl;
				}
			}

			while(openBracket--)
				cout << getIndent() << "}" << endl;
		}
	private:
		int getInt(int max = 100, int min = 1) {
			return rand() % max + min;
		}	

		string getName(int len = 5) {
			static const char alphanum[] =
		        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
			string name(1, alphanum[getInt(sizeof(alphanum) - 10, 10)]);

			for(int i = 1; i < len; i++)
				name += alphanum[getInt(sizeof(alphanum) - 10, 0)];

			return name;
		}

		string getVar() {
			return variables[getInt(variables.size(), 0)];	
		}

		string getOperator() {
			return operators[getInt(operators.size(), 0)];
		}

		string getIndent() {
			string indent = "";
			indent.insert(0, openBracket, '\t');

			return indent;
		}

		string getIf() {
			string ifStmt = getIndent() + "if " + getVar() + " then {";
			openBracket++;
			programSize--;
			return ifStmt;
		}

		string getWhile() {
			string whileStmt = getIndent() + "while " + getVar() + " {";
			openBracket++;
			programSize--;
			return whileStmt;
		}

		string getAssign() {
			string varName = getName(1);
			string assign = getIndent() + varName + " = ";
			stringstream ss;
			ss << getInt();
			if(variables.size() == 0 || getInt() > 50) {
				if(find(variables.begin(), variables.end(), varName) == variables.end())
					variables.push_back(varName);
				assign += ss.str() + ";"; 
			}
			else {
				assign += getVar() + " "; 
				assign += getOperator() + " ";
				assign += ss.str() + ";";
			}

			if(openBracket > 1 && getInt() > 50) {
				assign += "}";
				openBracket--;
			}

			programSize--;

			return assign;
		}

		string getCall() {
			return "";
		}

		string getProc() {
			string procName = getName();
			procedures.push_back(procName);
			openBracket++;
			return "procedure " + procName + " {";
		}
};

int main()
{
	int procNum, nestedLevel, programSize;
	
	cout	<< "Numbers of statements: ";
	cin		>> programSize;
	cout	<< "Numbers of procedure: ";
	cin 	>> procNum;
	cout	<< "Numbers of nested level: ";
	cin 	>> nestedLevel;

	Generator g (procNum, programSize, nestedLevel);
	g.generate();

	return 0;
}