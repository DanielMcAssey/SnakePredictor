#include "stdafx.h"
#include "../stdafx.h"
#include "GameScreen.h"

const int POINT_SIZE = 10; // 10 Pixels high and wide for every segment
const int SNAKE_START_SIZE = 3;  // 3 Points start size
const float SNAKE_UPDATE_FREQUENCY = 1.0f; // Once every second

GameScreen::GameScreen(String _name, InputManager* _input, SDL_Window* _window) : BaseScreen(_name, _input, _window)
{
}


GameScreen::~GameScreen()
{
}


void GameScreen::PlaceFood()
{
	bool isPlaced = false;

	while (!isPlaced)
	{
		int randomX = rand() % LevelWidth;
		int randomY = rand() % LevelHeight;

		if (LevelGrid[std::make_pair(randomX, randomY)] == LEVEL_SEGMENT_BLANK)
		{
			LevelGrid[std::make_pair(randomX, randomY)] = LEVEL_SEGMENT_PLAYER_FOOD;
			isPlaced = true;
		}
	}
}


void GameScreen::Load()
{
	BaseScreen::Load();

	srand(time(NULL)); // Initialize random seed

	SDL_GetWindowSize(gWindow, &ScreenWidth, &ScreenHeight);
	
	// Set initial height and width of level
	LevelWidth = ScreenWidth / POINT_SIZE;
	LevelHeight = ScreenHeight / POINT_SIZE;

	for (int x = 0; x < LevelWidth; x++)
	{
		for (int y = 0; y < LevelHeight; y++)
		{
			if (x == 0 || y == 0 || x == (LevelWidth - 1) || y == (LevelHeight - 1)) // Create boundries
			{
				LevelGrid[std::make_pair(x, y)] = LEVEL_SEGMENT_WALL;
			}
			else
			{
				LevelGrid[std::make_pair(x, y)] = LEVEL_SEGMENT_BLANK;
			}
		}
	}

	PlaceFood(); // Place initial food
}


void GameScreen::Unload()
{
	BaseScreen::Unload();

	ScreenWidth, ScreenHeight = 0;
	LevelWidth, LevelHeight = 0;
	LevelGrid.clear();
}


void GameScreen::Update(float _DeltaTime)
{
	BaseScreen::Update(_DeltaTime);

	SankeUpdateTimer += _DeltaTime;
	if (SankeUpdateTimer >= SNAKE_UPDATE_FREQUENCY)
	{
		SankeUpdateTimer = 0.0f;
		// Update snake movement
	}
}


void GameScreen::Render(SDL_Renderer* _Renderer)
{
	BaseScreen::Render(_Renderer);

	for (int x = 0; x < LevelWidth; x++)
	{
		for (int y = 0; y < LevelHeight; y++)
		{
			SDL_Rect levelSegment = { x * POINT_SIZE, y * POINT_SIZE, POINT_SIZE, POINT_SIZE };

			switch (LevelGrid[std::make_pair(x, y)])
			{
			case LEVEL_SEGMENT_WALL:
				SDL_SetRenderDrawColor(_Renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(_Renderer, &levelSegment);
				break;
			case LEVEL_SEGMENT_PLAYER_FOOD:
				SDL_SetRenderDrawColor(_Renderer, 51, 102, 0, 255);
				SDL_RenderFillRect(_Renderer, &levelSegment);
				break;
			case LEVEL_SEGMENT_PLAYER_SNAKE:
				SDL_SetRenderDrawColor(_Renderer, 255, 255, 255, 255);
				SDL_RenderFillRect(_Renderer, &levelSegment);
				break;
			default: // Equal to LEVEL_SEGMENT_BLANK
				// Draw nothing
				break;
			}
		}
	}
}