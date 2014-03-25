#include "header.h"
#include "preprocessor.h"
#include "keywords.h"
#include "lex.h"

using namespace std;

int main() {
    string file_name;
    cout<<"Enter File Name :";
    cin>>file_name;
    file_name = preprocessor(file_name);
    cout<<file_name;
    freopen(file_name.c_str(), "r", stdin);
    string s;
    static map<int,string> keyWord = {{0, "eoi"},{1, "auto"},{2, "break"},{3, "case"},{4, "char"},{5, "const"},{6, "continue"},{7, "default"},{8, "do"},{9, "double"},{10, "else"},{11, "enum"},{12, "extern"},{13, "float"},{14, "for"},{15, "goto"},{16, "if"},{17, "int"},{18, "long"},{19, "register"},{20, "return"},{21, "short"},{22, "signed"},{23, "sizeof"},{24, "static"},{25, "struct"},{26, "switch"},{27, "typedef"},{28, "union"},{29, "unsigned"},{30, "void"},{31, "volatile"},{32, "while"},{33, "identifier"},{40, "plus"},{41, "minus"},{42, "times"},{43, "div"},{44, "modulo"},{45, "equals"},{46, "pluseq"},{47, "minuseq"},{48, "timeseq"},{49, "diveq"},{50, "moduloeq"},{51, "empeq"},{52, "oreq"},{53, "xoreq"},{54, "lshifteq"},{55, "rshifteq"},{56, "bitand"},{57, "bitor"},{58, "bitxor"},{59, "lshift"},{60, "rshift"},{61, "not"},{62, "and"},{63, "or"},{64, "requals"},{65, "ne"},{66, "incr"},{67, "decr"},{68, "lt"},{69, "lte"},{70, "gt"},{71, "gte"},{80, "hash"},{81, "dollar"},{82, "atrate"},{83, "ls"},{84, "rs"},{85, "lb"},{86, "rb"},{87, "lp"},{88, "rp"},{89, "qmark"},{90, "colon"},{91, "dot"},{92, "ptrref"},{93, "semi"},{94, "comma"},{95, "number"},{96, "number"},{97, "number"},{98, "number"},{99, "identifier"},{100, "identifier"},{101, "identifier"},};
    int d = 1;
    while(d) {
        d = yylex();
        s.assign(yytext, yytext + yyleng);
        if(d>0){
		  cout << keyWord[d] << endl ;
        }
   }
    fclose(stdin);
    return 0;
}
