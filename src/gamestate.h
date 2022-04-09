#ifndef GAMESTATE_H
#define GAMESTATE_H
#define MAX_ITEMS 100
class gamestate
{
	struct sItem {
		int type; //which item type
		int extra; //to store extra info
	};

	struct sCell { //every cell of the world
		int type; //which type (rock,water,etc)
		int item; //which item is here
	};

	struct sWorld {
		sCell cells[256 * 256];
	};

	struct sPlayer {
		int x; //x position
		int y; //y position
		int energy; //total energy
		int inventory[16]; //max 16 items
	};

	struct sGameData {
		sItem items[MAX_ITEMS]; //available 
		sWorld level[12];
		sPlayer players[4];
	};

	sGameData myGame; //instance of the whole game
};
#endif // !GAMESTATE_H


