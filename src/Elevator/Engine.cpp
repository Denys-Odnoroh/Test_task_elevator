#include "Engine.h"

Engine::Engine(char* engineName)
{
	this->bStartFlag = false;
  this->m_cEngineName = engineName;
  this->setColor(1.0f, 0.0f, 0.0f);

  m_wallsVertexBuffer = new EngineWallsVertexBuffer;
  int bufferSize = 6;
  m_wallsVertexBuffer->resize(bufferSize);

  (*m_wallsVertexBuffer)[1] = { Point::Point(-4.0f, -6.0f, 1.5f),   Point::Point(-3.0f, -6.0f, 1.5f),   Point::Point(-3.0f, -4.0f, 1.5f),   Point::Point(-4.0f, -4.0f, 1.5f) };
  (*m_wallsVertexBuffer)[0] = { Point::Point(-4.0f, -6.0f, 0.01f),  Point::Point(-3.0f, -6.0f, 0.01f),  Point::Point(-3.0f, -4.0f, 0.01f),  Point::Point(-4.0f, -4.0f, 0.01f) };
  (*m_wallsVertexBuffer)[2] = { Point::Point(-4.0f, -4.0f, 0.0f),   Point::Point(-4.0f, -6.0f, 0.0f),   Point::Point(-4.0f, -6.0f, 1.5f),   Point::Point(-4.0f, -4.0f, 1.5f) };
  (*m_wallsVertexBuffer)[3] = { Point::Point(-3.0f, -4.0f, 0.0f),   Point::Point(-3.0f, -6.0f, 0.0f),   Point::Point(-3.0f, -6.0f, 1.5f),   Point::Point(-3.0f, -4.0f, 1.5f) };
  (*m_wallsVertexBuffer)[4] = { Point::Point(-3.0f, -6.0f, 0.0f),   Point::Point(-4.0f, -6.0f, 0.0f),   Point::Point(-4.0f, -6.0f, 1.5f),   Point::Point(-3.0f, -6.0f, 1.5f) };
  (*m_wallsVertexBuffer)[5] = { Point::Point(-3.0f, -4.0f, 0.0f),   Point::Point(-4.0f, -4.0f, 0.0f),   Point::Point(-4.0f, -4.0f, 1.5f),   Point::Point(-3.0f, -4.0f, 1.5f) };
}

Engine::~Engine()
{

}

void Engine::lift()
{
  if (this->bStartFlag == true)
  {
    this->m_elevator->move();
  }
}

void Engine::goDown()
{
  if (this->bStartFlag == true)
  {
    this->m_elevator->move();
  }
}

void Engine::drawEngine()
{
  glColor3f(0.5f, 0.5f, 0.5f);

  glEnableClientState(GL_VERTEX_ARRAY);

  glPushMatrix();

  for (int i = 0; i < 6; ++i)
  {
    glVertexPointer(3, GL_FLOAT, 0, m_wallsVertexBuffer->at(i).data());
    glColor3f(0.3f, 0.3f, 0.3f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  }

  glPopMatrix();
  glDisableClientState(GL_VERTEX_ARRAY);

  drawEngineButon();
  Point point(-3.5f, -5.0f, 1.51f);
  Button::drawText(m_cEngineName, point);
}

void Engine::setColor(float r, float g, float b)
{
  this->m_color[0] = r;
  this->m_color[1] = g;
  this->m_color[2] = b;
}

void Engine::drawEngineButon()
{
  std::array<float, 3> color = this->getColor();

  glPushMatrix();

  glBegin(GL_QUADS);
  glColor3f(color[0], color[1], color[2]);
  glVertex3f(-3.3f, -4.1f, 1.51f);
  glVertex3f(-3.5f, -4.1f, 1.51f);
  glVertex3f(-3.5f, -4.4f, 1.51f);
  glVertex3f(-3.3f, -4.4f, 1.51f);
  glEnd();

  glPopMatrix();
} 

void Engine::setFloorNumber(char* text)
{
  if (text != nullptr)
    this->m_cEngineName = text;
  else
  {
    std::cerr << "The passed pointer = nullptr" << std::endl;
  }
}

void Engine::setStartFlag(bool startFlag)
{
  this->bStartFlag = startFlag;
}

void Engine::setElevator(Elevator* elevator)
{
  if (elevator != nullptr)
    this->m_elevator = elevator;
  else
  {
    std::cerr << "The passed pointer = nullptr" << std::endl;
  }
}

Elevator* Engine::getElevator()
{
  if (this->m_elevator != nullptr)
    return this->m_elevator;
  else
  {
    std::cerr << "Elevator pointer = nullptr" << std::endl;
    return nullptr;
  }
}

bool Engine::getStartFlag()
{
  return this->bStartFlag;
}

char* Engine::getFloorNumber()
{
  if (this->m_cEngineName != nullptr)
    return this->m_cEngineName;
  else
  {
    std::cerr << "Text pointer = nullptr" << std::endl;
    return nullptr;
  }
}

std::array<float, 3> Engine::getColor()
{
  return this->m_color;
}
