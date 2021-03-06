/*
// This file is part of SnakePredictor
//
//  (c) Daniel McAssey <hello@glokon.me>
//
// For the full copyright and license information, please view the LICENSE
// file that was distributed with this source code.
*/
#ifndef __GLOBAL_ENUMS
#define __GLOBAL_ENUMS

enum LevelSegment
{
	LEVEL_SEGMENT_BLANK = 0,
	LEVEL_SEGMENT_WALL,
	LEVEL_SEGMENT_PLAYER_FOOD,
	LEVEL_SEGMENT_PLAYER_SNAKE,
	LEVEL_SEGMENT_PLAYER_SNAKE_HEAD
};

enum SnakeMovement
{
	SNAKE_MOVE_UP = 0,
	SNAKE_MOVE_DOWN,
	SNAKE_MOVE_LEFT,
	SNAKE_MOVE_RIGHT
};

#endif