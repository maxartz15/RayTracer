#include "MathLibrary.h"

#include <algorithm>

//Math
//Float
float Math::remap01(const float& a, const float& b, const float& t)
{
	return (t - a) / (b - a);
}

float Math::notSoRandomFloat01()
{
	return (float)rand() / (RAND_MAX);
}

void Math::rotateAroundPoint2D(float& posX, float& posY, const float& targetX, const float& targetY, float angle)
{
	angle = degToRad(angle);

	float s = sin(angle);
	float c = cos(angle);

	//Translate point to origin.
	posX -= targetX;
	posY -= targetY;

	//Rotate point.
	float xnew = posX * c - posY * s;
	float ynew = posX * s + posY * c;

	//Translate point back.
	posX = xnew + targetX;
	posY = ynew + targetY;
}

float Math::radToDeg(const float& radians)
{
	return (radians * 180) / PI;
}

float Math::degToRad(const float& degrees)
{
	return (degrees * PI) / 180;
}

void Math::wrapFloat(float& value, const float& min, const float& max)
{
	if (value < min)
	{
		//warp to max
		value = max;
	}
	else if (value > max)
	{
		//warp to min
		value = min;
	}
}

//Vec2
vec2::vec2()
{
	v[0] = 0;
	v[1] = 0;
}

vec2::vec2(float x, float y)
{
	v[0] = x;
	v[1] = y;
}

vec2& vec2::operator=(const vec2 rhs)
{
	v[0] = rhs[0];
	v[1] = rhs[1];

	return *this;
}

vec2& vec2::operator+=(const vec2 & rhs)
{
	v[0] += rhs[0];
	v[1] += rhs[1];

	return *this;
}

vec2& vec2::operator-=(const vec2 & rhs)
{
	v[0] -= rhs[0];
	v[1] -= rhs[1];

	return *this;
}

vec2& vec2::operator*=(float rhs)
{
	v[0] *= rhs;
	v[1] *= rhs;

	return *this;
}

vec2& vec2::operator/=(float rhs)
{
	v[0] /= rhs;
	v[1] /= rhs;

	return *this;
}

float vec2::operator[](int index) const
{
	return v[index];
}

float& vec2::operator[](int index)
{
	return v[index];
}

vec2& vec2::normalize()
{
	float l = length();
	v[0] /= l;
	v[1] /= l;

	return *this;

	//OR?
	//float l = length();
	//float inv = 1 / l;
	//v[0] *= inv;
	//v[1] *= inv;

	//return *this;
}

vec2 vec2::normalized()
{
	float l = length();
	return vec2(v[0] / l, v[1] / l);
}

vec2 operator+(const vec2& lhs, const vec2 & rhs)
{
	return vec2(lhs[0] + rhs[0], lhs[1] + rhs[1]);
}

vec2 operator-(const vec2& lhs, const vec2 & rhs)
{
	return vec2(lhs[0] - rhs[0], lhs[1] - rhs[1]);
}

vec2 operator*(const vec2& lhs, float rhs)
{
	return vec2(lhs[0] * rhs, lhs[1] * rhs);
}

vec2 operator*(float lhs, const vec2& rhs)
{
	return (rhs * lhs);
}

vec2 operator*(const vec2& lhs, const vec2& rhs)
{
	return vec2(lhs[0] * rhs[0], lhs[1] * rhs[1]);
}

vec2 operator/(const vec2& lhs, float rhs)
{
	return vec2(lhs[0] / rhs, lhs[1] / rhs);
}

vec2 operator/(float lhs, const vec2& rhs)
{
	return (rhs * lhs);
}

vec2 operator/(const vec2& lhs, const vec2& rhs)
{
	return vec2(lhs[0] / rhs[0], lhs[1] / rhs[1]);
}

bool operator==(const vec2& lhs, const vec2& rhs)
{
	if (lhs[0] == rhs[0] && lhs[1] == rhs[1])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator!=(const vec2& lhs, const vec2& rhs)
{
	if (lhs[0] != rhs[0] || lhs[1] != rhs[1])
	{
		return true;
	}
	else
	{
		return false;
	}
}

///Constructs an vector3 with 0 as the parameters.
vec3::vec3()
{
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
}

vec3::vec3(float x, float y, float a_Z)
{
	v[0] = x;
	v[1] = y;
	v[2] = a_Z;
}

vec3& vec3::operator=(const vec3& rhs)
{
	v[0] = rhs[0];
	v[1] = rhs[1];
	v[2] = rhs[2];

	return *this;
}

vec3& vec3::operator+=(const vec3& rhs)
{
	v[0] += rhs[0];
	v[1] += rhs[1];
	v[2] += rhs[2];

	return *this;
}

vec3& vec3::operator-=(const vec3& rhs)
{
	v[0] -= rhs[0];
	v[1] -= rhs[1];
	v[2] -= rhs[2];

	return *this;
}

vec3& vec3::operator*=(float rhs)
{
	v[0] *= rhs;
	v[1] *= rhs;
	v[2] *= rhs;

	return *this;
}

vec3& vec3::operator/=(float rhs)
{
	v[0] /= rhs;
	v[1] /= rhs;
	v[2] /= rhs;

	return *this;
}

float vec3::operator[](int index) const
{
	return v[index];
}

float& vec3::operator[](int index)
{
	return v[index];
}

//Ref: https://docs.google.com/document/d/12m5C-Fp3xP_zohZyFc-RsvFBmUFEuJR1rkjaHqLb_Z4/edit#heading=h.mp2omxmr1ruh
///Normalizes the vector.
vec3& vec3::normalize()
{
	float l = length();
	v[0] /= l;
	v[1] /= l;
	v[2] /= l;

	return *this;
}

//Ref: https://docs.google.com/document/d/12m5C-Fp3xP_zohZyFc-RsvFBmUFEuJR1rkjaHqLb_Z4/edit#heading=h.mp2omxmr1ruh
///Returns the normalized vector.
vec3 vec3::normalized() const
{
	float l = length();
	return vec3(v[0] / l, v[1] / l, v[2] / l);
}

///Flips/inverse the vector.
vec3 & vec3::inverse()
{
	v[0] = (-1 * v[0]);
	v[1] = (-1 * v[1]);
	v[2] = (-1 * v[2]);

	return *this;
}

///Returns the vector flipped/inversed.
vec3 vec3::inversed() const
{
	return vec3(-1 * v[0], -1 * v[1], -1 * v[2]);
}

///Rounds the vector.
vec3 & vec3::round()
{
	v[0] = std::roundf(v[0]);
	v[1] = std::roundf(v[1]);
	v[2] = std::roundf(v[2]);

	return *this;
}

///Return the vector rounded.
vec3 vec3::rounded() const
{
	return vec3(std::roundf(v[0]), std::roundf(v[1]), std::roundf(v[2]));
}

///Ceils the vector.
vec3 & vec3::ceil()
{
	v[0] = std::ceilf(v[0]);
	v[1] = std::ceilf(v[1]);
	v[2] = std::ceilf(v[2]);

	return *this;
}

///Returns the ceiled vector.
vec3 vec3::ceiled() const
{
	return vec3(std::ceilf(v[0]), std::ceilf(v[1]), std::ceilf(v[2]));
}

vec3 & vec3::floor()
{
	v[0] = std::floorf(v[0]);
	v[1] = std::floorf(v[1]);
	v[2] = std::floorf(v[2]);

	return *this;
}

vec3 vec3::floored() const
{
	return vec3(std::floorf(v[0]), std::floorf(v[1]), std::floorf(v[2]));
}

///Returns the dot product of 2 vectors.
float vec3::dot(vec3 const& lhs, vec3 const& rhs)
{
	return lhs.dot(rhs);
}

///Retuns the length of the vector.
float vec3::length(const vec3& lhs)
{
	return lhs.length();
}

///Returns the cross product of 2 vectors.
vec3 vec3::cross(const vec3& lhs, const vec3& rhs)
{
	return lhs.cross(rhs);
}

//Ref: https://docs.google.com/document/d/12m5C-Fp3xP_zohZyFc-RsvFBmUFEuJR1rkjaHqLb_Z4/edit#heading=h.gsxdsav2mztx
///Returns the angle between 2 vectors in radians.
float vec3::angle(const vec3& a, const vec3& b)
{
	float d = dot(a, b);
	float l = length(a) * length(b);

	return acosf(d / l);
}

//Ref: https://docs.google.com/document/d/12m5C-Fp3xP_zohZyFc-RsvFBmUFEuJR1rkjaHqLb_Z4/edit#heading=h.t6avepwqkoi0
///Returns the distance between 2 points.
float vec3::distance(const vec3& a, const vec3& b)
{
	return length(a - b);
}

///Normalizes the vector.
void vec3::normalize(vec3& vector)
{
	vector.normalize();
}

///Returns an normalized vector.
vec3 vec3::normalized(const vec3& vector)
{
	return vector.normalized();
}

///Clamps the vector between 2 values.
void vec3::clamp(vec3& vector, const float& min, const float& max)
{
	if (vector.x < min)
	{
		vector.x = min;
	}
	else if (vector.x > max)
	{
		vector.x = max;
	}

	if (vector.y < min)
	{
		vector.y = min;
	}
	else if (vector.y > max)
	{
		vector.y = max;
	}

	if (vector.z < min)
	{
		vector.z = min;
	}
	else if (vector.z > max)
	{ 
		vector.z = max;
	}
}

//Ref: https://docs.google.com/document/d/12m5C-Fp3xP_zohZyFc-RsvFBmUFEuJR1rkjaHqLb_Z4/edit#heading=h.bm1cp5g2bvun
///Returns the projected vector of A over B, returns vec3() if B is vec3().
vec3 vec3::project(const vec3& a, const vec3& b)
{
	if (b == vec3())
	{
		return vec3();
	}
	else
	{
		return vec3((a.dot(b) / b.dot(b)) * b);
	}
}

//Ref: https://docs.google.com/document/d/12m5C-Fp3xP_zohZyFc-RsvFBmUFEuJR1rkjaHqLb_Z4/edit#heading=h.bv8hv86lhvrl
///Reflect dir over normal (were L could be the lightdirection and R the surface normal).
vec3 vec3::reflect(const vec3& dir, const vec3& normal)
{
	return (dir - (2 * vec3::project(dir, normal))).inversed();
}

//Ref: https://docs.google.com/document/d/12m5C-Fp3xP_zohZyFc-RsvFBmUFEuJR1rkjaHqLb_Z4/edit#heading=h.bv8hv86lhvrl
///Reflect dir over normal (were dir could be the lightdirection and normal the surface normal).
vec3 vec3::reflect2(const vec3& dir, const vec3& normal)
{
	return vec3(2 * (normal * (normal.dot(dir))) - dir);
}

//Copied from https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/refract.xhtml
///Returns a refracted vector. eta is the refractionIndex.
vec3 vec3::refract(const vec3& dir, const vec3& normal, const float& eta)
{
	float k = 1.0f - eta * eta * (1.0f - dot(normal, dir) * dot(normal, dir));

	if (k < 0.0f)
	{
		return vec3(.0f, .0f, .0f);
	}
	else
	{
		return eta * dir - (eta * dot(normal, dir) + sqrt(k)) * normal;
	}
}

//Copied from: http://developer.download.nvidia.com/cg/refract.html
///Returns a refracted vector. eta is the refractionIndex.
vec3 vec3::refract2(const vec3& dir, const vec3& normal, const float& eta)
{
	float d = dot(dir.inversed(), normal);
	float cost2 = 1.0f - eta * eta * (1.0f - d * d);
	vec3 t = eta * dir + ((eta * d - sqrt(abs(cost2))) * normal);
	return t * (cost2 > 0);
}

//Copied from: https://www.reddit.com/r/Unity3D/comments/acwr62/made_a_function_to_simulate_the_refraction_of_a/
///Returns a refracted vector. r1 is the current refractionIndex and r2 the new one.
vec3 vec3::refract3(const vec3& dir, const vec3& normal, const float& ri1, const float& ri2)
{
	return (ri1 / ri2 * vec3::cross(normal, vec3::cross(normal.inversed(), dir)) - normal *
		sqrtf(1 - vec3::dot(vec3::cross(normal, dir) *
		(ri1 / ri2 * ri1 / ri2),
			vec3::cross(normal, dir)))).normalized();
}

//Copied from:
///Returns a refracted vector. ri is the refractionIndex.
vec3 vec3::refract4(const vec3& dir, const vec3& normal, const float& ri)
{
	float cosi = vec3::dot(dir, normal);
	float etai = 1.0f, etat = ri;
	vec3 n = normal;

	if (cosi < 0.0f)
	{
		cosi = -cosi;
	}
	else
	{
		etai = ri;
		etat = 1.0f;
		n = normal.inversed();
	}

	float eta = etai / etat;
	float k = 1.0f - eta * eta * (1.0f - cosi * cosi);
	return k < 0.0f ? vec3() : eta * dir + (eta * cosi - sqrtf(k)) * n;
}

///Returns a vector with random xyz values between 0 and 1.
vec3 vec3::random01()
{
	return vec3(Math::notSoRandomFloat01(), Math::notSoRandomFloat01(), Math::notSoRandomFloat01());
}

//Try to get a random point in a sphere by making a random vec3 and then checking if the length > 1 so that it is within the radius of a unit sphere.
///If your luck is hight use this function else use randomPointInUnitSphere2. This might take a while ;).
vec3 vec3::randomPointInUnitSphere()
{
	vec3 point;

	do
	{
		point = 2 * random01() - vec3(1.f, 1.f, 1.f);

	} while (point.length() > 1.0f);

	return point;
}

//Using normally distributed random numbers.
///Less luck in volved but havier calculations used.
vec3 vec3::randomPointInUnitSphere2()
{
	vec3 point = random01() * 2 - vec3(1.f, 1.f, 1.f);

	float l = point.length();
	point /= l;

	point *= cbrtf(Math::notSoRandomFloat01());

	return point;
}

vec3 operator+(const vec3& lhs, const vec3& rhs)
{
	return vec3(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
}

vec3 operator-(const vec3 & lhs, const vec3 & rhs)
{
	return vec3(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]);
}

vec3 operator*(const vec3& lhs, float rhs)
{
	return vec3(lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs);
}

vec3 operator*(float lhs, const vec3& rhs)
{
	return (rhs * lhs);
}

vec3 operator*(const vec3& lhs, const vec3& rhs)
{
	return vec3(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]);
}

vec3 operator/(const vec3& lhs, float rhs)
{
	return vec3(lhs[0] / rhs, lhs[1] / rhs, lhs[2] / rhs);
}

vec3 operator/(float lhs, const vec3& rhs)
{
	return (rhs * lhs);
}

vec3 operator/(const vec3& lhs, const vec3& rhs)
{
	return vec3(lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2]);
}

bool operator==(const vec3& lhs, const vec3& rhs)
{
	if (lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator!=(const vec3& lhs, const vec3& rhs)
{
	if (lhs[0] != rhs[0] || lhs[1] != rhs[1] || lhs[2] != rhs[2])
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Mat4
mat4::mat4()
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		m[i] = 0.0f;
	}
}

mat4::mat4(float a)
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		m[i] = a;
	}
}

mat4::mat4(vec3 a_Row0, float a_03, vec3 a_Row1, float a_13, vec3 a_Row2, float a_23, vec3 a_Row3, float a_33)
{
	for (unsigned int c = 0; c < 3; ++c)
	{
		mm[0][c] = a_Row0[c];
		mm[1][c] = a_Row1[c];
		mm[2][c] = a_Row2[c];
		mm[3][c] = a_Row3[c];
	}

	mm[0][3] = a_03;
	mm[1][3] = a_13;
	mm[2][3] = a_23;
	mm[3][3] = a_33;
}

mat4::mat4(float a_00, float a_01, float a_02, float a_03, 
	float a_10, float a_11, float a_12, float a_13, 
	float a_20, float a_21, float a_22, float a_23, 
	float a_30, float a_31, float a_32, float a_33)
{
	mm[0][0] = a_00; mm[0][1] = a_01; mm[0][2] = a_02; mm[0][3] = a_03;
	mm[1][0] = a_10; mm[1][1] = a_11; mm[1][2] = a_12; mm[1][3] = a_13;
	mm[2][0] = a_20; mm[2][1] = a_21; mm[2][2] = a_22; mm[2][3] = a_23;
	mm[3][0] = a_30; mm[3][1] = a_31; mm[3][2] = a_32; mm[3][3] = a_33;
}

mat4& mat4::operator=(const mat4& rhs)
{
	for (unsigned int r = 0; r < 4; ++r)
	{
		for (unsigned int c = 0; c < 4; ++c)
		{
			mm[r][c] = rhs.mm[r][c];
		}
	}

	return *this;
}

mat4& mat4::operator+=(const mat4& rhs)
{
	for (unsigned int r = 0; r < 4; ++r)
	{
		for (unsigned int c = 0; c < 4; ++c)
		{
			mm[r][c] += rhs.mm[r][c];
		}
	}

	return *this;
}

mat4& mat4::operator-=(const mat4& rhs)
{
	for (unsigned int r = 0; r < 4; ++r)
	{
		for (unsigned int c = 0; c < 4; ++c)
		{
			mm[r][c] -= rhs.mm[r][c];
		}
	}

	return *this;
}

mat4& mat4::operator*=(const mat4& rhs)
{
	mat4 matrix;

	for (unsigned int r = 0; r < 4; ++r)
	{
		for (unsigned int c = 0; c < 4; ++c)
		{
			matrix.mm[r][c] =
				mm[r][0] * rhs.mm[0][c] +
				mm[r][1] * rhs.mm[1][c] +
				mm[r][2] * rhs.mm[2][c] +
				mm[r][3] * rhs.mm[3][c];
		}
	}

	return (*this = matrix);
}

float mat4::determinant() const
{
	return (m[0] * (
			m[5] * (m[10] * m[15] - m[11] * m[14]) -
			m[6] * (m[9] * m[15] - m[11] * m[13]) +
			m[7] * (m[9] * m[14] - m[10] * m[13])
			) -
			m[1] * (
			m[4] * (m[10] * m[15] - m[11] * m[14]) -
			m[6] * (m[8] * m[15] - m[11] * m[12]) +
			m[7] * (m[8] * m[14] - m[10] * m[12])
			) +
			m[2] * (
			m[4] * (m[9] * m[15] - m[11] * m[13]) -
			m[5] * (m[8] * m[15] - m[11] * m[12]) + 
			m[7] * (m[8] * m[13] - m[9] * m[12])
			) -
			m[3] * (
			m[4] * (m[9] * m[14] - m[10] * m[13]) - 
			m[5] * (m[8] * m[14] - m[10] * m[12]) + 
			m[6] * (m[8] * m[13] - m[9] * m[12])));
}

mat4 mat4::identity()
{
	mat4 matrix;

	for (unsigned int r = 0; r < 4; ++r)
	{
		for (unsigned int c = 0; c < 4; ++c)
		{
			if (r == c)
			{
				matrix.mm[r][c] = 1;
			}
			else
			{
				matrix.mm[r][c] = 0;
			}
		}
	}

	return matrix;
}

mat4 mat4::rotateX(const float a_Radians)
{
	mat4 matrix = mat4::identity();

	matrix.mm[1][1] = cosf(a_Radians);
	matrix.mm[2][1] = sinf(a_Radians);
	matrix.mm[1][2] = matrix.mm[2][1] * -1.0f; //asinf(a_Radians);
	matrix.mm[2][2] = cosf(a_Radians);

	return matrix;
}

mat4 mat4::rotateY(const float a_Radians)
{
	mat4 matrix = mat4::identity();

	matrix.mm[0][0] = cosf(a_Radians);
	matrix.mm[0][2] = sinf(a_Radians);
	matrix.mm[2][0] = matrix.mm[0][2] * -1.0f; //asinf(a_Radians);
	matrix.mm[2][2] = cosf(a_Radians);

	return matrix;
}

mat4 mat4::rotateZ(const float a_Radians)
{
	mat4 matrix = mat4::identity();

	matrix.mm[0][0] = cosf(a_Radians);
	//matrix.mm[0][1] = asinf(a_Radians); //asinf gived me NaN results... Online I read something about float precision orso...
	matrix.mm[1][0] = sinf(a_Radians);
	matrix.mm[0][1] = matrix.mm[1][0] * -1.0f;
	matrix.mm[1][1] = cosf(a_Radians);

	return matrix;
}

mat4 mat4::translate(const vec3 & a_Translation)
{
	mat4 matrix = mat4::identity();

	for (unsigned int c = 0; c < 3; ++c)
	{
		matrix.mm[3][c] = a_Translation[c];
	}

	return matrix;
}

mat4 mat4::scale(const vec3 & a_Scale)
{
	mat4 matrix = mat4::identity();

	for (unsigned int rc = 0; rc < 3; ++rc)
	{
		matrix.mm[rc][rc] = a_Scale[rc];
	}

	return matrix;
}

mat4 operator+(const mat4& lhs, const mat4& rhs)
{
	mat4 matrix;

	for (unsigned int r = 0; r < 4; ++r)
	{
		for (unsigned int c = 0; c < 4; ++c)
		{
			matrix.mm[r][c] = lhs.mm[r][c] + rhs.mm[r][c];
		}
	}

	return matrix;
}

mat4 operator-(const mat4 & lhs, const mat4 & rhs)
{
	mat4 matrix;

	for (unsigned int r = 0; r < 4; ++r)
	{
		for (unsigned int c = 0; c < 4; ++c)
		{
			matrix.mm[r][c] = lhs.mm[r][c] - rhs.mm[r][c];
		}
	}

	return matrix;
}

mat4 operator*(const mat4& lhs, const mat4& rhs)
{
	mat4 matrix;

	for (unsigned int r = 0; r < 4; ++r)
	{
		for (unsigned int c = 0; c < 4; ++c)
		{
			matrix.mm[r][c] = 
				lhs.mm[r][0] * rhs.mm[0][c] +
				lhs.mm[r][1] * rhs.mm[1][c] +
				lhs.mm[r][2] * rhs.mm[2][c] +
				lhs.mm[r][3] * rhs.mm[3][c];
		}
	}

	return matrix;
}

mat4 operator*(const float & lhs, const mat4 & rhs)
{
	mat4 matrix;

	for (unsigned int r = 0; r < 4; ++r)
	{
		for (unsigned int c = 0; c < 4; ++c)
		{
			matrix.mm[r][c] = rhs.mm[r][c] * lhs;
		}
	}

	return matrix;
}

vec3 operator*(const vec3 & lhs, const mat4 & rhs)
{
	vec3 vec;

	for (unsigned int r = 0; r < 3; ++r)
	{
		for (unsigned int c = 0; c < 3; ++c)
		{
			vec[r] = rhs.mm[r][c] * lhs[c];
		}
	}

	return vec;
}
