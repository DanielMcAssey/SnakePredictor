/*
// This file is part of SnakePredictor
//
//  (c) Daniel McAssey <hello@glokon.me>
//
// For the full copyright and license information, please view the LICENSE
// file that was distributed with this source code.
*/
#include "stdafx.h"
#include "../stdafx.h"
#include "SnakeEntity.h"

// Determine priority for path node (in the priority queue)
bool operator<(const PathNode & a, const PathNode & b)
{
	return a.Priority > b.Priority;
}

SnakeEntity::SnakeEntity(std::map<std::pair<int, int>, LevelSegment>* _level, int _initial_size, int _level_width, int _level_height, std::pair<int, int>* _level_food_location)
{
	LevelGrid = _level;
	LevelWidth = _level_width;
	LevelHeight = _level_height;
	SnakeFoodLocation = _level_food_location;
	isDead = false;
	isFoodCollected = false;
	numFoodPoints = 0;

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

	SnakeDirections[SNAKE_MOVE_UP] = std::make_pair(0, -1);
	SnakeDirections[SNAKE_MOVE_DOWN] = std::make_pair(0, 1);
	SnakeDirections[SNAKE_MOVE_LEFT] = std::make_pair(-1, 0);
	SnakeDirections[SNAKE_MOVE_RIGHT] = std::make_pair(1, 0);
	
	UpdateBody();
}


SnakeEntity::~SnakeEntity()
{
}


void SnakeEntity::ClearBody()
{
	for (std::vector<std::pair<int, int>>::iterator itr = SnakePartsOld.begin(); itr != SnakePartsOld.end(); ++itr)
	{
		(*LevelGrid)[(*itr)] = LEVEL_SEGMENT_BLANK;
	}
	SnakePartsOld.clear();
}


void SnakeEntity::UpdateBody()
{
	ClearBody(); // Clear the old body and add the new one

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
	for (std::vector<SnakePart*>::iterator itr = SnakeParts.begin(); itr != SnakeParts.end(); ++itr)
	{
		SnakePartsOld.push_back((*itr)->Location);
	}

	std::pair<int, int> newPosition = std::make_pair(SnakeDirections[_Direction].first + SnakeParts.front()->Location.first, SnakeDirections[_Direction].second + SnakeParts.front()->Location.second);

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
				newPosition = std::make_pair(SnakeDirections[parentMovement].first + (*itr)->Location.first, SnakeDirections[parentMovement].second + (*itr)->Location.second);
				(*itr)->Location = newPosition;
				oldMovement = (*itr)->LastMovement;
				(*itr)->LastMovement = parentMovement;
				parentMovement = oldMovement;
			}
		}

		SnakeParts.front()->LastMovement = _Direction;
	}
}

// Kill the snake
void SnakeEntity::Kill()
{
	isDead = true;
	printf("SNAKE: Snake Died!\n");
}


bool SnakeEntity::CanMove(LevelSegment _SegmentType)
{
	switch (_SegmentType)
	{
	case LEVEL_SEGMENT_BLANK:
	case LEVEL_SEGMENT_PLAYER_FOOD:
		return true;
	default:
	case LEVEL_SEGMENT_WALL:
	case LEVEL_SEGMENT_PLAYER_SNAKE:
	case LEVEL_SEGMENT_PLAYER_SNAKE_HEAD: // Odd case check would never happen, never hurts to add it though
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
		Kill();
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


SnakeMovement SnakeEntity::GetOppositeMovement(SnakeMovement _Movement)
{
	switch (_Movement)
	{
	case SNAKE_MOVE_UP:
		return SNAKE_MOVE_DOWN;
	case SNAKE_MOVE_DOWN:
		return SNAKE_MOVE_UP;
	case SNAKE_MOVE_LEFT:
		return SNAKE_MOVE_RIGHT;
	default:
	case SNAKE_MOVE_RIGHT:
		return SNAKE_MOVE_LEFT;
	}
}

// Path Finding Algorithm
// A* Path finding algorithm originally from: http://code.activestate.com/recipes/577457-a-star-shortest-path-algorithm/
// TODO: Fix this method, it attempts to collide with it self causing it to die.
bool SnakeEntity::CalculatePath(std::pair<int, int> _ToGridReference)
{
	std::priority_queue<PathNode> possibleOpenNodesQueue[2];
	int queueIndex = 0;
	PathNode* gridNode;
	PathNode* gridChildNode;
	int gridX, gridY, xDirection, yDirection;
	std::pair<int, int> gridLocation, gridDirection, startPosition;
	startPosition = SnakeParts.front()->Location;

	// Clear any remaining paths from old calculations
	SnakePath.clear();

	// Clear nodes
	PathClosedNodes.clear();
	PathOpenNodes.clear();

	gridNode = new PathNode(startPosition, 0, 0);
	gridNode->UpdatePriority(_ToGridReference);

	possibleOpenNodesQueue[queueIndex].push(*gridNode);
	PathOpenNodes[startPosition] = gridNode->Priority; // Mark first point

	while (!possibleOpenNodesQueue[queueIndex].empty())
	{
		gridNode = new PathNode(possibleOpenNodesQueue[queueIndex].top().Position, possibleOpenNodesQueue[queueIndex].top().Depth, possibleOpenNodesQueue[queueIndex].top().Priority);
		gridX = gridNode->Position.first;
		gridY = gridNode->Position.second;
		gridLocation = std::make_pair(gridX, gridY);

		possibleOpenNodesQueue[queueIndex].pop();
		PathOpenNodes[gridLocation] = 0;
		PathClosedNodes[gridLocation] = true;

		if (gridLocation == _ToGridReference)
		{
			while (gridLocation != startPosition)
			{
				// Fill Snake path
				SnakeMovement tmpMovement = PathDirections[gridLocation];
				gridX += SnakeDirections[tmpMovement].first;
				gridY += SnakeDirections[tmpMovement].second;
				gridLocation = std::make_pair(gridX, gridY);
				SnakePath.push_back(GetOppositeMovement(tmpMovement));
			}
			delete gridNode;
			// Empty unused nodes
			while (!possibleOpenNodesQueue[queueIndex].empty())
			{
				possibleOpenNodesQueue[queueIndex].pop();
			}
			printf("SNAKE (FOOD FOUND): X: %i Y: %i\n", gridX, gridY);
			return true;
		}

		for (int i = 0; i < SnakeDirections.size(); i++)
		{
			xDirection = gridX + SnakeDirections[(SnakeMovement)i].first;
			yDirection = gridY + SnakeDirections[(SnakeMovement)i].second;
			gridDirection = std::make_pair(xDirection, yDirection);

			// Check to see if snake can move there or that the node isnt closed
			if (CanMove((*LevelGrid)[gridDirection]) || !PathClosedNodes[gridDirection])
			{
				gridChildNode = new PathNode(gridDirection, gridNode->Depth, gridNode->Priority);
				gridChildNode->NextDepth((SnakeMovement)i);
				gridChildNode->UpdatePriority(_ToGridReference);

				if (PathOpenNodes.count(gridDirection) == 0)
				{
					PathOpenNodes[gridDirection] = gridChildNode->Priority;
					possibleOpenNodesQueue[queueIndex].push(*gridChildNode);
					PathDirections[gridDirection] = GetOppositeMovement((SnakeMovement)i);
				}
				else if (PathOpenNodes[gridDirection] > gridChildNode->Priority)
				{
					PathOpenNodes[gridDirection] = gridChildNode->Priority;
					PathDirections[gridDirection] = GetOppositeMovement((SnakeMovement)i);

					while (possibleOpenNodesQueue[queueIndex].top().Position != gridDirection)
					{
						possibleOpenNodesQueue[1 - queueIndex].push(possibleOpenNodesQueue[queueIndex].top());
						possibleOpenNodesQueue[queueIndex].pop();
					}
					possibleOpenNodesQueue[queueIndex].pop();

					if (possibleOpenNodesQueue[queueIndex].size() > possibleOpenNodesQueue[1 - queueIndex].size())
					{
						queueIndex = 1 - queueIndex;
					}

					while (!possibleOpenNodesQueue[queueIndex].empty())
					{
						possibleOpenNodesQueue[1 - queueIndex].push(possibleOpenNodesQueue[queueIndex].top());
						possibleOpenNodesQueue[queueIndex].pop();
					}

					queueIndex = 1 - queueIndex;
					possibleOpenNodesQueue[queueIndex].push(*gridChildNode);
				}
				else
				{
					delete gridChildNode;
				}
			}
		}
		delete gridNode;
	}
	return false;
}


void SnakeEntity::MoveOnPath()
{
	if (!SnakePath.empty() && !isFoodCollected) // Move only if there is a next path
	{
		Move(SnakePath.front());
		SnakePath.erase(SnakePath.begin());
	}
	else
	{
		if (!CalculatePath(std::make_pair(SnakeFoodLocation->first, SnakeFoodLocation->second))) // Calculate route to food
		{
			// Cant calculate path, so move to any free space, to see if we can create a path.
			if (!MoveToFreeSpace())
			{
				// Cant move to free space, so set to dead
				Kill();
			}
		}
	}
}

// Move to any possible free space, this could be improved on.
bool SnakeEntity::MoveToFreeSpace()
{
	std::vector<int> movesAvailable;
	for (std::map<SnakeMovement, std::pair<int, int>>::iterator itr = SnakeDirections.begin(); itr != SnakeDirections.end(); ++itr)
		movesAvailable.push_back((int)itr->first);

	while (movesAvailable.size() > 0)
	{
		int randomIndex = (rand() % (movesAvailable.size()));
		SnakeMovement moveDirection = (SnakeMovement)movesAvailable[randomIndex];
		movesAvailable.erase(movesAvailable.begin() + randomIndex);
		std::pair<int, int> newPosition = std::make_pair(SnakeDirections[moveDirection].first + SnakeParts.front()->Location.first, SnakeDirections[moveDirection].second + SnakeParts.front()->Location.second);
		if (CanMove((*LevelGrid)[newPosition]))
		{
			Move((SnakeMovement)moveDirection);
			return true;
		}
	}
	return false;
}


void SnakeEntity::Unload()
{
	LevelGrid = nullptr;
	SnakeParts.clear();
	SnakePath.clear();
	isDead = false;
	isFoodCollected = false;
}


void SnakeEntity::Update(float _DeltaTime)
{
	if (!isDead) // Dont update if dead
	{
		// Move the snake on the calculated path, or if no path exists calculate one.
		MoveOnPath();

		// Update snake body to map with new positions
		UpdateBody();
	}
}