#pragma once

class Label;
class Terrain;

class Program
{
public:
	void init();
	void update();

private:
	Label* coordLabels[3];
	Label* drawLabels[2];
	Label* updatesLabel[2];
	Label* terrainLabel[2];

	Terrain* terrain;
};
