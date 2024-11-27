#pragma once
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <iostream>
#include <FastNoiseLite.h>
#include <vector>
#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"
#include <rlgl.h>
#include <external/glad.h>
#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

#define CHUNK_SIZE 32
#define VIEW_DISTANCE 8 // Number of chunks visible in each direction

Shader shader;

struct Vec3 {
	float x, y, z;

	Vec3() : x(0), y(0), z(0) {}
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vec3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}

	// Cross product
	Vec3 cross(const Vec3& other) const {
		return Vec3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	// Subtraction
	Vec3 operator-(const Vec3& other) const {
		return Vec3(x - other.x, y - other.y, z - other.z);
	}

	// Normalize the vector
	Vec3 normalize() const {
		float length = std::sqrt(x * x + y * y + z * z);
		return Vec3(x / length, y / length, z / length);
	}

	Vector3 toVector3() const {
		return Vector3(x, y, z);
	}


};
// Function to extract Vector3 from flat vector of floats
Vector3 getVertex(const std::vector<float>& data, size_t index) {
	return Vector3(data[index * 3], data[index * 3 + 1], data[index * 3 + 2]);
}

Vector3 getNormal(const std::vector<float>& data, size_t index) {
	return getVertex(data, index);
}

Vector2 getTexcoord(const std::vector<float>& data, size_t index) {
	return Vector2(data[index * 2], data[index * 2 + 1]);
}

void generateMeshData(const std::vector<float>& vertexData,
					  std::vector<unsigned short>& indices,
					  std::vector<float>& normals,  // Now normals are a flat list of floats
					  std::vector<float>& texCoords) // Now texCoords are a flat list of floats
{
	for (size_t i = 0; i < vertexData.size() / 9; ++i) {
		// Indices (triangle setup)
		unsigned int idx = i * 3;
		indices.push_back(idx);
		indices.push_back(idx + 1);
		indices.push_back(idx + 2);

		// Get vertices
		Vec3 v0 = getVertex(vertexData, idx);
		Vec3 v1 = getVertex(vertexData, idx + 1);
		Vec3 v2 = getVertex(vertexData, idx + 2);

		// Calculate normals for each triangle
		Vec3 edge1 = v1 - v0;
		Vec3 edge2 = v2 - v0;
		Vec3 normal = edge1.cross(edge2).normalize();

		// Store the normal (as three separate floats for each vertex)
		normals.push_back(normal.x);
		normals.push_back(normal.y);
		normals.push_back(normal.z);

		normals.push_back(normal.x);
		normals.push_back(normal.y);
		normals.push_back(normal.z);

		normals.push_back(normal.x);
		normals.push_back(normal.y);
		normals.push_back(normal.z);


	}
}

float* fromVec3(const Vec3& v) {
	return (float*)&v;
}

class Chunk {
public:
	float heightMap[CHUNK_SIZE + 1][CHUNK_SIZE + 1];
	Color col;
	Vector3 position;
	Mesh mesh = { 0 };
	Model mdl;
	int triangleCount;
	
	Image heightMapImg;
	Texture tex;

	// vertex buffer
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texCoords;
	std::vector<unsigned short> indices;

	unsigned int VBO, cubeVAO;
	Material mat = LoadMaterialDefault();
	void generateMesh() {

		generateMeshData(vertices, indices, normals, texCoords);



	}

	void addToVerticies(Vector3 vertex) {
		vertices.push_back(vertex.x);
		vertices.push_back(vertex.y);
		vertices.push_back(vertex.z);
	}

	void draw() {

	}

};

Chunk chunks[VIEW_DISTANCE * 2 + 1][VIEW_DISTANCE * 2 + 1];

Mesh loadMeshes(Vector3* vertices, Vector3* normals, Vector2* texcoords, int numVertices, int* indices, int numTriangles) {
	Mesh mesh = { 0 };

	mesh.vertices = (float*)malloc(numVertices * 3 * sizeof(float));
	mesh.normals = (float*)malloc(numVertices * 3 * sizeof(float));
	mesh.texcoords = (float*)malloc(numVertices * 2 * sizeof(float));
	mesh.indices = (unsigned short*)malloc(numTriangles * 3 * sizeof(unsigned short));
	mesh.vertexCount = numVertices;
	mesh.triangleCount = numTriangles;

	UploadMesh(&mesh, false);

	return mesh;
}

void GenerateTerrain() {
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
	srand((unsigned)time(NULL));

	// Simple terrain generation using Perlin noise
	for (int i = 0; i < VIEW_DISTANCE * 2 + 1; i++) {
		for (int j = 0; j < VIEW_DISTANCE * 2 + 1; j++) {
			Chunk& chunk = chunks[i][j];
			chunk.position.x = i * CHUNK_SIZE;
			chunk.position.y = 0;
			chunk.position.z = j * CHUNK_SIZE;
			
			for (int x = 0; x <= CHUNK_SIZE; x++) {
				for (int z = 0; z <= CHUNK_SIZE; z++) {
					float nx = (float)(x + i * CHUNK_SIZE) / (VIEW_DISTANCE * CHUNK_SIZE);
					float nz = (float)(z + j * CHUNK_SIZE) / (VIEW_DISTANCE * CHUNK_SIZE);

					float cellSize = 1.0f / CHUNK_SIZE;

					float cellValue = cellNoise.GetNoise(nx * cellSize, nz * cellSize) * 10.0f;
					float simplexValue = simplexNoise.GetNoise(nx * scale, nz * scale) * 10.0f;

					float px = nx, pz = nz;

					noise.DomainWarp(px, pz);

					px *= scale;
					pz *= scale;
					float perlinValue = noise.GetNoise(px, pz);

					//float noiseValue = perlinValue * simplexValue * 10.0f;

					float height = 10.0f * noise.GetNoise(nx * scale, nz * scale) + cellValue + simplexValue;

					/*					float caveNoise = noise.GetNoise(nx * 2, nz * 2); // Adjust noise frequency for caves
										if (caveNoise < 0.5f) {
											height -= 5.0f; // Lower the terrain height to create a cave
										}*/

										//std::cout << height << std::endl;
					chunk.heightMap[x][z] = height;
				}
			}
		}
	}
}

Camera camera;
void DrawTerrain() {
	float vDistMultiplier = 100.0f;
	float vDist = (VIEW_DISTANCE * CHUNK_SIZE) * vDistMultiplier;
	bool forceAllDraw = false;


	
	// Draw terrain for visible chunks
	for (int i = 0; i < VIEW_DISTANCE * 2 + 1; i++) {
		for (int j = 0; j < VIEW_DISTANCE * 2 + 1; j++) {
			Chunk& chunk = chunks[i][j];
			
			//glUseProgram(shader.id);

			rlPushMatrix();
			//BeginShaderMode(shader);
			rlBegin(RL_TRIANGLES);
			
			for (int x = 0; x < CHUNK_SIZE; x++) {
				for (int z = 0; z < CHUNK_SIZE; z++) {
					Vector3 p1 = { (float)(x + i * CHUNK_SIZE), chunk.heightMap[x][z], (float)(z + j * CHUNK_SIZE) };
					Vector3 p2 = { (float)(x + i * CHUNK_SIZE + 1), chunk.heightMap[x + 1][z], (float)(z + j * CHUNK_SIZE) };
					Vector3 p3 = { (float)(x + i * CHUNK_SIZE), chunk.heightMap[x][z + 1], (float)(z + j * CHUNK_SIZE + 1) };
					Vector3 p4 = { (float)(x + i * CHUNK_SIZE + 1), chunk.heightMap[x + 1][z + 1], (float)(z + j * CHUNK_SIZE + 1) };

					if (!forceAllDraw) {
						float dist = (camera.position.x - chunk.position.x) * (camera.position.x - chunk.position.x) + (camera.position.z - chunk.position.z) * (camera.position.z - chunk.position.z);

						float p1Dist = (p1.x - camera.position.x) * (p1.x - camera.position.x) + (p1.z - camera.position.z) * (p1.z - camera.position.z);
						float p2Dist = (p2.x - camera.position.x) * (p2.x - camera.position.x) + (p2.z - camera.position.z) * (p2.z - camera.position.z);
						float p3Dist = (p3.x - camera.position.x) * (p3.x - camera.position.x) + (p3.z - camera.position.z) * (p3.z - camera.position.z);
						float p4Dist = (p4.x - camera.position.x) * (p4.x - camera.position.x) + (p4.z - camera.position.z) * (p4.z - camera.position.z);

						if (dist < vDist) {

							//if ((p1Dist < vDist && p2Dist < vDist && p3Dist < vDist && p4Dist < vDist)) {
							//DrawModel(chunk.mdl, chunk.position, 1.0f, WHITE);
							//DrawTriangle3D(p3, p2, p1, GREEN);
							//DrawTriangle3D(p3, p4, p2, BLUE);
						
							rlVertex3f(p3.x, p3.y, p3.z);
							rlVertex3f(p2.x, p2.y, p2.z);
							rlVertex3f(p1.x, p1.y, p1.z);

							
							rlVertex3f(p3.x, p3.y, p3.z);
							rlVertex3f(p4.x, p4.y, p4.z);
							rlVertex3f(p2.x, p2.y, p2.z);
						}
					}
					else {
						//glUseProgram(shader.id);
						//rlSetShader
						//DrawModel(chunk.mdl, chunk.position, 1.0f, WHITE);
						rlVertex3f(p3.x, p3.y, p3.z);
						rlVertex3f(p2.x, p2.y, p2.z);
						rlVertex3f(p1.x, p1.y, p1.z);

						rlVertex3f(p3.x, p3.y, p3.z);
						rlVertex3f(p4.x, p4.y, p4.z);
						rlVertex3f(p2.x, p2.y, p2.z);
					}
				}
			}
			rlEnd();
			rlPopMatrix();
			//EndShaderMode();
		}
	}
}

int ChunkTesting() {
	/*// Initialization
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Procedural World Generation");
	camera = Camera();

	camera.position = Vector3{ 2.0f, 10.0f, 6.0f };    // Camera position
	camera.target = Vector3{ 0.0f, 0.5f, 0.0f };      // Camera looking at point
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
	
	const char* fragPath = "lighting.frag";
	time_t fragShaderFileModTime = GetFileModTime(fragPath);

	const char* vertPath = "lighting.vert";
	time_t vertShaderFileModTime = GetFileModTime(vertPath);

	shader = LoadShader(vertPath, fragPath);
	RenderTexture texture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
	//shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
	//int ambientLoc = GetShaderLocation(shader, "ambient");
	//float amb[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	//SetShaderValue(shader, ambientLoc, &amb, SHADER_UNIFORM_VEC4);

	// Create lights
	//Light lights[MAX_LIGHTS] = { 0 };

	//lights[0] = CreateLight(LightType::LIGHT_POINT, camera.position, Vector3{ 0.0f, 0.0f, 0.0f }, WHITE, shader);

		// Get some required shader locations
	shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
	// NOTE: "matModel" location name is automatically assigned on shader loading, 
	// no need to get the location again if using that uniform name
	//shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");

	// Ambient light level (some basic lighting)
	int ambientLoc = GetShaderLocation(shader, "ambient");

	static float amb[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	SetShaderValue(shader, ambientLoc, &amb, SHADER_UNIFORM_VEC4);

	// Create lights
	Light lights[MAX_LIGHTS] = { 0 };
	lights[0] = CreateLight(LIGHT_DIRECTIONAL, Vector3 { -2, 1, -2 }, Vector3Zero(), YELLOW, 8, shader);
	lights[1] = CreateLight(LIGHT_POINT, Vector3 { 2, 1, 2 }, Vector3Zero(), RED, 2,shader);
	lights[2] = CreateLight(LIGHT_POINT, Vector3 { -2, 1, 2 }, Vector3Zero(), GREEN, 2, shader);
	lights[3] = CreateLight(LIGHT_POINT, Vector3 { 2, 1, -2 }, Vector3Zero(), BLUE, 2, shader);
	GenerateTerrain();
	
	SetTargetFPS(60);
	DisableCursor();
	float color[] = { BLUE.r, BLUE.g, BLUE.b, BLUE.a };
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Main loop
	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_SPACE)) {
			camera.position.y += 1.0f;
		}

		if (IsKeyDown(KEY_C)) {
			camera.position.y -= 1.0f;
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			lights[0].position = camera.target;
			lights[0].target = camera.target;
			UpdateLightValues(shader, lights[0]);
		}

		// Reload shader
		if (IsKeyPressed(KEY_R)) {
			long currentFragShaderModTime = GetFileModTime(fragPath);
			long currentVertShaderModTime = GetFileModTime(vertPath);
			// Check if shader file has been modified
			if (currentFragShaderModTime != fragShaderFileModTime || currentVertShaderModTime != vertShaderFileModTime)
			{
				// Try reloading updated shader
				Shader updatedShader = LoadShader(vertPath, fragPath);

				if (updatedShader.id != rlGetShaderIdDefault())      // It was correctly loaded
				{
					UnloadShader(shader);
					shader = updatedShader;

					// Get shader locations for required uniforms
					shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
					// NOTE: "matModel" location name is automatically assigned on shader loading, 
					// no need to get the location again if using that uniform name
					//shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");

					// Ambient light level (some basic lighting)
					int ambientLoc = GetShaderLocation(shader, "ambient");

					static float amb[] = { 0.1f, 0.1f, 0.1f, 1.0f };
					SetShaderValue(shader, ambientLoc, &amb, SHADER_UNIFORM_VEC4);

					UpdateLightValues(shader, lights[0]);
					UpdateLightValues(shader, lights[1]);
					UpdateLightValues(shader, lights[2]);
					UpdateLightValues(shader, lights[3]);

					// Reset required uniforms
					//SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
				}



				fragShaderFileModTime = currentFragShaderModTime;
				vertShaderFileModTime = currentVertShaderModTime;
			}
		}
		// Update
		UpdateCamera(&camera, CAMERA_FIRST_PERSON);
		float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
		SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);

		// Check key inputs to enable/disable lights
		if (IsKeyPressed(KEY_Y)) { lights[0].enabled = !lights[0].enabled; }
		if (IsKeyPressed(KEY_R)) { lights[1].enabled = !lights[1].enabled; }
		if (IsKeyPressed(KEY_G)) { lights[2].enabled = !lights[2].enabled; }
		if (IsKeyPressed(KEY_B)) { lights[3].enabled = !lights[3].enabled; }

		// Update light values (actually, only enable/disable them)
		for (int i = 0; i < MAX_LIGHTS; i++) UpdateLightValues(shader, lights[i]);

		//float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
		//SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
		//for (int i = 0; i < MAX_LIGHTS; i++) UpdateLightValues(shader, lights[i]);

		// Draw
		BeginTextureMode(texture);
		ClearBackground(BLACK);
		BeginMode3D(camera);

		BeginShaderMode(shader);
			// Draw spheres to show where the lights are
			for (int i = 0; i < MAX_LIGHTS; i++)
			{
				if (lights[i].enabled) DrawSphereEx(lights[i].position, 0.2f, 8, 8, lights[i].color);
				else DrawSphereWires(lights[i].position, 0.2f, 8, 8, ColorAlpha(lights[i].color, 0.3f));
			}

			DrawSphere(Vector3{ 0.0f, 0.0f, 0.0f }, 1.0f, GREEN);
		DrawTerrain();
		EndShaderMode();
		

		
		EndMode3D();
		EndTextureMode();
		rlPopMatrix();

		BeginDrawing();
		
		// draw rendertexture
		ClearBackground(BLACK);
		// NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
		DrawTextureRec(texture.texture, Rectangle { 0, 0, (float)texture.texture.width, (float)-texture.texture.height }, Vector2 { 0, 0 }, WHITE);
		DrawFPS(10, 10);

		EndDrawing();
	}

	// Clean up
	CloseWindow();

	return 0;*/

	// Initialization
	//--------------------------------------------------------------------------------------
const int screenWidth = 800;
const int screenHeight = 450;

InitWindow(screenWidth, screenHeight, "raylib [shaders] example - vertex displacement");

// set up camera
Camera camera = { 0 };
camera.position = Vector3{ 20.0f, 5.0f, -20.0f };
camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
camera.fovy = 60.0f;
camera.projection = CAMERA_PERSPECTIVE;

// Load vertex and fragment shaders
Shader shader = LoadShader(
	TextFormat("resources/shaders/glsl%i/vertex_displacement.vs", GLSL_VERSION),
	TextFormat("resources/shaders/glsl%i/vertex_displacement.fs", GLSL_VERSION));

// Load perlin noise texture
Image perlinNoiseImage = GenImagePerlinNoise(512, 512, 0, 0, 1.0f);
Texture perlinNoiseMap = LoadTextureFromImage(perlinNoiseImage);
UnloadImage(perlinNoiseImage);

// Set shader uniform location
int perlinNoiseMapLoc = GetShaderLocation(shader, "perlinNoiseMap");
rlEnableShader(shader.id);
rlActiveTextureSlot(1);
rlEnableTexture(perlinNoiseMap.id);
rlSetUniformSampler(perlinNoiseMapLoc, 1);

// Create a plane mesh and model
Mesh planeMesh = GenMeshPlane(50, 50, 50, 50);
Model planeModel = LoadModelFromMesh(planeMesh);
// Set plane model material
planeModel.materials[0].shader = shader;

float time = 0.0f;

SetTargetFPS(60);
//--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose())    // Detect window close button or ESC key
{
	// Update
	//----------------------------------------------------------------------------------
	UpdateCamera(&camera, CAMERA_FREE); // Update camera

	time += GetFrameTime(); // Update time variable
	SetShaderValue(shader, GetShaderLocation(shader, "time"), &time, SHADER_UNIFORM_FLOAT); // Send time value to shader

	// Draw
	//----------------------------------------------------------------------------------
	BeginDrawing();

	ClearBackground(RAYWHITE);

	BeginMode3D(camera);

	BeginShaderMode(shader);
	// Draw plane model
	DrawModel(planeModel, Vector3 { 0.0f, 0.0f, 0.0f }, 1.0f, Color { 255, 255, 255, 255 });
	EndShaderMode();

	EndMode3D();

	DrawText("Vertex displacement", 10, 10, 20, DARKGRAY);
	DrawFPS(10, 40);

	EndDrawing();
	//----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
UnloadShader(shader);
UnloadModel(planeModel);
UnloadTexture(perlinNoiseMap);

CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------

return 0;

}
