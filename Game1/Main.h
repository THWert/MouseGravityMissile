#pragma once
#define BMAX 70

class Main : public Scene
{
private:
	ObRect		player;
	ObCircle	pet;
	ObRect		gaugeBar;
	Bullet		bullet[BMAX];

	GameObject  firePos;

	Vector2		lastPos;

public:
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
