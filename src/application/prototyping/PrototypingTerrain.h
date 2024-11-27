#pragma once
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <iostream>
#include <FastNoiseLite.h>
#include <vector>
#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

#define CHUNK_SIZE 32
#define VIEW_DISTANCE 8 // Number of chunks visible in each direction

Shader shader;

struct Chunk {
	float heightMap[CHUNK_SIZE + 1][CHUNK_SIZE + 1];

	Vector3 position;
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

Mesh genMeshFromChunk(const Chunk& chunk) {
	Mesh mesh = { 0 };

	int numVertices = (CHUNK_SIZE + 1) * (CHUNK_SIZE + 1);
	Vector3* vertices = (Vector3*)malloc(numVertices * sizeof(Vector3));
	Vector3* normals = (Vector3*)malloc(numVertices * sizeof(Vector3));
	Vector2* texcoords = (Vector2*)malloc(numVertices * sizeof(Vector2));

	int numTriangles = CHUNK_SIZE * CHUNK_SIZE * 2;
	int* indices = (int*)malloc(numTriangles * 3 * sizeof(int));

	int vertexIndex = 0;
	int indexIndex = 0;

	for (int x = 0; x <= CHUNK_SIZE; x++) {
		for (int z = 0; z <= CHUNK_SIZE; z++) {
			vertices[vertexIndex] = { chunk.position.x + x, chunk.heightMap[x][z], chunk.position.z + z };

			// Calculate normals (simple average of adjacent face normals)
			Vector3 normalSum = { 0.0f, 0.0f, 0.0f };
			int numNormals = 0;
			if (x > 0) {
				Vector3 v1 = { vertices[vertexIndex].x - 1, chunk.heightMap[x - 1][z], vertices[vertexIndex].z };
				Vector3 v2 = { vertices[vertexIndex].x, chunk.heightMap[x][z], vertices[vertexIndex].z };
				Vector3 v3 = { vertices[vertexIndex].x, chunk.heightMap[x][z - 1], vertices[vertexIndex].z - 1 };
				Vector3 faceNormal1 = Vector3Normalize(Vector3CrossProduct(Vector3Subtract(v2, v1), Vector3Subtract(v3, v1)));
				normalSum = Vector3Add(normalSum, faceNormal1);
				numNormals++;
			}
			if (x < CHUNK_SIZE) {
				Vector3 v1 = { vertices[vertexIndex].x, chunk.heightMap[x][z], vertices[vertexIndex].z };
				Vector3 v2 = { vertices[vertexIndex].x + 1, chunk.heightMap[x + 1][z], vertices[vertexIndex].z };
				Vector3 v3 = { vertices[vertexIndex].x, chunk.heightMap[x][z + 1], vertices[vertexIndex].z + 1 };
				Vector3 faceNormal2 = Vector3Normalize(Vector3CrossProduct(Vector3Subtract(v2, v1), Vector3Subtract(v3, v1)));
				normalSum = Vector3Add(normalSum, faceNormal2);
				numNormals++;
			}
			if (z > 0) {
				Vector3 v1 = { vertices[vertexIndex].x, chunk.heightMap[x][z - 1], vertices[vertexIndex].z - 1 };
				Vector3 v2 = { vertices[vertexIndex].x, chunk.heightMap[x][z], vertices[vertexIndex].z };
				Vector3 v3 = { vertices[vertexIndex].x - 1, chunk.heightMap[x - 1][z], vertices[vertexIndex].z };
				Vector3 faceNormal3 = Vector3Normalize(Vector3CrossProduct(Vector3Subtract(v2, v1), Vector3Subtract(v3, v1)));
				normalSum = Vector3Add(normalSum, faceNormal3);
				numNormals++;
			}
			if (z < CHUNK_SIZE) {
				Vector3 v1 = { vertices[vertexIndex].x + 1, chunk.heightMap[x + 1][z], vertices[vertexIndex].z };
				Vector3 v2 = { vertices[vertexIndex].x, chunk.heightMap[x][z + 1], vertices[vertexIndex].z + 1 };
				Vector3 v3 = { vertices[vertexIndex].x, chunk.heightMap[x][z], vertices[vertexIndex].z };
				Vector3 faceNormal4 = Vector3Normalize(Vector3CrossProduct(Vector3Subtract(v2, v1), Vector3Subtract(v3, v1)));
				normalSum = Vector3Add(normalSum, faceNormal4);
				numNormals++;
			}

			normals[vertexIndex] = Vector3Scale(normalSum, 1.0f / numNormals);
			texcoords[vertexIndex] = { (float)x / CHUNK_SIZE, (float)z / CHUNK_SIZE };

			vertexIndex++;
		}
	}

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			indices[indexIndex++] = (x + 1) * (CHUNK_SIZE + 1) + z;
			indices[indexIndex++] = x * (CHUNK_SIZE + 1) + z + 1;
			indices[indexIndex++] = x * (CHUNK_SIZE + 1) + z;

			indices[indexIndex++] = (x + 1) * (CHUNK_SIZE + 1) + z;
			indices[indexIndex++] = (x + 1) * (CHUNK_SIZE + 1) + z + 1;
			indices[indexIndex++] = x * (CHUNK_SIZE + 1) + z + 1;
		}
	}

	mesh = loadMeshes(vertices, normals, texcoords, numVertices, indices, numTriangles * 3);

	free(vertices);
	free(normals);
	free(texcoords);
	free(indices);

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
							DrawTriangle3D(p3, p2, p1, GREEN);
							DrawTriangle3D(p3, p4, p2, BLUE);
						}

						//}
					}
					else {

						//DrawModel(chunk.mdl, chunk.position, 1.0f, WHITE);

						DrawTriangle3D(p3, p2, p1, GREEN);
						DrawTriangle3D(p3, p4, p2, BLUE);
					}
				}
			}
		}
	}
}

int PrototypeTerrain() {
	// Initialization
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Procedural World Generation");
	camera = Camera();

	camera.position = Vector3{ 2.0f, 10.0f, 6.0f };    // Camera position
	camera.target = Vector3{ 0.0f, 0.5f, 0.0f };      // Camera looking at point
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

	shader = LoadShader("base.vs", "base.fs");

	//shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
	//int ambientLoc = GetShaderLocation(shader, "ambient");
	//float amb[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	//SetShaderValue(shader, ambientLoc, &amb, SHADER_UNIFORM_VEC4);

	// Create lights
	//Light lights[MAX_LIGHTS] = { 0 };

	//lights[0] = CreateLight(LightType::LIGHT_POINT, camera.position, Vector3{ 0.0f, 0.0f, 0.0f }, WHITE, shader);
	GenerateTerrain();

	SetTargetFPS(60);
	DisableCursor();
	float color[] = { BLUE.r, BLUE.g, BLUE.b, BLUE.a };

	// Main loop
	while (!WindowShouldClose()) {

		// Update
		UpdateCamera(&camera, CAMERA_FIRST_PERSON);

		if (IsKeyDown(KEY_SPACE)) {
			camera.position.y += 1.0f;
		}

		if (IsKeyDown(KEY_C)) {
			camera.position.y -= 1.0f;
		}

		//float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
		//SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
		//for (int i = 0; i < MAX_LIGHTS; i++) UpdateLightValues(shader, lights[i]);

		// Draw
		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode3D(camera);

		DrawSphere(Vector3{ 0.0f, 0.0f, 0.0f }, 1.0f, GREEN);

		//BeginShaderMode(shader);

		DrawTerrain();

		//EndShaderMode();
		EndMode3D();

		EndDrawing();
	}

	// Clean up
	CloseWindow();

	return 0;
}
