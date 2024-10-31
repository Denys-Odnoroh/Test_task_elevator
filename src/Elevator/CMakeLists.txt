cmake_minimum_required (VERSION 3.8)
set(CMAKE_GENERATOR_PLATFORM x64)
project(Elevator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable (Elevator "main.cpp" 
"CallElevatorButton.h" "CallElevatorButton.cpp"
"ElevatorPlatform.h" "ElevatorPlatform.cpp"
"ElevatorShaft.h" "ElevatorShaft.cpp"
"ElevatorDoor.h" "ElevatorDoor.cpp"
"BoundingBox.h" "BoundingBox.cpp"
"FloorButton.h" "FloorButton.cpp"
"DoorButton.h" "DoorButton.cpp"
"Elevator.h" "Elevator.cpp"
"Engine.h" "Engine.cpp"
"Button.h" "Button.cpp"
"Camera.h" "Camera.cpp"
"Point.h" "Point.cpp")

target_include_directories(Elevator PRIVATE
    ${CMAKE_SOURCE_DIR}/GLFW/include/GLFW
    ${CMAKE_SOURCE_DIR}/GLEW/bin
    ${CMAKE_SOURCE_DIR}/GLEW/include
    ${CMAKE_SOURCE_DIR}/GLUT/include/GL
)

target_link_directories(Elevator PRIVATE 
    ${CMAKE_SOURCE_DIR}/GLFW/lib-vc2019
    ${CMAKE_SOURCE_DIR}/GLEW/lib
    ${CMAKE_SOURCE_DIR}/GLUT/lib/x64
    ${CMAKE_SOURCE_DIR}/GLUT/bin/x64
)

include_directories(${CMAKE_SOURCE_DIR}/GLM)

target_link_libraries(Elevator PUBLIC OpenGL32 glew32 glfw3 glfw3_mt glfw3dll)
