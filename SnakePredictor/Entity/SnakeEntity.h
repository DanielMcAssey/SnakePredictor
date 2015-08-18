#ifndef __ENTITY_SNAKE
#define __ENTITY_SNAKE

struct SnakePart
{
	std::pair<int, int> Location;
	SnakeMovement LastMovement;
};

class SnakeEntity
{
public:
	SnakeEntity(std::map<std::pair<int, int>, LevelSegment>* _level, int _initial_size, int _level_width, int _level_height);
	~SnakeEntity();

	void Unload();
	void Update(float _DeltaTime);

	void Move(SnakeMovement _Direction);

	bool isDead;
	bool isFoodCollected;
private:
	void ClearBody();
	void UpdateBody();
	bool CanMove(std::pair<int, int> _Location);

	std::map<std::pair<int, int>, LevelSegment>* LevelGrid;
	int LevelWidth, LevelHeight;
	std::vector<SnakePart*> SnakeParts;
};

#endif