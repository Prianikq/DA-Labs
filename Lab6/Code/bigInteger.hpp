#pragma once
#include <iostream>
#include <vector>
#include <string>
namespace NMyStd {
    class TBigInteger {
        public:
            static const int BASE = 10000;
            static const int RADIX = 4;
            TBigInteger() = default;
            TBigInteger(const std::string&);
            void RemoveLeadZeros();
            friend std::istream& operator>>(std::istream&, TBigInteger&);
            friend std::ostream& operator<<(std::ostream&, const TBigInteger&);
            TBigInteger operator+(const TBigInteger&) const;
            TBigInteger operator-(const TBigInteger&) const;
            TBigInteger operator*(const TBigInteger&) const;
            TBigInteger operator/(const TBigInteger&) const;
            friend TBigInteger Pow(const TBigInteger&, const TBigInteger&);
            bool operator<(const TBigInteger&) const;
            bool operator>(const TBigInteger&) const;
            bool operator==(const TBigInteger&) const;
        private:
            std::vector<int32_t> Number;
    };
    const TBigInteger ZERO = TBigInteger("0"), ONE = TBigInteger("1"), TWO = TBigInteger("2");
}
