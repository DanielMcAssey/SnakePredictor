#ifndef __ENTITY_SNAKE
#define __ENTITY_SNAKE

struct SnakePart
{
	std::pair<int, int> Location;
	SnakeMovement LastMovement;
	bool NewPart;
};

class SnakeEntity
{
public:
	SnakeEntity(std::map<std::pair<int, int>, LevelSegment>* _level, int _initial_size, int _level_width, int _level_height);
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

	SnakeMovement Path_CalculateNextDirection();

	std::map<std::pair<int, int>, LevelSegment>* LevelGrid;
	int LevelWidth, LevelHeight;
	std::vector<SnakePart*> SnakeParts;
};

#endif