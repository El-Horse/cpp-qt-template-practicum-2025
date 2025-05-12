#pragma once


#include <compare>
#include <cstdint>
#include <iostream>

#include <numeric>
#include <cstdlib>

class Rational {
public:
    Rational(int numerator = 0, int denominator = 1)
        : numerator_(numerator)
        , denominator_(denominator) {
        if (denominator_ == 0) {
            std::abort();
        }
        // Приводим дробь к правильному формату.
        Reduction();
    };

    int GetNumerator() const{ return numerator_;}

    int GetDenominator() const{return denominator_;}

    Rational Inv() const{
        Rational temp {denominator_, numerator_};
        temp.Reduction();
        return temp;

    }

    Rational operator+() const { return *this;}

    Rational operator-() const{ return Rational{-numerator_, denominator_};}

    Rational operator+(const Rational& r2) const {
        Rational other{*this};
        other += r2;

        return other;
    }
    Rational operator-(const Rational &r2) const{
        Rational other{*this};
        other -= r2;
        return other;
    }

    Rational operator*(const Rational& r2) const{
        Rational other{*this};
        other *= r2;
        return other;
    }

    Rational operator/(const Rational& r2) const{
        Rational other{*this};
        other /= r2;
        return other;
    }

    bool operator==(const Rational& r) const {
        return (numerator_ == r.numerator_) &&
               (denominator_ == r.denominator_);
    }
    auto operator<=> (const Rational& other) const{

        std::int64_t left = static_cast<std::int64_t> (numerator_) * other.denominator_;
        std::int64_t right = static_cast<std::int64_t> (other.numerator_) * denominator_;

        return left <=> right;
    }

    Rational& operator+=(const Rational &other){
        int d_common  = denominator_ * other.denominator_;
        int n_common = (numerator_ * other.denominator_)+(other.numerator_ * denominator_);
        numerator_ = n_common;
        denominator_ = d_common;
        Reduction();
        return *this;
    };

    Rational& operator-=(const Rational &other){
        int d_common  = denominator_ * other.denominator_;
        int n_common = (numerator_ * other.denominator_)-(other.numerator_ * denominator_);
        numerator_ = n_common;
        denominator_ = d_common;
        Reduction();
        return *this;
    };

    Rational& operator*=(const Rational& other){
        numerator_ *= other.numerator_;
        denominator_ *= other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational& other){
        numerator_ *= other.denominator_;
        denominator_ *= other.numerator_;
        Reduction();
        return *this;
    }




    friend std::istream& operator>> (std::istream &is, Rational& num);
    friend std::ostream& operator<< (std::ostream &os, const Rational &num);
private:

    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;
};



inline std::istream& operator>> (std::istream &is, Rational& r){
    int num, den;
    char div;
    is >> num;
    if (is.fail())
        return is;
    is >> div;
    if (is.fail() || div != '/'){
        is.clear();
        is.unget();
        r.numerator_ = num;
        return is;
    }
    else
        is >> den;
    if (den == 0)
        is.setstate(std::_S_failbit);
    if(!is.fail()){
        r.numerator_ = num;
        r.denominator_ = den;

    }
    return is;
}

inline std::ostream& operator<< (std::ostream &os, const Rational &num){
    os << num.numerator_;
    if (num.denominator_ != 1){
        os << " / " << num.denominator_;
    }
    return os;
}
