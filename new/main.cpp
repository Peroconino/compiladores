#include "main.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char buffer[BUFFER_SIZE];
  int ini = 0, prox = 0, line = 1, column = 1;
  bool eof = false, has_lookahead = false;
  FILE *file;
} State;

State state;

void ReadFile(FILE *input) {
  fread(state.buffer, sizeof(char), BUFFER_SIZE, input);
}

bool NotLetterUnderlineOrDigit(char c) {
  return (!isalpha(c) || !isdigit(c) || c != '_');
}

char getNextChar() {
  char c;
  do {

    c = state.buffer[state.ini++];

    if (c == '\n') {
      state.line++;
      state.column = 1;
    } else {
      state.column++;
    }
  } while (isspace(c));
  return c;
}

Token *getNextToken() {
  int estado = 0;
  while (true) {
    switch (estado) {
    case 0: {
      char c = getNextChar();
      if (c == ')') {
        estado = 1; // x2
      } else if (c == '(') {
        estado = 2; // w2
      } else if (c == '\'') {
        estado = 3; // v2
      } else if (c == '*') {
        estado = 5; // t2
      } else if (c == '/') {
        estado = 6; // s3
      } else if (c == '-') {
        estado = 7; // r3
      } else if (c == '+') {
        estado = 8; // r2
      } else if (c == '!') {
        estado = 9; // q10
      } else if (c == '<') {
        estado = 10; // q7
      } else if (c == '>') {
        estado = 11; // q4
      } else if (c == '=') {
        estado = 12; // q2
      } else if (c == ',') {
        estado = 13; // y3
      } else if (c == ';') {
        estado = 14; // y2
      } else if (c == ':') {
        estado = 15; // z2
      } else if (c == '{') {
        estado = 16; // a2
      } else if (isdigit(c)) {
        estado = 17; // b2
      } else if (c == 'm') {
        estado = 18; // d2
      } else if (c == 'v') {
        estado = 19; // e2
      } else if (c == 'i') {
        estado = 20; // f2
      } else if (c == 'c') {
        estado = 21; // g2
      } else if (c == 't') {
        estado = 22; // j2
      } else if (c == 'e') {
        estado = 23; // k2
      } else if (c == 'w') {
        estado = 24; // m2
      } else if (c == 'd') {
        estado = 25; // n2
      } else if (c == 'f') {
        estado = 26; // o2
      } else if (isalpha(c) || c == '_') {
        estado = 4; // u2
      }
      break;
    }
    case 1: {
      Token *token = (Token *)malloc(sizeof(Token));

      token->type = TOKEN_OPERATOR;
      token->operador = Operator::PARDIR;
      token->line = state.line;
      token->column = state.column;

      return token;
    }
    default: {
      Token *token = (Token *)malloc(sizeof(Token));
      token->type = TOKEN_ERROR;
      token->error = ErrorKind::UNKNOWN_TOKEN;
      return token;
    }
    }
  }
}

int lexer() {
  FILE *input = fopen("file.txt", "r");
  if (!input) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  ReadFile(input);

  Token *token;
  do {
    token = getNextToken();
    printf("<%d, %s>\n", token->type, token->value);
  } while (token->type != TOKEN_EOF && token->type != TOKEN_ERROR);

  fclose(input);

  return 0;
}

int main() {
  try {
    lexer();
  } catch (const exception &e) {
    cout << e.what() << endl;
  }
}
