#include "DoorButton.h"

DoorButton::DoorButton(char* text, Point p1, Point p2, Point p3, Point p4)
{
  std::vector<Point> buttonVertex{ p1, p2, p3, p4 };
  this->setButtonVertex(buttonVertex);
  this->setButtonText(text);
  this->setColor(0.6f, 0.6f, 0.6f);
  this->m_doorButtonVertex = this->getButtonVertex();
  this->m_fButtonUpDownOffset = 0.0f;
}

DoorButton::~DoorButton()
{

}

void DoorButton::drawButton()
{
  std::vector<Point> vertexBuffer = this->m_doorButtonVertex;
  std::array<float, 3> color = this->getColor();

  glPushMatrix();

  glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
  glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
  glTranslatef(1, 1, 1);
  glColor3f(color[0], color[1], color[2]);
  glBegin(GL_QUADS);

  for (const auto& point : vertexBuffer)
    glVertex3f(point.x, point.y, point.z);

  glEnd();

  float x = vertexBuffer.at(2).x - 0.04f;
  float y = (vertexBuffer.at(3).y - ((vertexBuffer.at(3).y - vertexBuffer.at(1).y) / 2));
  float z = vertexBuffer.at(0).z - 0.03f;
  Point point(x, y, z);

  glColor3f(0.0f, 0.0f, 0.0f);
  drawText(m_cButtonText, point);

  glPopMatrix();
}

void DoorButton::move(float movingCoef, float floorHeight, int elevatorCurrentFloor)
{
  int floorAboveCoeff = elevatorCurrentFloor;
  int floorBelowCoeff = elevatorCurrentFloor - 2;

  m_fButtonUpDownOffset += movingCoef;

  for(int i = 0; i < 4; ++i)
    m_doorButtonVertex.at(i).y += movingCoef;

  if (m_fButtonUpDownOffset >= floorHeight * floorAboveCoeff)
    m_fButtonUpDownOffset = floorHeight * floorAboveCoeff;

  else if (m_fButtonUpDownOffset <= floorHeight * floorBelowCoeff)
    m_fButtonUpDownOffset = floorHeight * floorBelowCoeff;
}

void DoorButton::setButtonText(char* text)
{
  if (text != nullptr)
    this->m_cButtonText = text;
  else
  {
    std::cerr << "The passed pointer = nullptr" << std::endl;
  }
}

char* DoorButton::getButtonText()
{
  if (this->m_cButtonText != nullptr)
    return this->m_cButtonText;
  else
  {
    std::cerr << "Text pointer = nullptr" << std::endl;
    return nullptr;
  }
}
