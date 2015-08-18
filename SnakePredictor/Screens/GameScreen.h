#ifndef __SCREEN_GAME
#define __SCREEN_GAME

#include "../Entity/SnakeEntity.h"

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
	void PlaceFood();
	void CollectFood();

	int ScreenWidth, ScreenHeight;
	int LevelWidth, LevelHeight;
	std::map<std::pair<int, int>, LevelSegment> LevelGrid;
	std::pair<int, int> LevelFoodLocation;

	float SankeUpdateTimer;
	SnakeEntity* EntSnake;
};

#endif