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
    int d = 1;
    while(d) {
        d = yylex();
        s.assign(yytext, yytext + yyleng);
        if(d>=1 && d<=33)
            cout<<"< "<<s<<" , keyword >\n";
        else if(d>=40 && d<=71)
            cout<<"< "<<s<<" , operator >\n";
        else if(d>=80 && d<=94)
            cout<<"< "<<s<<" , symbol >\n";
        else if(d>=95 && d<=98)
            cout<<"< "<<s<<" , constant >\n";
        else if(d==99)
            cout<<"< "<<s<<" , identifier >\n";
        else if(d==100)
            cout<<"< "<<s<<" , string >\n";
        else if(d==101)
            cout<<"< "<<s<<" , character >\n";
    }
    fclose(stdin);
    return 0;
}
