#pragma once

#include <iostream>
#include <math.h>

struct Vec2 {
	double x;
	double y;

	double Mag() {
		return sqrt(x * x + y * y);
	}

	Vec2 Rotate(double angle) {
		double tempX{ 0 }, s{ sin(angle) }, c{ cos(angle) };

		tempX = x * c - y * s;
		y = x * s + y * c;

		x = tempX;

		return Vec2{ x, y };
	}
};

Vec2 operator+(const Vec2 v1, const Vec2 v2) {
	return Vec2{ v1.x + v2.x, v1.y + v2.y };
}

Vec2 operator-(const Vec2 v1, const Vec2 v2) {
	return Vec2{ v1.x - v2.x, v1.y - v2.y };
}
//scale
Vec2 operator*(const double scale, const Vec2 v1) {
	return Vec2{ scale * v1.x , scale * v1.y };
}
//dot
double operator*(const Vec2 v1, const Vec2 v2) {
	return v1.x * v2.x + v1.y * v2.y;
}
//cross
Vec2 operator^(const Vec2 v1, const Vec2 v2) {
	return Vec2{ v1.y * v2.x - v1.x * v2.y, v1.x * v2.y - v1.y * v2.x };
}


struct Vec3 {
	double x;
	double y;
	double z;
	
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
	*/
	Vec3 Rotate(Vec3 angle) {
		Vec3 outVec{ x, y, z };

		outVec.x = 1;
		outVec.y = outVec.x * 0 + outVec.y * cos(angle.x) - outVec.z * sin(angle.x);
		outVec.z = outVec.x * 0 + outVec.y * sin(angle.x) + outVec.z * cos(angle.x);

		outVec.x = outVec.x * cos(angle.x) + outVec.y * 0 + outVec.z * sin(angle.x);
		outVec.y = 1;
		outVec.z = -outVec.x * sin(angle.x) + outVec.y * 0 + outVec.z * cos(angle.x);
	}
};

Vec3 operator+(const Vec3 v1, const Vec3 v2) {
	return Vec3{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

Vec3 operator-(const Vec3 v1, const Vec3 v2) {
	return Vec3{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}
//scale
Vec3 operator*(const double scale, const Vec3 v1) {
	return Vec3{ scale * v1.x, scale * v1.y, scale * v1.z };
}
//dot
double operator*(const Vec3 v1, const Vec3 v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
//cross
Vec3 operator^(const Vec3 v1, const Vec3 v2) {
	return Vec3{ v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
}