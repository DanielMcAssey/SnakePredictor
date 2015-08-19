#ifndef __ENTITY_SNAKE
#define __ENTITY_SNAKE

struct SnakePart
{
	std::pair<int, int> Location;
	SnakeMovement LastMovement;
	bool NewPart;
};

// A* Path finding algorithm originally from: http://code.activestate.com/recipes/577457-a-star-shortest-path-algorithm/
class PathNode
{
public:
	PathNode(std::pair<int, int> _Position, int _Depth, int _Priority) { Position = _Position; Depth = _Depth; Priority = _Priority; }
	std::pair<int, int> Position;
	int Depth;
	int Priority;

	void NextDepth(SnakeMovement _Direction)
	{
		Depth += 10;
	}
	
	void UpdatePriority(std::pair<int, int> _Destination)
	{
		Priority = Depth + Estimate(_Destination) * 10; //A*
	}

	int Estimate(std::pair<int, int> _Destination)
	{
		double xDistance, yDistance;
		int totalDistance;
		xDistance = (double)(_Destination.first - Position.first);
		yDistance = (double)(_Destination.second - Position.second);
		// Euclidian Distance
		totalDistance = (int)sqrt(xDistance * xDistance + yDistance * yDistance);
		// Manhattan Distance
		//totalDistance = (int)(abs(xDistance) + abs(yDistance));
		// Chebyshev Distance
		//totalDistance = (int)(max(abs(xDistance), abs(yDistance)));
		return totalDistance;
	}
};

class SnakeEntity
{
public:
	SnakeEntity(std::map<std::pair<int, int>, LevelSegment>* _level, int _initial_size, int _level_width, int _level_height, std::pair<int, int>* _level_food_location);
	~SnakeEntity();

	void Unload();
	void Update(float _DeltaTime);

	bool isDead;
	bool isFoodCollected;
private:
	void Move(SnakeMovement _Direction);
	void ClearBody();
	void UpdateBody();
	bool CanMove(LevelSegment _SegmentType);
	bool Collision(std::pair<int, int> _Location);
	SnakeMovement GetOppositeMovement(SnakeMovement _Movement);
	void MoveOnPath();

	bool CalculatePath_Try1(std::pair<int, int> _ToGridReference);
	bool CalculatePath_Try2(std::pair<int, int> _ToGridReference);

	std::map<std::pair<int, int>, LevelSegment>* LevelGrid;
	int LevelWidth, LevelHeight;
	std::vector<SnakePart*> SnakeParts;
	std::vector<std::pair<int, int>> SnakePartsOld;
	std::vector<SnakeMovement> SnakePath;
	std::map<SnakeMovement, std::pair<int, int>> SnakeDirections;
	std::pair<int, int>* SnakeFoodLocation;

	std::map<std::pair<int, int>, int> PathOpenNodes;
	std::map<std::pair<int, int>, int> PathClosedNodes;
	std::map<std::pair<int, int>, SnakeMovement> PathDirections;
};

#endif