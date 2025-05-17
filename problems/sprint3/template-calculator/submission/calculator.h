
#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "rational.h"
#include "pow.h"

#include <QString>

#define NoError std::nullopt;

using Error = std::string;

// Реализация шаблонного калькулятора.

template <typename Number>
class Calculator
{
public:
    void Set(Number num){
        number_ = num;
    }
    Number GetNumber() const{return number_;}
    void Save(){memory_.value() = number_;}
    void Load(){number_ = memory_.value();}
    bool GetHasMem(){return memory_.has_value();}

    std::optional<Error> Add (Number n){number_ += n;return NoError;}
    std::optional<Error> Sub (Number n){number_ -= n;return NoError;}
    std::optional<Error> Mul (Number n){number_ *= n;return NoError;}
    std::optional<Error> Div(Number n){
        std::optional<Error>error_txt = CheckDivision(n);
        if (error_txt.has_value())
            return error_txt;
        number_ /= n;
        return NoError;
    }

    std::optional<Error> Pow (Number num){
        if(number_ == 0 && num == 0){ // 0^0
            return "Zero power to zero";
        }
        else if constexpr (std::is_same_v<Number, Rational>){ // тут про дробь
            if (num.GetDenominator() != 1){
                return "Fractional power is not supported";
            }
            number_ = ::Pow (number_, num);
        }
        else if constexpr (std::is_integral_v<Number>){
            if (num <0){
                return "Integer negative power";
            }
            number_ = IntegerPow(number_, num);
        }
        else if constexpr (std::is_same_v<Number,double> || std::is_same_v<Number,float>){
            number_ = std::pow(number_,num);
        }
        return NoError;
    }


    // bool is_zero = [](const Number a,const Number b){
    //     return a == 0? a == b : false;
    // };

private:
    Number result_;
    std::optional<Number> memory_;
    Number number_;
    // std::optional<Error> error_txt_ = std::nullopt;
    std::optional<Error> CheckDivision(Number num){
        if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>){
            if (num == 0 ){return "Division by zero";}
        }
        return std::nullopt;
    }
};








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
