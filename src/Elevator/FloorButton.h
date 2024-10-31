#pragma once
#include "Button.h"

class FloorButton : public Button
{
public:
  FloorButton(char* floorNumber, Point p1, Point p2, Point p3, Point p4);
	virtual ~FloorButton() override;
  virtual void drawButton() override;
  virtual void move(float movingCoef, float floorHeight, int elevatorCurrentFloor) override;

	void setFloorNumber(char* number);
	char* getFloorNumber();

private:
	char* m_cFloorNumber;
	float m_fButtonUpDownOffset;
	std::vector<Point> m_floorButtonVertex;
};