#pragma once
class Bullet
{
public:
	ObLine		missile;
	ObCircle	missilePet;

	Vector2		fireDir;

	float		scalar;
	float		gravity;
public:
	Bullet();
	void Update(ObRect player);
	void Render();

	bool Shoot(Vector2 fireDir, float scalar, Vector2 firePos);
};

