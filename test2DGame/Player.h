#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	virtual void Draw();
	virtual void Update();
	virtual void SetSpriteObject(Game2DSprite* _spriteObject);
	virtual D3DXVECTOR3 GetObjectPostion();
	virtual void Move(FLOAT _x, FLOAT _y);
	
private:
	Game2DSprite* spriteObject;
};

