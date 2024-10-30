#include "CallElevatorButton.h"

CallElevatorButton::CallElevatorButton(Point p1, Point p2, Point p3, Point p4)
{
  std::vector<Point> buttonVertex { p1, p2, p3, p4 };
  this->setButtonVertex(buttonVertex);
  this->setColor(1.0f, 0.0f, 0.0f);
}

CallElevatorButton::~CallElevatorButton()
{

}

void CallElevatorButton::drawButton()
{
  std::vector<Point> vertexBuffer = this->getButtonVertex();
  std::array<float, 3> color = this->getColor();

  glPushMatrix();

  glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
  glTranslatef(1, 1, 1);
  glColor3f(color[0], color[1], color[2]);
  glBegin(GL_QUADS);

  for (const auto& point : vertexBuffer)
    glVertex3f(point.x, point.y, point.z);

  glEnd();

  glPopMatrix();
}
