#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    player.SetWorldPos(Vector2(0.0f, 0.0f));
    player.scale = Vector2(80.0f, 80.0f);
    player.rotation = 0.0f;
    player.isAxis = true;
    player.isFilled = true;
    player.isVisible = true;
    player.color = Color(4.0f / 255.0f, 176.0f / 255.0f, 153.0f / 255.0f, 1.0f);

    pet.SetParentRT(player);
    pet.SetLocalPos(Vector2(100.0f, 100.0f));
    pet.scale = Vector2(30.0f, 30.0f);
    pet.rotation = 0.0f;
    pet.isAxis = true;

    gaugeBar.SetParentT(player);
    gaugeBar.pivot = OFFSET_L;
    gaugeBar.SetLocalPos(Vector2(-70.0f, 80.0f));
    gaugeBar.scale = Vector2(150.0f, 25.0f);
    gaugeBar.color = Color(113.0f / 255.0f, 79.0f / 255.0f, 209.0f / 255.0f, 1.0f);

    firePos.SetParentRT(player);
    firePos.SetLocalPosX(player.scale.x * 2.0f);
    firePos.scale = Vector2(80.0f, 80.0f);
    firePos.isAxis = false;
}

void Main::Release()
{
}

void Main::Update()
{
    if (INPUT->KeyPress('W'))
    {
        player.MoveWorldPos(player.GetUp() * 200.0f * DELTA);
    }
    if (INPUT->KeyPress('S'))
    {
        player.MoveWorldPos(-player.GetUp() * 200.0f * DELTA);
    }
    if (INPUT->KeyPress('A'))
    {
        player.MoveWorldPos(-player.GetRight() * 200.0f * DELTA);
    }
    if (INPUT->KeyPress('D'))
    {
        player.MoveWorldPos(player.GetRight() * 200.0f * DELTA);
    }

    if (INPUT->KeyDown(VK_LBUTTON))
    {
        gaugeBar.scale.x = 0.0f;
    }

    if (INPUT->KeyPress(VK_LBUTTON))
    {
        gaugeBar.scale.x += 150.0f * DELTA;

        if (gaugeBar.scale.x > 150.0f)
        {
            gaugeBar.scale.x = 150.0f;
        }
    }

    //발사해라
    if (INPUT->KeyUp(VK_LBUTTON))
    {
        for (int i = 0; i < BMAX; i++)
        {
            if(bullet[i].Shoot(player.GetRight(), gaugeBar.scale.x, firePos.GetWorldPos())) break;
        }       
    }

    Vector2 dir = INPUT->GetWorldMousePos() - player.GetWorldPos();
    player.rotation = Utility::DirToRadian(dir);

    pet.revolution += 30.0f * ToRadian * DELTA;

    player.Update();
    pet.Update();
    gaugeBar.Update();
    firePos.Update();
    for (int i = 0; i < BMAX; i++)
    {
        bullet[i].Update(player);
    }
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    player.Render();
    pet.Render();
    gaugeBar.Render();
    firePos.Render();
    for (int i = 0; i < BMAX; i++)
    {
        bullet[i].Render();
    }
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(1400, 800.0f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}