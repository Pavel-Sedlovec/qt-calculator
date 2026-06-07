#include <string>
#include <vector>
#ifndef CORE_H
#define CORE_H

enum TokenType { MULL, DIV, PLUS, MINUS, NUMBER, LPAREN, RPAREN };

struct Token
{
    TokenType type;
    double value;
};

class Core
{
public:
    Core();
};

class Parser
{
private:
    int pos;
    std::vector<Token> tokens;

public:
    Parser(std::vector<Token> tokens);

    double parse();

    double expression();

    double term();

    double factor();
};

std::vector<Token> tokenize(std::string str);

#endif // CORE_H
