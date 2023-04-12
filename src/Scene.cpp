#include "Scene.hpp"
#include <iostream>
#include <vector>

Scene::Scene() {
	createScene();
}

Polygon* Scene::getHitGeometry(Ray& _ray, vec3& _intersection, bool _isShadowRay) {
	vec3 point = vec3(0.0f);

	float distanceToIntersection = 100.0f;

	int index = 0;
	float dis1 = 0.0f;
	float dis2 = 100.0f;

	int hit = 0;
	
	for (int i = 0; i < sceneObjects.size(); i++) {
		
		if (sceneObjects[i]->intersects(_ray)) {
			
			point = sceneObjects[i]->calculateIntersectionPoint(_ray.getStartPoint(), _ray.getDirection());
			
			if (length((point - _ray.getStartPoint())) < distanceToIntersection) {
				_intersection = point;	
				dis1 = length((point - _ray.getStartPoint()));
								 
				if(dis1 < dis2) {				
					index = i;
					dis2 = dis1;	
				}
				hit++;
			}	
		}
		
		if (i == sceneObjects.size() - 1 && hit > 0) {
			return sceneObjects[index];
		}
	}
	return nullptr;
}

void Scene::createScene() {
	//Create the vertices for the walls, roof and floor  
	const vec3 V1 = vec3(0.0f, 6.0f, 5.0f);
	const vec3 V2 = vec3(0.0f, 6.0f, -5.0f);
	const vec3 V3 = vec3(-3.0f, 0.0f, -5.0f);
	const vec3 V4 = vec3(-3.0f, 0.0f, 5.0f);
	const vec3 V5 = vec3(10.0f, 6.0f, 5.0f);
	const vec3 V6 = vec3(10.0f, 6.0f, -5.0f);
	const vec3 V7 = vec3(13.0f, 0.0f, -5.0f);
	const vec3 V8 = vec3(13.0f, 0.0f, 5.0f);
	const vec3 V9 = vec3(0.0f, -6.0f, -5.0f);
	const vec3 V10 = vec3(0.0f, -6.0f, 5.0f);
	const vec3 V11 = vec3(10.0f, -6.0f, 5.0f);
	const vec3 V12 = vec3(10.0f, -6.0f, -5.0f);

	const vec3 sphereCenter = vec3(3.f, -2.5f, -1.f); //vec3(5.f, 0.f, 1.f)

	//Create the colors for the walls, roof and floor
	const colorDBL RED = colorDBL(1.0, 0.0, 0.0);
	const colorDBL GREEN = colorDBL(0.0, 1.0, 0.0);
	const colorDBL YELLOW = colorDBL(1.0, 1.0, 0.0);
	const colorDBL PURPLE = colorDBL(1.0, 0.0, 1.0);
	const colorDBL BLUE = colorDBL(0.0, 0.0, 1.0);
	const colorDBL GRAY = colorDBL(0.5, 0.5, 0.5);
	const colorDBL WHITE = colorDBL(1.0, 1.0, 1.0);
	const colorDBL CYAN = colorDBL(0.0, 1.0, 1.0);
	const colorDBL ORANGE = colorDBL(1.0, 0.5, 0.0);

	//create the vectors of vertices for the walls, roof and floor
	std::vector <vec3> topLeftWallVertices = { V2, V1, V4 ,V3 };
	std::vector <vec3> topRightWallVertices = { V5, V6, V7, V8 };
	std::vector <vec3> topWallVertices = { V1, V2, V6 ,V5 };
	std::vector <vec3> bottomLeftWallVertices = { V4, V10, V9 ,V3 };
	std::vector <vec3> bottomRightLeftWallVertices = { V8, V7, V12, V11 };
	std::vector <vec3> bottomWallVertices = { V10, V11, V12, V9 };
	std::vector <vec3> roofMiddleVertices = { V11, V10, V1, V5 }; // Byt plats på V5 och V10!!
	std::vector <vec3> roofLeftVertices = { V1, V10, V4 };
	std::vector <vec3> roofRightVertices = { V5, V8, V11 };
	std::vector <vec3> floorMiddleVertices = { V2, V9, V12 ,V6 };
	std::vector <vec3> floorLeftVertices = { V2, V3, V9 };
	std::vector <vec3> floorRightVertices = { V6, V12, V7 };

	//Det blir skuggor på väggarna från sfären, bör inte bli så. Shadowray = fel?? Skickas shadow rayen från ögat och inte intersectionpoint??
	//Golv kolsvart, fel normaler?
	//Röd vägg samt tak också kolsvart i spegel.
	//Specular är svart???


	//create the Rectangles //Have changed index 3 and 1 here!
	Rectangle* topLeftWall = new Rectangle(topLeftWallVertices[0], topLeftWallVertices[3], topLeftWallVertices[2], topLeftWallVertices[1], RED, DIFFUSE);
	Rectangle* topRightWall = new Rectangle(topRightWallVertices[0], topRightWallVertices[3], topRightWallVertices[2], topRightWallVertices[1], BLUE, DIFFUSE);
	Rectangle* topWall = new Rectangle(topWallVertices[0], topWallVertices[3], topWallVertices[2], topWallVertices[1], YELLOW, DIFFUSE); 
	Rectangle* bottomWall = new Rectangle(bottomWallVertices[0], bottomWallVertices[3], bottomWallVertices[2], bottomWallVertices[1], GREEN, DIFFUSE);
	Rectangle* bottomLeftWall = new Rectangle(bottomLeftWallVertices[0], bottomLeftWallVertices[3], bottomLeftWallVertices[2], bottomLeftWallVertices[1], PURPLE, DIFFUSE);
	Rectangle* bottomRightWall = new Rectangle(bottomRightLeftWallVertices[0], bottomRightLeftWallVertices[3], bottomRightLeftWallVertices[2], bottomRightLeftWallVertices[1], CYAN, MIRROR);
	Rectangle* roofMiddle = new Rectangle(roofMiddleVertices[0], roofMiddleVertices[3], roofMiddleVertices[2], roofMiddleVertices[1], ORANGE, DIFFUSE); //<-- Switch 1 and 3?
	Rectangle* floorMiddle = new Rectangle(floorMiddleVertices[0], floorMiddleVertices[3], floorMiddleVertices[2], floorMiddleVertices[1], GRAY, DIFFUSE);

	const vec3 tV1 = vec3(6.0f, 2.9f, -2.f); //x = 3.f y= -0.9 z = -0.8f
	const vec3 tV2 = vec3(6.0f, 0.2f, -2.f); //x = 3.f y= -0.2 z = -0.8f
	const vec3 tV3 = vec3(6.0f, 1.35f, -0.2f); //x = 3.f y= -0.5 z = -0.2f
	const vec3 tV4 = vec3(6.5f, 0.0f, -2.f); //x = 3.3f y= 0,0 z = -0.8f

	std::vector <vec3> triVerts = { tV1, tV2, tV3, tV4 };

	//Nope!
	Triangle* frontTri = new Triangle(triVerts[0], triVerts[2], triVerts[1], BLUE, DIFFUSE); //Switched 2 and 1
	Triangle* leftSideTri = new Triangle(triVerts[1], triVerts[2], triVerts[3], RED, DIFFUSE);
	Triangle* rightSideTri = new Triangle(triVerts[0], triVerts[3], triVerts[2], GREEN, DIFFUSE);
	Triangle* bottomTri = new Triangle(triVerts[0], triVerts[1], triVerts[3], PURPLE, DIFFUSE);

	Sphere* sphere = new Sphere(sphereCenter, 1.0, PURPLE, MIRROR);

	sceneObjects.push_back(topLeftWall);
	sceneObjects.push_back(topRightWall);
	sceneObjects.push_back(topWall);
	sceneObjects.push_back(bottomWall);
	sceneObjects.push_back(bottomLeftWall);
	sceneObjects.push_back(bottomRightWall);
	sceneObjects.push_back(roofMiddle);
	sceneObjects.push_back(floorMiddle);

	//create the triangles which make up part of the roof and floor
	Triangle* roofLeft = new Triangle(roofLeftVertices[0], roofLeftVertices[2], roofLeftVertices[1], ORANGE, DIFFUSE); //Switch 2 and 1
	Triangle* roofRight = new Triangle(roofRightVertices[0], roofRightVertices[2], roofRightVertices[1], ORANGE, DIFFUSE);
	Triangle* floorLeft = new Triangle(floorLeftVertices[2], floorLeftVertices[1], floorLeftVertices[0], GRAY, DIFFUSE);
	Triangle* floorRight = new Triangle(floorRightVertices[2], floorRightVertices[1], floorRightVertices[0], GRAY, DIFFUSE);

	//Push them to the sceneObjects vector
	sceneObjects.push_back(roofLeft);
	sceneObjects.push_back(roofRight);
	sceneObjects.push_back(floorLeft);
	sceneObjects.push_back(floorRight);

	//Push the sphere to the sceneObjects vector
	sceneObjects.push_back(sphere);

	//Push the pyramid to sceneObjects vector
	sceneObjects.push_back(frontTri);
	sceneObjects.push_back(leftSideTri);
	sceneObjects.push_back(rightSideTri);
	sceneObjects.push_back(bottomTri);

	//Creating the lightsource 
	
	vec3 L1Low(10.0, 2.0, 4.9), L1High(4.0, 2.0, 4.9);
	vec3 L2Low(10.0, -2.0, 4.9), L2High(4.0, -2.0, 4.9);
	//Switch lightsource pos
	/*vec3 L1Low(10.0, 4.9, 2.0), L1High(4.0, 4.9, 2.0);
	vec3 L2Low(10.0, 4.9, -2.0), L2High(4.0, 4.9, -2.0);*/
	

	sceneObjects.push_back(new Triangle(L1High, L1Low, L2High, WHITE, LIGHTSOURCE)); //Switch L2High and L1Low
	sceneObjects.push_back(new Triangle(L1Low, L2Low, L2High, WHITE, LIGHTSOURCE)); // Switch L2High and L2Low

	//Creating a new vector with just the lightsources, so that the information can be kept
	for (Polygon* i : sceneObjects) {
		if (i->getSurfaceType() == LIGHTSOURCE) {
			sceneLights.push_back(i);
		}
	}






}