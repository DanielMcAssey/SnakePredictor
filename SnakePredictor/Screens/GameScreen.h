#ifndef __SCREEN_GAME
#define __SCREEN_GAME

enum LevelSegment
{
	LEVEL_SEGMENT_BLANK = 0,
	LEVEL_SEGMENT_WALL,
	LEVEL_SEGMENT_PLAYER_FOOD,
	LEVEL_SEGMENT_PLAYER_SNAKE,
	LEVEL_SEGMENT_PLAYER_SNAKE_HEAD
};

class GameScreen : public BaseScreen
{
public:
	GameScreen(String _name, InputManager* _input, SDL_Window* _window);
	~GameScreen();

	void Load();
	void Unload();
	void Update(float _DeltaTime);
	void Render(SDL_Renderer* _Renderer);
private:
	int ScreenWidth, ScreenHeight;
	int LevelWidth, LevelHeight;
	std::map<std::pair<int, int>, LevelSegment> LevelGrid;

	float SankeUpdateTimer;

	void PlaceFood();
};

#endif