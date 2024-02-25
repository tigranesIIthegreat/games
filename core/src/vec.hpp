#pragma once

#include <array>
#include <cmath>
#include <initializer_list>
#include <string>

namespace core {

template <size_t SIZE, typename TYPE = float>
class Vec {
public:
    Vec() = default;
    Vec(const std::array<TYPE, SIZE>& vec);
    Vec(std::initializer_list<TYPE> values);

public:
    const TYPE& operator[](size_t index) const;
    TYPE& operator[](size_t index);
    size_t size() const;
    TYPE length() const;
    Vec normalized() const;
    bool equals(const Vec& other) const;
    bool equalsWithEpsilon(
        const Vec& other,
        TYPE epsilon = std::numeric_limits<TYPE>::epsilon()) const;

public:
    Vec& operator+=(const Vec& rhs);
    Vec& operator-=(const Vec& rhs);
    Vec& operator*=(const Vec& rhs);
    Vec& operator/=(const Vec& rhs);

    Vec& operator+=(TYPE number);
    Vec& operator-=(TYPE number);
    Vec& operator*=(TYPE number);
    Vec& operator/=(TYPE number);

private:
    void checkIndexValidity(size_t index) const;

private:
    std::array<TYPE, SIZE> data{};
};

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE> Vec<SIZE, TYPE>::normalized() const {
    return *this / length();
}

template <size_t SIZE, typename TYPE>
bool Vec<SIZE, TYPE>::equals(const Vec<SIZE, TYPE>& other) const {
    if (data.size() != other.data.size()) {
        return false;
    }

    for (size_t i{}; i < data.size(); ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

template <size_t SIZE, typename TYPE>
bool Vec<SIZE, TYPE>::equalsWithEpsilon(const Vec<SIZE, TYPE>& other,
                                        TYPE epsilon) const {
    if (data.size() != other.data.size()) {
        return false;
    }

    // TODO: find a better way than 10 * epsilon
    for (size_t i{}; i < data.size(); ++i) {
        if (std::abs(data[i] - other.data[i]) > 10 * epsilon) {
            return false;
        }
    }
    return true;
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>::Vec(const std::array<TYPE, SIZE>& vec) : data{vec} {}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>::Vec(std::initializer_list<TYPE> values) {
    if (values.size() != SIZE) {
        throw std::invalid_argument(
            "Initializer list size does not match Vec size.");
    }
    std::copy(values.begin(), values.end(), data.begin());
}

template <size_t SIZE, typename TYPE>
TYPE& Vec<SIZE, TYPE>::operator[](size_t index) {
    checkIndexValidity(index);
    return data[index];
}

template <size_t SIZE, typename TYPE>
const TYPE& Vec<SIZE, TYPE>::operator[](size_t index) const {
    checkIndexValidity(index);
    return data[index];
}

template <size_t SIZE, typename TYPE>
size_t Vec<SIZE, TYPE>::size() const {
    return SIZE;
}

template <size_t SIZE, typename TYPE>
TYPE Vec<SIZE, TYPE>::length() const {
    TYPE resultSquared{};
    for (size_t i{}; i < data.size(); ++i) {
        resultSquared += std::pow(data[i], 2);
    }
    return std::sqrt(resultSquared);
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator+=(const Vec<SIZE, TYPE>& rhs) {
    for (size_t i{}; i < SIZE; ++i) {
        this->operator[](i) += rhs[i];
    }
    return *this;
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator-=(const Vec<SIZE, TYPE>& rhs) {
    for (size_t i{}; i < SIZE; ++i) {
        this->operator[](i) -= rhs[i];
    }
    return *this;
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator*=(const Vec<SIZE, TYPE>& rhs) {
    for (size_t i{}; i < SIZE; ++i) {
        this->operator[](i) *= rhs[i];
    }
    return *this;
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator/=(const Vec<SIZE, TYPE>& rhs) {
    for (size_t i{}; i < SIZE; ++i) {
        if (rhs[i] == 0) {
            throw std::runtime_error("division by zero");
        }
        this->operator[](i) /= rhs[i];
    }
    return *this;
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator+=(TYPE num) {
    for (size_t i{}; i < SIZE; ++i) {
        this->operator[](i) += num;
    }
    return *this;
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator-=(TYPE num) {
    for (size_t i{}; i < SIZE; ++i) {
        this->operator[](i) -= num;
    }
    return *this;
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator*=(TYPE num) {
    for (size_t i{}; i < SIZE; ++i) {
        this->operator[](i) *= num;
    }
    return *this;
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator/=(TYPE num) {
    if (num == 0) {
        throw std::runtime_error("division by zero");
    }
    for (size_t i{}; i < SIZE; ++i) {
        this->operator[](i) /= num;
    }
    return *this;
}

template <size_t SIZE, typename TYPE>
void Vec<SIZE, TYPE>::checkIndexValidity(size_t index) const {
    if (index < 0 || index >= data.size()) {
        throw std::runtime_error("invalid index " + std::to_string(index) +
                                 " for vec with size " + std::to_string(SIZE));
    }
}

template <size_t SIZE, typename TYPE = float>
Vec<SIZE, TYPE> operator+(const Vec<SIZE, TYPE>& lhs,
                          const Vec<SIZE, TYPE>& rhs) {
    Vec<SIZE, TYPE> result;
    for (size_t i{}; i < SIZE; ++i) {
        result[i] = lhs[i] + rhs[i];
    }
    return result;
}

template <size_t SIZE, typename TYPE = float>
Vec<SIZE, TYPE> operator-(const Vec<SIZE, TYPE>& lhs,
                          const Vec<SIZE, TYPE>& rhs) {
    Vec<SIZE, TYPE> result;
    for (size_t i{}; i < SIZE; ++i) {
        result[i] = lhs[i] - rhs[i];
    }
    return result;
}

template <size_t SIZE, typename TYPE = float>
Vec<SIZE, TYPE> operator*(const Vec<SIZE, TYPE>& lhs,
                          const Vec<SIZE, TYPE>& rhs) {
    Vec<SIZE, TYPE> result;
    for (size_t i{}; i < SIZE; ++i) {
        result[i] = lhs[i] * rhs[i];
    }
    return result;
}

template <size_t SIZE, typename TYPE = float>
Vec<SIZE, TYPE> operator/(const Vec<SIZE, TYPE>& lhs,
                          const Vec<SIZE, TYPE>& rhs) {
    Vec<SIZE, TYPE> result;
    for (size_t i{}; i < SIZE; ++i) {
        if (rhs[i] == 0) {
            throw std::runtime_error("division by zero");
        }
        result[i] = lhs[i] / rhs[i];
    }
    return result;
}

template <size_t SIZE, typename TYPE = float>
Vec<SIZE, TYPE> operator+(const Vec<SIZE, TYPE>& lhs, TYPE num) {
    Vec<SIZE, TYPE> result;
    for (size_t i{}; i < SIZE; ++i) {
        result[i] = lhs[i] + num;
    }
    return result;
}

template <size_t SIZE, typename TYPE = float>
Vec<SIZE, TYPE> operator-(const Vec<SIZE, TYPE>& lhs, TYPE num) {
    Vec<SIZE, TYPE> result;
    for (size_t i{}; i < SIZE; ++i) {
        result[i] = lhs[i] - num;
    }
    return result;
}

template <size_t SIZE, typename TYPE = float>
Vec<SIZE, TYPE> operator*(const Vec<SIZE, TYPE>& lhs, TYPE num) {
    Vec<SIZE, TYPE> result;
    for (size_t i{}; i < SIZE; ++i) {
        result[i] = lhs[i] * num;
    }
    return result;
}

template <size_t SIZE, typename TYPE = float>
Vec<SIZE, TYPE> operator/(const Vec<SIZE, TYPE>& lhs, TYPE num) {
    if (num == 0) {
        throw std::runtime_error("division by zero");
    }
    Vec<SIZE, TYPE> result;
    for (size_t i{}; i < SIZE; ++i) {
        result[i] = lhs[i] / num;
    }
    return result;
}

using Vec2 = Vec<2, float>;

} // namespace core