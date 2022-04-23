#include "game.h"


#include <cmath>
using namespace std;

Game* Game::instance = NULL;
Color bgcolor(30, 80, 120);
Stage* current_stage;
MainMenuStage* main_menu_stage;
GameStage* game_stage;
ControlsStage* controls_stage;
GameOverStage* game_over_stage;
//Planet plt;


Game::Game(int window_width, int window_height, SDL_Window* window)
{
	this->window_width = window_width;
	this->window_height = window_height;
	this->window = window;
	instance = this;
	must_exit = false;

	fps = 0;
	frame = 0;
	time = 0.0f;
	elapsed_time = 0.0f;

	//plt = Planet(Vector2(0, 0), &Sprite("data/Sprites/MainPlanet.tga", SPRITE_TYPE::PLANET,49,49));
	
	main_menu.loadTGA("data/main_menu.tga"); 
	font.loadTGA("data/bitmap-font-white.tga"); //load bitmap-font image
	minifont.loadTGA("data/mini-font-white-4x6.tga"); //load bitmap-font image
	gameOver.loadTGA("data/game_over.tga");
	
	enableAudio(); //enable this line if you plan to add audio to your application
	
	main_menu_stage = new MainMenuStage();
	game_stage = new GameStage();
	controls_stage = new ControlsStage();
	game_over_stage = new GameOverStage();
	current_stage = main_menu_stage;
	world = World();
	//synth.playSample("data/Monster chase.wav",1,true);
	//synth.osc1.amplitude = 0.5;
}
//what to do when the image has to be draw
void Game::render(void)
{
	//Create a new Image (or we could create a global one if we want to keep the previous frame)
	Image framebuffer(160, 120); //do not change framebuffer size

	//add your code here to fill the framebuffer
	//...

	//some new useful functions
		
		
	
	getCurrentStage(&framebuffer);
	//send image to screen
	showFramebuffer(&framebuffer);
}
void Game::getCurrentStage(Image* framebuffer) {
	if (state == eState::MENU)
		current_stage = main_menu_stage;

	//framebuffer.drawText( toString(time), 1, 10, minifont,4,6);	//draws some text using a bitmap font in an image (assuming every char is 4x6)
	if (state == eState::GAME) {
		current_stage = game_stage;
	}
	if (state == eState::TUTORIAL)
		current_stage = controls_stage;
	if (state == eState::GAMEOVER)
		current_stage = game_over_stage;
	current_stage->render(framebuffer);
}
void checkIfInWindow(Vector2* mov,int width, int height) {
	mov->x = mov->x > width || mov->x < 0 ? 0 : mov->x;
	mov->y = mov->y > height || mov->y < 0 ? 0 : mov->y;
}
void Game::update(double seconds_elapsed)
{
	current_stage->update();
	//Add here your update method
	//...
	Vector2 movement, ship_movement;

	//Read the keyboard state, to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	int swap = -1;
	if (Input::wasKeyPressed(SDL_SCANCODE_1)) //if key up
	{		
		swap = 0;
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_2)) //if key down
	{
		swap = 1;
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_3)) //if key up
	{		
		swap = 2;
		
	}
	if (Input::isKeyPressed(SDL_SCANCODE_RIGHT)) //if key down
	{
	}
	world.updateMap(swap);
	if(swap != -1) cout << "World changed!" << "\nNow in: " << world.currentWorld << endl;

	//example of 'was pressed'
	if (Input::isKeyPressed(SDL_SCANCODE_A)) //if key A was pressed
	{
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_Z)) //if key Z was pressed
	{
		if (world.player.distanceToShip(world.ship.getPosition()) && world.ship.getPlayerInside()) {
			world.ship.setPlayerInside();
		}
		else {
			if (world.ship.getPlayerInside()) {
				Vector2 last_ship_pos = world.ship.getPosition();
				last_ship_pos.x -= 12.0f;
				world.player.setPosition(last_ship_pos);
				world.ship.setDirection(UP);
			}
			world.ship.setPlayerInside();
		}
	}
	if (Input::isKeyPressed(SDL_SCANCODE_P)) {
		state = eState::GAMEOVER;
	}
	//to read the gamepad state
	if (Input::gamepads[0].isButtonPressed(A_BUTTON)) //if the A button is pressed
	{
	}

	if (Input::gamepads[0].direction & PAD_UP) //left stick pointing up
	{
		bgcolor.set(0, 255, 0);
	}
}

//Keyboard event handler (sync input)
void Game::onKeyDown( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: must_exit = true; break; //ESC key, kill the app
	}
}

void Game::onKeyUp(SDL_KeyboardEvent event)
{
}

void Game::onGamepadButtonDown(SDL_JoyButtonEvent event)
{

}

void Game::onGamepadButtonUp(SDL_JoyButtonEvent event)
{

}

void Game::onMouseMove(SDL_MouseMotionEvent event)
{
}

void Game::onMouseButtonDown( SDL_MouseButtonEvent event )
{
}

void Game::onMouseButtonUp(SDL_MouseButtonEvent event)
{
}

void Game::onMouseWheel(SDL_MouseWheelEvent event)
{
}

void Game::onResize(int width, int height)
{
    std::cout << "window resized: " << width << "," << height << std::endl;
	glViewport( 0,0, width, height );
	window_width = width;
	window_height = height;
}

//sends the image to the framebuffer of the GPU
void Game::showFramebuffer(Image* img)
{
	static GLuint texture_id = -1;
	static GLuint shader_id = -1;
	if (!texture_id)
		glGenTextures(1, &texture_id);

	//upload as texture
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, img->width, img->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);

	glDisable(GL_CULL_FACE); glDisable(GL_DEPTH_TEST); glEnable(GL_TEXTURE_2D);
	float startx = -1.0; float starty = -1.0;
	float width = 2.0; float height = 2.0;

	//center in window
	float real_aspect = window_width / (float)window_height;
	float desired_aspect = img->width / (float)img->height;
	float diff = desired_aspect / real_aspect;
	width *= diff;
	startx = -diff;

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(startx, starty + height);
	glTexCoord2f(1.0, 0.0); glVertex2f(startx + width, starty + height);
	glTexCoord2f(1.0, 1.0); glVertex2f(startx + width, starty);
	glTexCoord2f(0.0, 1.0); glVertex2f(startx, starty);
	glEnd();

	/* this version resizes the image which is slower
	Image resized = *img;
	//resized.quantize(1); //change this line to have a more retro look
	resized.scale(window_width, window_height);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if (1) //flip
	{
	glRasterPos2f(-1, 1);
	glPixelZoom(1, -1);
	}
	glDrawPixels( resized.width, resized.height, GL_RGBA, GL_UNSIGNED_BYTE, resized.pixels );
	*/
}

//AUDIO STUFF ********************

SDL_AudioSpec audio_spec;

void AudioCallback(void*  userdata,
	Uint8* stream,
	int    len)
{
	static double audio_time = 0;

	memset(stream, 0, len);//clear
	if (!Game::instance)
		return;

	Game::instance->onAudio((float*)stream, len / sizeof(float), audio_time, audio_spec);
	audio_time += len / (double)audio_spec.freq;
}

void Game::enableAudio()
{
	SDL_memset(&audio_spec, 0, sizeof(audio_spec)); /* or SDL_zero(want) */
	audio_spec.freq = 48000;
	audio_spec.format = AUDIO_F32;
	audio_spec.channels = 1;
	audio_spec.samples = 1024;
	audio_spec.callback = AudioCallback; /* you wrote this function elsewhere. */
	if (SDL_OpenAudio(&audio_spec, &audio_spec) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		exit(-1);
	}
	SDL_PauseAudio(0);
}

void Game::onAudio(float *buffer, unsigned int len, double time, SDL_AudioSpec& audio_spec)
{
	//fill the audio buffer using our custom retro synth
	synth.generateAudio(buffer, len, audio_spec);
}

