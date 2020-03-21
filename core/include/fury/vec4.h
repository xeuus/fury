
//
// Created by Aryan on 10/28/18.
//

#ifndef FURY_PRIMITIVES_VEC4_H
#define FURY_PRIMITIVES_VEC4_H


#include "system.h"
#include "uniform.h"
#include "vec2.h"
#include "vec3.h"


struct Vec4 : Uniform<4, 1> {

    static const Vec4 one;
    static const Vec4 zero;

    explicit Vec4(f32 scale = 0.0f) : Uniform{scale, scale, scale, scale} {}

    Vec4(f32 x, f32 y, f32 z = 0.0f, f32 w = 0.0f) : Uniform{x, y, z, w} {}

    explicit Vec4(const Vec2 &a, f32 w = 0.0f) : Uniform{a[0], a[1], w, w} {}

    explicit Vec4(const Vec3 &a, f32 w = 0.0f) : Uniform{a[0], a[1], a[2], w} {}

    explicit Vec4(const Uniform &a) : Uniform(a) {}

    explicit Vec4(const Uniform &&a) noexcept : Uniform{a} {}


    f32 &x();

    [[nodiscard]] f32 x() const;

    f32 &y();

    [[nodiscard]] f32 y() const;

    f32 &z();

    [[nodiscard]] f32 z() const;

    f32 &w();

    [[nodiscard]] f32 w() const;

    Vec2 &xy();

    [[nodiscard]] Vec2 xy() const;

    Vec2 &yz();

    Vec2 yz() const;

    Vec2 &zw();

    [[nodiscard]] Vec2 zw() const;

    Vec3 &xyz();

    [[nodiscard]] Vec3 xyz() const;

    Vec3 &yzw();

    [[nodiscard]] Vec3 yzw() const;


    [[nodiscard]] f32 dot(const Vec4 &a) const;

    [[nodiscard]] f32 magnitude() const;

    [[nodiscard]] f32 sqrMagnitude() const;

    [[nodiscard]] Vec4 normal() const;


    static const f32 dot(const Vec4 &a, const Vec4 &b);

    static const f32 magnitude(const Vec4 &a);

    static const f32 sqrMagnitude(const Vec4 &a);

    static const Vec4 normalize(const Vec4 &a);


    friend Vec4 operator+(const Vec4 &a, const Vec4 &b);;

    friend Vec4 operator-(const Vec4 &a);;

    friend Vec4 operator-(const Vec4 &a, const Vec4 &b);;

    friend Vec4 operator*(const Vec4 &a, const Vec4 &b);;

    friend Vec4 operator*(const Vec4 &a, const f32 &b);;

    friend Vec4 operator*(const f32 &b, const Vec4 &a);;

    friend Vec4 operator/(const Vec4 &a, const f32 &b);;
};


#endif //GAME_VEC4_H
