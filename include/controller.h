#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QVector>
#include <QString>
#include <core.h>

struct  CalcRes{
    bool isSuccess = true;
    bool isGraph = false;
    double result = 0.0;
    QVector<double> xData;
    QVector<double> yData;
    QString errorMessage;

    CalcRes() = default;

    CalcRes(const ParseResult& parseResult){
        isSuccess = parseResult.isSuccess;
        result = parseResult.value;
        errorMessage = QString::fromStdString(parseResult.error_message);
    }
};

class Controller {
public:
    CalcRes processExpression(const std::string& expression);
    bool check_variable(std::vector<Token>& vec);
    CalcRes paint_chart(std::vector<Token> vec);
};

#endif // CONTROLLER_H
