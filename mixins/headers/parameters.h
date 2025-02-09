#ifndef PARAMETERS_H
#define PARAMETERS_H

#define SERVER_ADDRESS "localhost"
#define SERVER_PORT 8001
#define MAX_CONNECTIONS 20
#define INACTIVITY_TIMEOUT 1000 // in ms

#define WINDOW_SIZE_X 1200
#define WINDOW_SIZE_Y 600

#define SNAKE_CIRCLE_RADIUS 10
#define FOOD_CIRCLE_RADIUS 5

// EXACT background image size in pixels
#define BACKGROUND_SIZE_X 599
#define BACKGROUND_SIZE_Y 519

// GAME_SIZE = n times the background size
#define GAME_SIZE_X 5
#define GAME_SIZE_Y 5

#define MINIMAP_HEIGHT 120
#define SNAKE_CIRCLE_RADIUS_MINIMAP 2

#define FOOD_NUMBER 500

#define ADD_TAIL 4

#define INIT_LENGTH 4

#define LOW_SPEED 1
#define HIGH_SPEED 2
#define BOOST_SPEED 5
#define ROTATION_ANGLE 0.02

#define EPSILON 0.01

#define AI_NUMBER 5

// Network Status Codes
#define OK 200
#define INIT 201
#define CONTROLLER 202
#define POSITION 203
#define END 204

#define DISCONNECT 405
#define GAME_FULL 406

#endif
