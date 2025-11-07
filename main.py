FILE_NAME = 'teste.c'
BLOCK_SIZE = 25

TOKENS = {
    "KEYWORDS": [
        "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "#include", "inline", "int", "long", "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
    ],
    "OPERADORES_ARITMETICOS": ["+", "-", "*", "/", "%", "++", "--"],
    "OPERADORES_RELACIONAIS": ["==", "!=", "<", ">", "<=", ">="],
    "OPERADORES_LOGICOS": ["&&", "||", "!"],
    "OPERADORES_BITWISE": ["&", "|", "^", "~", "<<", ">>"],
    "OPERADORES_ATRIBUICAO": ["=", "+=", "-=", "*=", "/=", "%=", "<<=", ">>=", "&=", "|=", "^="],
    "OPERADORES_PONTEIRO_E_ACESSO": ["->", ".", "*", "&"],
    "DELIMITADORES": ["(", ")", "{", "}", "[", "]"],
    "PONTUACAO": [";", ",", ":", "?"]
}

TOKEN_MAP = {}
for category, token_list in TOKENS.items():
    for token in token_list:
        TOKEN_MAP[token] = category


def is_separator(ch):
    """Caracteres que encerram tokens de palavra"""
    return ch.isspace() or ch in "(){}[];,.:+-*/%<>=!&|^~?"


def identify_keywords_file(file_name):
    tokens_found = []
    lexeme = ""   # buffer contínuo

    with open(file_name, "r") as f:
        while True:
            block = f.read(BLOCK_SIZE)
            if not block:
                break

            for ch in block:

                # Se é parte de um identificador/palavra (letra, número, _)
                if ch.isalnum() or ch == "_":
                    lexeme += ch
                    continue

                # Se chegou aqui, é porque o caractere atual NÃO faz parte de palavra
                # Então fecha o token anterior se existir
                if lexeme:
                    if lexeme in TOKEN_MAP:
                        tokens_found.append((lexeme, TOKEN_MAP[lexeme]))
                    lexeme = ""

                # Agora processa símbolos individuais ou operadores compostos
                possible_op = ch

                # Olha um caractere adiante SEM ler do arquivo (olhamos o bloco)
                # Isso permite identificar "==", "<=", ">=", "&&", etc.
                # Mas temos que garantir que existe próximo char
                next_index = block.index(ch) + 1
                if next_index < len(block):
                    next_ch = block[next_index]
                    two = possible_op + next_ch
                    if two in TOKEN_MAP:
                        tokens_found.append((two, TOKEN_MAP[two]))
                        # pular o próximo char manualmente deixaria o laço errado,
                        # então vamos marcar de outra forma (resolveremos abaixo)
                        continue

                # Operador/Delimitador/Pontuação de 1 caractere
                if possible_op in TOKEN_MAP:
                    tokens_found.append((possible_op, TOKEN_MAP[possible_op]))

        # Se terminar o arquivo com buffer de palavra aberto
        if lexeme:
            if lexeme in TOKEN_MAP:
                tokens_found.append((lexeme, TOKEN_MAP[lexeme]))

    return tokens_found

def main():
    keywords = identify_keywords_file(FILE_NAME)
    
    for keyword in keywords:
        print(keyword)


if __name__ == "__main__":
    main()
