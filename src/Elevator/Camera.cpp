#include "Camera.h"

Camera::Camera()
{
  this->m_iCameraCurrentFloor = 1;
  this->m_fRotationAngleX = 70;
  this->m_fRotationAngleY = 0;
  this->m_fRotationAngleZ = -20;
  this->m_position.x = 0;
  this->m_position.y = 7;
  this->m_position.z = -3;
  this->m_bMoveUpDownFlag = false;
  this->m_BoundingBoxesBuffer = new std::vector<BoundingBox*>;
}

Camera::Camera(float fRotationAngleX, float fRotationAngleY, float fRotationAngleZ, float positionX, float positionY, float positionZ)
{
  this->m_iCameraCurrentFloor = 1;
  this->m_fRotationAngleX = fRotationAngleX;
  this->m_fRotationAngleY = fRotationAngleY;
  this->m_fRotationAngleZ = fRotationAngleZ;
  this->m_position.x = positionX;
  this->m_position.y = positionY;
  this->m_position.z = positionZ;
  this->m_bMoveUpDownFlag = false;
  this->m_BoundingBoxesBuffer = new std::vector<BoundingBox*>;
}

Camera::~Camera()
{

}

//moves the camera along the axes OX and OY
void Camera::moveCamera()
{
  float angle = this->m_fRotationAngleZ / 180 * M_PI;
  float speed = 0;
  float moveCoeff = 0.05;

  Position oldPosition = m_position;

  if (GetKeyState('S') < 0) speed = -moveCoeff;
  if (GetKeyState('W') < 0) speed = moveCoeff;
  if (GetKeyState('A') < 0) { speed = moveCoeff; angle -= M_PI * 0.5; }
  if (GetKeyState('D') < 0) { speed = moveCoeff; angle += M_PI * 0.5; }

  if (speed != 0)
  {
    Position newPosition = oldPosition;
    newPosition.x -= sin(angle) * speed;
    newPosition.y -= cos(angle) * speed;

    bool collisionDetected = false;
    int i;
    for (i = 0; i < m_BoundingBoxesBuffer->size(); ++i)
    {
      BoundingBox* boundingBox = m_BoundingBoxesBuffer->at(i);

      if (checkCollision(*boundingBox, newPosition))
      {
        collisionDetected = true;
        break;
      }
    }
    if (!collisionDetected)
      m_position = newPosition;
  }
}

void Camera::moveUpDown(float movingCoef, UpDownDirection direction, float floorHeight, int currentFloor)
{
  float cameraHeight = 3.0f;
  float x = this->m_position.x;
  float y = this->m_position.y;
  float z = this->m_position.z + cameraHeight;

  z -= movingCoef;

  if (z <= -floorHeight * currentFloor)
  {
    z = -floorHeight * currentFloor;
    m_bMoveUpDownFlag = false;
  }
  else if (z >= (-floorHeight * (currentFloor-2)))
  {
    z = (-floorHeight * (currentFloor - 2));
    m_bMoveUpDownFlag = false;
  }

  Point point(x, y, z - cameraHeight);
  this->setPosition(point);
}

void Camera::rotationCamera()
{
  float rotationCoeff = 0.55;

  if (GetKeyState(0x26) < 0) m_fRotationAngleX = (m_fRotationAngleX + rotationCoeff) > 180 ? 180 : (m_fRotationAngleX + rotationCoeff);
  if (GetKeyState(0x28) < 0) m_fRotationAngleX = (m_fRotationAngleX - rotationCoeff) < 0 ? 0 : (m_fRotationAngleX - rotationCoeff);
  if (GetKeyState(0x25) < 0) m_fRotationAngleZ = (m_fRotationAngleZ - rotationCoeff);
  if (GetKeyState(0x27) < 0) m_fRotationAngleZ = (m_fRotationAngleZ + rotationCoeff);

  glRotatef(-m_fRotationAngleX, 1, 0, 0);
  glRotatef(m_fRotationAngleZ, 0, 0, 1);
  glTranslatef(m_position.x, m_position.y, m_position.z);
}

void Camera::setMoveUpDownFlag(const bool moveUpDownFlag)
{
  this->m_bMoveUpDownFlag = moveUpDownFlag;
}

bool Camera::setMoveUpDownFlag() const
{
  return m_bMoveUpDownFlag;
}

void Camera::setRotatinAngleX(const float angle)
{
  if(angle < 180 || angle > 0)
    this->m_fRotationAngleX = angle;
}

void Camera::setRotatinAngleY(const float angle)
{
  this->m_fRotationAngleY = angle;
}

void Camera::setRotatinAngleZ(const float angle)
{
  if (angle >= std::numeric_limits<float>::lowest() && angle <= std::numeric_limits<float>::max())
    this->m_fRotationAngleX = angle;
}

void Camera::setCameraCurrentFloor(const int cameraCurrentFloor)
{
  m_iCameraCurrentFloor = cameraCurrentFloor;
}

void Camera::setPosition(const Point position)
{
  this->m_position.x = position.x;
  this->m_position.y = position.y;
  this->m_position.z = position.z;
}

void Camera::setDoorsPtr(const ElevatorDoor* elevatorDoor)
{
  this->m_elevatorDoor = const_cast<ElevatorDoor*>(elevatorDoor);
}

void Camera::setBoundingBoxesBuffer(std::vector<BoundingBox*>* boundingBoxesBuffer)
{
  m_BoundingBoxesBuffer = boundingBoxesBuffer;
}

float Camera::getRotatinAngleX() const
{
  return this->m_fRotationAngleX;
}

float Camera::getRotatinAngleY() const
{
  return this->m_fRotationAngleY;
}

float Camera::getRotatinAngleZ() const
{
  return this->m_fRotationAngleZ;
}

int Camera::getCameraCurrentFloor() const
{
  return m_iCameraCurrentFloor;
}

//Checks for camera collision with elevator walls
bool Camera::checkCollision(const BoundingBox box, const Position newPosition)
{
  float tolerance = 0.05f;
  if ((newPosition.x >= box.getMinPoint().x - tolerance && newPosition.x <= box.getMaxPoint().x + tolerance) &&
      (newPosition.y >= box.getMinPoint().y - tolerance && newPosition.y <= box.getMaxPoint().y + tolerance))
  {
    return true;
  }
  else
  {
    return false;
  }
}

Position Camera::getPosition() const
{
  return this->m_position;
}

bool areEqual(float a, float b)
{
  float epsilon = 0.1f;
  return fabs(a - b) < epsilon;
}