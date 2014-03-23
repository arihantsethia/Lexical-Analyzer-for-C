#include "header.h"
#include "keywords.h"
#include "lex.h"

using namespace std;

char* yytext = "";
int yyleng   = 0;
int yylineno = 0;
int Lookahead = -1;
static unordered_map<string,int> keys= {{"auto",1}, {"break",2}, {"case",3}, {"char",4}, {"const",5}, {"continue",6}, {"default",7}, {"do",8}, {"double",9}, {"else",10}, {"enum",11}, {"extern",12}, {"float",13}, {"for",14}, {"goto",15}, {"if",16}, {"int",17}, {"long",18}, {"register",19}, {"return",20}, {"short",21}, {"signed",22}, {"sizeof",23}, {"static",24}, {"struct",25}, {"switch",26}, {"typedef",27}, {"union",28}, {"unsigned",29}, {"void",30}, {"volatile",31}, {"while",32}, {"main",33}, {"+",40}, {"-",41}, {"*",42}, {"/",43}, {"%",44}, {"=",45}, {"+=",46}, {"-=",47}, {"*=",48}, {"/=",49}, {"%=",50}, {"&=",51}, {"|=",52}, {"^=",53}, {"<<=",54}, {">>=",55}, {"&",56}, {"|",57}, {"^",58}, {"<<",59}, {">>",60}, {"!",61}, {"&&",62}, {"||",63}, {"==",64}, {"!=",65}, {"++",66}, {"--",67}, {"<",68}, {"<=",69}, {">",70}, {">=",71}, {"#",80}, {"$",81}, {"@",82}, {"[",83}, {"]",84}, {"{",85}, {"}",86}, {"(",87}, {")",88}, {"?",89}, {":",90}, {".",91}, {"->",92},{",",93},{";",94}};
static unordered_map<char,bool> msymbols= {{'+',1}, {'-',1}, {'*',1}, {'/',1}, {'%',1}, {'=',1}, {'&',1}, {'|',1}, {'^',1}, {'!',1}, {'<',1}, {'>',1}};
static unordered_map<char,bool> ssymbols= {{'#',1}, {'$',1}, {'@',1}, {'[',1}, {']',1}, {'{',1}, {'}',1}, {'(',1}, {')',1}, {'?',1}, {':',1}, {'.',1}, {';',1}, {',',1}};
static unordered_map<char,bool> nseparators= {{']',1},{')',1},{'}',1}, {'?',1}, {':',1}, {';',1}, {',',1}};
static unordered_map<char,bool> escapechars= {{'a',1},{'b',1},{'f',1},{'n',1},{'r',1},{'t',1},{'v',1},{'\'',1},{'\"',1},{'\\',1},{'\?',1}};
int yylex() {
    static char input_buffer[10000];
    char *current = yytext + yyleng;
    string s;
    while(1) {
        while(!*current ) {
            current = input_buffer;
            if(!gets(input_buffer)) {
                *current = '\0' ;
                return EOI;
            }
            ++yylineno;
            while(isspace(*current))
                ++current;
        }
        for(; *current; ++current) {
            yytext = current;
            yyleng = 1;
            s="";
            if(*current!=' ' && *current!='\n' && *current!='\t') {
                bool flag = true;
                while(msymbols.find (*current) != msymbols.end()) {
                    flag = false;
                    s+=*current;
                    current++;
                }
                if(flag) {
                    if(ssymbols.find (*current) != ssymbols.end()) {
                        flag = false;
                        s+=*current;
                        current++;
                    }
                }
                if(!flag) {
                    for(int i=s.length(); i>=1 ; i--) {
                        if(keys.find(s.substr(0,i))!=keys.end()) {
                            yyleng = current - yytext;
                            return keys[s.substr(0,i)];
                        }
                        current--;
                    }
                    fprintf( stderr, "%s\'%s\'%s is not a valid symbol\n",KRED,s.c_str(),KNRM);
                    exit(1);
                } else {
                    flag = false;
                    if(isdigit(*current)) {
                        while(isdigit(*current)) {
                            s+=*current;
                            current++;
                        }
                        if(*current == '.') {
                            s+=*current++;
                            while(isdigit(*current)) {
                                flag = true;
                                s+=*current;
                                current++;
                            }
                            if(!flag) {
                                fprintf( stderr, "%s\'%s\'%s not a valid floating point number. Contains more than one dots.\n",KRED,s.c_str(),KNRM);
                                exit(1);
                            }
                        }
                        if(*current == 'e' || *current == 'E') {
                            flag = false;
                            s+=*current++;
                            if(*current=='+' || *current == '-')
                                s+=*current++;
                            while(isdigit(*current)) {
                                flag = true;
                                s+=*current;
                                current++;
                            }
                            if(!flag) {
                                fprintf( stderr, "%s\'%s\'%s should have atleast 1 digit after E \n",KRED,s.c_str(),KNRM);
                                exit(1);
                            }
                        }
                        if(isspace(*current) || msymbols.find (*current) != msymbols.end() || nseparators.find (*current) != nseparators.end()) {
                            yyleng = current - yytext;
                            if(flag)
                                return DOUBLE;
                            else
                                return NUMBER;
                        } else {
                            fprintf( stderr, "%s\'%s\'%s number is not properly formatted\n",KRED,s.c_str(),KNRM);
                            exit(1);
                        }
                    } else {
                        while(isalnum(*current) || *current == '_') {
                            flag = true;
                            s+=*current;
                            current++;
                        }
                        if(flag) {
                            yyleng = current - yytext;
                            if(keys.find(s)!=keys.end())
                                return keys[s];
                            else {
                                if(isalpha(s[0])||s[0]=='_') {
                                    if(is_identifier(s))
                                        return ID;
                                    fprintf( stderr, "%s\'%s\'%s is not a valid identifier.\n",KRED,s.c_str(),KNRM);
                                    exit(1);
                                }
                            }
                        } else {
                            if(*current == '\'') {
                                s+=*current++;
                                if(*current=='\\') {
                                    s+=*current;
                                    *current++;
                                }
                                if(!*current) {
                                    fprintf( stderr, "%s\'%s\'%s is not valid character. ' is expected.\n",KRED,s.c_str(),KNRM);
                                    exit(1);
                                }
                                s+=*current++;
                                if(*current == '\'') {
                                    s+='\'';
                                    *current++;
                                    yyleng = current - yytext;
                                    return CHARACTER;
                                }
                                fprintf( stderr, "%s\'%s\'%s is not a valid character.\n",KRED,s.c_str(),KNRM);
                                exit(1);

                            } else if(*current == '\"') {
                                s+=*current++;
                                while(*current!='\"') {
                                    s+=*current;
                                    if(*current=='\\') {
                                        *current++;
                                        s+=*current;
                                    }
                                    if(!*current) {
                                        fprintf( stderr, "%s\'%s\'%s \" is expected.\n",KRED,s.c_str(),KNRM);
                                        exit(1);
                                    }
                                    current++;
                                }
                                s+='\"';
                                current++;
                                yyleng = current - yytext;
                                return STRING;
                            }
                            fprintf( stderr, "%s\'%s\'%s is not a valid string\n",KRED,s.c_str(),KNRM);
                            exit(1);
                        }
                    }
                }
            }
        }
    }
    return 0;
}

bool is_identifier(string s) {
    if(isalpha(s[0])||s[0]=='_') {
        for(int i=1; i<s.length(); i++)
            if(!isdigit(s[i]) && !isalpha(s[i]) && s[i]!='_') {
                fprintf( stderr, "%s\'%s\'%s is not declared in scope\n",KRED,s.c_str(),KNRM);
                exit(1);
            }
    } else {
        fprintf( stderr, "%s\'%s\'%s identifier should start with an alphabet or _ \n",KRED,s.c_str(),KNRM);
        exit(1);
    }
    return ID;
}

bool is_num(string s) {
    for(int i=0; i<s.length(); i++)
        if(!isdigit(s[i])||s[i]=='.') {
            return false;
        }
    return true;
}

bool is_double(string s) {
    int pos = s.find('.');
    if(pos<=0) {
        fprintf( stderr, "%s\'%s\'%s should start with 0 \n",KRED,s.c_str(),KNRM);
        exit(1);
    } else if(pos==s.length()-1) {
        fprintf( stderr, "%s\'%s\'%s should have atleast 1 digit after decimal point \n",KRED,s.c_str(),KNRM);
        exit(1);
    } else if(pos<s.length()) {
        if(is_num(s.substr(0,pos)) && is_num(s.substr(pos+1)))
            return true;
        else
            return false;
    }
}

int match(int token) {
    if(Lookahead == -1)
        Lookahead = yylex();
    return token == Lookahead;
}

void advance(void) {
    Lookahead = yylex();
}
