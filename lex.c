#include "lex.h"
#include <stdio.h>
#include <ctype.h>


char* yytext = ""; /* Lexeme (not '\0'
                      terminated)              */
int yyleng   = 0;  /* Lexeme length.           */
int yylineno = 0;  /* Input line number        */
  

int lex(void){

   static char input_buffer[1024];
   char        *current;
   int first_char_is_digit = 0;
   int invalid_num= 0;

   current = yytext + yyleng; /* Skip current
                                 lexeme        */

   while(1){       /* Get the next one         */
      while(!*current ){
         /* Get new lines, skipping any leading
         * white space on the line,
         * until a nonblank line is found.
         */

         
         if(!gets(input_buffer)){
            *current = '\0' ;

            return EOI;
         }
         current = input_buffer;
         ++yylineno;
         while(isspace(*current))
            ++current;
      }
      for(; *current; ++current){
         /* Get the next token */
         yytext = current;
         yyleng = 1;
         switch( *current ){
           case '<':
            printf("LT\n");
            return LT;
           case '>':
            printf("GT\n");
            return GT;
           case ';':
            printf("semi colon\n");
            return SEMI;
           case '+':
           printf("plus\n");
            return PLUS;
           case '-':
           printf("minus\n");
            return MINUS;
           case '*':
           printf("mul\n");
            return TIMES;
           case '/':
           printf("div\n");
            return DIV;
           case '(':
            printf("lp\n");
            return LP;
           case ')':
            printf("rp\n");
            return RP;
           case '\n':
           case '\t':
           case ' ' :
            break;
           default:
            if(!isalnum(*current))
               fprintf(stderr, "Agvonse la8emevn eisagwgn <%c>\n", *current);
            else{               

               if(isdigit(*current)) 
                  first_char_is_digit = 1;
               
                current++;
               while(isalnum(*current)){
                  if(isalpha(*current)){

                    if(first_char_is_digit && !invalid_num)
                        invalid_num = 1;
                  }

                  
                  ++current;
               }

               yyleng = current - yytext;
               if(invalid_num)
                  fprintf(stderr, "Neither number nor id\n");
               else
                  if(first_char_is_digit)
                      return NUM;
                  else
                      return ID;
            }
            break;
         }
      }
   }
}


static int Lookahead = -1; /* Lookahead token  */

int match(int token){
   /* Return true if "token" matches the
      current lookahead symbol.                */

   if(Lookahead == -1)
      Lookahead = lex();

   return token == Lookahead;
}

void advance(void){
/* Advance the lookahead to the next
   input symbol.                               */

    Lookahead = lex();
}
