#include "BoundingBox.h"

BoundingBox::BoundingBox() 
{
  for (int i = 0; i < 4; ++i)
  {
    this->m_points[i] = {0.0f, 0.0f, 0.0f};
  }
  this->setMaxAndMinPoints();
}

BoundingBox::BoundingBox(std::vector<Point> vertexBuffer)
{
  for (int i = 0; i < 4; ++i)
  {
    this->m_points[i] = vertexBuffer[i];
  }
  this->setMaxAndMinPoints();
}

void BoundingBox::setBoundingBox(std::vector<Point> vertexBuffer)
{
  for (int i = 0; i < 4; ++i)
  {
    this->m_points[i] = vertexBuffer[i];
  }
  this->setMaxAndMinPoints();
}

void BoundingBox::setMaxAndMinPoints()
{
  m_min.x= this->m_points[0].x;
  m_min.y = this->m_points[0].y;
  m_min.z = this->m_points[0].z;
  m_max.x = this->m_points[0].x;
  m_max.y = this->m_points[0].y;
  m_max.z = this->m_points[0].z;

  for(int i = 1; i < 4; ++i)
  {
    if (m_points[i].x < m_min.x)
      m_min.x = m_points[i].x;

    if (m_points[i].y < m_min.y)
      m_min.y = m_points[i].y;

    if (m_points[i].z < m_min.z)
      m_min.z = m_points[i].z;

    if (m_points[i].x > m_max.x)
      m_max.x = m_points[i].x;

    if (m_points[i].y > m_max.y)
      m_max.y = m_points[i].y;

    if (m_points[i].z > m_max.z)
      m_max.z = m_points[i].z;
  }
}

Point BoundingBox::getMinPoint() const
{
  return this->m_min;
}


Point BoundingBox::getMaxPoint() const
{
  return this->m_max;
}
