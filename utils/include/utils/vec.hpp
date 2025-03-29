#pragma once

#include <array>
#include <cmath>
#include <initializer_list>
#include <string>

namespace core {

template <int SIZE, typename TYPE = int>
class Vec {
public:
    Vec() = default;
    Vec(const std::array<TYPE, SIZE>& vec);
    Vec(std::initializer_list<TYPE> values);

public:
    const TYPE& operator[](int index) const;
    TYPE& operator[](int index);
    int size() const;
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
    void checkIndexValidity(int index) const;

private:
    std::array<TYPE, SIZE> data{};
};

template <int SIZE, typename TYPE>
Vec<SIZE, TYPE> Vec<SIZE, TYPE>::normalized() const {
    return *this / length();
}

template <int SIZE, typename TYPE>
bool Vec<SIZE, TYPE>::equals(const Vec<SIZE, TYPE>& other) const {
    if (data.size() != other.data.size()) {
        return false;
    }

    for (int i{}; i < data.size(); ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

template <int SIZE, typename TYPE>
bool Vec<SIZE, TYPE>::equalsWithEpsilon(const Vec<SIZE, TYPE>& other,
                                        TYPE epsilon) const {
    if (data.size() != other.data.size()) {
        return false;
    }

    // TODO: find a better way than 10 * epsilon
    for (int i{}; i < static_cast<int>(data.size()); ++i) {
        if (std::abs(data[i] - other.data[i]) > 10 * epsilon) {
            return false;
        }
    }
    return true;
}

template <int SIZE, typename TYPE>
Vec<SIZE, TYPE>::Vec(const std::array<TYPE, SIZE>& vec) : data{vec} {}

template <int SIZE, typename TYPE>
Vec<SIZE, TYPE>::Vec(std::initializer_list<TYPE> values) {
    if (values.size() != SIZE) {
        throw std::invalid_argument(
            "Initializer list size does not match Vec size.");
    }
    std::copy(values.begin(), values.end(), data.begin());
}

template <int SIZE, typename TYPE>
TYPE& Vec<SIZE, TYPE>::operator[](int index) {
    checkIndexValidity(index);
    return data[index];
}

template <int SIZE, typename TYPE>
const TYPE& Vec<SIZE, TYPE>::operator[](int index) const {
    checkIndexValidity(index);
    return data[index];
}

template <int SIZE, typename TYPE>
int Vec<SIZE, TYPE>::size() const {
    return SIZE;
}

template <int SIZE, typename TYPE>
TYPE Vec<SIZE, TYPE>::length() const {
    TYPE resultSquared{};
    for (int i{}; i < static_cast<int>(data.size()); ++i) {
        resultSquared += std::pow(data[i], 2);
    }
    return std::sqrt(resultSquared);
}

template <int SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator+=(const Vec<SIZE, TYPE>& rhs) {
    for (int i{}; i < SIZE; ++i) {
        this->operator[](i) += rhs[i];
    }
    return *this;
}

template <int SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator-=(const Vec<SIZE, TYPE>& rhs) {
    for (int i{}; i < SIZE; ++i) {
        this->operator[](i) -= rhs[i];
    }
    return *this;
}

template <int SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator*=(const Vec<SIZE, TYPE>& rhs) {
    for (int i{}; i < SIZE; ++i) {
        this->operator[](i) *= rhs[i];
    }
    return *this;
}

template <int SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator/=(const Vec<SIZE, TYPE>& rhs) {
    for (int i{}; i < SIZE; ++i) {
        if (rhs[i] == 0) {
            throw std::runtime_error("division by zero");
        }
        this->operator[](i) /= rhs[i];
    }
    return *this;
}

template <int SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator+=(TYPE num) {
    for (int i{}; i < SIZE; ++i) {
        this->operator[](i) += num;
    }
    return *this;
}

template <int SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator-=(TYPE num) {
    for (int i{}; i < SIZE; ++i) {
        this->operator[](i) -= num;
    }
    return *this;
}

template <int SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator*=(TYPE num) {
    for (int i{}; i < SIZE; ++i) {
        this->operator[](i) *= num;
    }
    return *this;
}

template <int SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator/=(TYPE num) {
    if (num == 0) {
        throw std::runtime_error("division by zero");
    }
    for (int i{}; i < SIZE; ++i) {
        this->operator[](i) /= num;
    }
    return *this;
}

template <int SIZE, typename TYPE>
void Vec<SIZE, TYPE>::checkIndexValidity(int index) const {
    if (index < 0 || index >= static_cast<int>(data.size())) {
        throw std::runtime_error("invalid index " + std::to_string(index) +
                                 " for vec with size " + std::to_string(SIZE));
    }
}

template <int SIZE, typename TYPE = int>
Vec<SIZE, TYPE> operator+(const Vec<SIZE, TYPE>& lhs,
                          const Vec<SIZE, TYPE>& rhs) {
    Vec<SIZE, TYPE> result;
    for (int i{}; i < SIZE; ++i) {
        result[i] = lhs[i] + rhs[i];
    }
    return result;
}

template <int SIZE, typename TYPE = int>
Vec<SIZE, TYPE> operator-(const Vec<SIZE, TYPE>& lhs,
                          const Vec<SIZE, TYPE>& rhs) {
    Vec<SIZE, TYPE> result;
    for (int i{}; i < SIZE; ++i) {
        result[i] = lhs[i] - rhs[i];
    }
    return result;
}

template <int SIZE, typename TYPE = int>
Vec<SIZE, TYPE> operator*(const Vec<SIZE, TYPE>& lhs,
                          const Vec<SIZE, TYPE>& rhs) {
    Vec<SIZE, TYPE> result;
    for (int i{}; i < SIZE; ++i) {
        result[i] = lhs[i] * rhs[i];
    }
    return result;
}

template <int SIZE, typename TYPE = int>
Vec<SIZE, TYPE> operator/(const Vec<SIZE, TYPE>& lhs,
                          const Vec<SIZE, TYPE>& rhs) {
    Vec<SIZE, TYPE> result;
    for (int i{}; i < SIZE; ++i) {
        if (rhs[i] == 0) {
            throw std::runtime_error("division by zero");
        }
        result[i] = lhs[i] / rhs[i];
    }
    return result;
}

template <int SIZE, typename TYPE = int>
Vec<SIZE, TYPE> operator+(const Vec<SIZE, TYPE>& lhs, TYPE num) {
    Vec<SIZE, TYPE> result;
    for (int i{}; i < SIZE; ++i) {
        result[i] = lhs[i] + num;
    }
    return result;
}

template <int SIZE, typename TYPE = int>
Vec<SIZE, TYPE> operator-(const Vec<SIZE, TYPE>& lhs, TYPE num) {
    Vec<SIZE, TYPE> result;
    for (int i{}; i < SIZE; ++i) {
        result[i] = lhs[i] - num;
    }
    return result;
}

template <int SIZE, typename TYPE = int>
Vec<SIZE, TYPE> operator*(const Vec<SIZE, TYPE>& lhs, TYPE num) {
    Vec<SIZE, TYPE> result;
    for (int i{}; i < SIZE; ++i) {
        result[i] = lhs[i] * num;
    }
    return result;
}

template <int SIZE, typename TYPE = int>
Vec<SIZE, TYPE> operator/(const Vec<SIZE, TYPE>& lhs, TYPE num) {
    if (num == 0) {
        throw std::runtime_error("division by zero");
    }
    Vec<SIZE, TYPE> result;
    for (int i{}; i < SIZE; ++i) {
        result[i] = lhs[i] / num;
    }
    return result;
}

using Coords = Vec<2, int>;
using Point = Vec<2, int>;
using Velocity = Vec<2, int>;
using Acceleration = Vec<2, int>;
using Rect = Vec<4, int>;

}  // namespace core