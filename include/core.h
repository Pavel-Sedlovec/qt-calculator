#ifndef CORE_H
#define CORE_H

#include <string>
#include <vector>

enum TokenType { MULL, DIV, PLUS, MINUS, NUMBER, LPAREN, RPAREN, FUNC, FACT, VARIABLE };

struct Token
{
    TokenType type;
    double value;
    std::string funcName;
};

struct ParseResult {
    double value = 0.0;
    bool isSuccess = true;
    std::string error_message;
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
    Parser(std::vector<Token>& tokens);

    ParseResult parse();

    ParseResult parse(double x);

    ParseResult expression(double x);

    ParseResult term(double x);

    ParseResult factor(double x);
};

std::vector<Token> tokenize(std::string str);

#endif // CORE_H
