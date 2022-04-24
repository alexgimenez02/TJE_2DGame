#include "stage.h"

void MainMenuStage::render(Image* framebuffer) 
{
	//Load a game instance
	Game* game = Game::instance;
	//Get the background and the font
	Image& bckground = game->main_menu;
	Image& font = game->font;

	blink++; //Update the blink variable for the rectangle blink
	framebuffer->drawImage(bckground, 0, 0); //Draw background
	framebuffer->drawText("It ends", 55, 20, font); //Draw the title
	if (blink % 15 == 0 || blink % 15 == 1 || blink % 15 == 2 || blink % 15 == 3 || blink % 15 == 4 || blink % 15 == 5)
		framebuffer->drawRectangle(menu_rec.x, menu_rec.y, menu_wh.x, menu_wh.y, Color::WHITE); //Rectangle draw (modified)
	//Draw the options
	framebuffer->drawText("New Game", 15, 80, font); 
	framebuffer->drawText("Tutorial", 15, 90, font);
	framebuffer->drawText("Exit", 15, 100, font);
}

void MainMenuStage::update()
{
	Game* game = Game::instance;
	if (Input::wasKeyPressed(SDL_SCANCODE_UP)) //if key up
	{
		menu_rec.y -= 10; //Update rect position
		
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_DOWN)) //if key up
	{
		menu_rec.y += 10; //Update rect position
		
	}
	//Avoid the rectangle to appear somewhere else
	if (menu_rec.y < 80) menu_rec.y = 80; 
	else if (menu_rec.y > 100) menu_rec.y = 100;

	if (Input::wasKeyPressed(SDL_SCANCODE_A)) {
		//Option select
		if (menu_rec.y == 80) { 
			game->state = eState::GAME;
			game->synth.samples_playback->stop();
			game->synth.playSample("data/Tenebras.wav", 1.25, true);
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
	//Load a game instance
	Game* game = Game::instance;
	//Load the background
	Image& background = game->world.background;
	//Check if the cam follows the player or the ship
	if (!game->world.ship.getPlayerInside()) game->world.camOffset = game->world.player.getPosition() + game->world.playerToCam;
	else game->world.camOffset = game->world.ship.getPosition() + game->world.playerToCam;
	//We draw the background of the stage
	framebuffer->drawImage(background, 0,0, Area(((int)(game->time * 2.0f) % 4)*160, 0, 160, 120));
	//Then we load the map
	game->world.showWorld(framebuffer,game->time);
	//Here, we check which map we are in
	if (game->world.actualMap != game->world.worldMap) {
		//If the letter 'Z' is pressed
		if(trigger)
		{
			//Checks the world
			if(game->world.currentWorld != 2){
				//Shows on screen the scanning planet text
				game->time = 0;
				if ((int)(game->time * 2.0f) % 3 == 0) scanner = "Scanning planet.";
				else if ((int)(game->time * 2.0f) % 3 == 1) scanner = "Scanning planet..";
				else if ((int)(game->time * 2.0f) % 3 == 2) scanner = "Scanning planet...";

				//If the player position does not fit the expected in the world, will appear a message or another
				if (game->world.player.getPosition().x >= 170) {
					//Checks which world is it
					if (game->world.currentWorld == 0) {
						scanner = "Valid planet!"; //Victory condition
						game->synth.samples_playback->stop();
						game->synth.playSample("data/Victoria.wav");
						Sleep(1500);
						win = true; //Bool to reset the game
					}
					else if (game->world.currentWorld == 1) {
						scanner = "Invalid planet!"; //Loss condition
						Sleep(200); 
						game->state = GAMEOVER; //Gameover state
					}
				}
				//If the position is not the correct one:
				if((int)(game->time * 2.0f) % 6 == 5) {
					scanner = "Insuficient height";
					trigger = false;
				}
			}
			//If the map is not the 1 or the 2 (ship whrecker)
			else {
				scanner = "Cannot scan this place";
			}
		}
		if (win) {
			//Win condition, restarts game
			game->state = MENU;
			game->reset_world = true;
			win = false;
			
		}
		//Draws the text from the scanner
		framebuffer->drawText(scanner, 0, 0, game->font);
		//If there was no trigger, we clear the scanner string
		if (!trigger  && (int) (game->time * 2.0f) % 8 == 7) scanner.clear();
	}
	//If the actual map is the world map
	if (game->world.actualMap == game->world.worldMap) {
		//We render each planet
		game->world.planets[0].RenderPlanet(framebuffer, game->time, 50, game->world.camOffset);
		game->world.planets[1].RenderPlanet(framebuffer, game->time, 50, game->world.camOffset);
		game->world.planets[2].RenderPlanet(framebuffer, game->time, 75, game->world.camOffset);
		//We render the ship
		game->world.ship.RenderShip(framebuffer, game->time, game->ship_width, game->ship_height, game->world.camOffset);
		//We get the coordinates of the ship
		string coords = game->world.ship.getPosition().toString();
		//We write in on screen
		framebuffer->drawText(coords, 0, 0,game->minifont, 4, 6);
	}
	else {
		//To avoid the player entering the ship while in a platforming stage
		game->world.ship.setPosition(-10000, -10000);
	}
	//Render player
	if(!game->world.ship.getPlayerInside()) game->world.player.RenderPlayer(framebuffer, game->time, game->sprite_width, game->sprite_height,game->world.camOffset);
	//We render the monster only in the expected stage
	if (game->world.currentWorld == 2) game->world.monster.RenderPlayer(framebuffer, game->time, game->sprite_width, game->sprite_height, game->world.camOffset);
}

void GameStage::update()
{
	Game* game = Game::instance;
	Vector2 movement; //To calculate the player movement
	Vector2 ship_movement; //To calculate the ship movement
	if (Input::isKeyPressed(SDL_SCANCODE_UP)) //if key up
	{
		//Only ship can move upwards
		if (game->world.ship.getPlayerInside()) ship_movement.y -= game->speed * game->elapsed_time;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_DOWN)) //if key down
	{
		//Only ship can move downwards
		if (game->world.ship.getPlayerInside()) ship_movement.y += game->speed * game->elapsed_time;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_LEFT)) //if key up
	{
		//calculate the left movement
		movement.x -= game->speed * game->elapsed_time;
		if (game->world.ship.getPlayerInside()) ship_movement.x -= game->speed * game->elapsed_time;

	}
	if (Input::isKeyPressed(SDL_SCANCODE_RIGHT)) //if key down
	{
		//calculate the right movement
		movement.x += game->speed * game->elapsed_time;
		if (game->world.ship.getPlayerInside()) ship_movement.x += game->speed * game->elapsed_time;

	}

	//Update player and ship position (jump function to check the jumping)
	game->world.player.MovePlayer(movement, &game->world);
	game->world.player.Jump(game->jump_speed -= game->elapsed_time, &game->world);
	game->world.ship.ShipMovement(ship_movement, &game->world);
	
	//Jump action or entering planet
	if (Input::wasKeyPressed(SDL_SCANCODE_A)) //if key A was pressed
	{
		//If player outside ship
		if(!game->world.ship.getPlayerInside()) game->jump_speed = 1.2;
		//If player inside ship
		else 
		{
			//Check for the 3 planets 
			for (int i = 0; i < 3; i++)
			{
				//Distance function
				float dist = game->world.ship.getPosition().distance(game->world.planets[i].pos);
				//Enter the expected planet
				if (dist < 50)
				{
					//We change the world
					game->world.updateMap(i);
					game->world.ship.setPlayerInside();
					
					if (i == 2) { 
						game->synth.samples_playback->stop(); //Stop the previous music
						game->synth.playSample("data/Monster chase.wav", 0.75, true);
					}
					break; //Avoid doing extra iterations
				}

			}
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_Z))
	{
		//If the map isn't the world map
		if (game->world.actualMap != game->world.worldMap) {
			trigger = !trigger; //Activate trigger
		}
		//If it is the worldmap
		if (game->world.actualMap == game->world.worldMap) {
			//Check if player is in distance of ship
			if (game->world.player.distanceToShip(game->world.ship.getPosition()) && game->world.ship.getPlayerInside()) {
				game->world.ship.setPlayerInside();
			}
			//If not, we get outside
			else {
				if (game->world.ship.getPlayerInside()) {
					Vector2 last_ship_pos = game->world.ship.getPosition();
					last_ship_pos.x -= 12.0f;
					game->world.player.setPosition(last_ship_pos);
					game->world.ship.setDirection(UP);
				}
				game->world.ship.setPlayerInside();
			}
		}
	}
	//Debug keys (L -> Player position, I -> Ship position)
	if (Input::wasKeyPressed(SDL_SCANCODE_L))
		cout << "Player pos: " << game->world.player.getPosition().toString() << endl;
	if(Input::wasKeyPressed(SDL_SCANCODE_I))
		cout << "Ship pos: " << game->world.ship.getPosition().toString() << endl;
	//Debug double the player speed
	if (Input::wasKeyPressed(SDL_SCANCODE_K))
		game->world.player.setSpeed(2.0f);

	//Possible game overs
	if(game->world.actualMap != game->world.worldMap)
	{
		//If the player falls down the map
		if ((game->world.currentWorld != 2 && game->world.actualMap->height * 8 <= game->world.player.getPosition().y) || (game->world.currentWorld == 2 && game->world.actualMap->height * 12 <= game->world.player.getPosition().y))
		{
			//Game over
			game->state = GAMEOVER;
		}
	}
	//If the world is the ship whrecker
	if (game->world.currentWorld == 2)
	{
		//Get the distance between player and monster
		float dist = game->world.player.getPosition().distance(game->world.monster.getPosition());
		if (dist < 120) //If distance is less than 120, the monster starts moving 
		{
			game->world.monster.MovePlayer(Vector2(-1, 0), &game->world);
		}
		//If the distance in component x is less than 10, then the monsters kills you, game over state
		if (abs(game->world.player.getPosition().x - game->world.monster.getPosition().x) < 10)
		{
			game->state = GAMEOVER;
		}
	}
}

void GameOverStage::render(Image* framebuffer)
{
	Game* game = Game::instance;
	Image& bckground = game->gameOver;
	//We draw the background
	framebuffer->drawImage(bckground, 0, 0);

	if (once)
	{
		//We play the music once
		game->synth.samples_playback->stop();
		game->synth.playSample("data/GameOverSong.wav", 1, true);
		once = false;
	}
}

void GameOverStage::update()
{
	Game* game = Game::instance;
	//If A is pressed we return to the main menu
	if (Input::wasKeyPressed(SDL_SCANCODE_A))
	{
		game->state = MENU;
		game->synth.stopAll();
		game->reset_world = true; //We reset the world instance, so the next time we play, it restarts
	}
}

void ControlsStage::render(Image* framebuffer)
{
	//We load the tutorial
	Game* game = Game::instance;
	Image& bckground = game->world.tutorial[game->tut_page];

	framebuffer->drawImage(bckground, 0, 0);
	if (game->tut_page == 1) 
	{
		//we render the animated player (not interactive)
		renderPlayerShow(framebuffer);
	}
	else if (game->tut_page == 2)
	{
		//We render the animated ship (Not interactive)
		renderShipShow(framebuffer);
	}

}

void ControlsStage::renderPlayerShow(Image* framebuffer)
{
	Game* game = Game::instance;
	//It loads the sprite and draws the necesary sprites
	Sprite spr = game->world.player.getSprite();
	framebuffer->drawImage(spr.getImage(), 20,56,Area(((int)(game->time * 2.0f) % 6 * spr.getWidth()), 3*spr.getHeight(),spr.getWidth(),spr.getHeight()));
	framebuffer->drawImage(spr.getImage(), 20 + spr.getWidth() + 10, 56, Area(((int)(game->time * 2.0f) % 6 * spr.getWidth()), 2 * spr.getHeight(), spr.getWidth(), spr.getHeight()));
	framebuffer->drawImage(spr.getImage(), 20 + (spr.getWidth() + 12) * 2, 56, Area(((int)(game->time * 2.0f) % 5 * spr.getWidth()), 4 * spr.getHeight(), spr.getWidth(), spr.getHeight()));
}
void ControlsStage::renderShipShow(Image* framebuffer)
{
	//It loads the sprite and draws the necesary sprite
	Game* game = Game::instance;
	Sprite spr = *game->world.ship.getSprite();
	framebuffer->drawImage(spr.getImage(), 22, 55, Area(((int)(game->time * 2.0f) % 4) * spr.getWidth(), ((int)(game->time * 0.5f) % 4 + 1) * spr.getHeight() , spr.getWidth(), spr.getHeight()));
}

void ControlsStage::update()
{
	Game* game = Game::instance;
	//Swap pages
	if (Input::wasKeyPressed(SDL_SCANCODE_LEFT))
	{
		new_page -= 1;
		
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_RIGHT))
	{
		new_page += 1;
	}
	//Swaps the page with a modulus function
	game->tut_page = abs(new_page) % 3;
	//Return to menu
	if (Input::wasKeyPressed(SDL_SCANCODE_Z))
	{
		game->state = MENU;
	}
}
