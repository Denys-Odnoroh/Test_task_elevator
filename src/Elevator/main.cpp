#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include "Camera.h"
#include "Elevator.h"
#include "Engine.h"

using namespace std;

Elevator* elevator = new Elevator(1, 4);
Engine* engine = new Engine("Engine");
Camera* camera = new Camera;

void screenToWorldRay(double mouseX, double mouseY, double* ox, double* oy, double* oz)
{
  int iVievPort[4];
  double modelViewMatrix[16], projectionMatrix[16];
  float z;

  glGetIntegerv(GL_VIEWPORT, iVievPort);
  mouseY = iVievPort[3] - mouseY - 1;

  glGetDoublev(GL_MODELVIEW_MATRIX, modelViewMatrix);
  glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);
  glReadPixels(mouseX, mouseY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
  gluUnProject(mouseX, mouseY, z, modelViewMatrix, projectionMatrix, iVievPort, ox, oy, oz);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) 
{
  double x, y, z;

  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
  {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    int screenWidth, screenHeight;
    glfwGetWindowSize(window, &screenWidth, &screenHeight);

    screenToWorldRay(mouseX, mouseY, &x, &y, &z);
    system("cls");
    std::cout << "Mouse press coordinates (x, y, z): " << x << ", " << y << ", " << z;
  }
}

void enableMoveFlags()
{
  if (elevator->getElevatorDoor()->getOpenFlag() == true)
  {
    elevator->getElevatorDoor()->setMoveDoorsFlag(true);
  }
  elevator->setMoveElevatorFlag(true);
}

void inputFloorNumber(int minFloor, int maxFloor, int *calledFloor)
{
  std::cout << "\nInput floor. Min: " << minFloor << ". Max: " << maxFloor << "\n";
  std::cin >> *calledFloor;

  while (*calledFloor < minFloor || *calledFloor > maxFloor)
  {
    std::cout << "Incorrect data. Input valid floor: ";
    std::cin >> *calledFloor;
  }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
  if (action == GLFW_PRESS)
  {
    std::vector<CallElevatorButton*> callElevatorButtonBuffer = elevator->getCallElevatorButtons();
    int iElevatorCurrentFloor = elevator->getElevatorCurrentFloor();
    int iCameraFloor = camera->getCameraCurrentFloor();

    switch (key)
    {
    case GLFW_KEY_1:
    {
      int *iCalledFloor = elevator->getCalledFloor();
      int iMinFloor = elevator->getMinFloor();
      int iMaxFloor = elevator->getMaxFloor();

      if (engine->getStartFlag() == true)
      {
        inputFloorNumber(iMinFloor, iMaxFloor, iCalledFloor);

        if (*iCalledFloor != iElevatorCurrentFloor)
        {
          callElevatorButtonBuffer.at(iElevatorCurrentFloor - 1)->setColor(1.0f, 0.0f, 0.0f);
          callElevatorButtonBuffer.at(*iCalledFloor - 1)->setColor(0.0f, 1.0f, 0.0f);
          enableMoveFlags();
        }
        
        if (*iCalledFloor > iElevatorCurrentFloor)
          elevator->setMovingDirection(UpDownDirection::UP);
        else if (*iCalledFloor < iElevatorCurrentFloor)
          elevator->setMovingDirection(UpDownDirection::DOWN);
      }  
      break;
    }
    case GLFW_KEY_2:
    {
      if (engine->getStartFlag() == true && iElevatorCurrentFloor != iCameraFloor)
      {
        enableMoveFlags();
        
        if (iCameraFloor < iElevatorCurrentFloor)
        {
          elevator->setMovingDirection(UpDownDirection::DOWN);
          elevator->setCallElevatorFlag(true);
        }
          
        else if (iCameraFloor > iElevatorCurrentFloor)
        {
          elevator->setMovingDirection(UpDownDirection::UP);
          elevator->setCallElevatorFlag(true);
        }
        callElevatorButtonBuffer.at(iElevatorCurrentFloor - 1)->setColor(1.0f, 0.0f, 0.0f);
        callElevatorButtonBuffer.at(iCameraFloor - 1)->setColor(0.0f, 1.0f, 0.0f);
      }
      break;
    }
    case GLFW_KEY_3:
    {
      ElevatorDoor* door = elevator->getElevatorDoor();
      float closeCoeff = 0.0f;
      float openCoeff = 0.49f;

      if(engine->getStartFlag() == true)
      {
        if ((door->getDoor1SideOffset() == closeCoeff) ||(door->getDoor1SideOffset() == -openCoeff && door->getDoor2SideOffset() == openCoeff))
        {
          door->setMoveDoorsFlag(true);
        }
      }
      break;
    }
    case GLFW_KEY_4:
    {
      if (engine->getColor()[0] == 1.0f)
      {
        engine->setStartFlag(true);
        engine->setColor(0.0f, 1.0f, 0.0f);
        callElevatorButtonBuffer.at(iElevatorCurrentFloor - 1)->setColor(0.0f, 1.0f, 0.0f);
      }
      else if (engine->getColor()[0] == 0.0f)
      {
        engine->setStartFlag(false);
        engine->setColor(1.0f, 0.0f, 0.0f);
        callElevatorButtonBuffer.at(iElevatorCurrentFloor - 1)->setColor(1.0f, 0.0f, 0.0f);
      }
      break;
    }
    }
  }
}

void drawFloor()
{
  std::vector<float> m_rectangleVertexBuffer = { 1,1,0, 1,-1,0, -1,-1,0, -1,1,0 };

  glEnableClientState(GL_VERTEX_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, m_rectangleVertexBuffer.data());

  for (int i = -10; i < 5; i++)
  {
    for (int j = -10; j < 5; j++)
    {
      glPushMatrix();

      if ((i + j) % 2 == 0)
        glColor3f(0, 0.5, 0);
      else glColor3f(1, 1, 1);

      glTranslatef(i * 2.0f, j * 2.0f, 0.0f);
      glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

      glPopMatrix();
    }
  }

  glDisableClientState(GL_VERTEX_ARRAY);
}

void lightInit()
{
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);

  GLfloat lightPos[] = { 0.0f, 0.0f, 1.0f, 1.0f };
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

int glInit(GLFWwindow* window, int argc, char** argv)
{
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK)
  {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    glfwTerminate();
    return -1;
  }

  glutInit(&argc, argv);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-0.5, 0.5, -0.5, 0.5, 0.5, 80);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glEnable(GL_DEPTH_TEST);
  lightInit();
}

int main(int argc, char** argv)
{
  GLFWwindow* window;
  ElevatorDoor* door = elevator->getElevatorDoor();
  //std::vector<BoundingBox*>* boundingBoxesBuffer = elevator->getElevatorShuft()->getBoundingBoxesBuffer();
  //boundingBoxesBuffer->push_back(door1->getBoundingBox());
  //boundingBoxesBuffer->push_back(door2->getBoundingBox());

  elevator->setCamera(camera);
  engine->setElevator(elevator);
  camera->setDoorsPtr(elevator->getElevatorDoor());
  //camera->setBoundingBoxesBuffer(boundingBoxesBuffer);

  if (!glfwInit())
    return -1;

  window = glfwCreateWindow(1900, 1600, "Elevator", NULL, NULL);

  glInit(window, argc, argv);

  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetKeyCallback(window, key_callback);

  while (!glfwWindowShouldClose(window))
  {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (door->getMoveDoorsFlag() == true)
    {
      door->setDoorsState();
    }

    if (door->getOpenFlag() == false && elevator->getMoveElevatorFlag() == true)
    {
      if (elevator->getMovingDirection() == UpDownDirection::UP)
      {
        engine->lift();
      }
      else if (elevator->getMovingDirection() == UpDownDirection::DOWN)
      {
        engine->goDown();
      }
    }

    //If the doors are opened, the timer for closing them is activated
    if (door->getOpenFlag() == true && elevator->getMoveElevatorFlag() == false)
    {
      if (door->getTimerActiveFlag() == false)
      {
        door->startTimer();
      }
      else if (door->getTimerActiveFlag() == true)
      {
        door->updateTimer();
      }
    }
      
    glPushMatrix();

    camera->moveCamera();
    camera->rotationCamera();
    drawFloor();
    elevator->drawElevator();
    engine->drawEngine();

    glPopMatrix();

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
