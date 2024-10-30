#include "Button.h"

Button::Button()
{

}

Button::~Button()
{

}

void Button::setPressFlag(const bool pressFlag)
{
	this->m_bPressFlag = pressFlag;
}

void Button::setColor(const float r, const float g, const float b)
{
  this->m_color[0] = r;
  this->m_color[1] = g;
  this->m_color[2] = b;
}

std::array<float, 3> Button::getColor() const
{
  return this->m_color;
}

bool Button::getPressFlag() const
{
	return this->m_bPressFlag;
}

void Button::setBoundingBox(const BoundingBox boundingBox)
{
  this->m_boundingBox = boundingBox;
}

BoundingBox Button::getBoundingBox() const
{
  return this->m_boundingBox;
}

void Button::setButtonVertex(const std::vector<Point> buttonVertex)
{
	this->m_buttonVertex = buttonVertex;
}

std::vector<Point> Button::getButtonVertex() const
{
	return this->m_buttonVertex;
}

void Button::drawText(const char* text, Point point)
{
  glRasterPos3f(point.x, point.y, point.z);
  while (*text)
  {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
    text++;
  }
}
