#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
	delete spriteObject;
}

void Player::Update()
{
	spriteObject->DrawSprite();
}

void Player::SetSpriteObject(Game2DSprite* _spriteObject)
{
	if (_spriteObject != nullptr) spriteObject = _spriteObject;
}

D3DXVECTOR3 Player::GetObjectPostion()
{
	return spriteObject->GetSpritePos();
}

void Player::Move(FLOAT _x, FLOAT _y)
{
	spriteObject->TranslateSprite(_x, _y);
}
