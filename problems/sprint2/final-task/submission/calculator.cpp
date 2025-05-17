#include <cmath>
#include "calculator.h"

Number Calculator::Calculate(QString action, Number num) const{
    if (action == "+"){
        return (number_ + num);
    }
    else if (action == "−"){
        return (number_ - num);
    }
    else if (action == "×"){
        return (number_ * num);
    }
    else if (action == "÷"){
        return (number_ / num);
    }
    else if (action == "^"){
        return (std::pow(number_,num));
    }
}