#include "stdafx.h"

Bullet::Bullet()
{
	missile.SetLocalPos(Vector2(2000.0f, 2000.0f));
	missile.scale.x = 30.0f;
	missile.rotation = 0.0f;
	missile.isVisible = false;

	missilePet.SetParentRT(missile);
	missilePet.SetLocalPos(Vector2(50.0f, 50.0f));
	missilePet.scale = Vector2(10.0f, 10.0f);
	missilePet.rotation = 0.0f;
	missilePet.isAxis = true;
	missilePet.isVisible = false;
}

void Bullet::Update(ObRect player)
{
	if (!missilePet.isVisible) return;

	Vector2 dir = fireDir * scalar + DOWN * gravity;

	missile.MoveWorldPos(dir * DELTA);
	missile.rotation = Utility::DirToRadian(dir);

	missilePet.revolution += 360.0f * ToRadian * DELTA;

	//scalar += 300.0f * DELTA;
	gravity += 300.0f * DELTA;

	missile.Update();
	missilePet.Update();

	Vector2 velocity = missile.GetWorldPos() - player.GetWorldPos();
	float dis = velocity.Length();

	if (dis > 2000.0f)
	{
		missile.isVisible = false;
		missilePet.isVisible = false;
	}
}

void Bullet::Render()
{
	if (!missilePet.isVisible) return;
	missile.Render();
	missilePet.Render();
}

bool Bullet::Shoot(Vector2 fireDir, float scalar, Vector2 firePos)
{
	if (!missilePet.isVisible)
	{
		missile.isVisible = true;
		missilePet.isVisible = true;
		missilePet.revolution = 0.0f;
		missile.rotation = Utility::DirToRadian(fireDir);
		missile.SetWorldPos(firePos);
		this->fireDir = fireDir;
		gravity = 0.0f;

		//rand() % 5 -> 0 4 
		//0 ~ 150 * 2 -> 0 ~ 300 + 150 -> 150 ~ 450
		//this->scalar = -scalar * 3.0f;
		this->scalar = scalar * 6.0f;

		return true;
	}
	return false;
}
