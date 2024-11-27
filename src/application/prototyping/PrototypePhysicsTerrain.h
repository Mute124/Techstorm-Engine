#pragma once
#include <utils/Singleton.h>
// STL includes
#include <iostream>
#include <cstdarg>
#include <thread>

#include <raylib.h>
#include "raymath.h"
#include <map>
#include <vector>
#define RLIGHTS_IMPLEMENTATION
#include "../../include/rlights.h"
#include "rlgl.h"
#include "../../include/FastNoiseLite.h"
#include <stdio.h>
#include <string>
#include <utility>
#include <vadefs.h>


#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "PhysicsPrototype.h"
#include "CircularMap.h"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif




#define CHUNK_SIZE 20
#define VIEW_DISTANCE 4 // Number of chunks visible in each direction


class TerrainSector {
public:
	float heightMap[CHUNK_SIZE + 1][CHUNK_SIZE + 1];

	Vector3 objectPosition;
};

class GameObject {
public:
	JPH::BodyID id;
	Quaternion rotation;
	Vector3 position;
	Model model;
	bool hasModel = false;
	Color color = WHITE;
	static inline Texture texture;
	JPH::BodyInterface& bodyInterface;
	bool mIsCulled = false;

	GameObject(JPH::BodyCreationSettings const& settings, Model const& model, JPH::BodyInterface& bodyInterface) : model(model), hasModel(true), bodyInterface(bodyInterface) {
		id = bodyInterface.CreateAndAddBody(settings, JPH::EActivation::Activate);

		SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);
		bool isValid = IsMaterialValid(model.materials[0]);



	}

	GameObject(JPH::BodyInterface& bodyInterface) : bodyInterface(bodyInterface) {




	}

	virtual void draw() {
		JPH::RVec3 boxPosR = bodyInterface.GetPosition(id);
		JPH::Quat boxRotR = bodyInterface.GetRotation(id);

		position = { boxPosR.GetX(), boxPosR.GetY(), boxPosR.GetZ() };


		rotation = { boxRotR.GetX(), boxRotR.GetY(), boxRotR.GetZ(), boxRotR.GetW() };

		model.transform = QuaternionToMatrix(rotation);

		DrawModel(model, position, 1.0f, color);
	}


	void setPosition(Vector3 pos) {
		bool shouldActivate = !mIsCulled;

		// Since a bool is either a 1 or a zero and EActivate follows the same pattern (Activated = 0, Deactivated = 1), it can be casted
		JPH::EActivation activate = static_cast<JPH::EActivation>(shouldActivate);

		bodyInterface.SetPosition(id, JPH::RVec3(pos.x, pos.y, pos.z), activate);
	}

	void setVelocity(Vector3 vel) {
		bodyInterface.SetLinearVelocity(id, JPH::RVec3(vel.x, vel.y, vel.z));
	}

	void deactivate() {
		bodyInterface.DeactivateBody(id);
	}

	void activate() {
		bodyInterface.ActivateBody(id);
	}

	bool isCulled() {
		return !bodyInterface.IsActive(this->id);
	}

	void destroy() {
		bodyInterface.DestroyBody(id);
		UnloadModel(model);
	}

};

/*
std::unordered_map<std::pair<int, int>, TerrainSector> terrainSectors;

	std::cout << "Generating..." << std::endl;

	std::cout << "setuping noise" << std::endl;
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise.SetFrequency(0.1f); // Adjust the frequency of the Perlin noise
	noise.SetSeed(123); // Set a seed for consistent noise generation
	noise.SetDomainWarpType(FastNoiseLite::DomainWarpType_OpenSimplex2);

	FastNoiseLite cellNoise;
	cellNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
	noise.SetFrequency(0.1f); // Adjust the frequency of the Perlin noise
	noise.SetSeed(123); // Set a seed for consistent noise generation
	FastNoiseLite simplexNoise;
	simplexNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	noise.SetFrequency(0.4f); // Adjust the frequency of the Perlin noise
	noise.SetSeed(123); // Set a seed for consistent noise generation
	float scale = 10.0f;

	float cellSize = 1.0f / CHUNK_SIZE;
	using namespace JPH;
	uint32 max_material_index = 0;
	JPH::TriangleList triangles;

	std::cout << "Generating terrain sectors" << std::endl;
	for (int i = 0; i < VIEW_DISTANCE * 2 + 1; i++) {
		for (int j = 0; j < VIEW_DISTANCE * 2 + 1; j++) {
			TerrainSector& sector = terrainSectors[std::make_pair(i, j)];
			sector.objectPosition.x = i * CHUNK_SIZE;
			sector.objectPosition.y = 0;
			sector.objectPosition.z = j * CHUNK_SIZE;

			for (int x = 0; x <= CHUNK_SIZE; x++) {
				for (int z = 0; z <= CHUNK_SIZE; z++) {
					float nx = (float)(x + i * CHUNK_SIZE) / (VIEW_DISTANCE * CHUNK_SIZE);
					float nz = (float)(z + j * CHUNK_SIZE) / (VIEW_DISTANCE * CHUNK_SIZE);

					float cellValue = cellNoise.GetNoise(nx * cellSize, nz * cellSize) * 10.0f;
					float simplexValue = simplexNoise.GetNoise(nx * scale, nz * scale) * 10.0f;

					float px = nx, pz = nz;

					noise.DomainWarp(px, pz);

					px *= scale;
					pz *= scale;
					float perlinValue = noise.GetNoise(px, pz);

					//float noiseValue = perlinValue * simplexValue * 10.0f;

					float height = 10.0f * noise.GetNoise(nx * scale, nz * scale) + cellValue + simplexValue;

					sector.heightMap[x][z] = height;
					using namespace JPH;

					Float3 v1 = { (float)(x + i * CHUNK_SIZE), height, (float)(z + j * CHUNK_SIZE) };
					Float3 v2 = { (float)(x + i * CHUNK_SIZE + 1), height, (float)(z + j * CHUNK_SIZE) };
					Float3 v3 = { (float)(x + i * CHUNK_SIZE), height, (float)(z + j * CHUNK_SIZE + 1) };
					Float3 v4 = { (float)(x + i * CHUNK_SIZE + 1), height, (float)(z + j * CHUNK_SIZE + 1) };

					uint32 material_index = uint32((Vec3(v1) + Vec3(v2) + Vec3(v3) + Vec3(v4)).Length() / 40.0f);
					max_material_index = JPH::max(max_material_index, material_index);

					triangles.push_back(JPH::Triangle(v1, v3, v4, material_index));
					triangles.push_back(JPH::Triangle(v1, v4, v2, material_index));
				}
			}
		}
	}
	std::cout << "Finished generating terrain sectors, Total sectors : " << VIEW_DISTANCE * 2 + 1 * VIEW_DISTANCE * 2 + 1 << std::endl;

	std::cout << "Generating terrain physics" << std::endl;
	// Create materials
	std::cout << "Creating materials" << std::endl;
	JPH::PhysicsMaterialList materials;
	for (uint i = 0; i <= max_material_index; ++i)
		materials.push_back(new JPH::PhysicsMaterialSimple("Material " + ConvertToString(i), JPH::Color::sGetDistinctColor(i)));

	std::cout << "Creating terrain physics body" << std::endl;


	GameObject terrain = GameObject(BodyCreationSettings(new MeshShapeSettings(triangles, std::move(materials)), JPH::Vec3::sZero(), Quat::sIdentity(), EMotionType::Static, Physics::Layers::NON_MOVING))


*/




std::stringstream terrainPieceOutput;

class Terrain {
public:
	Camera& camera;
	JPH::BodyInterface& bodyInterface;
	JPH::BodyID id;
	JPH::TriangleList triangles;
	Mesh terrainMesh = { 0 };
	Model mdl = { 0 };
	Vector3 position = { 0.0f, 0.0f, 0.0f };

	struct TriangleStruct {
		Vector3 v1;
		Vector3 v2;
		Vector3 v3;
		Color color;
		TriangleStruct(Vector3 v1, Vector3 v2, Vector3 v3, Color color) : v1(v1), v2(v2), v3(v3), color(color) {}

		void draw() {
			DrawTriangle3D(v1, v2, v3, color);
		}
	};
	std::vector<TriangleStruct> trianglesVector;


	// Size of the terrain
	static constexpr int	cSampleCount = 10;

	float heightMap[cSampleCount][cSampleCount];

	static inline bool isInit = false;
	float startX = 0.0f;
	float startZ = 0.0f;
	static inline FastNoiseLite noise;

	// noise scale
	static inline float scaleY = 8.0f;

	// Colors that are used to color the terrain. This is a circular map
	static inline CircularMap<Color> colors = CircularMap<Color>(3, { { 0, RED }, { 1, GREEN }, { 2, BLUE } });
	
	Color meshColor = colors.next();
	
	static inline void init() {
		noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	}

	Terrain(JPH::BodyInterface& bodyInterface, Camera camera, Vector2 start, Vector3 position) : camera(camera), bodyInterface(bodyInterface), startX(start.x), startZ(start.y) {
		this->generate();
	}

	void generate() {
		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

		if (!isInit) {
			init();
			isInit = true;
		}

		for (int x = startX; x < cSampleCount; ++x) {
			for (int z = startZ; z < cSampleCount; ++z) {
				heightMap[x][z] = noise.GetNoise((float)x, (float)z) * scaleY;
				terrainPieceOutput << "Height at " << x << ", " << z << " : " << heightMap[x][z] << std::endl;
			}
		}
		
		// Used to convert the heightmap to a mesh
		std::vector<float> vertices;

		// construct triangles
		for (int x = startX; x < cSampleCount - 1; ++x) {
			for (int z = startZ; z < cSampleCount - 1; ++z) {
				Vector3 v1 = Vector3(x, heightMap[x][z], z);
				Vector3 v2 = Vector3(x + 1, heightMap[x + 1][z], z);
				Vector3 v3 = Vector3(x, heightMap[x][z + 1], z + 1);
				Vector3 v4 = Vector3(x + 1, heightMap[x + 1][z + 1], z + 1);

				vertices.push_back(v1.x);
				vertices.push_back(v1.y);
				vertices.push_back(v1.z);

				vertices.push_back(v3.x);
				vertices.push_back(v3.y);
				vertices.push_back(v3.z);

				vertices.push_back(v4.x);
				vertices.push_back(v4.y);
				vertices.push_back(v4.z);

				vertices.push_back(v1.x);
				vertices.push_back(v1.y);
				vertices.push_back(v1.z);

				vertices.push_back(v4.x);
				vertices.push_back(v4.y);
				vertices.push_back(v4.z);

				vertices.push_back(v2.x);
				vertices.push_back(v2.y);
				vertices.push_back(v2.z);

				// calculate indicies
				unsigned short index1 = (unsigned short)vertices.size() / 3;
				unsigned short index2 = index1 + 1;
				unsigned short index3 = index1 + 2;

				// create triangles
				trianglesVector.push_back(
					TriangleStruct(
						v1,
						v3,
						v4,
						RED
					));

				terrainPieceOutput
					<< "Creating Triangle 1 at "
					<< x
					<< ", "
					<< z
					<< " With vertices "
					<< "(" + std::to_string(v1.x) + ", " + std::to_string(v1.y) + ", " + std::to_string(v1.z) + ")" // v1
					<< ", "
					<< "(" + std::to_string(v3.x) + ", " + std::to_string(v3.y) + ", " + std::to_string(v3.z) + ")" // v3
					<< ", "
					<< "(" + std::to_string(v4.x) + ", " + std::to_string(v4.y) + ", " + std::to_string(v4.z) + ")" // v4
					<< ""
					<< std::endl;

				trianglesVector.push_back(
					TriangleStruct(
						v1,
						v4,
						v2,
						BLUE
					));

				terrainPieceOutput
					<< "Creating Triangle 2 at "
					<< x
					<< ", "
					<< z
					<< " With vertices "
					<< "(" + std::to_string(v1.x) + ", " + std::to_string(v1.y) + ", " + std::to_string(v1.z) + ")" // v1
					<< ", "
					<< "(" + std::to_string(v4.x) + ", " + std::to_string(v4.y) + ", " + std::to_string(v4.z) + ")" // v4
					<< ", "
					<< "(" + std::to_string(v2.x) + ", " + std::to_string(v2.y) + ", " + std::to_string(v2.z) + ")" // v2
					<< ""
					<< std::endl;
			}
		}

		// Create raylib mesh
		terrainMesh.vertexCount = vertices.size() / 3; // 3 floats per vertex
		terrainMesh.vertices = (float*)malloc(vertices.size() * sizeof(float));
		memcpy(terrainMesh.vertices, vertices.data(), vertices.size() * sizeof(float));

		UploadMesh(&terrainMesh, false);

		mdl = LoadModelFromMesh(terrainMesh);

		// Create regular grid of triangles
		JPH::uint32 max_material_index = 0;
		JPH::TriangleList triangles;

		{
			using namespace JPH;

			for (int x = startX; x < cSampleCount - 1; ++x)
				for (int z = startZ; z < cSampleCount - 1; ++z)
				{
					float x1 = 10.0f * x;
					float z1 = 10.0f * z;
					float x2 = x1 + 10.0f;
					float z2 = z1 + 10.0f;

					Float3 v1 = Float3(x1, 0, z1);
					Float3 v2 = Float3(x2, 0, z1);
					Float3 v3 = Float3(x1, 0, z2);
					Float3 v4 = Float3(x2, 0, z2);

					uint32 material_index = uint32((Vec3(v1) + Vec3(v2) + Vec3(v3) + Vec3(v4)).Length() / 40.0f);

					max_material_index = max(max_material_index, material_index);

					triangles.push_back(Triangle(v1, v3, v4, material_index));
					triangles.push_back(Triangle(v1, v4, v2, material_index));

				}
		}

		// Ensure collision triangles are matching with the mesh and vice versa
		for (int i = 0; i < triangles.size(); ++i) {

			Vector3 vec1;
			Vector3 vec2;
			Vector3 vec3;

			// convert JPH::Float3 to Vector3. mV[0] is the first vertex, mV[1] is the second, and mV[2] is the third
			memcpy(&vec1, &triangles[i].mV[0], sizeof(Vector3));
			memcpy(&vec2, &triangles[i].mV[1], sizeof(Vector3));
			memcpy(&vec3, &triangles[i].mV[2], sizeof(Vector3));

			vec1 = trianglesVector[i].v1;
			vec2 = trianglesVector[i].v2;
			vec3 = trianglesVector[i].v3;

			JPH::Float3 v1 = JPH::Float3(vec1.x, vec1.y, vec1.z);
			JPH::Float3 v2 = JPH::Float3(vec2.x, vec2.y, vec2.z);
			JPH::Float3 v3 = JPH::Float3(vec3.x, vec3.y, vec3.z);

			triangles[i].mV[0] = v1;
			triangles[i].mV[1] = v2;
			triangles[i].mV[2] = v3;

		}

		{
			using namespace JPH;

			// Convert triangles into a collision mesh.

			// Create materials
			PhysicsMaterialList materials;
			for (uint i = 0; i <= max_material_index; ++i)
				materials.push_back(new PhysicsMaterialSimple("Material " + ConvertToString(i), JPH::Color::sGetDistinctColor(i)));

			// Check if a duplicate body already exists, and remove it if it does
			if (!this->id.IsInvalid()) {
				bodyInterface.RemoveBody(this->id);
				bodyInterface.DestroyBody(this->id);
			}

			// Create body
			RVec3 bodyPos = RVec3(startX, 0, startZ);
			Body const& floor = *bodyInterface.CreateBody(BodyCreationSettings(new MeshShapeSettings(triangles, std::move(materials)), bodyPos, Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING));
			bodyInterface.AddBody(floor.GetID(), EActivation::DontActivate);
			this->id = floor.GetID();

			// make sure the mesh draws at the correct position
			position = Vector3{ floor.GetPosition().GetX(), floor.GetPosition().GetY(), floor.GetPosition().GetZ() };

			terrainPieceOutput << "Body at " << floor.GetPosition().GetX() << ", " << floor.GetPosition().GetY() << ", " << floor.GetPosition().GetZ() << std::endl;
		}

		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		terrainPieceOutput << "Terrain generation time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl << std::endl;
	}

	void draw() {

		DrawModel(mdl, position, 1.0f, meshColor);
	}
};

template<typename T>
void PushObject(T object, std::vector<T>& objects) {
	objects.push_back(object);
	std::cout << "Added :" << typeid(T).name() << ", number of objects : " << objects.size() << std::endl;
}

// Program entry point
int PrototypePhysicsTerrain()
{

	PhysicsEngine& physicsEngine = PhysicsEngine::Instance();
	physicsEngine.init(AllocatedPhysicsResources());

	JPH::BodyInterface& bodyInterface = physicsEngine.getBodyInterface();


	//JPH::BodyID sphere_id = body_interface.CreateAndAddBody(sphere_settings, JPH::EActivation::Activate);

	// Now you can interact with the dynamic body, in this case we're going to give it a velocity.
	// (note that if we had used CreateBody then we could have set the velocity straight on the body before adding it to the physics system)
	//body_interface.SetLinearVelocity(sphere_id, JPH::Vec3(0.0f, -5.0f, 0.0f));

	// We simulate the physics world in discrete time steps. 60 Hz is a good rate to update the physics system.
	const float cDeltaTime = 1.0f / 60.0f;



	// Now we're ready to simulate the body, keep simulating until it goes to sleep
	//JPH::uint step = 0;

	SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
	InitWindow(800, 600, "Techstorm");
	// Define the camera to look into our 3d world (position, target, up vector)
	Camera camera = { 0 };
	camera.position = Vector3{ 0.0f, 2.0f, 4.0f };    // Camera position
	camera.target = Vector3{ 0.0f, 2.0f, 0.0f };      // Camera looking at point
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 60.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

	int cameraMode = CAMERA_FIRST_PERSON;

	// Load basic lighting shader
	Shader shader = LoadShader("lighting.vs", "lighting.fs");

	// Get some required shader locations
	shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
	// NOTE: "matModel" location name is automatically assigned on shader loading, 
	// no need to get the location again if using that uniform name
	//shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");

	// Ambient light level (some basic lighting)
	int ambientLoc = GetShaderLocation(shader, "ambient");
	static float ambientColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	SetShaderValue(shader, ambientLoc, &ambientColor, SHADER_UNIFORM_VEC4);

	// Create lights
	Light lights[MAX_LIGHTS] = { 0 };
	lights[0] = CreateLight(LIGHT_POINT, Vector3{ -2, 1, -2 }, Vector3Zero(), YELLOW, shader);
	lights[1] = CreateLight(LIGHT_POINT, Vector3{ 2, 1, 2 }, Vector3Zero(), RED, shader);
	lights[2] = CreateLight(LIGHT_POINT, Vector3{ -2, 1, 2 }, Vector3Zero(), GREEN, shader);
	lights[3] = CreateLight(LIGHT_POINT, Vector3{ 2, 1, -2 }, Vector3Zero(), BLUE, shader);

	GameObject::texture = LoadTexture("container.jpg");
	GenTextureMipmaps(&GameObject::texture);
	DisableCursor();                    // Limit cursor to relative movement inside the window



	// used to test the speeds of the physics system
	std::vector<GameObject*> objectsPtr;
	std::vector<GameObject> objects;

	bool drawUsingObjectsPtr = false;
	int count = 0;
	float deltaTime = 0.0f;
	/*
				for (int z = 0; z < 100; z += 2) {
				//
			}*/
	bool shouldClose = false;

	// make terrain
	std::vector<Terrain*> terrains;
	Vector3 lastPos = { 0, 0, 0 };
	for (int x = 0; x < Terrain::cSampleCount; x += 4) {
		for (int z = 0; z < Terrain::cSampleCount; z += 4) {
			Vector2 start = { (float)x, (float)z };
			terrainPieceOutput << "Starting terrain at " << start.x << ", " << start.y << ", In position " << lastPos.x << ", " << lastPos.y << ", " << lastPos.z << std::endl;
			Terrain* terrain = new Terrain(bodyInterface, camera, start, lastPos);
			terrain->mdl.materials[0].shader = shader;
			terrains.push_back(terrain);
		}
	}


	// Put the name as terrainPieceOutput[time]
	int num = 0;



	// Keep increasing num by 1 as long as there is another terrainPieceOutput[num].txt file.
	while (FileExists(TextFormat("terrainPieceOutput[%i].txt", num))) {
		num++;
	}

	std::string name = TextFormat("terrainPieceOutput[%i].txt", num);
	std::cout << "Saving terrainPieceOutput to " << name << std::endl;
	// write terrainPieceoutput to a file
	std::ofstream terrainPieceOutputFile("terrainPieceOutput.txt");

	// Check if the file was successfully opened
	if (!terrainPieceOutputFile) {
		std::cerr << "Error opening file for writing." << std::endl;
		return 1;
	}

	if (terrainPieceOutputFile.is_open()) {
		terrainPieceOutputFile << terrainPieceOutput.str();
		terrainPieceOutputFile.close();
	}


	//Terrain terrain = Terrain(bodyInterface, camera);
	//terrain.mdl.materials[0].shader = shader;
	// Next we can create a rigid body to serve as the floor, we make a large box
// Create the settings for the collision volume (the shape).
// Note that for simple shapes (like boxes) you can also directly construct a BoxShape.
	//JPH::BoxShapeSettings floor_shape_settings(JPH::Vec3(100.0f, 10.0f, 100.0f));
	//floor_shape_settings.SetEmbedded(); // A ref counted object on the stack (base class RefTarget) should be marked as such to prevent it from being freed when its reference count goes to 0.

	// Create the shape
	//JPH::ShapeSettings::ShapeResult floor_shape_result = floor_shape_settings.Create();
	//JPH::ShapeRefC floor_shape = floor_shape_result.Get(); // We don't expect an error here, but you can check floor_shape_result for HasError() / GetError()

	// Create the settings for the body itself. Note that here you can also set other properties like the restitution / friction.
	//JPH::BodyCreationSettings floor_settings(floor_shape, JPH::RVec3(0.0_r, -100.0_r, 0.0_r), JPH::Quat::sIdentity(), JPH::EMotionType::Static, Layers::NON_MOVING);

	// Create the actual rigid body
	//JPH::Body* floor = bodyInterface.CreateBody(floor_settings); // Note that if we run out of bodies this can return nullptr

	// Add it to the world
	//bodyInterface.AddBody(floor->GetID(), JPH::EActivation::DontActivate);



	// Now create a dynamic body to bounce on the floor
// Note that this uses the shorthand version of creating and adding a body to the world
	JPH::BodyCreationSettings boxSettings(new JPH::BoxShape({ 0.5f, 0.5f, 0.5f }), JPH::RVec3(0.0_r, 5.0_r, 0.0_r), JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic, Layers::MOVING);



	// Now create a dynamic body to bounce on the floor
	// Note that this uses the shorthand version of creating and adding a body to the world
	JPH::BodyCreationSettings sphere_settings(new JPH::SphereShape(0.5f), JPH::RVec3(0.0_r, 2.0_r, 0.0_r), JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic, Layers::MOVING);

	bool enableCull = false;
	bool hasDeactivatedBodies = false;
	// Optional step: Before starting the physics simulation you can optimize the broad phase. This improves collision detection performance (it's pointless here because we only have 2 bodies).
// You should definitely not call this every frame or when e.g. streaming in a new level section as it is an expensive operation.
// Instead insert all new objects in batches instead of 1 at a time to keep the broad phase efficient.
	physicsEngine.optimizeBroadPhase();

	SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
	//inputThread.detach();

	while (!shouldClose)
	{
		shouldClose = WindowShouldClose();
		deltaTime = GetFrameTime();



		//JPH::RVec3 spherePosR = body_interface.GetPosition(sphere_id);
		// Output current position and velocity of the sphere
		//JPH::RVec3 position = body_interface.GetCenterOfMassPosition(sphere_id);
		//JPH::Vec3 velocity = body_interface.GetLinearVelocity(sphere_id);
		//cout << "Step " << step << ": Position = (" << position.GetX() << ", " << position.GetY() << ", " << position.GetZ() << "), Velocity = (" << velocity.GetX() << ", " << velocity.GetY() << ", " << velocity.GetZ() << ")" << endl;

		// If you take larger steps than 1 / 60th of a second you need to do multiple collision steps in order to keep the simulation stable. Do 1 collision step per 1 / 60th of a second (round up).
		const int cCollisionSteps = 1;



		// Put a box into objectsPtr
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			// Set to camera target
			//body_interface.SetPosition(box.id, {camera.target.x, camera.target.y, camera.target.z}, JPH::EActivation::Activate);

			Model mdl = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));
			mdl.materials[0].shader = shader;
			GameObject* box = new GameObject(boxSettings, mdl, bodyInterface);
			box->setPosition({ camera.target.x, camera.target.y, camera.target.z });
			//boxes.push_back(new GameObject(boxSettings, mdl, body_interface));

			PushObject<GameObject*>(box, objectsPtr);
		}

		// put a box into objects
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
			Model mdl = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));
			mdl.materials[0].shader = shader;
			GameObject box = GameObject(boxSettings, mdl, bodyInterface);
			box.setPosition({ camera.target.x, camera.target.y, camera.target.z });
			PushObject<GameObject>(box, objects);
		}

		// Throw a sphere and put it into objectsPtr
		if (IsKeyPressed(KEY_B)) {
			Model mdl = LoadModelFromMesh(GenMeshSphere(0.5f, 32, 32));
			mdl.materials[0].shader = shader;
			GameObject* sphere = new GameObject(sphere_settings, mdl, bodyInterface);

			sphere->setPosition({ camera.position.x, camera.position.y, camera.position.z });

			// Shoot box at center of screen
			sphere->setVelocity({ (camera.target.x - camera.position.x) * 2 , (camera.target.y - camera.position.y) * 2 , (camera.target.z - camera.position.z) * 2 });

			PushObject<GameObject*>(sphere, objectsPtr);
		}

		// Throw a Sphere and put it into objects
		if (IsKeyPressed(KEY_V)) {
			Model mdl = LoadModelFromMesh(GenMeshSphere(0.5f, 32, 32));
			mdl.materials[0].shader = shader;
			GameObject sphere = GameObject(sphere_settings, mdl, bodyInterface);
			sphere.setPosition({ camera.position.x, camera.position.y, camera.position.z });
			sphere.setVelocity({ (camera.target.x - camera.position.x) * 2 , (camera.target.y - camera.position.y) * 2 , (camera.target.z - camera.position.z) * 2 });

			PushObject<GameObject>(sphere, objects);
		}

		// Test how many boxes being put into objectsPtr until we hit 0 FPS
		if (IsKeyDown(KEY_T) && !IsKeyPressed(KEY_R) && GetFPS() > 0) {

			Model mdl = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));
			mdl.materials[0].shader = shader;
			GameObject* box = new GameObject(boxSettings, mdl, bodyInterface);
			box->setPosition({ camera.target.x, camera.target.y, camera.target.z });
			//boxes.push_back(new GameObject(boxSettings, mdl, body_interface));

			PushObject<GameObject*>(box, objectsPtr);


		}
		else if (GetFPS() == 0) {
			std::cout << "Was able to create " << count << " boxes (pointer) before hitting 0 FPS." << std::endl;
		}

		if (IsKeyPressed(KEY_R)) {


			for (int i = 0; i < objectsPtr.size(); i++) {
				objectsPtr[i]->destroy();
			}
			objectsPtr.clear();

			std::cout << "Was able to create " << count << " boxes (pointer) before resetting. The FPS reached was " << GetFPS() << std::endl;
			count = 0;
		}

		if (IsKeyPressedRepeat(KEY_R)) {
			for (int i = 0; i < objects.size(); i++) {
				objects[i].destroy();
			}
			std::cout << "Was able to create " << objects.size() << " boxes (non-pointer) before resetting. The FPS reached was " << GetFPS() << std::endl;
			objects.clear();


		}

		if (IsKeyPressed(KEY_P)) {
			camera.position = { 0.0f, 2.0f, 410.0f };
		}

		if (IsKeyPressed(KEY_M)) {
			camera.position = { 0.0f, 2.0f, camera.position.z + 100.0f };
			camera.target = objects[0].position;
		}

		if (IsKeyPressed(KEY_O)) {
			camera.position = { 0.0f, 2.0f, 4.0f };
		}

		if (IsKeyPressed(KEY_C)) {
			// switch cull mode
			enableCull = !enableCull;
		}

		if (IsKeyPressed(KEY_U)) {
			if (!hasDeactivatedBodies) {
				for (int i = 0; i < objects.size(); i++) {
					objects[i].bodyInterface.DeactivateBody(objects[i].id);
				}
				hasDeactivatedBodies = true;
			}
			else {
				for (int i = 0; i < objects.size(); i++) {
					objects[i].bodyInterface.ActivateBody(objects[i].id);
				}

				hasDeactivatedBodies = false;
			}
		}

		// Test how many spheres until we hit 0 FPS
		if (IsKeyPressed(KEY_Y)) {
			drawUsingObjectsPtr = !drawUsingObjectsPtr;
		}

		if (IsKeyDown(KEY_SPACE))
		{
			camera.position.y += 2.0f * GetFrameTime();
		}

		if (IsKeyDown(KEY_LEFT_CONTROL)) {
			camera.position.y -= 2.0f * GetFrameTime();
		}

		// 
		if (IsKeyPressed(KEY_LEFT_ALT)) {
			camera.position = { lerp(camera.position.x, camera.target.x, 0.1f), camera.position.y, lerp(camera.position.z, camera.target.z, 0.1f) };
		}



		UpdateCamera(&camera, cameraMode);                  // Update camera

		// Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
		float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
		SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
		BeginDrawing();

		ClearBackground(BLACK);

		BeginMode3D(camera);

		BeginShaderMode(shader);

		//for (int i = 0; i < objectsPtr.size(); i++) {
			//objectsPtr[i]->draw();
		//}
		for (int i = 0; i < terrains.size(); i++) {
			terrains[i]->draw();
		}
		for (int i = 0; i < objects.size(); i++) {
			GameObject obj = objects[i];
			float dst = Vector3Distance(obj.position, camera.position);

			bool culled = false;
			if (enableCull && dst > 200.0f) {
				//obj.deactivate();
				//culled = true;
			}
			else {


				//obj.activate();

				//culled = false;
			}
			objects[i].draw();
			if (!culled) {

			}
		}

		EndShaderMode();

		//Vector3 spherePos = { spherePosR.GetX(), spherePosR.GetY(), spherePosR.GetZ() };
		//DrawSphere(spherePos, 0.5f, GREEN);

		//Vector3 planePos = { floor->GetPosition().GetX(), floor->GetPosition().GetY() + 1.0f, floor->GetPosition().GetZ() };

		//DrawPlane(planePos, Vector2{ 100.0f, 100.0f }, BLUE);

		// Draw spheres to show where the lights are
		for (int i = 0; i < MAX_LIGHTS; i++)
		{
			if (lights[i].enabled) DrawSphereEx(lights[i].position, 0.2f, 8, 8, lights[i].color);
			else DrawSphereWires(lights[i].position, 0.2f, 8, 8, ColorAlpha(lights[i].color, 0.3f));
		}
		EndMode3D();

		DrawFPS(10, 10);

		DrawText(TextFormat("Number of Pointer Objects: %i", objectsPtr.size()), 10, 40, 20, WHITE);
		DrawText(TextFormat("Number of Objects: %i", objects.size()), 10, 60, 20, WHITE);
		DrawText(TextFormat("Drawing with objectsPtr : %i", drawUsingObjectsPtr), 10, 80, 20, WHITE);
		DrawText(TextFormat("Culling objects : %i", enableCull), 10, 100, 20, WHITE);


		for (int i = 0; i < terrains.size(); i++) {
			//Vector3 pos = terrains[i]->position;
			//Vector2 screenPos = GetWorldToScreen(pos, camera);
			//DrawText(TextFormat("Terrain #%i: %f, %f, %f", i, pos.x, pos.y, pos.z), screenPos.x, screenPos.y, 20, WHITE);
		}
		EndDrawing();
		// Step the world
		//physics_system.Update(cDeltaTime, cCollisionSteps, 4, &temp_allocator, &job_system);

		physicsEngine.update(cDeltaTime);
	}

	//inputThread.join();
	// Remove the sphere from the physics system. Note that the sphere itself keeps all of its state and can be re-added at any time.
	//body_interface.RemoveBody(sphere_id);

	// Destroy the sphere. After this the sphere ID is no longer valid.
	//body_interface.DestroyBody(sphere_id);

	// Remove and destroy the floor
	//bodyInterface.RemoveBody(floor->GetID());
	//bodyInterface.DestroyBody(floor->GetID());

	// Unregisters all types with the factory and cleans up the default material
	JPH::UnregisterTypes();

	// Destroy the factory
	delete JPH::Factory::sInstance;
	JPH::Factory::sInstance = nullptr;

	return 0;
}