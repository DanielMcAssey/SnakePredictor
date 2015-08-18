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
	tmpPart->NewPart = false;
	SnakeParts.push_back(tmpPart);
	for (int i = 1; i < _initial_size; i++)
	{
		tmpPart = new SnakePart();
		tmpPart->Location = std::make_pair(startPosX + i, startPosY);
		tmpPart->LastMovement = SNAKE_MOVE_LEFT;
		tmpPart->NewPart = false;
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

	if (!Collision(newPosition)) // Make sure we dont collide with anything
	{
		SnakeParts.front()->Location = newPosition; // Update snake head position
		SnakeMovement parentMovement = SnakeParts.front()->LastMovement;
		SnakeMovement oldMovement;
		std::pair<int, int> lastPosition;

		// Update body
		for (std::vector<SnakePart*>::iterator itr = SnakeParts.begin(); itr != SnakeParts.end(); ++itr)
		{
			if (itr == SnakeParts.begin()) // Ignore head
				continue;

			if ((*itr)->NewPart) // Expand snake to add new part
			{
				(*itr)->Location = lastPosition;
				(*itr)->LastMovement = oldMovement;
				(*itr)->NewPart = false;
			}
			else
			{
				lastPosition = (*itr)->Location;

				switch (parentMovement)
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
				oldMovement = (*itr)->LastMovement;
				(*itr)->LastMovement = parentMovement;
				parentMovement = oldMovement;
			}
		}

		SnakeParts.front()->LastMovement = _Direction;
	}
}


bool SnakeEntity::CanMove(LevelSegment _SegmentType)
{
	switch (_SegmentType)
	{
	case LEVEL_SEGMENT_BLANK:
	case LEVEL_SEGMENT_PLAYER_FOOD:
		return true;
	case LEVEL_SEGMENT_WALL:
	case LEVEL_SEGMENT_PLAYER_SNAKE:
	case LEVEL_SEGMENT_PLAYER_SNAKE_HEAD: // Odd case check would never happen, never hurts to add it though
	default:
		return false;
	}
}


bool SnakeEntity::Collision(std::pair<int, int> _Location)
{
	LevelSegment segmentCheck = (*LevelGrid)[_Location];
	switch (segmentCheck)
	{
	case LEVEL_SEGMENT_PLAYER_FOOD:
		isFoodCollected = true;
		break;
	case LEVEL_SEGMENT_WALL:
	case LEVEL_SEGMENT_PLAYER_SNAKE:
	case LEVEL_SEGMENT_PLAYER_SNAKE_HEAD: // Odd case check would never happen, never hurts to add it though
		isDead = true;
		break;
	}

	if (isFoodCollected) // If food is collected increase snake length by 1
	{
		SnakePart* tmpPart = new SnakePart();
		tmpPart->NewPart = true;
		SnakeParts.push_back(tmpPart);
	}

	return !CanMove(segmentCheck);
}

// Path finding
SnakeMovement SnakeEntity::Path_CalculateNextDirection()
{
	// TODO: A* Pathfinding
	return SNAKE_MOVE_DOWN;
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

		// Move the snake to the next direction
		Move(Path_CalculateNextDirection());

		// Update snake body to map with new positions
		UpdateBody();
	}
}