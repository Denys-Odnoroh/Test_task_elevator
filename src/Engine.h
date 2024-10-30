#pragma once

#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <glfw3native.h>
#include <array>
#include "Button.h"
#include "Elevator.h"

typedef std::vector <std::vector<Point>> EngineWallsVertexBuffer;

class Engine
{
public:
	Engine(char* engineName);
	~Engine();

	void lift();
	void goDown();
	void drawEngine();
  void setColor(float r, float g, float b);
  void setFloorNumber(char* text);
	void setStartFlag(bool startFlag);
	void setElevator(Elevator* elevator);
	Elevator* getElevator();
	bool getStartFlag();
  char* getFloorNumber();
	std::array<float, 3> getColor();
	
private:
	void drawEngineButon();

private:
	EngineWallsVertexBuffer* m_wallsVertexBuffer;
	Elevator* m_elevator;
	std::array<float, 3> m_color;
	bool bStartFlag;
	char* m_cEngineName;
};