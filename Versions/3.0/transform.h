#pragma once
#include <iostream>
#include <math.h>
#include "Matrix.h"

#define r2d 0.0174532925 //radian to degree

using namespace std;

class vec3 {
public:
	float x;
	float y;
	float z;
	vec3() : x(0), y(0), z(0) {}
	vec3(float a, float b, float c) : x(a), y(b), z(c) {}
	float magnitude() { return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)); }
	float AngleBetween(vec3& b) {
		return acos(
			(this->x * b.x + this->y * b.y + this->z * b.z) /
			(this->magnitude() * b.magnitude())
		);
	}
	void Normalize() {
		this->x /= this->magnitude();
		this->y /= this->magnitude();
		this->z /= this->magnitude();
	}
	vec3 Cross(const vec3& b) {
		return vec3(this->y * b.z - this->z * b.y, this->z * b.x - this->x * b.z, this->x * b.y - this->y * b.x);
	}
	float Dot(const vec3& b) {
		return (this->x*b.x + this->y*b.y + this->z*b.z);
	}
	vec3 operator + (const vec3& b) {
		return vec3(this->x + b.x, this->y + b.y, this->z + b.z);
	}
	vec3 operator += (const vec3& b) {
		this->x += b.x;
		this->y += b.y;
		this->z += b.z;
		return vec3(this->x, this->y, this->z);
	}
	vec3 operator - (const vec3& b) {
		return vec3(this->x - b.x, this->y - b.y, this->z - b.z);
	}
	vec3 operator -= (const vec3& b) {
		this->x -= b.x;
		this->y -= b.y;
		this->z -= b.z;
		return vec3(this->x, this->y, this->z);
	}
	vec3 operator * (const vec3& b) {
		return vec3(this->y * b.z - this->z * b.y, this->z * b.x - this->x * b.z, this->x * b.y - this->y * b.x);
	}
	vec3 operator * (float b) {
		return vec3(this->x * b, this->y * b, this->z * b);
	}
	friend ostream& operator<<(ostream& os, const vec3& v) {
		os << v.x << " " << v.y << " " << v.z << "\n";
		return os;
	}
};

class EulerAngle {
public:
	float x;
	float y;
	float z;
	EulerAngle() : x(0), y(0), z(0) {}
	EulerAngle(float a, float b, float c) : x(a), y(b), z(c) {}	
	EulerAngle operator + (const EulerAngle& b) {
		return EulerAngle(this->x + b.x, this->y + b.y, this->z + b.z);
	}
	EulerAngle operator - (const EulerAngle& b) {
		return EulerAngle(this->x - b.x, this->y - b.y, this->z - b.z);
	}
	EulerAngle operator * (float b) {
		return EulerAngle(this->x * b, this->y * b, this->z * b);
	}
	friend ostream& operator<<(ostream& os, const EulerAngle& v) {
		os << v.x << " " << v.y << " " << v.z << "\n";
		return os;
	}
};

class Transform {
public:
	vec3 position;
	EulerAngle rotation;
	vec3 scale;
	Transform() {
		position = vec3(0.0f, 0.0f, 0.0f);
		rotation = EulerAngle(0.0f, 0.0f, 0.0f);
		scale = vec3(1.0f, 1.0f, 1.0f);
	}
	Transform(vec3 pos, EulerAngle rot, vec3 sc) : position(pos), rotation(rot), scale(sc) {}
	void Translate(vec3 pos) {
		this->position = vec3(
			this->position.x + pos.x,
			this->position.y + pos.y,
			this->position.z + pos.z);
	}
	void Rotate(EulerAngle angle) {
		this->rotation = EulerAngle(
			this->rotation.x + angle.x,
			this->rotation.y + angle.y,
			this->rotation.z + angle.z);
	}
	void Scale(vec3 enLarge) {
		this->scale = vec3(
			this->scale.x * enLarge.x,
			this->scale.y * enLarge.y,
			this->scale.z * enLarge.z);
	}
	Matrix LookAt(vec3 target, vec3 up) {
		Matrix m = Matrix::Identity(4);
		vec3 S, U, F;

		F = target - this->position;
		F.Normalize();
		S = F.Cross(up);
		S.Normalize();
		U = S.Cross(F);

		m.setValueAt(0, 0, S.x);
		m.setValueAt(1, 0, S.y);
		m.setValueAt(2, 0, S.z);
		m.setValueAt(0, 1, U.x);
		m.setValueAt(1, 1, U.y);
		m.setValueAt(2, 1, U.z);
		m.setValueAt(0, 2, -F.x);
		m.setValueAt(1, 2, -F.y);
		m.setValueAt(2, 2, -F.z);
		m.setValueAt(3, 0, -(S.Dot(this->position)));
		m.setValueAt(3, 1, -(U.Dot(this->position)));
		m.setValueAt(3, 2, F.Dot(this->position));
		return m;
	}
	Matrix PositionMatrix() {
		Matrix m = Matrix::Identity(4);
		m.setValueAt(0, 3, this->position.x);
		m.setValueAt(1, 3, this->position.y);
		m.setValueAt(2, 3, this->position.z);
		return m;
	}
	Matrix RotationMatrix() {
		float _x = this->rotation.x * r2d;
		float _y = this->rotation.y * r2d;
		float _z = this->rotation.z * r2d;

		Matrix pitch = Matrix::Identity(4);
		pitch.setValueAt(1, 1, cos(_x));
		pitch.setValueAt(1, 2, sin(_x));
		pitch.setValueAt(2, 1, -sin(_x));
		pitch.setValueAt(2, 2, cos(_x));
		Matrix yaw = Matrix::Identity(4);
		yaw.setValueAt(0, 0, cos(_y));
		yaw.setValueAt(0, 2, -sin(_y));
		yaw.setValueAt(2, 0, sin(_y));
		yaw.setValueAt(2, 2, cos(_y));
		Matrix roll = Matrix::Identity(4);
		roll.setValueAt(0, 0, cos(_z));
		roll.setValueAt(0, 1, -sin(_z));
		roll.setValueAt(1, 0, sin(_z));
		roll.setValueAt(1, 1, cos(_z));

		Matrix res = roll * yaw * pitch;
		return res;
	}
	Matrix ScaleMatrix() {
		Matrix m = Matrix::Identity(4);
		m.setValueAt(0, 0, this->scale.x);
		m.setValueAt(1, 1, this->scale.y);
		m.setValueAt(2, 2, this->scale.z);
		return m;
	}
	vec3 forward() {
		vec3 forward(
			cos(this->rotation.x * r2d) * sin(this->rotation.y * r2d),
			sin(this->rotation.y * r2d),
			cos(this->rotation.x * r2d) * cos(this->rotation.y * r2d));
		forward.Normalize();
		return forward * -1;
	}
	vec3 right() {
		vec3 right(this->forward().Cross(vec3(0, 1, 0)));
		right.Normalize();
		return right;
	}
	vec3 up() {
		vec3 up(this->right() * this->forward());
		up.Normalize();
		return up;
	}
};