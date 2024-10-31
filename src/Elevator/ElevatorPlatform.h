#pragma once
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <glfw3native.h>
#include <vector>
#include "BoundingBox.h"
#include "Point.h"

class ElevatorPlatform
{
public:
	ElevatorPlatform(Point p1, Point p2, Point p3, Point p4);
	~ElevatorPlatform();

	void drawElevatorPlatform();
	void move(float movingCoef, float floorHeight, int elevatorCurrentFloor);
	void setPlatformVertex(const std::vector<Point> platformVertex);
	void setBoundingBox(const BoundingBox* boundingBox);
	void setPlatformUpDownOffset(const float platformUpDownOffset);
	float getPlatformUpDownOffset() const;
	std::vector<Point> getPlatformVertex() const;
	BoundingBox* getBoundingBox() const;

private:
	std::vector<Point> m_platformVertex;
	BoundingBox* m_boundingBox;
	float m_fPlatformUpDownOffset;
};