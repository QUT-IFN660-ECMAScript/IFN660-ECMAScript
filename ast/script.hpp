#pragma once
#include <typeinfo>
#include <cstdio>
#include <iostream>
#include "node.hpp"
#include "statement.hpp"

using namespace std;

class ScriptBody: public Node, public LexicalScope {
private:
  vector<Statement*> *stmts;
public:  

	
  ScriptBody(vector<Statement*> *stmts):
    stmts(stmts) {};
    
    
	void dump(int indent) {
    	label(indent, "ScriptBody\n");
    	vector<Statement*>::iterator iter;
    	for (iter = stmts->begin(); iter != stmts->end(); ++iter) {
      		(*iter)->dump(indent+1);
    	}
  	}
  
	void emit(FILE* outputfile, char* fmt, ...) {	
		va_list args;
		va_start(args, fmt);
		vfprintf(outputfile, fmt, args);
		fprintf(outputfile, "\n");
		va_end(args);
	}

 
    
    void genCode(FILE* file) {
		emit(file, "#include \"./runtime/core.hpp\"");
		emit(file, "#include \"./runtime/console.hpp\"\n");
		emit(file, "int main() {");
		for (std::vector<Statement*>::iterator child = stmts->begin(); child != stmts->end(); ++child) {
			(*child)->genCode(file);
		}
		emit(file, "return 0;");
		emit(file, "}");
	}
	
	unsigned int genStoreCode(FILE* file) {}
   
};
