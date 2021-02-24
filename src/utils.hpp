#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

#include "vec3.hpp"

inline std::ostream& operator<<(std::ostream& out, const Vec3 &v);
inline Vec3 operator*(double k, const Vec3& v);
inline double dot(const Vec3& u, const Vec3& v);
inline Vec3 cross(const Vec3& u, const Vec3& v);
inline Vec3 unitVector(const Vec3& v);

#endif
