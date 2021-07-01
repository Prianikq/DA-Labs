#include "bigInteger.hpp"
#include <iomanip>
#include <stdexcept>
#include <algorithm>
namespace NMyStd {
    TBigInteger::TBigInteger(const std::string& str) {
        Number.resize(str.size() / RADIX + 1);
        int counter = 1, index = 0;
        for (int i = str.size() - 1; i >= 0; --i) {
            Number[index] += static_cast<int>(str[i] - '0') * counter;
            counter *= 10;
            if (counter == BASE) {
                counter = 1;
                ++index;
            }
        }
        RemoveLeadZeros();
    }
    void TBigInteger::RemoveLeadZeros() {
        while (Number.size() > 1 && Number[Number.size() - 1] == 0) {
            Number.pop_back();
        }
    }
    std::istream& operator>>(std::istream& in, TBigInteger& num) {
        std::string input;
        in >> input;
        num = TBigInteger(input);
        return in;
    }
    std::ostream& operator<<(std::ostream& out, const TBigInteger& num) {
        if (num.Number.empty()) {
           out << "0";
           return out;
        }
        out << num.Number.back();
        for (int i = num.Number.size()-2; i >= 0; --i) {
            out << std::setfill('0') << std::setw(TBigInteger::RADIX) << num.Number[i];
        }
        return out;
    }
    bool TBigInteger::operator<(const TBigInteger& right) const {
        if (Number.size() != right.Number.size()) {
            return Number.size() < right.Number.size();
        }
        for (int i = Number.size() - 1; i >= 0; --i) {
            if (Number[i] != right.Number[i]) {
                return Number[i] < right.Number[i];
            }
        }
        return false;
    }
    bool TBigInteger::operator>(const TBigInteger& right) const {
        if (Number.size() != right.Number.size()) {
            return Number.size() > right.Number.size();
        }
        for (int i = Number.size() - 1; i >= 0; --i) {
            if (Number[i] != right.Number[i]) {
                return Number[i] > right.Number[i];
            }
        }
        return false;
    }
    bool TBigInteger::operator==(const TBigInteger& right) const {
        if (Number.size() != right.Number.size()) {
            return false;
        }
        for (int i = Number.size() - 1; i >= 0; --i) {
            if (Number[i] != right.Number[i]) {
                return false;
            }
        }
        return true;
    }
    TBigInteger TBigInteger::operator+(const TBigInteger& value) const {
        TBigInteger result;
        size_t size = std::max(Number.size(), value.Number.size());
        result.Number.resize(size);
        int32_t transfer = 0;
        for (size_t i = 0; i < size; ++i) {
            if (i < Number.size()) {
                result.Number[i] += Number[i];
            }
            if (i < value.Number.size()) {
                result.Number[i] += value.Number[i];
            }
            result.Number[i] += transfer;
            transfer = result.Number[i] / BASE;
            result.Number[i] %= BASE;
        }
        if (transfer != 0) {
            result.Number.push_back(transfer);
        }
        return result;
    }
    TBigInteger TBigInteger::operator-(const TBigInteger& value) const {
        if ((*this) < value) {
            throw std::runtime_error("Error");
        }
        TBigInteger result;
        size_t size = std::max(Number.size(), value.Number.size());
        result.Number.resize(size);
        int32_t transfer = 0;
        for (size_t i = 0; i < size; ++i) {
            result.Number[i] = Number[i] - transfer;
            if (i < value.Number.size()) {
                result.Number[i] -= value.Number[i];
            }
            if (result.Number[i] < 0) {
                transfer = 1;
                result.Number[i] += BASE;
            }
            else {
                transfer = 0;
            }
        }
        result.RemoveLeadZeros();
        return result;
    }
    TBigInteger TBigInteger::operator*(const TBigInteger& value) const {
        TBigInteger result;
        size_t size = Number.size() + value.Number.size();
        result.Number.resize(size);
        for (size_t i = 0; i < value.Number.size(); ++i) {
            for (size_t j = 0; j < Number.size(); ++j) {
                result.Number[i + j] += value.Number[i] * Number[j];
                result.Number[i + j + 1] += result.Number[i + j] / BASE;
                result.Number[i + j] %= BASE;
            }
        }
        result.RemoveLeadZeros();
        return result;
    }
    TBigInteger TBigInteger::operator/(const TBigInteger& value) const {
        if (value == ZERO) {
            throw std::runtime_error("Error");
        }
        if ((*this) < value) {
            return ZERO;
        }
        TBigInteger result, current;
        for (int i = Number.size() - 1; i >= 0; --i) {
            current.Number.insert(current.Number.begin(), Number[i]);
            current.RemoveLeadZeros();
            int x = 0, l = 0, r = BASE;
            while (l <= r) {
                int m = (l + r) / 2;
                TBigInteger mBig(std::to_string(m));
                TBigInteger t = value * mBig;
                if (t < current || t == current) {
                    x = m;
                    l = m + 1;
                }
                else {
                    r = m - 1;
                }
            }
            if (x != 0 || (x == 0 && result.Number.size() != 0) || i == 0) {
                result.Number.push_back(x);
            }
            TBigInteger xBig(std::to_string(x));
            current = current - value * xBig;
        }
        std::reverse(result.Number.begin(), result.Number.end());
        result.RemoveLeadZeros();
        return result;
    }
    TBigInteger Pow(const TBigInteger& exponet, const TBigInteger& base) {
        if (exponet == ZERO && base == ZERO) {
            throw std::runtime_error("Error");
        }
        TBigInteger result = ONE, factor = exponet, workBase = base;
        if (base == ZERO) {
            return result;
        }
        while (!(workBase == ZERO)) {
            if (workBase.Number[0] % 2 != 0) {
                result = result * factor;
            }
            factor = factor * factor;
            workBase = workBase / TWO;
        }
        result.RemoveLeadZeros();
        return result;
    }
}
