#include "stage.h"

void MainMenuStage::render(Image* framebuffer) 
{
	Game* game = Game::instance;
	Image& bckground = game->main_menu;
	Image& font = game->font;

	blink++;
	framebuffer->drawImage(bckground, 0, 0);
	framebuffer->drawText("It ends", 55, 20, font);
	if (blink % 15 == 0 || blink % 15 == 1 || blink % 15 == 2 || blink % 15 == 3 || blink % 15 == 4 || blink % 15 == 5)
		framebuffer->drawRectangle(menu_rec.x, menu_rec.y, menu_wh.x, menu_wh.y, Color::WHITE);
	framebuffer->drawText("New Game", 15, 80, font);				//draws some text using a bitmap font in an image (assuming every char is 7x9)
	framebuffer->drawText("Controls", 15, 90, font);
	framebuffer->drawText("Exit", 15, 100, font);
}

void MainMenuStage::update()
{
	Game* game = Game::instance;
	if (Input::isKeyPressed(SDL_SCANCODE_UP)) //if key up
	{
		menu_rec.y -= 10;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_DOWN)) //if key up
	{
		menu_rec.y += 10;
	}

	if (menu_rec.y < 80) menu_rec.y = 80;
	else if (menu_rec.y > 100) menu_rec.y = 100;

	if (Input::wasKeyPressed(SDL_SCANCODE_A)) {
		if (menu_rec.y == 80) {
			game->state = 1;
		}
		else if (menu_rec.y == 90)
			game->state = 2;
		else if (menu_rec.y == 100)
			game->must_exit = true;

	}
	Sleep(50);
}

void GameStage::render(Image* framebuffer)
{
	Game* game = Game::instance;
	framebuffer->fill(Color(30, 80, 120));								//fills the image with one color
	game->ship.RenderShip(framebuffer, game->time, game->ship_width, game->ship_height);
	if (!game->ship.getPlayerInside()) game->player.RenderPlayer(framebuffer, game->time, game->sprite_width, game->sprite_height);
}

void GameStage::update()
{
	Game* game = Game::instance;
	Vector2 movement;
	Vector2 ship_movement;
	if (Input::isKeyPressed(SDL_SCANCODE_UP)) //if key up
	{
		movement.y -= game->speed * game->elapsed_time;
		if (game->ship.getPlayerInside()) ship_movement.y -= game->speed * game->elapsed_time;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_DOWN)) //if key down
	{
		movement.y += game->speed * game->elapsed_time;
		if (game->ship.getPlayerInside()) ship_movement.y += game->speed * game->elapsed_time;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_LEFT)) //if key up
	{
		movement.x -= game->speed * game->elapsed_time;
		if (game->ship.getPlayerInside()) ship_movement.x -= game->speed * game->elapsed_time;

	}
	if (Input::isKeyPressed(SDL_SCANCODE_RIGHT)) //if key down
	{
		movement.x += game->speed * game->elapsed_time;
		if (game->ship.getPlayerInside()) ship_movement.x += game->speed * game->elapsed_time;

	}
	game->player.MovePlayer(movement);
	game->player.Jump(game->jump_speed -= game->elapsed_time);
	game->ship.ShipMovement(ship_movement);

	if (Input::isKeyPressed(SDL_SCANCODE_A)) //if key A was pressed
	{
		game->jump_speed = 1.0;
	}
}

void GameOverStage::render(Image* framebuffer)
{
	Game* game = Game::instance;
	Image& bckground = game->gameOver;

	framebuffer->drawImage(bckground, 0, 0);

	game->synth.playSample("data/GameOverSong.wav",1,true);
}

void GameOverStage::update()
{
}

void ControlsStage::render(Image* framebuffer)
{
	Game* game = Game::instance;
	Image& bckground = game->controls;

	framebuffer->drawImage(bckground, 0, 0);

}

void ControlsStage::update()
{
}
