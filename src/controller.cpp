#include<string>
#include <controller.h>
#include <core.h>

CalcRes Controller::processExpression(const std::string& expression){

    std::vector<Token> vec = tokenize(expression);

    Parser parser(vec);
    if(check_variable(vec)){
        return paint_chart(vec);
    }

    ParseResult parseResult = parser.parse();
    CalcRes calcRes(parseResult);

    return calcRes;

}

bool Controller::check_variable(std::vector<Token>& vec){
    for(int i = 0; i < vec.size(); i++){
        if(vec[i].type == VARIABLE){
            return true;
        }
    }
    return false;
}

CalcRes Controller::paint_chart(std::vector<Token> vec){
    CalcRes calcRes;
    calcRes.isGraph = true;

    Parser parser(vec);

    int pointsCount = 101;
    calcRes.xData.resize(pointsCount);
    calcRes.yData.resize(pointsCount);

    double xStart = -10.0;
    double xEnd = 10.0;
    double step = (xEnd - xStart) / (pointsCount - 1);

    for(int i = 0; i < pointsCount; i++){
        calcRes.xData[i] = xStart + i*step;
        ParseResult parseResult = parser.parse(calcRes.xData[i]);
        if(parseResult.isSuccess){
            calcRes.yData[i] = parseResult.value;
        }
    }

    return calcRes;
}
