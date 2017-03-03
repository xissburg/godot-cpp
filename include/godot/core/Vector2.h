#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

#include <godot/godot_vector2.h>

#include "String.h"

namespace godot {

typedef float real_t; // @Todo  move to a global Godot.h

struct Vector2 {

	union {
		real_t x;
		real_t width;
	};
	union {
		real_t y;
		real_t height;
	};


	real_t& operator[](int p_idx) {
		return p_idx?y:x;
	}
	const real_t& operator[](int p_idx) const {
		return p_idx?y:x;
	}

	Vector2 operator+(const Vector2& p_v) const
	{
		return Vector2(x + p_v.x, y + p_v.y);
	}

	void operator+=(const Vector2& p_v)
	{
		x += p_v.x;
		y += p_v.y;
	}

	Vector2 operator-(const Vector2& p_v) const
	{
		return Vector2(x - p_v.x, y - p_v.y);
	}

	void operator-=(const Vector2& p_v)
	{
		x -= p_v.x;
		y -= p_v.y;
	}

	Vector2 operator*(const Vector2 &p_v1) const
	{
		return Vector2(x * p_v1.x, y * p_v1.y);
	}

	Vector2 operator*(const real_t &rvalue) const
	{
		return Vector2(x * rvalue, y * rvalue);
	}

	void operator*=(const real_t &rvalue)
	{
		x *= rvalue;
		y *= rvalue;
	}

	void operator*=(const Vector2 &rvalue) { *this = *this * rvalue; }

	Vector2 operator/(const Vector2 &p_v1) const
	{
		return Vector2(x / p_v1.x, y / p_v1.y);
	}

	Vector2 operator/(const real_t &rvalue) const
	{
		return Vector2(x / rvalue, y / rvalue);
	}

	void operator/=(const real_t &rvalue)
	{
		x /= rvalue;
		y /= rvalue;
	}

	Vector2 operator-() const
	{
		return Vector2(-x, -y);
	}

	bool operator==(const Vector2& p_vec2) const
	{
		return x == p_vec2.x && y == p_vec2.y;
	}

	bool operator!=(const Vector2& p_vec2) const
	{
		return x != p_vec2.x || y != p_vec2.y;
	}

	bool operator<(const Vector2& p_vec2) const { return (x==p_vec2.x)?(y<p_vec2.y):(x<p_vec2.x); }
	bool operator<=(const Vector2& p_vec2) const { return (x==p_vec2.x)?(y<=p_vec2.y):(x<=p_vec2.x); }


	void normalize()
	{
		real_t l = x*x + y*y;
		if (l != 0) {
			l = (l);
			x /= l;
			y /= l;
		}
	}

	Vector2 normalized() const
	{
		Vector2 v = *this;
		v.normalize();
		return v;
	}

	real_t length() const
	{
		return sqrt(x*x + y*y);
	}
	real_t length_squared() const
	{
		return x*x + y*y;
	}

	real_t distance_to(const Vector2& p_vector2) const
	{
		return sqrt((x - p_vector2.x) * (x - p_vector2.x) + (y - p_vector2.y) * (y - p_vector2.y));
	}

	real_t distance_squared_to(const Vector2& p_vector2) const
	{
		return (x - p_vector2.x) * (x - p_vector2.x) + (y - p_vector2.y) * (y - p_vector2.y);
	}

	real_t angle_to(const Vector2& p_vector2) const
	{
		return atan2(cross(p_vector2), dot(p_vector2));
	}

	real_t angle_to_point(const Vector2& p_vector2) const
	{
		return atan2(y - p_vector2.y, x-p_vector2.x);
	}

	real_t dot(const Vector2& p_other) const
	{
		return x * p_other.x + y * p_other.y;
	}

	real_t cross(const Vector2& p_other) const
	{
		return x * p_other.y - y * p_other.x;
	}

	Vector2 cross(real_t p_other) const
	{
		return Vector2(p_other * y, -p_other * x);
	}

	Vector2 project(const Vector2& p_vec) const
	{
		Vector2 v1 = p_vec;
		Vector2 v2 = *this;
		return v2 * (v1.dot(v2) / v2.dot(v2));
	}

	Vector2 plane_project(real_t p_d, const Vector2& p_vec) const
	{
		return  p_vec - *this * ( dot(p_vec) -p_d);
	}

	Vector2 clamped(real_t p_len) const
	{
		real_t l = length();
		Vector2 v = *this;
		if (l > 0 && p_len < l) {
			v /= l;
			v *= p_len;
		}
		return v;
	}

	static Vector2 linear_interpolate(const Vector2& p_a, const Vector2& p_b,real_t p_t)
	{
		Vector2 res=p_a;
		res.x+= (p_t * (p_b.x-p_a.x));
		res.y+= (p_t * (p_b.y-p_a.y));
		return res;
	}

	Vector2 linear_interpolate(const Vector2& p_b,real_t p_t) const
	{
		Vector2 res=*this;
		res.x+= (p_t * (p_b.x-x));
		res.y+= (p_t * (p_b.y-y));
		return res;

	}
	Vector2 cubic_interpolate(const Vector2& p_b,const Vector2& p_pre_a, const Vector2& p_post_b,real_t p_t) const
	{
		Vector2 p0=p_pre_a;
		Vector2 p1=*this;
		Vector2 p2=p_b;
		Vector2 p3=p_post_b;

		real_t t = p_t;
		real_t t2 = t * t;
		real_t t3 = t2 * t;

		Vector2 out;
		out = ( ( p1 * 2.0) +
		( -p0 + p2 ) * t +
		( p0 * 2.0 - p1 * 5.0 + p2 * 4 - p3 ) * t2 +
		( -p0 + p1 * 3.0 - p2 * 3.0 + p3 ) * t3 ) * 0.5;

		return out;
	}

	// Vector2 cubic_interpolate_soft(const Vector2& p_b,const Vector2& p_pre_a, const Vector2& p_post_b,real_t p_t) const;

	Vector2 slide(const Vector2& p_vec) const
	{
		return p_vec - *this * this->dot(p_vec);
	}

	Vector2 reflect(const Vector2& p_vec) const
	{
		return p_vec - *this * this->dot(p_vec) * 2.0;
	}

	real_t angle() const
	{
		return atan2(y, x);
	}

	void set_rotation(real_t p_radians) {

		x = cosf(p_radians);
		y = sinf(p_radians);
	}

	Vector2 abs() const {

		return Vector2( fabs(x), fabs(y) );
	}

	Vector2 rotated(real_t p_by) const
	{
		Vector2 v;
		v.set_rotation(angle() + p_by);
		v *= length();
		return v;
	}

	Vector2 tangent() const {

		return Vector2(y,-x);
	}

	Vector2 floor() const
	{
		return Vector2(::floor(x), ::floor(y));
	}

	Vector2 snapped(const Vector2& p_by) const
	{
		return Vector2(
			p_by.x != 0 ? ::floor(x / p_by.x + 0.5) * p_by.x : x,
			p_by.y != 0 ? ::floor(y / p_by.y + 0.5) * p_by.y : y
		);
	}
	real_t aspect() const { return width/height; }


	operator String() const { return String(); /* @Todo String::num() */ }

	Vector2(real_t p_x,real_t p_y) { x=p_x; y=p_y; }
	Vector2() { x=0; y=0; }
};


Vector2 operator*(real_t p_scalar, const Vector2& p_vec)
{
	return p_vec*p_scalar;
}



}

#endif // VECTOR2_H
