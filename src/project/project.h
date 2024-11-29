#pragma once
#include "../engine/Project.h"
#include <renderer/GameObject.h>
#include <raylib.h>
#include <FastNoiseLite.h>

#define PROJECT_TYPENAME Project
#define CHUNK_SIZE 32
#define VIEW_DISTANCE 8 // Number of chunks visible in each direction

using namespace Techstorm;
struct Chunk {
	float heightMap[CHUNK_SIZE + 1][CHUNK_SIZE + 1];

	Vector3 position;
};


class Terrain final : public GameObject {
private:
	static inline Chunk chunks[VIEW_DISTANCE * 2 + 1][VIEW_DISTANCE * 2 + 1];

	Renderer& mRenderer;
public:

	Terrain(Renderer& renderer) : mRenderer(renderer), GameObject() {
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

	void texture() override {
		float vDistMultiplier = 100.0f;
		float vDist = (VIEW_DISTANCE * CHUNK_SIZE) * vDistMultiplier;
		bool forceAllDraw = true;

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
							Camera3D camera = mRenderer.mCamera.getCameraData();
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
};

/// <summary>
/// Write your project code here or do what you want with it. However,
/// you MUST implement the IProject interface somehow and set the project reference!
/// See <see cref="Techstorm::IProject" /> for more information on this.
/// </summary>
/// <inheritdoc />
class Project final : public Techstorm::IProject {
private:

public:

	Project() : IProject() {
		//mRenderer = Renderer();
		
	}

	void preInit() override {
		// WARNING: This MUST be called before any operations that use the file registry. The only exceptions is if you are adding load functions and adding extensions
		// that need to be loaded on registration.
		IProject::preInit();
	}

	void init(int argc, char* argv[]) override {
		IProject::init(argc, argv);
		mRenderer.addGameObject(new Terrain(mRenderer));
	}

	int texture() override {
		IProject::texture();
		
		return 0;
	}
};
