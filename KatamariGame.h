#pragma once
#include "Engine/Game.h"
#include "BoxObject.h"
#include "Engine/ModelObject.h"
#include "KatamariSphere.h"
#include "Engine/TexturedShader.h"
#include "Engine/Shader.h"

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

private:
	KatamariSphere* katamariSphere;
	BoxObject* plane;

	Shader* shader;
	TexturedShader* texturedShader;
	Texture* texture;
};

