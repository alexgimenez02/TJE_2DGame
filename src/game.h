/*  by Javi Agenjo 2013 UPF  javi.agenjo@gmail.com
	This class encapsulates the game, is in charge of creating the game, getting the user input, process the update and render.
*/

#ifndef GAME_H
#define GAME_H

#include "includes.h"

#include "image.h"
#include "input.h"
#include "utils.h"
#include "synth.h"
#include "player.h"
#include "ship.h"
#include "stage.h"
#include "gamemap.h"
#include "world.h"


enum eState {
	MENU = 0,
	GAME = 1,
	TUTORIAL = 2,
	GAMEOVER = 3
};

class Game
{
private:
	void getCurrentStage(Image* framebuffer);
public:
	static Game* instance;
	
	//window
	SDL_Window* window;
	int window_width;
	int window_height;

	//some globals
	long frame;
    float time;
	float elapsed_time;
	int fps;
	bool must_exit, death = false;
	float speed = 20.0f;
	int blink = 0, iter = 0;
	int menu_rec_x = 14, menu_rec_y = 79, menu_rec_h = 59, menu_rec_w = 11;
	eState state = eState::MENU;
	int sprite_width = 14, ship_width = 30;
	int sprite_height = 17, ship_height = 30;
	float jump_speed = 0.0f;
	World world;


	Image font, minifont, sprite, main_menu, gameOver, controls, mapTGA;
	
	//audio
	Synth synth;

	//ctor
	Game( int window_width, int window_height, SDL_Window* window );

	//main functions
	void render( void );
	
	void update( double dt );

	void showFramebuffer(Image* img);

	//events
	void onKeyDown( SDL_KeyboardEvent event );
	void onKeyUp(SDL_KeyboardEvent event);
	void onMouseButtonDown( SDL_MouseButtonEvent event );
	void onMouseButtonUp(SDL_MouseButtonEvent event);
	void onMouseMove(SDL_MouseMotionEvent event);
	void onMouseWheel(SDL_MouseWheelEvent event);
	void onGamepadButtonDown(SDL_JoyButtonEvent event);
	void onGamepadButtonUp(SDL_JoyButtonEvent event);
	void onResize(int width, int height);

	//audio stuff
	void enableAudio(); //opens audio channel to play sound
	void onAudio(float* buffer, unsigned int len, double time, SDL_AudioSpec &audio_spec); //called constantly to fill the audio buffer
};

#endif 