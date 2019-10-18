#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include "glm/gtx/string_cast.hpp"
#include <Windows.h>
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"
#include "Texture.h"
#include "Camera.h"
#include "FrameBuffer.h"
#include "Screen.h"
#include "CubeMap.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "BezierSurface.h"
#include "TicTacGrid.h"
#include "Quad.h"
#include "Sphere.h"
#include "Position.h"
#include "Player.h"
#include "Enemy.h"
#include "AStar.h"

#pragma region RenderingAndInputVariables
bool ShouldQuit = false;
bool KeyState[GLFW_KEY_LAST] = { false };
bool KeyDown[GLFW_KEY_LAST] = { false };
bool KeyHeld[GLFW_KEY_LAST] = { false };
Camera TheCamera;

double MouseX = 0.0;
double MouseY = 0.0;

bool CameraMovementActive = false;

BezierSurface BS;

Mesh TriangleMesh;
Mesh QuadMesh;
Mesh CubeMesh;
Material DefaultMaterial;
Material SkyboxMaterial;
Material LightSourceMaterial;
Texture CherylTexture;
CubeMap SkyboxTexture;
PointLight MainLight;
PointLight SecondLight;
SpotLight FlashLight;

glm::mat4 Projection;
ttg::GameInstanceData* GID;
glm::vec3 GridOffset = glm::vec3(0.f, 3.f, 0.f);
ttg::QuadData* QD[ttg::size] = { };
#pragma endregion RenderingAndInputVariables

Position PlayerPosition;
Player player;
Enemy enemy;

glm::vec3 playerPosition = glm::vec3(0.f, 0.f, 0.f);
glm::vec3 enemyPosition = glm::vec3(-2.f, 0.f, -2.f);

const int xlen = 8;
const int ylen = 8;
glm::vec3 grid[xlen][ylen] = { };
Node nodeGrid[xlen][ylen] = { };
float size = 2.f;
int nrx, nry;
int prevX, prevY;

std::vector<Node> path;

void SetRandomGridPosition(std::vector<Node> _path);

#pragma region RenderingAndInputFunctions
const float CubeVertexData[] = {
	// FRONT FACE
	-1.f, -1.f, +1.f,		0.f, 0.f, 1.f,		0.f, 0.f,	// 0
	+1.f, -1.f, +1.f,		0.f, 0.f, 1.f,		1.f, 0.f,	// 1
	+1.f, +1.f, +1.f,		0.f, 0.f, 1.f,		1.f, 1.f,	// 2
	-1.f, +1.f, +1.f,		0.f, 0.f, 1.f,		0.f, 1.f,	// 3

	// BACK FACE
	-1.f, -1.f, -1.f,		0.f, 0.f, -1.f,		0.f, 0.f,	// 4
	+1.f, -1.f, -1.f,		0.f, 0.f, -1.f,		1.f, 0.f,	// 5
	+1.f, +1.f, -1.f,		0.f, 0.f, -1.f,		1.f, 1.f,	// 6
	-1.f, +1.f, -1.f,		0.f, 0.f, -1.f,		0.f, 1.f,	// 7

	// RIGHT FACE
	+1.f, -1.f, +1.f,		1.f, 0.f, 0.f,		0.f, 0.f,	// 8
	+1.f, -1.f, -1.f,		1.f, 0.f, 0.f,		1.f, 0.f,	// 9
	+1.f, +1.f, -1.f,		1.f, 0.f, 0.f,		1.f, 1.f,	// 10
	+1.f, +1.f, +1.f,		1.f, 0.f, 0.f,		0.f, 1.f,	// 11

	// LEFT FACE
	-1.f, -1.f, +1.f,		-1.f, 0.f, 0.f,		0.f, 0.f,	// 12
	-1.f, -1.f, -1.f,		-1.f, 0.f, 0.f,		1.f, 0.f,	// 13
	-1.f, +1.f, -1.f,		-1.f, 0.f, 0.f,		1.f, 1.f,	// 14
	-1.f, +1.f, +1.f,		-1.f, 0.f, 0.f,		0.f, 1.f,	// 15

	// TOP FACE
	-1.0, +1.f, +1.f,		0.f, 1.f, 0.f,		0.f, 0.f,	// 16
	+1.f, +1.f, +1.f,		0.f, 1.f, 0.f,		1.f, 0.f,	// 17
	+1.f, +1.f, -1.f,		0.f, 1.f, 0.f,		1.f, 1.f,	// 18
	-1.f, +1.f, -1.f,		0.f, 1.f, 0.f,		0.f, 1.f,	// 19

	// BOTTOM FACE
	-1.0, -1.f, +1.f,		0.f, -1.f, 0.f,		0.f, 0.f,	// 20
	+1.f, -1.f, +1.f,		0.f, -1.f, 0.f,		1.f, 0.f,	// 21
	+1.f, -1.f, -1.f,		0.f, -1.f, 0.f,		1.f, 1.f,	// 22
	-1.f, -1.f, -1.f,		0.f, -1.f, 0.f,		0.f, 1.f,	// 23
};

const unsigned int CubeIndexData[] = {
	// FRONT FACE
	0, 1, 2,	0, 2, 3,
	// BACK FACE
	4, 5, 6,	4, 6, 7,
	// RIGHT FACE
	8, 9, 10,	8, 10, 11,
	// LEFT FACE
	12, 13, 14,	12, 14, 15,
	// TOP FACE
	16, 17, 18, 16, 18, 19,
	// BOTTOM FACE
	20, 21, 22, 20, 22, 23,
};

const char* SkyboxImages[] = {
	"Res/Skybox/alps_ft.tga",	// POSITIVE X (front)
	"Res/Skybox/alps_bk.tga",	// NEGATIVE X (back)
	"Res/Skybox/alps_up.tga",	// POSITIVE Y (up)
	"Res/Skybox/alps_dn.tga",	// NEGATIVE Y (down)
	"Res/Skybox/alps_rt.tga",	// POSITIVE Z (right)
	"Res/Skybox/alps_lf.tga",	// NEGATIVE Z (left)
};


bool IsKeyPressed(int Key)
{
	return KeyState[Key];
}

bool IsKeyDown(int Key)
{
	return KeyDown[Key];
}

void OnKeyEvent(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	KeyState[Key] = (Action == GLFW_PRESS || Action == GLFW_REPEAT);

	if (Key == GLFW_KEY_G && Action == GLFW_PRESS)
	{
		SetRandomGridPosition(path);
	}

	if (Action == GLFW_PRESS)
	{
		//printf("OnKeyEvent( %d )\n", Key);

		if (Key == GLFW_KEY_ESCAPE)
			ShouldQuit = true;
	}
}

void OnMouseButton(GLFWwindow* Window, int Button, int Action, int Mods)
{
	if (Button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		CameraMovementActive = (Action == GLFW_PRESS);
		glfwSetInputMode(Window, GLFW_CURSOR, CameraMovementActive ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
	}
}

void OnCursorMove(GLFWwindow* Window, double X, double Y)
{
	MouseX = X;
	MouseY = Y;
}

void RenderQuad(const Transform& Transform)
{
	QuadMesh.Bind();
	DefaultMaterial.Set("u_World", Transform.GetMatrix());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void RenderTriangle(const Transform& Transform)
{
	TriangleMesh.Bind();
	DefaultMaterial.Set("u_World", Transform.GetMatrix());
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void RenderCube(const Transform& Transform)
{
	CubeMesh.Bind();
	DefaultMaterial.Set("u_World", Transform.GetMatrix());
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void RenderSkybox()
{
	SkyboxTexture.Bind();
	CubeMesh.Bind();
	SkyboxMaterial.Use();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void RenderFullscreenQuad()
{
	glBindVertexArray(0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void RenderLightSource(const PointLight& Light)
{
	LightSourceMaterial.Use();
	LightSourceMaterial.Set("u_World", Transform(Light.Position, quat_identity, glm::vec3(0.2f)).GetMatrix());
	LightSourceMaterial.Set("u_Color", Light.Color);
	CubeMesh.Bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

#pragma endregion RenderingAndInputFunctions

void SetGridPosition(std::vector<Node> path, int x, int y)
{
	if (nodeGrid[x][x].isObstacle)
	{
		std::cout << "tried to set obstacle as destination" << std::endl;
		return;
	}

	enemy.currentPathIndex = 0;

	Node currentEnemyNode;
	currentEnemyNode.x = enemy.curX;
	currentEnemyNode.y = enemy.curY;

	enemy.goalX = x;
	enemy.goalY = x;

	Node destination;
	destination.x = x;
	destination.y = y;

	nrx = x;
	nry = y;

	enemy.currentPath = Pathfinder::aStar(currentEnemyNode, destination, nodeGrid);
}

void RenderScene(bool RenderPlayer)
{
	CherylTexture.Bind();
	Material::MyValue += 5;

	float Time = glfwGetTime();

	RenderSkybox();

	int playerPosX = 0;
	int playerPosY = 0;

	glm::vec3 gridPlayerPos = glm::vec3(0.f);

	{
		float dst = INFINITY;

		for (int x = 0; x < xlen; x++)
		{
			for (int y = 0; y < ylen; y++)
			{
				Node n = nodeGrid[x][y];

				float newDist = glm::distance(grid[x][y], playerPosition);
				if (newDist < dst)
				{
					playerPosX = x;
					playerPosY = y;
					dst = newDist;
				}

				float flatSize = 1.0f;

				glm::vec3 regularSize = glm::vec3(flatSize, 0.2f, flatSize);
				glm::vec3 obstacleSize = glm::vec3(flatSize, 1.f, flatSize);

				RenderCube(
					Transform(grid[x][y],
					n.isObstacle? obstacleSize : regularSize
					));
			}
		}

		if (prevX != playerPosX || prevY != playerPosY)
		{
			prevX = playerPosX;
			prevY = playerPosY;

			if (!nodeGrid[prevX][prevY].isObstacle)
				SetGridPosition(path, playerPosX, playerPosY);
		}
	}

	{
		if (enemy.currentPath.size() != 0)
		{
			for (int i = 0; i < enemy.currentPath.size() - 1; i++)
			{
				Node n = enemy.currentPath[i];

				glm::vec3 pos = grid[n.x][n.y];
				pos.y += 0.5f;
				RenderCube(Transform(pos, glm::vec3(0.3f, 0.3f, 0.3f)));
			}
		}
	}

	RenderCube(Transform(grid[nrx][nry], glm::vec3(0.1f, 2.f, 0.1f)));

	if (RenderPlayer)
	{
		RenderCube(Transform(playerPosition + glm::vec3(0.f, 2.5f, 0.f),
			player.GetTransform().Rotation,
			glm::vec3(0.2f, 2.0f, 0.2f))
			);

		RenderCube(Transform(grid[playerPosX][playerPosY] + glm::vec3(0.f, 0.9f, 0.f),
				   glm::vec3(0.9f, 0.5f, 0.9f))
		);

		RenderCube(Transform(enemyPosition + glm::vec3(0.f, 1.f, 0.f),
			enemy.GetTransform().Rotation,
			glm::vec3(0.5f, 1.f, 0.5f))
			);
	}
}

void SetRandomGridPosition(std::vector<Node> _path)
{
	int xrand = glm::linearRand(0, xlen - 1);
	int yrand = glm::linearRand(0, ylen - 1);

	if (nodeGrid[xrand][yrand].isObstacle)
	{
		std::cout << "tried to set obstacle as destination" << std::endl;
		return;
	}

	enemy.currentPathIndex = 0;

	Node currentEnemyNode;
	currentEnemyNode.x = enemy.curX;
	currentEnemyNode.y = enemy.curY;

	enemy.goalX = xrand;
	enemy.goalY = yrand;

	Node destination;
	destination.x = xrand;
	destination.y = yrand;

	nrx = xrand;
	nry = yrand;

	enemy.currentPath = Pathfinder::aStar(currentEnemyNode, destination, nodeGrid);
}

int main()
{
	// Used for comparing to previous path & position data
	player = Player();
	enemy = Enemy();

	// Create grid
	{
		for (int x = 0; x < xlen; x++)
		{
			for (int y = 0; y < ylen; y++)
			{
				nodeGrid[x][y] = Node(x, y);
				grid[x][y] = glm::vec3(x * size, 0.f, y * size);
			}
		}
	}

	nodeGrid[2][2].isObstacle = true;
	nodeGrid[2][3].isObstacle = true;
	nodeGrid[2][4].isObstacle = true;
	nodeGrid[2][5].isObstacle = true;
	nodeGrid[2][6].isObstacle = true;
	nodeGrid[2][7].isObstacle = true;

	nodeGrid[1][2].isObstacle = true;
	nodeGrid[2][2].isObstacle = true;
	nodeGrid[3][2].isObstacle = true;
	nodeGrid[4][2].isObstacle = true;
	nodeGrid[5][2].isObstacle = true;
	nodeGrid[6][2].isObstacle = true;

	#pragma region RenderingThings
	/* WINDOW STUFF */
	// Initialize GLFW, create a window and context
	glfwInit();

	GLFWwindow* Window;
	Window = glfwCreateWindow(ScreenWidth, ScreenHeight, "This is OpenGL my dude", nullptr, nullptr);

	glfwSetKeyCallback(Window, OnKeyEvent);
	glfwSetCursorPosCallback(Window, OnCursorMove);
	glfwSetMouseButtonCallback(Window, OnMouseButton);
	glfwMakeContextCurrent(Window);
	glfwSwapInterval(0);

	// After the context is bound, we can import the OpenGL extensions, through the extension wrangler
	glewInit();

	/* VERTEX STUFF */
	BS.Setup();
	// Triangle, bejbii
	float TriData[] = {
		-0.5f, -0.5f, 0.0f,		0.f, 0.f, 1.f,		0.0f, 0.0f,
		+0.5f, -0.5f, 0.0f,		0.f, 0.f, 1.f,		1.0f, 0.0f,
		+0.0f, +0.5f, 0.0f,		0.f, 0.f, 1.f,		0.5f, 1.0f,
	};
	 
	TriangleMesh.LoadVerts(TriData, sizeof(TriData), nullptr, 0);

	float QuadData[] = {
		-0.5f, -0.5f, 0.f,		0.f, 0.f, 1.f,		0.f, 0.f,
		+0.5f, -0.5f, 0.f,		0.f, 0.f, 1.f,		1.f, 0.f,
		-0.5f, +0.5f, 0.f,		0.f, 0.f, 1.f,		0.f, 1.f,
		+0.5f, +0.5f, 0.f,		0.f, 0.f, 1.f,		1.f, 1.f,
	};
	
	QuadMesh.LoadVerts(QuadData, sizeof(QuadData), nullptr, 0);

	CubeMesh.LoadVerts(CubeVertexData, sizeof(CubeVertexData), CubeIndexData, sizeof(CubeIndexData));

	DefaultMaterial.LoadFiles("Res/Shader/default.vert", "Res/Shader/default.frag"); //insert cheese
	DefaultMaterial.Set("u_DirLight.ShadowBuffer", 2);

	Material PostProcessMaterial;
	PostProcessMaterial.LoadFiles("Res/Shader/post_process.vert", "Res/Shader/post_process.frag");
	PostProcessMaterial.Set("u_FrameColor", 0);
	PostProcessMaterial.Set("u_FrameDepth", 1);

	SkyboxMaterial.LoadFiles("Res/Shader/skybox.vert", "Res/Shader/skybox.frag");
	LightSourceMaterial.LoadFiles("Res/Shader/light_source.vert", "Res/Shader/light_source.frag");

	CherylTexture.LoadFile("Res/brick.jpg");
	CherylTexture.Bind();

	SkyboxTexture.LoadFiles(SkyboxImages);

	float Ratio = (float)ScreenWidth / ScreenHeight;
	float OrthoSize = 2.f;

	TheCamera.Position = glm::vec3(0.f, 4.f, 8.f);

	glm::vec3 LightDirection = glm::normalize(glm::vec3(-1.f, -0.55f, 0.35f));
	DefaultMaterial.Set("u_DirLight.Direction", LightDirection);
	DefaultMaterial.Set("u_DirLight.Color", glm::vec3(0.9f, 0.9f, 1.f));

	// Point light stuff!
	//MainLight.Position = glm::vec3(0.f, 1.f, 0.f);
	//MainLight.Color =  glm::vec3(1.f, 0.f, 0.f);
	//MainLight.Radius = 20.f;
	//MainLight.UploadToMaterial(0, DefaultMaterial);
	//
	//SecondLight.Position = glm::vec3(0.f, 1.f, 0.f);
	//SecondLight.Color =  glm::vec3(0.4f, 0.4f, 1.f);
	//SecondLight.Radius = 40.f;
	//SecondLight.UploadToMaterial(1, DefaultMaterial);
	//
	//FlashLight.Position = glm::vec3(0.f, 2.f, 10.f);
	//FlashLight.Direction = glm::vec3(0.f, 0.f, -1.f);
	//FlashLight.Color = glm::vec3(0.3f, 1.f, 0.3f);
	//FlashLight.Angle = glm::radians(20.f);
	//FlashLight.Length = 30.f;
	//FlashLight.UploadToMaterial(DefaultMaterial);

	Projection = glm::perspective(glm::radians(60.f), Ratio, 0.2f, 150.f);
	DefaultMaterial.Set("u_Projection", Projection);

	glEnable(GL_DEPTH_TEST);
	float LastFrameTime = 0.f;

	double LastMouseX = 0.0;
	double LastMouseY = 0.0;

	FrameBuffer LightBuffer;
	LightBuffer.Create(4096, 4096);

	FrameBuffer FB;
	FB.Create(2000, 2000);

	glm::mat4 LightProjection;
	glm::mat4 LightView;
	LightProjection = glm::ortho(-25.f, 25.f, -25.f, 25.f, -30.f, 30.f);
	LightView = glm::lookAt(glm::vec3(0.f), LightDirection, glm::vec3(0.f, 1.f, 0.f));

	TheCamera.AddPitch(-25.f);
#pragma endregion RenderingThings

	// Main loop of the program
	while (!glfwWindowShouldClose(Window) && !ShouldQuit)
	{
		#pragma region PlayerAndCameraMovement
		DefaultMaterial.Use();

		float CurrentTime = glfwGetTime();
		float DeltaTime = CurrentTime - LastFrameTime;
		LastFrameTime = CurrentTime;

		double MouseDeltaX = MouseX - LastMouseX;
		double MouseDeltaY = MouseY - LastMouseY;
		LastMouseX = MouseX;
		LastMouseY = MouseY;

		if (CameraMovementActive)
		{
			player.AddYaw(-MouseDeltaX * 0.1f);

			TheCamera.AddYaw(-MouseDeltaX * 0.1f);
			TheCamera.AddPitch(-MouseDeltaY * 0.05f, -45.f, 85.f);
		}

		glm::vec3 PlayerMovement = glm::vec3(0.f);
		if (IsKeyPressed(GLFW_KEY_W))
			PlayerMovement += player.GetForwardVector();
		if (IsKeyPressed(GLFW_KEY_S))
			PlayerMovement += -player.GetForwardVector();
		if (IsKeyPressed(GLFW_KEY_D))
			PlayerMovement += player.GetRightVector();
		if (IsKeyPressed(GLFW_KEY_A))
			PlayerMovement += -player.GetRightVector();

		if (PlayerMovement != glm::vec3(0.f))
		{
			playerPosition += PlayerMovement * 6.f * DeltaTime;
		}

		glm::vec3 cameraPos =
			playerPosition
			- player.GetForwardVector() * 12.f
			+ glm::vec3(0.f, 1.f, 0.f) * 8.f;

		if (IsKeyDown(GLFW_KEY_G))
		{
			SetRandomGridPosition(path);
		}
#pragma endregion PlayerAndCameraMovement

		// Follow current path
		if (enemy.currentPath.size() != 0)
		{
			if (enemy.currentPathIndex < enemy.currentPath.size())
			{
				Node currentPathNode = enemy.currentPath[enemy.currentPathIndex];
				glm::vec3 nextPathNodePos = grid[currentPathNode.x][currentPathNode.y];
				glm::vec3 dirToPos = nextPathNodePos - enemyPosition;

 				float len = glm::distance(nextPathNodePos, enemyPosition);
				if (len < 0.01f)
				{
					enemy.currentPathIndex++;

					if (enemy.currentPathIndex >= enemy.currentPath.size())
					{
						enemy.currentPath = std::vector<Node>();
						enemy.currentPathIndex = 0;
					} else
					{
						enemy.curX = enemy.currentPath[enemy.currentPathIndex].x;
						enemy.curY = enemy.currentPath[enemy.currentPathIndex].y;
					}
				} else
				{
					// hardcoded enemy movement speed >:)
					enemyPosition += glm::normalize(dirToPos) * 4.f * DeltaTime;
				}
			}
		}

		#pragma region MoreRenderings
		TheCamera.Position = cameraPos;

		DefaultMaterial.Set("u_View", TheCamera.GetViewMatrix());
		DefaultMaterial.Set("u_EyePosition", TheCamera.Position);

		MainLight.Color = glm::vec3(1.f, 0.3f, 0.3f) * (glm::sin(CurrentTime * 5.f) + 1.f) * 4.f;
		MainLight.Position = glm::vec3(glm::sin(CurrentTime) * 5.f, 0.2f, glm::cos(CurrentTime) * 2.f);
		MainLight.UploadToMaterial(0, DefaultMaterial);

		if (IsKeyPressed(GLFW_KEY_F))
		{
			FlashLight.Position = TheCamera.Position;
			FlashLight.Direction = TheCamera.GetForwardVector();
			FlashLight.UploadToMaterial(DefaultMaterial);	
		}

		glClearColor(0.1f, 0.1f, 0.1f, 1.f);

		// Render the light pass!
		DefaultMaterial.Set("u_Projection", LightProjection);
		DefaultMaterial.Set("u_View", LightView);
		LightSourceMaterial.Set("u_Projection", LightProjection);
		LightSourceMaterial.Set("u_View", LightView);

		LightBuffer.Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RenderScene(true);

		LightBuffer.Unbind();

		// Render to Frame Buffer
		DefaultMaterial.Set("u_Projection", Projection);
		DefaultMaterial.Set("u_View", TheCamera.GetViewMatrix());
		DefaultMaterial.Set("u_DirLight.ViewProjection", LightProjection * LightView);
		LightSourceMaterial.Set("u_Projection", Projection);
		LightSourceMaterial.Set("u_View", TheCamera.GetViewMatrix());

		SkyboxMaterial.Set("u_Projection", Projection);
		SkyboxMaterial.Set("u_View", TheCamera.GetViewMatrix());

		LightBuffer.DepthTexture.Bind(2);

		FB.Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RenderScene(true);

		FB.Unbind();

		// Render to screen!
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//FB.ColorTexture.Bind();
		//RenderQuad(Transform(glm::vec3(0.f, 20.f, -20.f), quat_identity, glm::vec3(40.f)));

		PostProcessMaterial.Use();
		FB.ColorTexture.Bind(0);
		FB.DepthTexture.Bind(1);
		RenderFullscreenQuad();


		// Swap the back-buffer to the front and poll and handle window events
		glfwSwapBuffers(Window);
		glfwPollEvents();
#pragma endregion MoreRenderings
	}

	return 0;
}
