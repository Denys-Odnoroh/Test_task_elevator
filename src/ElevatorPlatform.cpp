#include "ElevatorPlatform.h"

ElevatorPlatform::ElevatorPlatform(Point p1, Point p2, Point p3, Point p4)
{
  std::vector<Point> platformVertex{ p1, p2, p3, p4 };
  this->setPlatformVertex(platformVertex);
  this->m_boundingBox = new BoundingBox();
  this->m_boundingBox = new BoundingBox(this->m_platformVertex);
  this->m_fPlatformUpDownOffset = 0.0f;
}

ElevatorPlatform::~ElevatorPlatform()
{

}

void ElevatorPlatform::drawElevatorPlatform()
{
  std::vector<Point> vertexBuffer = this->getPlatformVertex();

  glPushMatrix();

  glTranslatef(0.0f, 0.0f, 0.01f);
  glColor3f(0.6f, 0.6f, 0.6f);
  glBegin(GL_QUADS);

  for (const auto& point : vertexBuffer) 
    glVertex3f(point.x, point.y, point.z);

  glEnd();

  glPopMatrix();
}

void ElevatorPlatform::move(float movingCoef, float floorHeight, int elevatorCurrentFloor)
{
  int floorAboveCoeff = elevatorCurrentFloor;
  int floorBelowCoeff = elevatorCurrentFloor - 2;

  m_fPlatformUpDownOffset += movingCoef;

  for (int i = 0; i < 4; ++i)
    m_platformVertex.at(i).z += movingCoef;

  if (m_fPlatformUpDownOffset >= floorHeight * floorAboveCoeff)
    m_fPlatformUpDownOffset = floorHeight * floorAboveCoeff;

  else if (m_fPlatformUpDownOffset <= floorHeight * floorBelowCoeff)
    m_fPlatformUpDownOffset = floorHeight * floorBelowCoeff;

  this->m_boundingBox->setBoundingBox(m_platformVertex);
}

void ElevatorPlatform::setPlatformVertex(const std::vector<Point> platformVertex)
{
  this->m_platformVertex = platformVertex;
}

void ElevatorPlatform::setBoundingBox(const BoundingBox* boundingBox)
{
  this->m_boundingBox = const_cast<BoundingBox*>(boundingBox);
}

void ElevatorPlatform::setPlatformUpDownOffset(const float platformUpDownOffset)
{
  this->m_fPlatformUpDownOffset = platformUpDownOffset;
}

std::vector<Point> ElevatorPlatform::getPlatformVertex() const
{
  return this->m_platformVertex;
}

BoundingBox* ElevatorPlatform::getBoundingBox() const
{
  return this->m_boundingBox;
}

float ElevatorPlatform::getPlatformUpDownOffset() const
{
  return this->m_fPlatformUpDownOffset;
}
