#ifndef BF_TOKEN_H
#define BF_TOKEN_H

typedef enum{
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_COMMA,
    TOKEN_DOT,
    TOKEN_LEFT,
    TOKEN_RIGHT,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_EOF   //END OF FILE
}TokenType;

typedef struct{
    TokenType type;
    unsigned int line;
    unsigned int position;
    unsigned int offset;    //mousequerramienta
    unsigned int jumpTo;    //mousequerramienta 2.0
}Token;
#endif