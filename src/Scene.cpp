#include "Scene.hpp"
#include <vector>

Scene::Scene() {
	createScene();
}

void Scene::createScene() {
	//Create the vertices for the walls, roof and floor  
	const vec3 V1 = vec3(0.f, 6.f, 5.f);
	const vec3 V2 = vec3(0.f, 6.f, -5.f);
	const vec3 V3 = vec3(-3.f, 0.f, -5.f);
	const vec3 V4 = vec3(-3.f, 0.f, 5.f);
	const vec3 V5 = vec3(10.f, 6.f, 5.f);
	const vec3 V6 = vec3(10.f, 6.f, -5.f);
	const vec3 V7 = vec3(13.f, 0.f, -5.f);
	const vec3 V8 = vec3(13.f, 0.f, 5.f);
	const vec3 V9 = vec3(0.f, -6.f, -5.f);
	const vec3 V10 = vec3(0.f, -6.f, 5.f);
	const vec3 V11 = vec3(10.f, -6.f, 5.f);
	const vec3 V12 = vec3(10.f, -6.f, -5.f);

	//Create the colors for the walls, roof and floor
	const colorDBL RED = colorDBL(1.0, 0.0, 0.0);
	const colorDBL GREEN = colorDBL(0.0, 1.0, 0.0);
	const colorDBL YELLOW = colorDBL(1.0, 1.0, 0.0);
	const colorDBL PURPLE = colorDBL(1.0, 0.0, 1.0);
	const colorDBL BLUE = colorDBL(0.0, 0.0, 1.0);
	const colorDBL GRAY = colorDBL(0.5, 0.5, 0.5);
	const colorDBL WHITE = colorDBL(1.0, 1.0, 1.0);
	const colorDBL CYAN = colorDBL(0.0, 1.0, 1.0);
	
	//create the vectors of vertices for the walls, roof and floor
	std::vector <vec3> topLeftWallVertices = { V2, V1, V4 ,V3 };
	std::vector <vec3> topRightWallVertices = { V5, V6, V7, V8 };
	std::vector <vec3> topWallVertices = { V1, V2, V6 ,V5 };
	std::vector <vec3> bottomLeftWallVertices = { V4, V10, V9 ,V3 };
	std::vector <vec3> bottomRightLeftWallVertices = { V8, V7, V12, V11 };
	std::vector <vec3> bottomWallVertices = { V10, V11, V12, V9 };
	std::vector <vec3> roofMiddleVertices = { V1, V5, V11, V10 };
	std::vector <vec3> roofLeftVertices = { V1, V10, V4 };
	std::vector <vec3> roofRightVertices = { V5, V8, V11 };
	std::vector <vec3> floorMiddleVertices = { V2, V9, V12 ,V6 };
	std::vector <vec3> floorLeftVertices = { V2, V3, V9 };
	std::vector <vec3> floorRightVertices = { V6, V12, V7 };

	//create the Rectangles
	Rectangle topLeftWall(topLeftWallVertices[0], topLeftWallVertices[1], topLeftWallVertices[2], topLeftWallVertices[3], RED);
	Rectangle topRightWall(topRightWallVertices[0], topRightWallVertices[1], topRightWallVertices[2], topRightWallVertices[3], BLUE);
	Rectangle topWall(topWallVertices[0], topWallVertices[1], topWallVertices[2], topWallVertices[3], YELLOW);
	Rectangle bottomWall(bottomWallVertices[0], bottomWallVertices[1], bottomWallVertices[2], bottomWallVertices[3], GREEN);
	Rectangle bottomLeftWall(bottomLeftWallVertices[0], bottomLeftWallVertices[1], bottomLeftWallVertices[2], bottomLeftWallVertices[3], PURPLE);
	Rectangle bottomRightWall(bottomRightLeftWallVertices[0], bottomRightLeftWallVertices[1], bottomRightLeftWallVertices[2], bottomRightLeftWallVertices[3], CYAN);
	Rectangle roofMiddle(roofMiddleVertices[0], roofMiddleVertices[1], roofMiddleVertices[2], roofMiddleVertices[3], WHITE);
	Rectangle floorMiddle(floorMiddleVertices[0], floorMiddleVertices[1], floorMiddleVertices[2], floorMiddleVertices[3], GRAY);
	
	//create the triangles which make up part of the roof and floor
	Triangle roofLeft(roofLeftVertices[0], roofLeftVertices[1], roofLeftVertices[2], WHITE);
	Triangle roofRight(roofRightVertices[0], roofRightVertices[1], roofRightVertices[2], WHITE);
	Triangle floorLeft(floorLeftVertices[0], floorLeftVertices[1], floorLeftVertices[2], GRAY);
	Triangle floorRight(floorRightVertices[0], floorRightVertices[1], floorRightVertices[2], GRAY);
	
	//add the triangles to the vector of triangles
	sceneTriangles.push_back(roofLeft);
	sceneTriangles.push_back(roofRight);
	sceneTriangles.push_back(floorLeft);
	sceneTriangles.push_back(floorRight);
	
	//add the rectangles to the vector of rectangles
	sceneRectangles.push_back(topLeftWall);
	sceneRectangles.push_back(topRightWall);
	sceneRectangles.push_back(topWall);
	sceneRectangles.push_back(bottomWall);
	sceneRectangles.push_back(bottomLeftWall);
	sceneRectangles.push_back(bottomRightWall);
	sceneRectangles.push_back(roofMiddle);
	sceneRectangles.push_back(floorMiddle);
}