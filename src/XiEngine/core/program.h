#pragma once

class Label;

class Program
{
public:
	void init();
	void update();

private:
	Label* coordLabels[3];
};
