
#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "rational.h"
#include "pow.h"

#include <QString>

using Error = std::string;

// Реализация шаблонного калькулятора.

template <typename Number>
class Calculator
{
public:
    void Set(double num){
        number_ = num;
    }
    Number Get() const{
        return number_;
    }

    std::optional<Error> Calculate(QString action, Number num) const{
        std::optional<Number> result;
        std::optional <Error> error_txt = std::nullopt;
        if (action == "+"){

            result = number_ + num;
        }
        else if (action == "−"){
            result = number_ - num;
        }
        else if (action == "×"){
            result = number_ * num;
        }
        else if (action == "÷"){     // подумать тут
            error_txt = CheckDivision(num);
            result = number_ / num;
        }
        else if (action == "^"){
            if(is_zero(number_,num)){
                return "Zero power to zero";
            }
            else if (std::is_same_v<Number, Rational>) // тут про знаменатель
                result = power(number_,num);


        }
        if (result.has_value()){
            return error_txt;
        }
        else{
            return error_txt;
        }

    }


    bool is_zero = [](const Number a,const Number b){
        return a == 0? a == b : false;
    };

private:
    Number number_;
    std::optional<Error> CheckDivision(Number num){
        if constexpr (num == 0 &&
                      (std::is_integral_v<Number>
                        || std::is_same_v<Number, Rational>)){
            return "Division by zero";
       }
    }
};

template <typename T>
auto power (const T num1,const T num2){

    return IntegerPow(num1, num2);
};

auto power (const Rational num1,const Rational num2){

    return Pow (num1, num2);
};


