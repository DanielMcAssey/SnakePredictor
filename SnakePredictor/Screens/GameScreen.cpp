#include "stdafx.h"
#include "../stdafx.h"
#include "GameScreen.h"

const int POINT_SIZE = 10; // 10 Pixels high and wide for every segment
const int BORDER_WIDTH = 3; // 2 Points of border
const int SNAKE_START_SIZE = 3;  // 3 Points start size
const float SNAKE_UPDATE_FREQUENCY = 0.8f; // .8 of Every second

GameScreen::GameScreen(String _name, InputManager* _input, SDL_Window* _window) : BaseScreen(_name, _input, _window)
{
}


GameScreen::~GameScreen()
{
}


void GameScreen::PlaceFood()
{
	// TODO: Find a better/faster way of randomly placing food
	bool isPlaced = false;

	while (!isPlaced)
	{
		int randomX = rand() % LevelWidth;
		int randomY = rand() % LevelHeight;

		if (LevelGrid[std::make_pair(randomX, randomY)] == LEVEL_SEGMENT_BLANK)
		{
			LevelGrid[std::make_pair(randomX, randomY)] = LEVEL_SEGMENT_PLAYER_FOOD;
			LevelFoodLocation = std::make_pair(randomX, randomY);
			isPlaced = true;
		}
	}
}


void GameScreen::CollectFood()
{
	// TODO: Add points
	EntSnake->isFoodCollected = false;
	PlaceFood();
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
			if (x < BORDER_WIDTH || y < BORDER_WIDTH || x >= (LevelWidth - BORDER_WIDTH) || y >= (LevelHeight - BORDER_WIDTH)) // Create boundries
			{
				LevelGrid[std::make_pair(x, y)] = LEVEL_SEGMENT_WALL;
			}
			else
			{
				LevelGrid[std::make_pair(x, y)] = LEVEL_SEGMENT_BLANK;
			}
		}
	}

	SankeUpdateTimer = 0.0f;
	EntSnake = new SnakeEntity(&LevelGrid, SNAKE_START_SIZE, LevelWidth, LevelHeight); // Create the snake

	PlaceFood(); // Place initial food
}


void GameScreen::Unload()
{
	BaseScreen::Unload();

	ScreenWidth, ScreenHeight = 0;
	LevelWidth, LevelHeight = 0;
	LevelGrid.clear();

	SankeUpdateTimer = 0.0f;
	delete EntSnake;
	EntSnake = nullptr;
}


void GameScreen::Update(float _DeltaTime)
{
	BaseScreen::Update(_DeltaTime);

	SankeUpdateTimer += _DeltaTime;
	if (SankeUpdateTimer >= SNAKE_UPDATE_FREQUENCY)
	{
		SankeUpdateTimer = 0.0f;
		// Update snake movement
		if (EntSnake != nullptr && !EntSnake->isDead)
		{
			EntSnake->Update(_DeltaTime);
			if (EntSnake->isFoodCollected)
			{
				CollectFood();
			}
		}
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
			case LEVEL_SEGMENT_PLAYER_SNAKE_HEAD:
				SDL_SetRenderDrawColor(_Renderer, 237, 32, 36, 255);
				SDL_RenderFillRect(_Renderer, &levelSegment);
				break;
			default: // Equal to LEVEL_SEGMENT_BLANK
				// Draw nothing
				break;
			}
		}
	}
}