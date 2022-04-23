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
	if (Input::wasKeyPressed(SDL_SCANCODE_UP)) //if key up
	{
		menu_rec.y -= 10;
		
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_DOWN)) //if key up
	{
		menu_rec.y += 10;
		
	}

	if (menu_rec.y < 80) menu_rec.y = 80;
	else if (menu_rec.y > 100) menu_rec.y = 100;

	if (Input::wasKeyPressed(SDL_SCANCODE_RETURN)) {
		if (menu_rec.y == 80) {
			game->state = eState::GAME;
		}
		else if (menu_rec.y == 90)
			game->state = eState::TUTORIAL;
		else if (menu_rec.y == 100)
			game->must_exit = true;
		if (!game->must_exit) Sleep(1000);
	}

}

void GameStage::render(Image* framebuffer)
{
	Game* game = Game::instance;

	game->world.camOffset = game->world.player.getPosition() + game->world.playerToCam;
	framebuffer->drawImage(game->world.background, 0,0, Area(((int)(game->time * 2.0f) % 4)*160, 120, 160, 120));
	game->world.showWorld(framebuffer,game->time);
	//game->world.ship.RenderShip(framebuffer, game->time, game->ship_width, game->ship_height);
	if (!game->world.ship.getPlayerInside()) game->world.player.RenderPlayer(framebuffer, game->time, game->sprite_width, game->sprite_height,game->world.camOffset);
}

void GameStage::update()
{
	Game* game = Game::instance;
	Vector2 movement;
	Vector2 ship_movement;
	if (Input::isKeyPressed(SDL_SCANCODE_UP)) //if key up
	{
		//movement.y -= game->speed * game->elapsed_time;
		if (game->world.ship.getPlayerInside()) ship_movement.y -= game->speed * game->elapsed_time;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_DOWN)) //if key down
	{
		//movement.y += game->speed * game->elapsed_time;
		if (game->world.ship.getPlayerInside()) ship_movement.y += game->speed * game->elapsed_time;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_LEFT)) //if key up
	{
		movement.x -= game->speed * game->elapsed_time;
		if (game->world.ship.getPlayerInside()) ship_movement.x -= game->speed * game->elapsed_time;

	}
	if (Input::isKeyPressed(SDL_SCANCODE_RIGHT)) //if key down
	{
		movement.x += game->speed * game->elapsed_time;
		if (game->world.ship.getPlayerInside()) ship_movement.x += game->speed * game->elapsed_time;

	}
	game->world.player.MovePlayer(movement, &game->world);
	game->world.player.Jump(game->jump_speed -= game->elapsed_time, &game->world);
	game->world.ship.ShipMovement(ship_movement);

	if (Input::wasKeyPressed(SDL_SCANCODE_A)) //if key A was pressed
	{
		game->jump_speed = 1.2;
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_L))
		cout << "Player pos: " << game->world.player.getPosition().toString() << endl;
	if (Input::wasKeyPressed(SDL_SCANCODE_K))
		game->world.player.setSpeed(2.0f);

	if ((game->world.currentWorld != 2 && game->world.actualMap->height * 8 <= game->world.player.getPosition().y) || (game->world.currentWorld == 2 && game->world.actualMap->height * 12 <= game->world.player.getPosition().y))
	{
		cout << "You died!" << endl;
		game->state = GAMEOVER;
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
