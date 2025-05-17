#pragma once
#include <QString>


using Number = double;

class Calculator
{
public:
    void Set(double num){
        number_ = num;
    }
    Number Get() const{
        return number_;
    }

   Number Calculate(QString action, Number num) const;

private:
    Number number_;
};
