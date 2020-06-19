#pragma once

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

#include "Engine/Game.h"
#include "BoxObject.h"
#include "Engine/ModelObject.h"
#include "KatamariSphere.h"
#include "Engine/TexturedShader.h"
#include "Engine/Shader.h"
#include "SceneGameObject.h"

#include <d2d1.h>
#include <d2d1_1.h>
#include <dwrite.h>

using namespace DirectX::SimpleMath;

class KatamariGame : public Game
{
public:
	KatamariGame();
	~KatamariGame();

	void init() override;
protected:
	void update() override;
	void drawObjects();
	void collisionCheck(GameObject* gameObject);

	void initDirect2D();

private:

	//Direct2d
	ID2D1Factory* pD2D1Factory;
	ID2D1SolidColorBrush* pSolidBrush;
	ID2D1RenderTarget* pRenderTarget2D;

	IDWriteFactory* pDWriteFactory;
	IDWriteTextFormat* pDTextFormat;
	IDWriteTextLayout* pDTextLayout;
	//end Direct2D
	
	SceneGameObject* katamariPlayer;
	KatamariSphere* katamariSphere;
	BoxObject* plane;
	BoxObject* box1;
	BoxObject* box2;
	BoxObject* box3;

	Shader* shader;
	TexturedShader* texturedShader;
	Texture* texture;
};

