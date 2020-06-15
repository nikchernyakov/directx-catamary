#pragma once
#include "Engine/Game.h"
#include "BoxObject.h"
#include "PyramidObject.h"
#include "Engine/ModelObject.h"

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
	ModelObject* model;
	BoxObject* plane;
};

