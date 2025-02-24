#include "app.h"
#include "task_list.h"
#include "app_dbg.h"

#include "flynshoot_display.h"
#include "flynshoot_ship.h"

int topTunnel[tunnelWidth];
int botTunnel[tunnelWidth];
int score;
Adafruit_ssd1306syp screenObj;

static void drawTunnel();
static void updateTunnel();

void task_control_display(ak_msg_t* msg) {
	switch (msg->sig) {
		case AC_FLYNSHOOT_INIT:
		{
			score = 0;
			for(int i = 0; i < tunnelWidth; i++)
			{
				topTunnel[i] = 0;
				botTunnel[i] = 0;
			}
			screenObj.initialize();
			screenObj.clear();
			screenObj.display_on();
			screenObj.update();
			task_post_pure_msg(AC_DISPLAY_ID,AC_FLYNSHOOT_DRAW_TUNNEL);
		}
		break;
		case AC_FLYNSHOOT_DRAW_TUNNEL:
		{
			if(gameOver) {
				task_post_pure_msg(AC_GAME_CONTROL_ID, AC_GAME_CONTROL_OVER);
			}
			drawTunnel();
			checkDeath();
		}
		break;

		case AC_FLYNSHOOT_UPDATE_TUNNEL:
		{
			//APP_DBG("UPDATE TUNNEL \n");
			updateTunnel();
			task_post_pure_msg(AC_DISPLAY_ID,AC_FLYNSHOOT_DRAW_TUNNEL);
		}
		break;
	}
}

static void updateTunnel(){
	for(int i = 0; i < tunnelWidth-1; i++)
	{
		topTunnel[i] = topTunnel[i+1];
		botTunnel[i] = botTunnel[i+1];
	}
	int topOldBlocks = topTunnel[tunnelWidth-2];
	int botOldBlocks = botTunnel[tunnelWidth-2];
	int topNewBlocks = topOldBlocks + ((rand()%3)-1);
	int botNewBlocks = botOldBlocks + ((rand()%3)-1);

	if(topNewBlocks > tunnelHeight) topNewBlocks--;
	if(botNewBlocks > tunnelHeight) botNewBlocks--;
	if(topNewBlocks < 0) topNewBlocks=0;
	if(botNewBlocks < 0) botNewBlocks=0;
	topTunnel[tunnelWidth-1] = topNewBlocks;
	botTunnel[tunnelWidth-1] = botNewBlocks;
	score++;
	screenObj.setCursor(85,5);
	screenObj.print("Score");
	screenObj.setCursor(85,15);
	screenObj.fillRect(85,15,40,10,BLACK);
	screenObj.print(score);
}

bool checkTunnelOverlap(uint8_t x, uint8_t y)
{
	if(y<=20)
	{
		int sizeTunnel = 2*topTunnel[x];
		if(sizeTunnel >= y) return true;
	}

	if(y>=40)
	{
		int sizeTunnel = 2*botTunnel[x];
		if(sizeTunnel >= 60-y) return true;
	}
	return false;
}


static void drawTunnel(){
	for(int i = 0; i < tunnelWidth; i++)
	{
		screenObj.fillRect(i,-1,2,10,BLACK);
		screenObj.fillRect(i,-1,2,2*topTunnel[i],WHITE);
	}
	for(int i = 0; i < tunnelWidth; i++)
	{
		screenObj.fillRect(i,60,2,-10,BLACK);
		screenObj.fillRect(i,60,2,2*-botTunnel[i],WHITE);
	}
	drawShip();
}
