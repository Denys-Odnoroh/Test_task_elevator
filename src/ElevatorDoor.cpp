#include "ElevatorDoor.h"

ElevatorDoor::ElevatorDoor(DoorSide door1Side, DoorSide door2Side, 
  float XShift1, float YShift1, float YShift2, 
  Point p1, Point p2, Point p3, Point p4, Point p5, Point p6, Point p7, Point p8)
{
  m_door1Side = door1Side;
  m_door2Side = door2Side;
  m_XShift1 = XShift1;
  m_YShift1 = YShift1;
  m_YShift2 = YShift2;
  std::vector<Point> door1Vertex{ p1, p2, p3, p4 };
  std::vector<Point> door2Vertex{ p5, p6, p7, p8 };
  this->setDoor1Vertex(door1Vertex);
  this->setDoor2Vertex(door2Vertex);
  this->m_bOpenFlag = false;
  this->m_bMoveDoors = false;
  this->m_bTimerActive = false;
  this->m_door1boundingBox = new BoundingBox(this->m_door1Vertex);
  this->m_door2boundingBox = new BoundingBox(this->m_door2Vertex);
  this->m_fDoor1SideOffset = 0.0f;
  this->m_fDoor2SideOffset = 0.0f;
  this->m_fDoorUpDownOffset = 0.0f;
  this->m_fDoorAutoCloseDelay = 5.0f;
  this->m_fDoorOpenTime = 0.0f;
}

ElevatorDoor::~ElevatorDoor()
{

}

void ElevatorDoor::startTimer()
{
  m_fDoorOpenTime = glfwGetTime();
  m_bTimerActive = true;
}

void ElevatorDoor::updateTimer()
{
  float f = glfwGetTime();
  if(m_bTimerActive && (glfwGetTime() - m_fDoorOpenTime >= m_fDoorAutoCloseDelay))
  {
    m_bMoveDoors = !m_bMoveDoors;
    m_bTimerActive = false;
  }
}

void ElevatorDoor::setOpenFlag(const bool openFlag)
{
  this->m_bOpenFlag = openFlag;
}

void ElevatorDoor::setDoor1BoundingBox(const BoundingBox* boundingBox)
{
  this->m_door1boundingBox = const_cast<BoundingBox*>(boundingBox);
}

void ElevatorDoor::setDoor2BoundingBox(const BoundingBox* boundingBox)
{
  this->m_door2boundingBox = const_cast<BoundingBox*>(boundingBox);
}

bool ElevatorDoor::getOpenFlag() const
{
  return this->m_bOpenFlag;
}

bool ElevatorDoor::getTimerActiveFlag() const
{
  return m_bTimerActive;
}

bool ElevatorDoor::getMoveDoorsFlag() const
{
  return this->m_bMoveDoors;
}

float ElevatorDoor::getDoor1SideOffset() const
{
  return this->m_fDoor1SideOffset;
}

float ElevatorDoor::getDoor2SideOffset() const
{
  return this->m_fDoor2SideOffset;
}

float ElevatorDoor::getDoorUpDownOffset() const
{
  return this->m_fDoorUpDownOffset;
}

BoundingBox* ElevatorDoor::getDoor1BoundingBox() const
{
  return this->m_door1boundingBox;
}

BoundingBox* ElevatorDoor::getDoor2BoundingBox() const
{
  return this->m_door2boundingBox;
}

void ElevatorDoor::setDoor1Vertex(const std::vector<Point> doorVertex)
{
  this->m_door1Vertex = doorVertex;
}

void ElevatorDoor::setDoor2Vertex(const std::vector<Point> doorVertex)
{
  this->m_door2Vertex = doorVertex;
}

void ElevatorDoor::setMoveDoorsFlag(bool b_moveDoorsFlag)
{
  this->m_bMoveDoors = b_moveDoorsFlag;
}

void ElevatorDoor::setDoor1SideOffset(float doorOffset)
{
  this->m_fDoor1SideOffset = doorOffset;
}

void ElevatorDoor::setDoor2SideOffset(float doorOffset)
{
  this->m_fDoor2SideOffset = doorOffset;
}

void ElevatorDoor::setDoorUpDownOffset(float doorUpDownOffset)
{
  this->m_fDoorUpDownOffset = doorUpDownOffset;
}

std::vector<Point> ElevatorDoor::getDoor1Vertex() const
{
  return this->m_door1Vertex;
}

std::vector<Point> ElevatorDoor::getDoor2Vertex() const
{
  return this->m_door2Vertex;
}

//Open or close door
void ElevatorDoor::setDoorsState()
{
  std::vector<Point> vertexBuffer1 = this->m_door1Vertex;
  std::vector<Point> vertexBuffer2 = this->m_door2Vertex;
  float movingCoef1 = 0;
  float movingCoef2 = 0;

  if (this->m_bOpenFlag == false)
  {
      movingCoef1 = -0.005f;
      movingCoef2 = 0.005f;
  }
  else if (this->m_bOpenFlag == true)
  {
      movingCoef1 = 0.005f;
      movingCoef2 = -0.005f;
  }

  if (!m_bOpenFlag)
  {
    m_fDoor1SideOffset += movingCoef1;
    m_fDoor2SideOffset += movingCoef2;

    for (int i = 0; i < 4; ++i)
    {
      m_door1Vertex.at(i).y -= movingCoef1;
      m_door2Vertex.at(i).y -= movingCoef2;
    }      

    if (m_fDoor1SideOffset <= -0.49f && m_fDoor2SideOffset >= 0.049f)
    {
        m_fDoor1SideOffset = -0.49f;
        m_fDoor2SideOffset = 0.49f;

      m_bOpenFlag = true;
      m_bMoveDoors = false;
      m_door1boundingBox->setBoundingBox(m_door1Vertex);
      m_door2boundingBox->setBoundingBox(m_door2Vertex);
    }
  }
  else 
  {
    m_fDoor1SideOffset += movingCoef1;
    m_fDoor2SideOffset += movingCoef2;

    for (int i = 0; i < 4; ++i)
    {
      m_door1Vertex.at(i).y -= movingCoef1;
      m_door2Vertex.at(i).y -= movingCoef2;
    }

    if ((m_fDoor1SideOffset >= 0.0f && m_fDoor2SideOffset <= 0.0f))
    {
      m_fDoor1SideOffset = 0.0f;
      m_fDoor2SideOffset = 0.0f;
      m_bOpenFlag = false;
      m_bMoveDoors = false;
      m_bTimerActive = false;
      m_door1boundingBox->setBoundingBox(m_door1Vertex);
      m_door2boundingBox->setBoundingBox(m_door2Vertex);
    }
  }
}

void ElevatorDoor::drawDoor()
{
  std::vector<Point> vertexBuffer1 = this->m_door1Vertex;
  std::vector<Point> vertexBuffer2 = this->m_door2Vertex;

  glPushMatrix();

  glRotatef(90.0f, 0.0f, 0.0f, 1.0f);

  glTranslatef(m_XShift1, m_YShift1, 0.0f);
  glBegin(GL_QUADS);
  glColor3f(0.7f, 0.7f, 0.7f); 
  glVertex3f(m_door1Vertex.at(0).x, m_door1Vertex.at(0).y - this->m_fDoor1SideOffset, m_door1Vertex.at(0).z + this->m_fDoorUpDownOffset);
  glVertex3f(m_door1Vertex.at(1).x, m_door1Vertex.at(1).y - this->m_fDoor1SideOffset, m_door1Vertex.at(1).z + this->m_fDoorUpDownOffset);
  glVertex3f(m_door1Vertex.at(2).x, m_door1Vertex.at(2).y - this->m_fDoor1SideOffset, m_door1Vertex.at(2).z + this->m_fDoorUpDownOffset);
  glVertex3f(m_door1Vertex.at(3).x, m_door1Vertex.at(3).y - this->m_fDoor1SideOffset, m_door1Vertex.at(3).z + this->m_fDoorUpDownOffset);
  glEnd();

  glTranslatef(0.0f, m_YShift2, 0.0f);
  glBegin(GL_QUADS);
  glVertex3f(m_door2Vertex.at(0).x, m_door2Vertex.at(0).y - this->m_fDoor2SideOffset, m_door2Vertex.at(0).z + this->m_fDoorUpDownOffset);
  glVertex3f(m_door2Vertex.at(1).x, m_door2Vertex.at(1).y - this->m_fDoor2SideOffset, m_door2Vertex.at(1).z + this->m_fDoorUpDownOffset);
  glVertex3f(m_door2Vertex.at(2).x, m_door2Vertex.at(2).y - this->m_fDoor2SideOffset, m_door2Vertex.at(2).z + this->m_fDoorUpDownOffset);
  glVertex3f(m_door2Vertex.at(3).x, m_door2Vertex.at(3).y - this->m_fDoor2SideOffset, m_door2Vertex.at(3).z + this->m_fDoorUpDownOffset);
  glEnd();

  glPopMatrix();
}

void ElevatorDoor::move(float movingCoef, float floorHeight, int elevatorCurrentFloor)
{
  int floorAboveCoeff = elevatorCurrentFloor;
  int floorBelowCoeff = elevatorCurrentFloor - 2;
  
  m_fDoorUpDownOffset += movingCoef;

  if (m_fDoorUpDownOffset >= floorHeight * floorAboveCoeff)
  {
    m_fDoorUpDownOffset = floorHeight * floorAboveCoeff;
    m_bMoveDoors = false;
  }
  else if (m_fDoorUpDownOffset <= floorHeight * floorBelowCoeff)
  {
    m_fDoorUpDownOffset = floorHeight * floorBelowCoeff;
    m_bMoveDoors = false;
  }
}
