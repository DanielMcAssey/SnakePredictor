#ifndef __ENTITY_SNAKE
#define __ENTITY_SNAKE

class SnakeEntity
{
public:
	SnakeEntity(std::map<std::pair<int, int>, LevelSegment>* _level, int _initial_size, int _level_width, int _level_height);
	~SnakeEntity();

	void Unload();
	void Update(float _DeltaTime);
private:
	std::map<std::pair<int, int>, LevelSegment>* LevelGrid;
	int LevelWidth, LevelHeight;
	std::vector<std::pair<int, int>> SnakeParts;

	void ClearBody();
	void UpdateBody();
};

#endif