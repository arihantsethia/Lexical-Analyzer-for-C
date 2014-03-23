#ifndef LEX_H_INCLUDED
#define LEX_H_INCLUDED

extern char *yytext;
extern int yyleng;
extern int yylineno;
extern int Lookahead;

int yylex(void);
bool is_identifier(std::string);
bool is_num(std::string);
bool is_string(std::string);
bool is_double(std::string);
int match(int);
void advance(void);

#endif
