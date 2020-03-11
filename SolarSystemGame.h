#pragma once
#include "Game.h"
#include "BoxObject.h"
#include "PyramidObject.h"

using namespace DirectX::SimpleMath;

class SolarSystemGame : public Game
{
public:
	SolarSystemGame();
	~SolarSystemGame();

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

