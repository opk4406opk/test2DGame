#pragma once
#include "Game2DSprite.h"
class Player2DSprite :
	public Game2DSprite
{
public:
	Player2DSprite();
	~Player2DSprite() override;
	void Init(IDirect3DDevice9 * _d3dDevice, char * _spriteFileName, RECT _rect) override;
	void DrawSprite() override;
	void TranslateSprite(FLOAT _x, FLOAT _y) override;
	void SetSpriteRect(RECT _spriteRect) override;
	void SetSpritePos(D3DXVECTOR3 _pos) override;
	D3DXVECTOR3 GetSpritePos() override;
protected:
	void CreateSprite() override;
	void CreateTexture2D() override;
};
