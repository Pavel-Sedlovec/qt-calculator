#include "core.h"
#include "parsermath.h"
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include<QDebug>

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

        if (std::isdigit(str[i]) || str[i] == '.') {
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
        else if(std::isalpha(str[i])){
            std::string funcName = "";
            funcName +=str[i];
            i++;
            while(i < str.length() && std::isalpha(str[i])){
                funcName +=str[i++];
            }
            if(funcName == "sin" || funcName == "cos" || funcName =="tan" || funcName == "log" || funcName == "ln"){
                Token toc;
                toc.type = FUNC;
                toc.funcName = funcName;
                tokens.push_back(toc);
            }
            else if(funcName == "x" || funcName =="X"){
                Token toc;
                toc.type = VARIABLE;
                toc.funcName = funcName;
                tokens.push_back(toc);
            }
            continue;
        }
        else if(str[i] == '!'){
            Token toc;
            toc.type = FACT;
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

Parser::Parser(std::vector<Token>& tokens)
{
    this->tokens = tokens;
    qDebug() << "Adress tokens" << &tokens;
    pos = 0;
}

ParseResult Parser::parse()
{

    pos = 0;
    if(tokens.size() <= 0) return {0.0, true, ""};
    ParseResult parseResult = expression(0.0);
    return parseResult;
}

ParseResult Parser::parse(double x)
{
    pos = 0;
    if(tokens.size() <= 0) return {0.0, true, ""};
    ParseResult parseResult = expression(x);
    return parseResult;
}

ParseResult Parser::expression(double x)
{
    ParseResult parseResultFirst = term(x);
    if(!parseResultFirst.isSuccess){
        return parseResultFirst;
    }

    while (pos < tokens.size() && (tokens[pos].type == PLUS || tokens[pos].type == MINUS)) {
        TokenType op = tokens[pos].type;
        pos++;

        ParseResult parseResultSecond = term(x);
        if(!parseResultSecond.isSuccess){
            return parseResultSecond;
        }

        if (op == PLUS)
            parseResultFirst.value += parseResultSecond.value;
        if (op == MINUS)
            parseResultFirst.value -= parseResultSecond.value;
    }
    return parseResultFirst;
}

ParseResult Parser::term(double x)
{
    ParseResult parseResultFirst = factor(x);

    while (pos < tokens.size() && (tokens[pos].type == MULL || tokens[pos].type == DIV)) {
        TokenType op = tokens[pos].type;
        pos++;

        ParseResult parseResultSecond = factor(x);
        if (op == MULL)
            parseResultFirst.value *= parseResultSecond.value;
        if (op == DIV) {
            if (parseResultSecond.value == 0.0) {
                return {0.0, false, "Div by 0.0"};
            }
            parseResultFirst.value /= parseResultSecond.value;
        }
    }
    return parseResultFirst;
}

ParseResult Parser::factor(double x)
{
    ParseResult parseResult;
    parseResult.value = 0.0;

    if(tokens[pos].type == FUNC){
        std::string funcName = tokens[pos].funcName;
        pos++;
        if(tokens[pos].type != LPAREN){
            return {0.0, false, "There is no opening parenthesis"};
        }
        pos++;

        parseResult = expression(x);

        if(!parseResult.isSuccess){
            return parseResult;
        }

        if (pos >= tokens.size() || tokens[pos].type != RPAREN) {
            return {0.0, false, "There is no closing parenthesis"};
        }
        pos++;
        parseResult = accept_func(funcName, parseResult.value);

        if(!parseResult.isSuccess){
            return parseResult;
        }
    }
    else if (tokens[pos].type == LPAREN) {
        pos++;
        parseResult = expression(x);

        if(!parseResult.isSuccess){
            return parseResult;
        }

        if (pos >= tokens.size() || tokens[pos].type != RPAREN) {
            return {0.0, false, "There is no closing parenthesis"};
        }
        pos++;
    }
    else if (tokens[pos].type == NUMBER) {
        parseResult.value = tokens[pos].value;
        pos++;
    }
    else if (tokens[pos].type == MINUS) {
        pos++;
        parseResult = factor(x);
        parseResult.value *= -1;

        if(!parseResult.isSuccess){
            return parseResult;
        }

    }
    else if(tokens[pos].type == VARIABLE){
        parseResult.value = x;
        pos++;
    }
    else{
        return {0.0, false, "Syntax error"};
    }

    while(pos < tokens.size() && tokens[pos].type == FACT){
        pos++;
        parseResult = accept_func("fact", parseResult.value);

        if(!parseResult.isSuccess){
            return parseResult;
        }
    }

    return parseResult;
}
