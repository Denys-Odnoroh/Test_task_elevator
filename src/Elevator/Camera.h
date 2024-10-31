#pragma once
#define _USE_MATH_DEFINES
#define NOMINMAX
#include <iostream>
#include <limits>
#include <math.h>
#include <windows.h>
#include <glew.h>
#include <glfw3.h>
#include <glfw3native.h>
#include "BoundingBox.h"
#include "ElevatorDoor.h"
#include "ElevatorShaft.h"

struct Position
{
  float x, y, z;
};

enum UpDownDirection
{
  UP,
  DOWN,
  NONE
};

class Camera
{


public:
  Camera();
  Camera(float fRotationAngleX, float fRotationAngleY, float fRotationAngleZ, float positionX, float positionY, float positionZ);
  ~Camera();
  
  void moveCamera();
  void moveUpDown(float movingCoef, UpDownDirection direction, float floorHeight, int currentFloor);
  void rotationCamera();
  void setMoveUpDownFlag(const bool moveUpDownFlag);
  void setRotatinAngleX(const float angle);
  void setRotatinAngleY(const float angle);
  void setRotatinAngleZ(const float angle);
  void setCameraCurrentFloor(const int cameraCurrentFloor);
  void setPosition(const Point position);
  void setDoorsPtr(const ElevatorDoor* elevatorDoor);
  void setBoundingBoxesBuffer(std::vector<BoundingBox*>* boundingBoxesBuffer);
  bool setMoveUpDownFlag() const;
  float getRotatinAngleX() const;
  float getRotatinAngleY() const;
  float getRotatinAngleZ() const;
  int getCameraCurrentFloor() const;
  Position getPosition() const;

private:
  bool checkCollision(const BoundingBox box, const Position newPosition);

private:
  std::vector<BoundingBox*>* m_BoundingBoxesBuffer;
  ElevatorDoor* m_elevatorDoor;
  float m_fRotationAngleX;
  float m_fRotationAngleY;
  float m_fRotationAngleZ;
  bool m_bMoveUpDownFlag;
  int m_iCameraCurrentFloor;
  Position m_position;
};

bool areEqual(float a, float b);