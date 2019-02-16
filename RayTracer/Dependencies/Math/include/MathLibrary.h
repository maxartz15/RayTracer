#pragma once
#include <math.h>
#include <iostream>

//Contains: math, float, vec2, vec3.

namespace Math
{
	//Float PI
	const float PI = 3.1415927f;
	const float PI_2 = 1.5707965f;
	const float PI_4 = 0.7853982f;

	float remap01(const float& a, const float& b, const float& t);
	float notSoRandomFloat01();
	void rotateAroundPoint2D(float& posX, float& posY, const float& targetX, const float& targetY, float angle);
	float radToDeg(const float& radians);
	float degToRad(const float& degrees);
	void wrapFloat(float& value, const float& min, const float& max);
};

//Vec2
class vec2
{
public:
#pragma warning(push)
#pragma warning(disable : 4201)
	union
	{
		struct
		{
			float x;
			float y;
		};
		float v[2];
	};

public:
	vec2();
	vec2(float x, float y);

	vec2& operator=(const vec2 rhs);

	vec2& operator+=(const vec2& rhs);
	vec2& operator-=(const vec2& rhs);
	vec2& operator*=(float rhs);
	vec2& operator/=(float rhs);

	float operator[](int index) const;
	float& operator[](int index);

	inline float dot(vec2 const& rhs) const;
	vec2& normalize();
	vec2 normalized();
	inline float length() const;

	static float dot(const vec2& lhs, const vec2& rhs);
	static float length(const vec2& lhs);
};

inline float vec2::dot(vec2 const& rhs) const
{
	return (v[0] * rhs[0]) + (v[1] * rhs[1]);
}

inline float vec2::length() const
{
	return sqrtf((v[0] * v[0]) + (v[1] * v[1]));
}

inline float vec2::dot(const vec2& lhs, const vec2& rhs)
{
	return lhs.dot(rhs);
}

inline float vec2::length(const vec2& lhs)
{
	return lhs.length();
}

inline std::istream& operator>>(std::istream& lhs, vec2& rhs)
{
	lhs >> rhs.v[0] >> rhs.v[1];
	return lhs;
}

inline std::ostream& operator<<(std::ostream& lhs, const vec2& rhs)
{
	lhs << rhs.v[0] << " " << rhs.v[1];
	return lhs;
}

vec2 operator+(const vec2& lhs, const vec2& rhs);
vec2 operator-(const vec2& lhs, const vec2& rhs);
vec2 operator*(const vec2& lhs, float rhs);
vec2 operator*(float lhs, const vec2& rhs);
vec2 operator*(const vec2& lhs, const vec2& rhs);
vec2 operator/(const vec2& lhs, float rhs);
vec2 operator/(float lhs, const vec2& rhs);
vec2 operator/(const vec2& lhs, const vec2& rhs);
bool operator==(const vec2& lhs, const vec2& rhs);
bool operator!=(const vec2& lhs, const vec2& rhs);

//Vec3
class vec3 
{
public:
#pragma warning(push)
#pragma warning(disable : 4201)
	union 
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		struct
		{
			float r;
			float g;
			float b;
		};
		float v[3];
	};

public:
	vec3();
	vec3(float x, float y, float z);

	vec3& operator=(const vec3& rhs);

	vec3& operator+=(const vec3& rhs);
	vec3& operator-=(const vec3& rhs);
	vec3& operator*=(float rhs);
	vec3& operator/=(float rhs);

	float operator[](int index) const;
	float& operator[](int index);

	inline float dot(vec3 const& rhs) const;
	inline vec3 cross(vec3 const& rhs) const;
	vec3& normalize();
	vec3 normalized() const;
	inline float length() const;
	vec3& inverse();
	vec3 inversed() const;
	vec3& round();
	vec3 rounded() const;
	vec3& ceil();
	vec3 ceiled() const;
	vec3& floor();
	vec3 floored() const;

	static float dot(vec3 const& lhs, vec3 const& rhs);
	static float length(const vec3& lhs);
	static vec3 cross(const vec3& lhs, const vec3& rhs);
	static float angle(const vec3& lhs, const vec3& rhs);
	static float distance(const vec3& lhs, const vec3& rhs);
	static void normalize(vec3& lhs);
	static vec3 normalized(const vec3& lhs);
	static void clamp(vec3& lhs, const float& min, const float& max);
	static vec3 project(const vec3& lhs, const vec3& rhs);
	static vec3 reflect(const vec3& lhs, const vec3& rhs);
	static vec3 reflect2(const vec3& lhs, const vec3& rhs);
	static vec3 refract(const vec3& dir, const vec3& normal, const float& eta);
	static vec3 refract2(const vec3& dir, const vec3& normal, const float& eta);
	static vec3 refract3(const vec3& dir, const vec3& normal, const float& ri1, const float& ri2);
	static vec3 refract4(const vec3& dir, const vec3& normal, const float& ri1);
	static vec3 random01();
	static vec3 randomPointInUnitSphere();
	static vec3 randomPointInUnitSphere2();
};

//Ref: https://docs.google.com/document/d/12m5C-Fp3xP_zohZyFc-RsvFBmUFEuJR1rkjaHqLb_Z4/edit#heading=h.5j4d6ppmg9m0
///Returns the dot product of 2 vectors.
inline float vec3::dot(vec3 const& rhs) const
{
	return (v[0] * rhs[0]) + (v[1] * rhs[1]) + (v[2] * rhs[2]);
}

///Returns the cross product of 2 vectors.
inline vec3 vec3::cross(vec3 const& rhs) const
{
	return vec3((v[1] * rhs[2] - rhs[1] * v[2]),
				(v[2] * rhs[0] - rhs[2] * v[0]),
				(v[0] * rhs[1] - rhs[0] * v[1]));
}

///Retuns the length of the vector.
inline float vec3::length() const
{
	return sqrtf((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
}

inline std::istream& operator>>(std::istream& lhs, vec3& rhs)
{
	lhs >> rhs.v[0] >> rhs.v[1] >> rhs.v[2];
	return lhs;
}

inline std::ostream& operator<<(std::ostream& lhs, vec3& rhs)
{
	lhs << rhs.v[0] << " " << rhs.v[1] << " " << rhs.v[2];
	return lhs;
}

vec3 operator+(const vec3& lhs, const vec3& rhs);
vec3 operator-(const vec3& lhs, const vec3& rhs);
vec3 operator*(const vec3& lhs, float rhs);
vec3 operator*(float lhs, const vec3& rhs);
vec3 operator*(const vec3& lhs, const vec3& rhs);
vec3 operator/(const vec3& lhs, float rhs);
vec3 operator/(float lhs, const vec3& rhs);
vec3 operator/(const vec3& lhs, const vec3& rhs);
bool operator==(const vec3& lhs, const vec3& rhs);
bool operator!=(const vec3& lhs, const vec3& rhs);

//Mat4
class mat4
{
public:
#pragma warning(push)
#pragma warning(disable : 4201)
	union 
	{
		float m[16];
		//struct
		//{
		//	float m_00; float m_01; float m_02; float m_03;
		//	float m_10; float m_11; float m_12; float m_13;
		//	float m_20; float m_21; float m_22; float m_23;
		//	float m_30; float m_31; float m_32; float m_33;
		//};

		float mm[4][4];
		struct
		{
			vec3 xAxis;
			float wx;
			vec3 yAxis;
			float wy;
			vec3 zAxis;
			float wz;
			vec3 translation;
			float one;
		};
	};

public:
	mat4();
	mat4(float a);
	mat4(vec3 a_Row0, float a_03,
		vec3 a_Row1, float a_13,
		vec3 a_Row2, float a_23,
		vec3 a_Row3, float a_33);
	mat4(float a_00, float a_01, float a_02, float a_03,
		float a_10, float a_11, float a_12, float a_13,
		float a_20, float a_21, float a_22, float a_23,
		float a_30, float a_31, float a_32, float a_33);

	mat4& operator=(const mat4& rhs);
	mat4& operator+=(const mat4 &rhs);
	mat4& operator-=(const mat4 &rhs);
	mat4& operator*=(const mat4 &rhs);

	float determinant() const;

	static mat4 identity();
	//static mat4 inverse();
	static mat4 rotateX(const float a_Radians);
	static mat4 rotateY(const float a_Radians);
	static mat4 rotateZ(const float a_Radians);
	static mat4 translate(const vec3& a_Translation);
	static mat4 scale(const vec3& a_Scale);

	//static mat4 lookat(const vec3 &a_Eye, const vec3 &a_Center, const vec3 &a_Up);
	//static mat4 projection(float a_FovY, float a_AspectRatio, float a_Near, float a_Far);
};

mat4 operator+(const mat4 &lhs, const mat4 &rhs);
mat4 operator-(const mat4 &lhs, const mat4 &rhs);
mat4 operator*(const mat4 &lhs, const mat4 &rhs);
mat4 operator*(const float &lhs, const mat4 &rhs);
vec3 operator*(const vec3 &lhs, const mat4 &rhs);

inline std::ostream& operator<<(std::ostream& lhs, const mat4& rhs)
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		lhs << rhs.m[i] << " ";

		if (((i + 1) % 4) == 0)
		{
			lhs << "\n";
		}
	}

	return lhs;
}

inline std::istream& operator>>(std::istream& lhs, mat4& rhs)
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		lhs >> rhs.m[i];
	}

	return lhs;
}