#version 330

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 finalColor;

uniform sampler2D heightmap;
uniform vec3 lightPos;

// Colors for different terrain heights
vec3 grassColor = vec3(0.1, 0.8, 0.1);
vec3 dirtColor = vec3(0.4, 0.26, 0.13);
vec3 snowColor = vec3(1.0, 1.0, 1.0);

void main()
{
    vec2 mapPos = vec2(fragPosition.x, fragPosition.y);
    // Sample the heightmap to determine the terrain height
    float height = texture(heightmap, mapPos).r;
    
    // Determine the color based on the height
    vec3 terrainColor;
    if (height < 0.3) {
        terrainColor = grassColor;
    } else if (height < 0.5) {
        terrainColor = dirtColor;
    } else {
        terrainColor = grassColor;
    }

    // Simple diffuse lighting based on the light position
    vec3 lightDir = normalize(lightPos - fragPosition);
    float diff = max(dot(normalize(fragNormal), lightDir), 0.0);

    vec3 result = diff * terrainColor;
    finalColor = vec4(result, 1.0);
}
