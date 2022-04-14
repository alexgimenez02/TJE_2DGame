#include "game.h"
#include "utils.h"
#include "input.h"
#include "image.h"
#include "sprite.h"

#include <cmath>
using namespace std;

Game* Game::instance = NULL;

Image font;
Image minifont;
Image sprite;
Image ship;
Color bgcolor(130, 80, 100);


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

	font.loadTGA("data/bitmap-font-white.tga"); //load bitmap-font image
	minifont.loadTGA("data/mini-font-white-4x6.tga"); //load bitmap-font image
	player = Player(&Sprite("data/Sprites/spritesheet1.tga", SPRITE_TYPE::PLAYER, 14, 17),0,50);
	//sprite.loadTGA(); //example to load an sprite
	ship.loadTGA("data/Sprites/spritesheet_ship.tga");

	//enableAudio(); //enable this line if you plan to add audio to your application
	//synth.playSample("data/Monster chase.wav",1,true);
	//synth.osc1.amplitude = 0.5;
}/*
void RenderSprite(Game::sPlayer ply, Image* framebuffer, float time, int sprite_width, int sprite_height) {

	//Astronaut:
	// Initial position: x = 0, y = 0, width = 12, height = 17
	
	int sprite_x, sprite_y;
	if (ply.death) {
		sprite_x = ((int)(time * 4.0f) % 4);
		sprite_y = 6;
	}
	else if (ply.isJumping) {
		sprite_x = ((int)(time * 2.0f) % 5);
		sprite_y = ply.dir + 4;
	}
	else {
		sprite_x = ((int)(time * 2.0f) % 6);
		sprite_y = ((ply.isMoving ? 2 : 0) + ply.dir);
	}

	sprite_x *= sprite_width;
	sprite_y *= sprite_height;
	framebuffer->drawImage(sprite, ply.pos.x, ply.pos.y, Area(sprite_x, sprite_y, sprite_width, sprite_height));	//draws only a part of an image
}
*/


void RenderShip(Game::sShip shp, Image* framebuffer, float time, int ship_width, int ship_height) {
	int ship_x, ship_y;
	if (shp.playerInside) {
		if (shp.isMoving) {
			ship_x = ((int)(time * 2.0f) % 3);
			ship_y = shp.dir + 1;
		}
		else {
			ship_x = ((int)(time * 2.0f) % 4);
			ship_y = 0;
		}
	}
	else {
		ship_x = 0;
		ship_y = 0;
	}
	ship_x *= ship_width;
	ship_y *= ship_height;
	framebuffer->drawImage(ship, shp.pos.x, shp.pos.y, Area(ship_x, ship_y, ship_width, ship_height));
}

//what to do when the image has to be draw
void Game::render(void)
{
	//Create a new Image (or we could create a global one if we want to keep the previous frame)
	Image framebuffer(160, 120); //do not change framebuffer size

	//add your code here to fill the framebuffer
	//...

	//some new useful functions
		framebuffer.fill( bgcolor);								//fills the image with one color
		
		
		if (state == 0) {
			blink++;
			if (blink % 15 == 0 || blink % 15 == 1 || blink % 15 == 2 || blink % 15 == 3 || blink % 15 == 4 || blink % 15 == 5) framebuffer.drawRectangle(menu_rec_x, menu_rec_y, menu_rec_h, menu_rec_w, Color::WHITE);
			framebuffer.drawRectangle(menu_rec_x + 1, menu_rec_y + 1, menu_rec_h - 2, menu_rec_w - 2, bgcolor);
			framebuffer.drawText("New Game", 15, 80, font);				//draws some text using a bitmap font in an image (assuming every char is 7x9)
			framebuffer.drawText("Options", 15, 90, font);
		}
		//framebuffer.drawText( toString(time), 1, 10, minifont,4,6);	//draws some text using a bitmap font in an image (assuming every char is 4x6)
		if (state == 1) {
			if (!shipStruct.playerInside) player.RenderPlayer(&framebuffer, time, sprite_width, sprite_height);
			RenderShip(shipStruct, &framebuffer, time, ship_width, ship_height);
		}
	//send image to screen
	showFramebuffer(&framebuffer);
}
void checkIfInWindow(Vector2* mov,int width, int height) {
	mov->x = mov->x > width || mov->x < 0 ? 0 : mov->x;
	mov->y = mov->y > height || mov->y < 0 ? 0 : mov->y;
}
void Game::update(double seconds_elapsed)
{
	//Add here your update method
	//...
	Vector2 movement, ship_movement;

	//Read the keyboard state, to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	if (Input::isKeyPressed(SDL_SCANCODE_UP)) //if key up
	{
		if (state == 1) {
			movement.y -= speed * elapsed_time;
			if (shipStruct.playerInside) ship_movement.y -= speed * elapsed_time;
		}
		if(state == 0)
			menu_rec_y -= 10;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_DOWN)) //if key down
	{
		if (state == 1) {
			movement.y += speed * elapsed_time;
			if (shipStruct.playerInside) ship_movement.y += speed * elapsed_time;
		}
		if(state == 0)
			menu_rec_y += 10;
		
	}
	if (Input::isKeyPressed(SDL_SCANCODE_LEFT)) //if key up
	{
		movement.x -= speed * elapsed_time;
		if (shipStruct.playerInside) ship_movement.x -= speed * elapsed_time;
		
	}
	if (Input::isKeyPressed(SDL_SCANCODE_RIGHT)) //if key down
	{
		movement.x += speed * elapsed_time;
		if (shipStruct.playerInside) ship_movement.x += speed * elapsed_time;
		
	}
	
	player.MovePlayer(movement);
	shipStruct.pos += ship_movement;
	//checkIfInWindow(&player.pos, this->window_width, this->window_height);
	/*if (player.isJumping) {
		player.pos.y -= jump_speed;
		jump_speed -= elapsed_time;
		if (jump_speed < -1.05f) player.isJumping = false;
		
	}
	if (player.death) {
		player.death = ++iter % 10 == 0 ? false : true;
	}*/
	shipStruct.isMoving = ship_movement.x != 0.0f;
	
	
	if (state == 0) {
		if (menu_rec_y < 80) menu_rec_y = 80;
		else if (menu_rec_y > 90) menu_rec_y = 90;
	}

	//example of 'was pressed'
	if (Input::isKeyPressed(SDL_SCANCODE_A)) //if key A was pressed
	{
		if (state == 0) {
			if (menu_rec_y == 80)
				state = 1;
		}
		else {
			//player.isJumping = true;
			jump_speed = 1.0;
		}
	}
	if (Input::isKeyPressed(SDL_SCANCODE_Z)) //if key Z was pressed
	{
		/*if (player.pos.distance(Vector2(shipStruct.pos.x, shipStruct.pos.y)) < 10.0f && !shipStruct.playerInside) {
			shipStruct.playerInside = true;
			Sleep(50);
		}
		else {
			if (shipStruct.playerInside) {
				player.pos.x = shipStruct.pos.x - 12.0f;
				player.pos.y = shipStruct.pos.y;
			}
			shipStruct.playerInside = false;
			Sleep(50);
		}*/
	}
	if (Input::isKeyPressed(SDL_SCANCODE_P)) {
		//player.death = true;
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
