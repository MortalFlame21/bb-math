#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <functional>
#include <numeric>

namespace bb { // namespace bb
// @brief An N dimension vector
template<typename T, std::size_t N>
    requires (std::is_integral_v<T> || std::is_floating_point_v<T>) && (N > 1)
class Vector {
public:
    // alias
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using container_type = std::array<T, N>;

    // creation
    constexpr Vector() = default;
    constexpr explicit Vector(container_type v) : _v{v} { }

    // specialisation ctor
    constexpr Vector(T vx, T vy) requires (N == 2) : _v{vx, vy} { }
    constexpr Vector(T vx, T vy, T vz) requires (N == 3) : _v{vx, vy, vz} { }
    constexpr Vector(T vx, T vy, T vz, T vw) requires (N == 4) : _v{vx, vy, vz, vw} { }

    // access
    constexpr reference operator[](size_type i){ return _v[i]; }
    constexpr const_reference operator[](size_type i) const { return _v[i]; }

    // specialisation access
    constexpr reference x() { return _v[0]; }
    constexpr const_reference x() const { return _v[0]; }
    constexpr reference y() requires (N >= 2) { return _v[1]; }
    constexpr const_reference y() const requires (N >= 2) { return _v[1]; }
    constexpr reference z() requires (N >= 3) { return _v[2]; }
    constexpr const_reference z() const requires (N >= 3) { return _v[2]; }
    constexpr reference w() requires (N >= 4) { return _v[3]; }
    constexpr const_reference w() const requires (N >= 4) { return _v[3]; }

    // operations
    // unary
    friend constexpr Vector operator-(const Vector& v) {
        Vector v_new{v};
        std::transform(v_new.begin(), v_new.end(), v_new.begin(), std::negate<value_type>{});
        return v_new;
    }

    friend constexpr Vector operator+(const Vector& v) {
        return v;
    }

    constexpr Vector& operator+=(const Vector& o) {
        std::transform(o.begin(), o.end(), begin(), begin(), std::plus<value_type>{});
        return *this;
    }

    constexpr Vector& operator-=(const Vector& o) {
        std::transform(o.begin(), o.end(), begin(), begin(), std::minus<value_type>{});
        return *this;
    }

    constexpr Vector& operator*=(value_type s) {
        for (auto& vi : _v) vi *= s;
        return *this;
    }

    constexpr Vector& operator/=(value_type s) {
        return *this * (static_cast<value_type>(1) / s);
    }

    // binary
    friend constexpr Vector operator+(const Vector& a, const Vector& b) {
        Vector v_new{a};
        v_new += b;
        return v_new;
    }

    friend constexpr Vector operator-(const Vector& a, const Vector& b) {
        Vector v_new{a};
        v_new -= b;
        return v_new;
    }

    friend constexpr Vector operator*(const Vector& v, value_type s) {
        Vector v_new{v};
        v_new *= s;
        return v_new;
    }

    friend constexpr Vector operator/(const Vector& v, value_type s) {
        Vector v_new{v};
        v_new *= (static_cast<value_type>(1) / s);
        return v_new;
    }

    // comparision
    friend constexpr bool operator==(const Vector& a, const Vector& b) {
        return a._v == b._v;
    }

    friend constexpr bool operator!=(const Vector& a, const Vector& b) {
        return !(a._v == b._v);
    }

    // iterators
    container_type::iterator begin() { return _v.begin(); }
    container_type::const_iterator begin() const { return _v.begin(); }
    container_type::const_iterator cbegin() const { return _v.cbegin(); }

    container_type::iterator end() { return _v.end(); }
    container_type::const_iterator end() const { return _v.end(); }
    container_type::const_iterator cend() const { return _v.cend(); }

    private:
    container_type _v{};
};

// alias specialisations
template<std::size_t N>
using Vec = Vector<float, N>;
using Vec2d = Vector<float, 2>;
using Vec3d = Vector<float, 3>;

// calculations
template<typename T, std::size_t N>
constexpr float magnitude(const Vector<T, N>& v) {
    auto sqr_sum{std::inner_product(v.begin(), v.end(), v.begin(), T{})};
    return std::sqrt(sqr_sum);
}

template<typename T, std::size_t N>
constexpr float length(const Vector<T, N>& v) {
    return magnitude(v);
}

template<typename T, std::size_t N>
constexpr Vector<T, N> normalise(const Vector<T, N>& v) {
    return v / magnitude(v);
}

template<typename T, std::size_t N>
constexpr Vector<T, N> unit_vector(const Vector<T, N>& v) {
    return normalise(v);
}


} // namespace bb