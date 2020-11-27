#pragma once
#include <cmath>
#include <algorithm>

struct Vector2 {
	float x, y;
	
public:
	
	Vector2() {
		x = 0;
		y = 0;
	}
	
	Vector2(float xVal, float yVal) {
		x = xVal;
		y = yVal;
	}
	
	// Operator overload so vectors can be added as v3 = v1 + v2
	Vector2 operator +(Vector2 vect) {
		Vector2 v(x + vect.x, y + vect.y);
		return v;
	}
	
	void setX(float xVal) {
		x = xVal;
	}
	
	void setY(float yVal) {
		y = yVal;
	}
	
	float getX() {
		return x;
	}
	
	float getY() {
		return y;
	}
	
	void setAngle(float angle) {
		float magnitude = getMagnitude();
		x = cos(angle) * magnitude;
		y = sin(angle) * magnitude;
	}
	
	float getAngle() {
		return atan2(y, x);
	}
	
	void setMagnitude(float magnitude) {
		float angle = getAngle();
		x = cos(angle) * magnitude;
		y = sin(angle) * magnitude;
	}
	
	float getMagnitude() {
		return sqrt(x*x + y*y);
	}
};

class Particle {
private:
	Vector2 gravity;
	Vector2 gTemp;
	Vector2 position;
public:
	Vector2 velocity;
	float mass, radius;
	olc::Pixel colour;
	
	Particle() {
		position = Vector2();
		velocity = Vector2();
		mass = 0;
		radius = 0;
		colour = olc::WHITE;
	}
	
	Particle(Vector2 pos, Vector2 vel, float m, float r, olc::Pixel p = olc::WHITE) {
		position = pos;
		velocity = vel;
		mass = m;
		radius = r;
		colour = p;
	}
	
	void setVelocity(const Vector2 &vel) {
		velocity.setX(vel.x);
		velocity.setY(vel.y);
	}
	
	float getX() {
		return position.getX();
	}
	
	float getY() {
		return position.getY();
	}
	
	void gravityTo(Particle obj) {
		float angleTo = atan2(obj.getY() - getY(), obj.getX() - getX());
		float distanceToX = obj.getX() - getX();
		float distanceToY = obj.getY() - getY();
		float distanceTo = sqrt(distanceToX * distanceToX + distanceToY * distanceToY);
		
		gTemp.setMagnitude(obj.mass / (distanceTo * distanceTo));
		gTemp.setAngle(angleTo);
		gravity = gravity + gTemp;
	}
	
	bool move(int ScreenWidth, int ScreenHeight) {
		velocity = velocity + gravity;
		position = position + velocity;
		gravity = Vector2();
		
		// Return false if object is far out of bounds
		if(position.getX() < -100) return false;
		if(position.getX() > ScreenWidth + 100) return false;
		if(position.getY() < -100) return false;
		if(position.getY() > ScreenHeight + 100) return false;
		
		return true;
	}
};
