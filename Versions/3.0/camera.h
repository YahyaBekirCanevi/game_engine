#pragma once
#include <GLFW/glfw3.h>
#include "transform.h"
#include "Matrix.h"

#define SCREEN_W 600 
#define SCREEN_H 600 

class Camera {
public:
	float fov;
	float speed;
	float mouse_speed;
	float near; 
	float far;

	Camera() {
		this->mouse_speed = 10.0f;//0.005f
		this->fov = 60.0f;
		this->speed = 3.0f;
		this->near = 0.1f;
		this->far = 10.0f;
	}

	Matrix Perspective(float screenRatio) {
		Matrix m = Matrix::Zeros({4,4});
		float a = cos(this->fov * r2d * 0.5f)/sin(this->fov * r2d * 0.5f);
		m.setValueAt(0, 0, a / (screenRatio));
		m.setValueAt(1, 1, a);
		m.setValueAt(2, 2, (this->far + this->near) / (this->near - this->far));
		m.setValueAt(3, 2, (2 * this->far * this->near) / (this->near - this->far));
		m.setValueAt(2, 3, -1);
		return m;
	}
};