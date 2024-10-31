#include "Elevator.h"

Elevator::Elevator(int minFloor, int maxFloor)
{
	this->m_direction = UpDownDirection::NONE;
	this->m_bMoveElevatorFlag = false;
	this->m_bCallElevator = false;
	this->m_iMinFloor = minFloor;
	this->m_iMaxFloor = maxFloor;
	this->m_iElevatorCurrentFloor = 1;
	this->m_iCalledFloor = new int(0);

	this->m_elevatorPlatform = new ElevatorPlatform( Point::Point(-2.0f, -2.0f, 0.0f) , Point::Point(2.0f, -2.0f, 0.0f), Point::Point(2.0f, 2.0f, 0.0f), Point::Point(-2.0f, 2.0f, 0.0f));

	{
		//elevator shaft initialization
    ShaftWallsVertexBuffer* buffer = new ShaftWallsVertexBuffer;
		int bufferSize = 6 + m_iMaxFloor;
    buffer->resize(bufferSize);

		(*buffer)[0] = { Point::Point(-2.0f, -2.0f, 0.0f), Point::Point(-2.0f, -2.0f, 6.0f * m_iMaxFloor), Point::Point(-2.0f, 2.0f, 6.0f * m_iMaxFloor), Point::Point(-2.0f, 2.0f, 0.0f) };
    (*buffer)[1] = { Point::Point(2.0f, -2.0f, 0.0f), Point::Point(2.0f, -2.0f, 6.0f * m_iMaxFloor), Point::Point(2.0f, 2.0f, 6.0f * m_iMaxFloor), Point::Point(2.0f, 2.0f, 0.0f) };
    (*buffer)[2] = { Point::Point(-2.0f, 2.0f, 0.0f), Point::Point(2.0f, 2.0f, 0.0f), Point::Point(2.0f, 2.0f, 6.0f * m_iMaxFloor), Point::Point(-2.0f, 2.0f, 6.0f * m_iMaxFloor) };
    (*buffer)[3] = { Point::Point(2.0f, -2.0f, 0.0f), Point::Point(1.0f, -2.0f, 0.0f), Point::Point(1.0f, -2.0f, 6.0f * m_iMaxFloor), Point::Point(2.0f, -2.0f, 6.0f * m_iMaxFloor) };
    (*buffer)[4] = { Point::Point(-2.0f, -2.0f, 0.0f), Point::Point(-1.0f, -2.0f, 0.0f), Point::Point(-1.0f, -2.0f, 6.0f * m_iMaxFloor), Point::Point(-2.0f, -2.0f, 6.0f * m_iMaxFloor) };
    (*buffer)[5] = { Point::Point(-2.0f, -2.0f, 6.0f * m_iMaxFloor), Point::Point(2.0f, -2.0f, 6.0f * m_iMaxFloor), Point::Point(2.0f, -1.0f, 6.0f * m_iMaxFloor), Point::Point(-2.0f, -1.0f, 6.0f * m_iMaxFloor) };

		int floorNumb = 0;

		for (int i = 6; i < buffer->size(); ++i)
		{ 
			(*buffer)[i] = { Point::Point(-1.0f, -2.0f, 4.0f + (6 * floorNumb)), Point::Point(1.0f, -2.0f, 4.0f + (6 * floorNumb)), Point::Point(1.0f, -2.0f, 6.0f + (6 * floorNumb)), Point::Point(-1.0f, -2.0f, 6.0f + (6 * floorNumb)) };
			floorNumb++;
		}

    this->m_elevatorShaft = new ElevatorShaft(buffer);
	}
	
  {
		int floorNumb = 0;

		for (int i = 0; i < m_iMaxFloor; ++i)
		{
			CallElevatorButton* button = new CallElevatorButton(Point::Point(0.2f, 1.1f + (6 * floorNumb), 1.01f), Point::Point(0.4f, 1.1f + (6 * floorNumb), 1.01f), Point::Point(0.4f, 1.4f + (6 * floorNumb), 1.01f), Point::Point(0.2f, 1.4f + (6 * floorNumb), 1.01f));
			this->m_callElevatorButtons.push_back(button);
			++floorNumb;
		}		 
	}																													 

	{
    ElevatorDoor* door = new ElevatorDoor(DoorSide::Left, DoorSide::Right, -2.0f, 0.0f, -2.0f,
			Point::Point(0.01f, 0.01f, 0.0f), Point::Point(0.01f, 1.0f, 0.0f), Point::Point(0.01f, 1.0f, 4.0f), Point::Point(0.01f, 0.01f, 4.0f), 
			Point::Point(0.01f, 1.0f, 0.0f), Point::Point(0.01f, 1.99f, 0.0f), Point::Point(0.01f, 1.99f, 4.0f), Point::Point(0.01f, 1.0f, 4.0f));
    this->m_elevatorDoor = door;
	}

  {
    DoorButton* openDoor = new DoorButton("Open", Point::Point(- 2.6f, 1.1f, 0.99f), Point::Point(-2.4f, 1.1f, 0.99f), Point::Point(-2.4f, 1.4f, 0.99f), Point::Point(-2.6f, 1.4f, 0.99f));
    DoorButton* closeDoor = new DoorButton("Close", Point::Point(-2.2f, 1.1f, 0.99f), Point::Point(-2.0f, 1.1f, 0.99f), Point::Point(-2.0f, 1.4f, 0.99f), Point::Point(-2.2f, 1.4f, 0.99f));
    this->m_doorButtons.push_back(openDoor);
    this->m_doorButtons.push_back(closeDoor);
  }

  {
    FloorButton* firstFloor = new FloorButton("1", Point::Point(1.2f, -1.5f, 0.99f), Point::Point(1.0f, -1.5f, 0.99f), Point::Point(1.0f, -1.8f, 0.99f), Point::Point(1.2f, -1.8f, 0.99f));
		FloorButton* secondFloor = new FloorButton("2", Point::Point(1.6f, -1.5f, 0.99f), Point::Point(1.4f, -1.5f, 0.99f), Point::Point(1.4f, -1.8f, 0.99f), Point::Point(1.6f, -1.8f, 0.99f));
    this->m_floorButtons.push_back(firstFloor);
    this->m_floorButtons.push_back(secondFloor);
  }
	
}

Elevator::~Elevator()
{

}

bool Elevator::checkPersonInElevator()
{
	float x = this->getCamera()->getPosition().x;
	float y = this->getCamera()->getPosition().y;
	float z = -this->getCamera()->getPosition().z - 3;

	float maxX = this->getElevatorPlatform()->getBoundingBox()->getMaxPoint().x;
	float maxY = this->getElevatorPlatform()->getBoundingBox()->getMaxPoint().y;
	float maxZ = this->getElevatorPlatform()->getBoundingBox()->getMaxPoint().z;
	float minX = this->getElevatorPlatform()->getBoundingBox()->getMinPoint().x;
	float minY = this->getElevatorPlatform()->getBoundingBox()->getMinPoint().y;

	BoundingBox* platformBB = this->getElevatorPlatform()->getBoundingBox();

	platformBB->setBoundingBox(this->getElevatorPlatform()->getPlatformVertex());
	platformBB->setMaxAndMinPoints();

	if (minX < x && x < maxX && minY < y && y < maxY && areEqual(z, maxZ))
	{
		return true;
	}
	
	return false;
}

void Elevator::move()
{
	float movingCoef = 0;
	float floorHeight = 6.0f;
	int cameraCurrentFloor = m_camera->getCameraCurrentFloor();
	ElevatorPlatform* platform = this->getElevatorPlatform();
	Camera* camera = this->getCamera();
  ElevatorDoor* door = this->getElevatorDoor();

  if (this->getMovingDirection() == UpDownDirection::UP)
    movingCoef = 0.025f;
  else if (this->getMovingDirection() == UpDownDirection::DOWN)
    movingCoef = -0.025f;

	if ((m_iElevatorCurrentFloor > m_iMinFloor && this->getMovingDirection() == UpDownDirection::DOWN)
		|| (m_iElevatorCurrentFloor < m_iMaxFloor && this->getMovingDirection() == UpDownDirection::UP))
	{
    this->getElevatorDoor()->move(movingCoef, floorHeight, m_iElevatorCurrentFloor);
    this->getFloorButtons()[0]->move(movingCoef, floorHeight, m_iElevatorCurrentFloor);
    this->getFloorButtons()[1]->move(movingCoef, floorHeight, m_iElevatorCurrentFloor);
    this->getDoorButtons()[0]->move(movingCoef, floorHeight, m_iElevatorCurrentFloor);
    this->getDoorButtons()[1]->move(movingCoef, floorHeight, m_iElevatorCurrentFloor);
		this->getElevatorPlatform()->move(movingCoef, floorHeight, m_iElevatorCurrentFloor);
	}

//Check whether the camera is in the elevator and whether the elevator has gone up or down one floor
	if (this->getMovingDirection() == UpDownDirection::UP 
		&& m_iElevatorCurrentFloor < m_iMaxFloor && m_iElevatorCurrentFloor >= m_iMinFloor)
	{
		if (this->checkPersonInElevator() == true)
			camera->moveUpDown(movingCoef, this->getMovingDirection(), floorHeight, m_iElevatorCurrentFloor);

		if ((fmod(platform->getPlatformUpDownOffset(), floorHeight)) == 0)
		{
			m_iElevatorCurrentFloor += 1;

      if (m_bCallElevator == false && m_iElevatorCurrentFloor == *m_iCalledFloor)
        m_bMoveElevatorFlag = false;

			if (m_bCallElevator == false && this->checkPersonInElevator() == true)
			{
				m_camera->setCameraCurrentFloor(cameraCurrentFloor + 1);
			}
			else if (m_bCallElevator == true && m_iElevatorCurrentFloor == cameraCurrentFloor)
			{
				m_bCallElevator = false;
				m_bMoveElevatorFlag = false;
			}
		}
	}
	else if (this->getMovingDirection() == UpDownDirection::DOWN 
		&& m_iElevatorCurrentFloor > m_iMinFloor && m_iElevatorCurrentFloor <= m_iMaxFloor)
	{
		if (this->checkPersonInElevator() == true)
			camera->moveUpDown(movingCoef, this->getMovingDirection(), floorHeight, m_iElevatorCurrentFloor);

		if ((fmod(platform->getPlatformUpDownOffset(), floorHeight)) == 0)
    {
      m_iElevatorCurrentFloor -= 1;
			
			if (m_bCallElevator == false && m_iElevatorCurrentFloor == *m_iCalledFloor)
				m_bMoveElevatorFlag = false;

			if (m_bCallElevator == false && this->checkPersonInElevator() == true)
			{
				m_camera->setCameraCurrentFloor(cameraCurrentFloor - 1);
			}
      else if (m_bCallElevator == true && m_iElevatorCurrentFloor == cameraCurrentFloor)
      {
        m_bCallElevator = false;
        m_bMoveElevatorFlag = false;
      }
		}
	}

	if (m_bMoveElevatorFlag == false)
	{
    m_elevatorDoor->setMoveDoorsFlag(true);
	}
}

void Elevator::drawElevator()
{
	this->m_elevatorPlatform->drawElevatorPlatform();
	this->m_elevatorShaft->drawElevatorShuft();

  for (int i = 0; i < m_callElevatorButtons.size(); ++i)
    this->m_callElevatorButtons.at(i)->drawButton();

		this->m_elevatorDoor->drawDoor();

  for (int i = 0; i < m_floorButtons.size(); ++i)
    this->m_floorButtons.at(i)->drawButton();

  for (int i = 0; i < m_doorButtons.size(); ++i)
    this->m_doorButtons.at(i)->drawButton();
}

void Elevator::setCallElevatorButtons(const std::vector<CallElevatorButton*> callElevatorButtons)
{
		this->m_callElevatorButtons = callElevatorButtons;
}

void Elevator::setDoorButton(const std::vector<DoorButton*> doorButton)
{
		this->m_doorButtons = doorButton;
}

void Elevator::setFloorButton(const std::vector<FloorButton*> floorButton)
{
		this->m_floorButtons = floorButton;
}

void Elevator::setElevatorShuft(const ElevatorShaft* elevatorShuft)
{
	if (elevatorShuft != nullptr)
		this->m_elevatorShaft = const_cast<ElevatorShaft*>(elevatorShuft);
	else
		std::cerr << "Transmitted object pointer == nullptr" << std::endl;
}

void Elevator::setElevatorPlatform(const ElevatorPlatform* elevatorPlatform)
{
	if (elevatorPlatform != nullptr)
		this->m_elevatorPlatform = const_cast<ElevatorPlatform*>(elevatorPlatform);
	else
		std::cerr << "Transmitted object pointer == nullptr" << std::endl;
}

void Elevator::setElevatorDoor(const ElevatorDoor* elevatorDoor)
{
		this->m_elevatorDoor = const_cast<ElevatorDoor*>(elevatorDoor);
}

void Elevator::setElevatorCurrentFloor(const int currentFloor)
{
	this->m_iElevatorCurrentFloor = currentFloor;
}

void Elevator::setCamera(const Camera* camera)
{
  if (camera != nullptr)
    this->m_camera = const_cast<Camera*>(camera);
  else
    std::cerr << "Transmitted object pointer == nullptr" << std::endl;
}

void Elevator::setMoveElevatorFlag(const bool moveElevatorFlag)
{
	this->m_bMoveElevatorFlag = moveElevatorFlag;
}

void Elevator::setMovingDirection(const UpDownDirection direction)
{
	this->m_direction = direction;
}

void Elevator::setCalledFloor(int* calledFloor)
{
	m_iCalledFloor = calledFloor;
}

std::vector<CallElevatorButton*> Elevator::getCallElevatorButtons() const
{
	return this->m_callElevatorButtons;
}

std::vector<DoorButton*> Elevator::getDoorButtons() const
{
  return this->m_doorButtons;
}

std::vector<FloorButton*> Elevator::getFloorButtons() const
{
	return this->m_floorButtons;
}

ElevatorShaft* Elevator::getElevatorShuft() const
{
	if (m_elevatorShaft != nullptr)
	{
		return this->m_elevatorShaft;
	}
  else
  {
    std::cerr << "ElevatorShuft pointer == nullptr" << std::endl;
    return nullptr;
  }
}

ElevatorPlatform* Elevator::getElevatorPlatform() const
{
	if (m_elevatorPlatform != nullptr)
	{
		return this->m_elevatorPlatform;
	}
	else
	{
		std::cerr << "ElevatorPlatform pointer == nullptr" << std::endl;
		return nullptr;
	}
}

ElevatorDoor* Elevator::getElevatorDoor() const
{
	return this->m_elevatorDoor;
}

Camera* Elevator::getCamera() const
{
  if (m_camera != nullptr)
  {
    return this->m_camera;
  }
  else
  {
    std::cerr << "Camera pointer == nullptr" << std::endl;
    return nullptr;
  }
}

int Elevator::getElevatorCurrentFloor() const
{
	return m_iElevatorCurrentFloor;
}

int Elevator::getMinFloor() const
{
	return m_iMinFloor;
}

int Elevator::getMaxFloor() const
{
	return m_iMaxFloor;
}

int* Elevator::getCalledFloor() const
{
	return m_iCalledFloor;
}

bool Elevator::getMoveElevatorFlag() const
{
	return m_bMoveElevatorFlag;
}

bool Elevator::getCallElevatorFlag() const
{
	return m_bCallElevator;
}

void Elevator::setCallElevatorFlag(const bool callElevatorFlag)
{
	m_bCallElevator = callElevatorFlag;
}

UpDownDirection Elevator::getMovingDirection() const
{
  return m_direction;
}