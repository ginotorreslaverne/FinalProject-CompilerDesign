%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
int temp_count = 0;

// Function to generate a temporary variable
char* new_temp() 
{
    static char buffer[16];
    sprintf(buffer, "t%d", temp_count++);
    return buffer;
}

// Storage for intermediate code
typedef struct 
{
    char* code;
    char* place;
} Node;

#define YYSTYPE Node
%}

%token NUMBER LPAREN RPAREN PLUS MULT

%%
program:
    expression { printf("Generated Code:\n%s", $1.code); free($1.code); free($1.place); }
;

expression:
    expression PLUS term 
  {
        char *temp = new_temp();
        asprintf(&$$.code, "%s%s%s = %s + %s\n", $1.code, $3.code, temp, $1.place, $3.place);
        asprintf(&$$.place, "%s", temp);
        free($1.code); free($1.place); free($3.code); free($3.place);
  }
  | term 
  {
        $$.code = $1.code;
        $$.place = $1.place;
  }
;

term:
    term MULT factor 
  {
        char *temp = new_temp();
        asprintf(&$$.code, "%s%s%s = %s * %s\n", $1.code, $3.code, temp, $1.place, $3.place);
        asprintf(&$$.place, "%s", temp);
        free($1.code); free($1.place); free($3.code); free($3.place);
  }
  | factor 
  {
        $$.code = $1.code;
        $$.place = $1.place;
  }
;

factor:
    LPAREN expression RPAREN 
  {
        $$.code = $2.code;
        $$.place = $2.place;
  }
  | NUMBER 
  {
        asprintf(&$$.code, "");
        asprintf(&$$.place, "%d", $1);
  }
;
%%

void yyerror(const char *s) 
{
    fprintf(stderr, "Error: %s\n", s);
}

int main() 
{
    return yyparse();
}
