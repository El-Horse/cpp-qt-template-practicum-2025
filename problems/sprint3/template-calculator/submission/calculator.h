
#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "enums.h"
#include "rational.h"
#include "pow.h"

#include <QString>

using Error = std::string;

// Реализация шаблонного калькулятора.
template <typename T>
T power (const T num1,const T num2){

    return IntegerPow(num1, num2);
};

Rational power (const Rational num1,const Rational num2){

    return Pow (num1, num2);
};

template <typename Number>
class Calculator
{
public:
    void Set(double num){
        number_ = num;
    }
    Number GetNumber() const{return number_;}
    void Save(Number n){memory_ = n;}
    Number Load(){number_ = memory_;}
    bool GetHasMem(){return memory_.has_value();}

    Number Add (Number n){return number_ + n;}
    Number Sub (Number n){return number_ - n;}
    Number Mul (Number n){return number_ * n;}
    Number Div(Number n){
        error_txt_ = CheckDivision(n);
        if (!error_txt_.has_value())
            return 0;
        return number_ / n;
    }
    Number Pow (Number num){
        if(is_zero(number_,num)){ // 0^0
            error_txt_ = "Zero power to zero";
            return 0;
            }
        else if constexpr (std::is_same_v<Number, Rational>){ // тут про знаменатель
            std::optional<Rational> den = num.denominator_;
            if (den != 1){
                error_txt_ = "Fractional power is not supported";
                return 0;
            }
        }
            else if constexpr (std::is_integral_v<Number>){
                if (num <0){
                    error_txt_ = "Integer negative power";
                    return 0;
                }
        }
        return power(number_,num);
    }







    // std::optional<Error> Calculate
    //     ( std::optional<Operation> action, const Number num, Number& result) const{
    //     // Number result;
    //     std::optional <Error> error_txt = std::nullopt;
    //     if (action == Operation::ADDITION){

    //         result = number_ + num;
    //     }
    //     else if (action == Operation::SUBTRACTION){
    //         result = number_ - num;
    //     }
    //     else if (action == Operation::MULTIPLICATION){
    //         result = number_ * num;
    //     }
    //     else if (action == Operation::DIVISION){     // подумать тут
    //         error_txt = CheckDivision(num);
    //         result = number_ / num;
    //     }
    //     else if (action == Operation::POWER){
    //         if(is_zero(number_,num)){
    //             return "Zero power to zero";
    //         }
    //         else if constexpr (std::is_same_v<Number, Rational>){ // тут про знаменатель
    //             std::optional<Rational> den = num.denominator_;
    //             if (den != 1){
    //                 return "Fractional power is not supported";
    //             }
    //         }
    //         else if constexpr (std::is_integral_v<Number>
    //                              && num < 0){
    //             return "Integer negative power";
    //         }
    //         result = power(number_,num);
    //     }

    //     return error_txt;
    // }


    bool is_zero = [](const Number a,const Number b){
        return a == 0? a == b : false;
    };

private:
    Number result_;
    std::optional<Number> memory_;
    Number number_;
    std::optional<Error> error_txt_ = std::nullopt;
    std::optional<Error> CheckDivision(Number num){
        if constexpr (num == 0 &&
                      (std::is_integral_v<Number>
                        || std::is_same_v<Number, Rational>)){
            return "Division by zero";
       }
    }
};




