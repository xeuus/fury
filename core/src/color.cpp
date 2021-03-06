#include "fury/color.h"


const Color Color::red{1, 0, 0};
const Color Color::green{0, 1, 0};
const Color Color::blue{0, 0, 1};
const Color Color::white{1, 1, 1};
const Color Color::black{0, 0, 0};
const Color Color::yellow{0, 1, 1};


f32 &Color::r() {
    return data[0];
}

f32 Color::r() const {
    return data[0];
}

f32 &Color::g() {
    return data[1];
}

f32 Color::g() const {
    return data[1];
}

f32 &Color::b() {
    return data[2];
}

f32 Color::b() const {
    return data[2];
}

f32 &Color::a() {
    return data[3];
}

f32 Color::a() const {
    return data[3];
}

Vec3 &Color::rgb() {
    return *((Vec3 *) (data));
}

Vec3 Color::rgb() const {
    return Vec3{data[0], data[1], data[2]};
}