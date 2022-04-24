#ifndef STAGE_H
#define STAGE_H


#include "input.h"
#include "game.h"
class Stage {
public:
	virtual void render(Image* framebuffer) {};
	virtual void update() {};
};

class MainMenuStage : public Stage {
private:
	int blink = 0;
	Vector2 menu_rec = Vector2(14,80);
	Vector2 menu_wh = Vector2(59,11);
public:
	virtual void render(Image* framebuffer);
	virtual void update();
};

class GameStage : public Stage {
private:
	string scanner = "";
	bool trigger = false, win = false;
public:
	
	virtual void render(Image* framebuffer);
	virtual void update();
};

class ControlsStage : public Stage {
private: 
	int new_page = 0;
	void renderPlayerShow(Image* framebuffer);
	void renderShipShow(Image* framebuffer);
public:
	virtual void render(Image* framebuffer);
	virtual void update();
};

class GameOverStage : public Stage {
public:
	bool once = true;

	virtual void render(Image* framebuffer);
	virtual void update();
};

#endif // !STAGE_H

