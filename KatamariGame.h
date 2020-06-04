#pragma once
#include "Engine/Game.h"
#include "BoxObject.h"
#include "PyramidObject.h"

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
	BoxObject* box1;
	BoxObject* box2;
	BoxObject* box3;
	BoxObject* box4;
	PyramidObject* pyramid;
};

