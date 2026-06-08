#include <string>
#include <vector>
#ifndef CORE_H
#define CORE_H

enum TokenType { MULL, DIV, PLUS, MINUS, NUMBER, LPAREN, RPAREN, FUNC, FACT, VARIABLE };

struct Token
{
    TokenType type;
    double value;
    std::string funcName;
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

    double parse(double x);

    double expression(double x);

    double term(double x);

    double factor(double x);
};

std::vector<Token> tokenize(std::string str);

#endif // CORE_H
