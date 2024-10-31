#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <glew.h>
#include <glfw3.h>
#include <glfw3native.h>
#include <freeglut_std.h>
#include <freeglut_ext.h>
#include <freeglut.h>
#include <glut.h>
#include "BoundingBox.h"

class Button
{
public:
	Button();
	virtual ~Button();

  virtual void drawButton() = 0;
  virtual void move(float movingCoef, float floorHeight, int elevatorCurrentFloor) = 0;
	static void drawText(const char* text, Point point);
	void setButtonVertex(const std::vector<Point> buttonVertex);
	void setBoundingBox(const BoundingBox boundingBox);
	void setPressFlag(const bool pressFlag);
	void setColor(const float r, const float g, const float b);
	bool getPressFlag() const;
	BoundingBox getBoundingBox() const;
	std::array<float, 3> getColor() const;
	std::vector<Point> getButtonVertex() const;

private:
	bool m_bPressFlag;
	BoundingBox m_boundingBox;
	std::array<float, 3> m_color;
	std::vector<Point> m_buttonVertex;
};