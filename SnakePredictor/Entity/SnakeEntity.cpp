#include "stdafx.h"
#include "../stdafx.h"
#include "SnakeEntity.h"

SnakeEntity::SnakeEntity(std::map<std::pair<int, int>, LevelSegment>* _level, int _initial_size, int _level_width, int _level_height)
{
	LevelGrid = _level;
	LevelWidth = _level_width;
	LevelHeight = _level_height;
	isDead = false;
	isFoodCollected = false;

	// Create starting snake
	int startPosX = LevelWidth / 2;
	int startPosY = LevelHeight / 2;

	SnakePart* tmpPart = new SnakePart();
	tmpPart->Location = std::make_pair(startPosX, startPosY);
	tmpPart->LastMovement = SNAKE_MOVE_LEFT;
	SnakeParts.push_back(tmpPart);
	for (int i = 1; i < _initial_size; i++)
	{
		tmpPart = new SnakePart();
		tmpPart->Location = std::make_pair(startPosX + i, startPosY);
		tmpPart->LastMovement = SNAKE_MOVE_LEFT;
		SnakeParts.push_back(tmpPart);
	}

	UpdateBody();
}


SnakeEntity::~SnakeEntity()
{
}


void SnakeEntity::ClearBody()
{
	for (std::vector<SnakePart*>::iterator itr = SnakeParts.begin(); itr != SnakeParts.end(); ++itr)
	{
		(*LevelGrid)[(*itr)->Location] = LEVEL_SEGMENT_BLANK;
	}
}


void SnakeEntity::UpdateBody()
{
	for (std::vector<SnakePart*>::iterator itr = SnakeParts.begin(); itr != SnakeParts.end(); ++itr)
	{
		if (itr == SnakeParts.begin()) // First element should always be a head
		{
			(*LevelGrid)[(*itr)->Location] = LEVEL_SEGMENT_PLAYER_SNAKE_HEAD;
		}
		else
		{
			(*LevelGrid)[(*itr)->Location] = LEVEL_SEGMENT_PLAYER_SNAKE;
		}
	}
}


void SnakeEntity::Move(SnakeMovement _Direction)
{
	SnakePart* snakeHead = SnakeParts.front();
	std::pair<int, int> newPosition;

	switch (_Direction)
	{
	case SNAKE_MOVE_UP:
		newPosition = std::make_pair(snakeHead->Location.first, snakeHead->Location.second - 1);
		break;
	case SNAKE_MOVE_DOWN:
		newPosition = std::make_pair(snakeHead->Location.first, snakeHead->Location.second + 1);
		break;
	case SNAKE_MOVE_LEFT:
		newPosition = std::make_pair(snakeHead->Location.first - 1, snakeHead->Location.second);
		break;
	case SNAKE_MOVE_RIGHT:
		newPosition = std::make_pair(snakeHead->Location.first + 1, snakeHead->Location.second);
		break;
	default:
		// Dont move
		break;
	}

	if (CanMove(newPosition))
	{
		SnakeParts.front()->Location = newPosition; // Update snake head position
		SnakeMovement lastMovement = SnakeParts.front()->LastMovement;
		SnakeMovement nextMovement;

		// Update body
		for (std::vector<SnakePart*>::iterator itr = SnakeParts.begin(); itr != SnakeParts.end(); ++itr)
		{
			if (itr == SnakeParts.begin()) // Ignore head
				continue;

			switch (lastMovement)
			{
			case SNAKE_MOVE_UP:
				newPosition = std::make_pair((*itr)->Location.first, (*itr)->Location.second - 1);
				break;
			case SNAKE_MOVE_DOWN:
				newPosition = std::make_pair((*itr)->Location.first, (*itr)->Location.second + 1);
				break;
			case SNAKE_MOVE_LEFT:
				newPosition = std::make_pair((*itr)->Location.first - 1, (*itr)->Location.second);
				break;
			case SNAKE_MOVE_RIGHT:
				newPosition = std::make_pair((*itr)->Location.first + 1, (*itr)->Location.second);
				break;
			default:
				// Dont move
				break;
			}

			(*itr)->Location = newPosition;
			nextMovement = (*itr)->LastMovement;
			(*itr)->LastMovement = lastMovement;
			lastMovement = nextMovement;
		}

		SnakeParts.front()->LastMovement = _Direction;
	}
}


bool SnakeEntity::CanMove(std::pair<int, int> _Location)
{
	switch ((*LevelGrid)[_Location])
	{
	case LEVEL_SEGMENT_BLANK:
		return true;
	case LEVEL_SEGMENT_PLAYER_FOOD:
		isFoodCollected = true;
		return true;
	case LEVEL_SEGMENT_WALL:
	case LEVEL_SEGMENT_PLAYER_SNAKE:
	case LEVEL_SEGMENT_PLAYER_SNAKE_HEAD: // Odd case check would never happen, never hurts to add it though
		isDead = true;
		return false;
	default:
		return false;
	}
}


void SnakeEntity::Unload()
{
	LevelGrid = nullptr;
	SnakeParts.clear();
	isDead = false;
	isFoodCollected = false;
}


void SnakeEntity::Update(float _DeltaTime)
{
	if (!isDead) // Dont update if dead
	{
		// Clear body from level to update the movement
		ClearBody();

		Move(SNAKE_MOVE_DOWN); // Test snake movement
		// TODO: A* Pathfinding

		// Update snake body to map with new positions
		UpdateBody();
	}
}