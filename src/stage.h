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
	bool starting = false;
public:
	
	virtual void render(Image* framebuffer);
	virtual void update();
};

class ControlsStage : public Stage {
public:
	virtual void render(Image* framebuffer);
	virtual void update();
};

class GameOverStage : public Stage {
public:
	virtual void render(Image* framebuffer);
	virtual void update();
};

#endif // !STAGE_H

