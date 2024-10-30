#pragma once
#include <iostream>
#include "CallElevatorButton.h"
#include "ElevatorPlatform.h"
#include "ElevatorShaft.h"
#include "ElevatorDoor.h"
#include "FloorButton.h"
#include "DoorButton.h"
#include "Camera.h"

class Elevator
{
public:
	Elevator(int minFloor, int maxFloor);
	~Elevator();

	void drawElevator();
	void move();
	void setCallElevatorButtons(const std::vector<CallElevatorButton*> callElevatorButtons);
	void setDoorButton(const std::vector<DoorButton*> doorButton);
	void setFloorButton(const std::vector<FloorButton*> floorButton);
	void setElevatorShuft(const ElevatorShaft* elevatorShuft);
	void setElevatorPlatform(const ElevatorPlatform* ElevatorPlatform);
	void setElevatorDoor(const ElevatorDoor* elevatorDoor);
	void setElevatorCurrentFloor(const int currentFloor);
	void setCamera(const Camera* camera);
	void setMoveElevatorFlag(const bool moveElevatorFlag);
	void setCallElevatorFlag(const bool callElevatorFlag);
	void setMovingDirection(const UpDownDirection direction);
	void setCalledFloor(int* calledFloor);
	std::vector<CallElevatorButton*> getCallElevatorButtons() const;
	std::vector<DoorButton*> getDoorButtons() const;
	std::vector<FloorButton*> getFloorButtons() const;
	ElevatorShaft* getElevatorShuft() const;
	ElevatorPlatform* getElevatorPlatform() const;
	ElevatorDoor* getElevatorDoor() const;
	Camera* getCamera() const;
	int getElevatorCurrentFloor() const;
	int getMinFloor() const;
	int getMaxFloor() const;
	int* getCalledFloor() const;
	bool getMoveElevatorFlag() const;
	bool getCallElevatorFlag() const;
	UpDownDirection getMovingDirection() const;

private:
	bool checkPersonInElevator();

private:
	std::vector<DoorButton*> m_doorButtons;
	std::vector<FloorButton*> m_floorButtons;
	ElevatorDoor* m_elevatorDoor;
	std::vector<CallElevatorButton*> m_callElevatorButtons;
	ElevatorPlatform* m_elevatorPlatform;
	ElevatorShaft* m_elevatorShaft;
  Camera* m_camera;
	int m_iElevatorCurrentFloor;
	int m_iMaxFloor;
	int m_iMinFloor;
	int* m_iCalledFloor;
	bool m_bMoveElevatorFlag;
	bool m_bCallElevator;
	UpDownDirection m_direction;
};