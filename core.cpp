#include "core.h"
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

Core::Core() {}

std::vector<Token> tokenize(std::string str)
{
    std::vector<Token> tokens;
    int i = 0;
    std::string num;
    while (i < str.length()) {
        if (str[i] == ' ') {
            i++;
            continue;
        }

        if (std::isdigit(str[i]) || str[i] == ',') {
            num += str[i++];
            continue;
        } else {
            if (num != "") {
                Token toc;
                toc.type = NUMBER;
                toc.value = std::stod(num);
                num = "";
                tokens.push_back(toc);
            }
        }

        if (str[i] == '+') {
            Token toc;
            toc.type = PLUS;
            tokens.push_back(toc);
        } else if (str[i] == '-') {
            Token toc;
            toc.type = MINUS;
            tokens.push_back(toc);
        } else if (str[i] == '/') {
            Token toc;
            toc.type = DIV;
            tokens.push_back(toc);
        } else if (str[i] == '*') {
            Token toc;
            toc.type = MULL;
            tokens.push_back(toc);
        } else if (str[i] == '(') {
            Token toc;
            toc.type = LPAREN;
            tokens.push_back(toc);
        } else if (str[i] == ')') {
            Token toc;
            toc.type = RPAREN;
            tokens.push_back(toc);
        }
        i++;
    }
    if (num != "") {
        Token toc;
        toc.type = NUMBER;
        toc.value = std::stod(num);
        tokens.push_back(toc);
    }
    return tokens;
}

Parser::Parser(std::vector<Token> tokens)
{
    this->tokens = tokens;
    pos = 0;
}

double Parser::parse()
{
    double result = expression();
    return result;
}

double Parser::expression()
{
    double first = term();

    while (pos < tokens.size() && (tokens[pos].type == PLUS || tokens[pos].type == MINUS)) {
        TokenType op = tokens[pos].type;
        pos++;

        double second = term();
        if (op == PLUS)
            first += second;
        if (op == MINUS)
            first -= second;
    }
    return first;
}

double Parser::term()
{
    double first = factor();

    while (pos < tokens.size() && (tokens[pos].type == MULL || tokens[pos].type == DIV)) {
        TokenType op = tokens[pos].type;
        pos++;

        double second = factor();
        if (op == MULL)
            first *= second;
        if (op == DIV) {
            if (second == 0.0) {
                throw std::runtime_error("Div by 0.0");
            }
            first /= second;
        }
    }
    return first;
}

double Parser::factor()
{
    if (tokens[pos].type == LPAREN) {
        pos++;
        double result = expression();
        if (pos >= tokens.size() || tokens[pos].type != RPAREN) {
            throw std::runtime_error("There is no closing parenthesis");
        }
        pos++;
        return result;
    }
    if (tokens[pos].type == NUMBER) {
        double val = tokens[pos].value;
        pos++;
        return val;
    }

    if (tokens[pos].type == MINUS) {
        pos++;
        return -factor();
    }
    throw std::runtime_error("Syntax error");
    return 0;
}
