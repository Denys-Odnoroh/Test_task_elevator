#include "ElevatorShaft.h"

ElevatorShaft::ElevatorShaft(ShaftWallsVertexBuffer* shaftWallsVertexBuffer)
{
  this->m_shaftWallsVertex = shaftWallsVertexBuffer;
  this->m_iNumberOfElements = this->m_shaftWallsVertex->size();
  this->m_boundingBoxesBuffer = new std::vector<BoundingBox*>;
  this->m_boundingBoxesBuffer->resize(m_iNumberOfElements);

  for (int i = 0; i < shaftWallsVertexBuffer->size(); ++i)
  {
    this->m_boundingBoxesBuffer->at(i) = new BoundingBox(shaftWallsVertexBuffer->at(i));
  }
}

ElevatorShaft::~ElevatorShaft()
{

}

void ElevatorShaft::drawElevatorShuft()
{
  glEnableClientState(GL_VERTEX_ARRAY);

  glPushMatrix();

  for (int i = 0; i < m_iNumberOfElements; ++i)
  {
    glVertexPointer(3, GL_FLOAT, 0, m_shaftWallsVertex->at(i).data());
    glColor3f(0.3f, 0.3f, 0.3f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  }

  glPopMatrix();
  glDisableClientState(GL_VERTEX_ARRAY);
}

void ElevatorShaft::setBoundingBoxesBuffer(const std::vector<BoundingBox*>* m_boundingBoxesBuffer)
{
  m_boundingBoxesBuffer = const_cast<std::vector<BoundingBox*>*>(m_boundingBoxesBuffer);
}

ShaftWallsVertexBuffer* ElevatorShaft::getshaftWallsVertex() const
{
  return this->m_shaftWallsVertex;
}

std::vector<BoundingBox*>* ElevatorShaft::getBoundingBoxesBuffer() const
{
  return m_boundingBoxesBuffer;
}
