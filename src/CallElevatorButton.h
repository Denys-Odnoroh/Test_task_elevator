#pragma once
#include "Button.h"

class CallElevatorButton : public Button
{
public:
  CallElevatorButton(Point p1, Point p2, Point p3, Point p4);
  virtual ~CallElevatorButton() override;
  virtual void drawButton() override;
  virtual void move(float movingCoef, float floorHeight, int elevatorCurrentFloor) override {};
 
};