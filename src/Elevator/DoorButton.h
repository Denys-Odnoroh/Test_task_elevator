#pragma once
#include "Button.h"

class DoorButton : public Button
{
public:
  DoorButton(char* text, Point p1, Point p2, Point p3, Point p4);
	virtual ~DoorButton() override;
  virtual void drawButton() override;
  virtual void move(float movingCoef, float floorHeight, int elevatorCurrentFloor) override;

	void setButtonText(char* text);
	char* getButtonText();
  
private:
	char* m_cButtonText;
  float m_fButtonUpDownOffset;
	std::vector<Point> m_doorButtonVertex;
};