#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glfw3native.h> 
#include <vector>
#include "BoundingBox.h"

typedef std::vector <std::vector<Point>> ShaftWallsVertexBuffer;

class ElevatorShaft
{
public:
	ElevatorShaft(ShaftWallsVertexBuffer* shaftWallsVertexBuffer);
	~ElevatorShaft();

	void drawElevatorShuft();
	void setBoundingBoxesBuffer(const std::vector<BoundingBox*>* boundingBox);
	ShaftWallsVertexBuffer* getshaftWallsVertex() const;
	std::vector<BoundingBox*>* getBoundingBoxesBuffer() const;

private:
	ShaftWallsVertexBuffer* m_shaftWallsVertex;
	std::vector<BoundingBox*>* m_boundingBoxesBuffer;
	int m_iNumberOfElements;
};