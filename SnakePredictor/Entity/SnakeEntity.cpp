#include "stdafx.h"
#include "../stdafx.h"
#include "SnakeEntity.h"

SnakeEntity::SnakeEntity(std::map<std::pair<int, int>, LevelSegment>* _level, int _initial_size, int _level_width, int _level_height)
{
	LevelGrid = _level;
	LevelWidth = _level_width;
	LevelHeight = _level_height;

	// Create starting snake
	int startPosX = LevelWidth / 2;
	int startPosY = LevelHeight / 2;

	SnakeParts.push_back(std::make_pair(startPosX, startPosY));
	for (int i = 1; i < _initial_size; i++)
	{
		SnakeParts.push_back(std::make_pair(startPosX + i, startPosY));
	}

	UpdateBody();
}


SnakeEntity::~SnakeEntity()
{
}


void SnakeEntity::ClearBody()
{
	for (std::vector<std::pair<int, int>>::iterator itr = SnakeParts.begin(); itr != SnakeParts.end(); ++itr) {
		(*LevelGrid)[(*itr)] = LEVEL_SEGMENT_BLANK;
	}
}


void SnakeEntity::UpdateBody()
{
	for (std::vector<std::pair<int, int>>::iterator itr = SnakeParts.begin(); itr != SnakeParts.end(); ++itr) {
		if (itr == SnakeParts.begin()) // First element should always be a head
		{
			(*LevelGrid)[(*itr)] = LEVEL_SEGMENT_PLAYER_SNAKE_HEAD;
		}
		else
		{
			(*LevelGrid)[(*itr)] = LEVEL_SEGMENT_PLAYER_SNAKE;
		}
	}
}


void SnakeEntity::Unload()
{
	LevelGrid = nullptr;
	SnakeParts.clear();
}


void SnakeEntity::Update(float _DeltaTime)
{
	// Clear body from level to update the movement
	ClearBody();

	// TODO: A* Pathfinding, Snake Length Update and Movement

	// Update snake body to map with new positions
	UpdateBody();
}