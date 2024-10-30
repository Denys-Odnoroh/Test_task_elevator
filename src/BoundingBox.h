#pragma once

#include <glfw3.h>
#include <cmath>
#include <vector>
#include "Point.h"

class BoundingBox
{
public:
  BoundingBox();
  BoundingBox(std::vector<Point> vertexBuffer);
  ~BoundingBox() {}

  void setBoundingBox(std::vector<Point> vertexBuffer);
  void setMaxAndMinPoints();
  Point getMinPoint() const;
  Point getMaxPoint() const;

private:
  Point m_points[4];
  Point m_min;
  Point m_max;
};