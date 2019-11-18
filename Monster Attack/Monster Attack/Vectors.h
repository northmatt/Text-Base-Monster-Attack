#pragma once

#include <iostream>
#include <math.h>

class Vec2 {
public:
	Vec2(double xIn = 0, double yIn = 0) { x = xIn; y = yIn; }

	double x{ 0 };
	double y{ 0 };

	void Zero() {
		x = 0;
		y = 0;
	}

	double Mag() {
		return sqrt(x * x + y * y);
	}

	Vec2 Normalize() {
		double theMag = Mag();
		if (theMag > 0)
			return Vec2{ x / theMag, y / theMag };

		return Vec2{};
	}

	Vec2 Rotate(double angle) {
		double tempX{ 0 }, s{ sin(angle) }, c{ cos(angle) };

		tempX = x * c - y * s;
		y = x * s + y * c;

		x = tempX;

		return Vec2{ x, y };
	}

	Vec2 operator+(const Vec2 v2) {
		return Vec2{ x + v2.x, y + v2.y };
	}

	Vec2 operator-(const Vec2 v2) {
		return Vec2{ x - v2.x, y - v2.y };
	}
	//scale
	Vec2 operator*(const double scale) {
		return Vec2{ scale * x , scale * y };
	}
	//dot
	double operator*(const Vec2 v2) {
		return x * v2.x + y * v2.y;
	}
	//cross
	Vec2 operator^(const Vec2 v2) {
		return Vec2{ y * v2.x - x * v2.y, x * v2.y - y * v2.x };
	}
};

class Vec3 {
public:
	Vec3(double xIn = 0, double yIn = 0, double zIn = 0) { x = xIn; y = yIn; z = zIn; }

	double x{ 0 };
	double y{ 0 };
	double z{ 0 };

	double Mag() {
		return sqrt(x * x + y * y + z * z);
	}

	/*
	x
	[ 1 0     0    ]
	[ 0 yCos -zSin ]
	[ 0 ySin  zCos ]

	y
	[ xCos  0 zSin ]
	[ 0     1 0    ]
	[ -xSin 0 zCos ]

	z
	[ xCos -ySin 0 ]
	[ xSin  yCos 0 ]
	[ 0     0    1 ]
	
	Vec3 Rotate(Vec3 angle) {
		Vec3 outVec{ x, y, z };

		outVec.x = 1;
		outVec.y = outVec.x * 0 + outVec.y * cos(angle.x) - outVec.z * sin(angle.x);
		outVec.z = outVec.x * 0 + outVec.y * sin(angle.x) + outVec.z * cos(angle.x);

		outVec.x = outVec.x * cos(angle.x) + outVec.y * 0 + outVec.z * sin(angle.x);
		outVec.y = 1;
		outVec.z = -outVec.x * sin(angle.x) + outVec.y * 0 + outVec.z * cos(angle.x);
	}
	*/

	Vec3 operator+(const Vec3 v2) {
		return Vec3{ x + v2.x, y + v2.y, z + v2.z };
	}

	Vec3 operator-(const Vec3 v2) {
		return Vec3{ x - v2.x, y - v2.y, z - v2.z };
	}
	//scale
	Vec3 operator*(const double scale) {
		return Vec3{ scale * x, scale * y, scale * z };
	}
	//dot
	double operator*(const Vec3 v2) {
		return x * v2.x + y * v2.y + z * v2.z;
	}
	//cross
	Vec3 operator^(const Vec3 v2) {
		return Vec3{ y * v2.z - z * v2.y, z * v2.x - x * v2.z, x * v2.y - y * v2.x };
	}
};