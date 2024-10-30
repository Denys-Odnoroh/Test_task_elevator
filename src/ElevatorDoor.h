#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glfw3native.h>
#include <vector>
#include "BoundingBox.h"

enum DoorSide
{
  Left,
  Right
};

class ElevatorDoor
{
public:
  ElevatorDoor(DoorSide door1Side, DoorSide door2Side, float XShift1, float YShift1, float YShift2, Point p1, Point p2, Point p3, Point p4, Point p5, Point p6, Point p7, Point p8);
  ~ElevatorDoor();

  void startTimer();
  void updateTimer();
  void setOpenFlag(const bool openFlag);
  void setDoor1BoundingBox(const BoundingBox* boundingBox);
  void setDoor2BoundingBox(const BoundingBox* boundingBox);
  void setDoor1Vertex(const std::vector<Point> doorVertex);
  void setDoor2Vertex(const std::vector<Point> doorVertex);
  void setMoveDoorsFlag(const bool moveDoorsFlag);
  void setDoor1SideOffset(const float doorDideOffset);
  void setDoor2SideOffset(const float doorDideOffset);
  void setDoorUpDownOffset(const float doorUpDownOffset);
  bool getOpenFlag() const;
  bool getTimerActiveFlag() const;
  bool getMoveDoorsFlag() const;
  float getDoor1SideOffset() const;
  float getDoor2SideOffset() const;
  float getDoorUpDownOffset() const;
  BoundingBox* getDoor1BoundingBox() const;
  BoundingBox* getDoor2BoundingBox() const;
  std::vector<Point> getDoor1Vertex() const;
  std::vector<Point> getDoor2Vertex() const;

  void setDoorsState();
  void move(float movingCoef, float floorHeight, int elevatorCurrentFloor);
  void drawDoor();

private:
  float m_fDoorUpDownOffset;
  float m_fDoor1SideOffset;
  float m_fDoor2SideOffset;
  float m_XShift1, m_YShift1, m_YShift2;
  float m_fDoorAutoCloseDelay;
  float m_fDoorOpenTime;
  bool m_bTimerActive;
  bool m_bMoveDoors;
  bool m_bOpenFlag;
  std::vector<Point> m_door1Vertex;
  std::vector<Point> m_door2Vertex;
  BoundingBox* m_door1boundingBox;
  BoundingBox* m_door2boundingBox;
  DoorSide m_door1Side;
  DoorSide m_door2Side;
};