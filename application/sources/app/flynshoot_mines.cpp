#include "flynshoot_mines.h"
#include "flynshoot_display.h"
#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "timer.h"

coord_t	mines_coords[NUM_MINES];
//static uint8_t mine_ctr = 0;
//static uint8_t oldest_mine = 0;

// prototypes
void updateMines (void);
void renderMines (void);
void minesInit (void);
uint8_t minePassScr (void);

void task_control_mines(ak_msg_t* msg) {
	switch(msg->sig) {
	case AC_MINES_INIT: {
		minesInit();
		task_post_pure_msg(AC_MINES_ID, AC_MINES_ARMED);
	}
		break;

	case AC_MINES_ARMED: {
		updateMines();
		task_post_pure_msg(AC_MINES_ID, AC_MINES_FLYING);
	}
		break;

	case AC_MINES_FLYING: {
		for(uint8_t i = 0; i < NUM_MINES; i++) {
			mines_coords[i].x -= MINE_SPEED_X;
		}
		renderMines();
		timer_set(AC_MINES_ID, AC_MINES_ARMED, 50, TIMER_PERIODIC);
	}
		break;

	case AC_MINES_EXPLODING: {

	}
		break;

	default:
		break;
	}
}

uint8_t minePassScr (void) {
	for(uint8_t i = 0; i < NUM_MINES; i++) {
		if(mines_coords[i].x + mineWidth < 0 || mines_coords[i].available == false) {
			return i;
		}
	}
	return NUM_MINES;
}

void minesInit (void) {
	mines_coords[0].x = tunnelWidth + mineWidth - 2 + (rand() % (tunnelWidth + 1));
	mines_coords[0].y = rand() % (BOT_TUNNEL_HIGHEST - TOP_TUNNEL_LOWEST + 1) + TOP_TUNNEL_LOWEST;
	for(uint8_t i = 1; i < NUM_MINES; i++) {
		mines_coords[i].x = mines_coords[i-1].x + (rand() % (tunnelWidth - MINE_MIN_DIST_X + 1)) + MINE_MIN_DIST_X;
		mines_coords[i].y = rand() % (BOT_TUNNEL_HIGHEST - TOP_TUNNEL_LOWEST + 1) + TOP_TUNNEL_LOWEST;;
		mines_coords[i].available = true;
	}
}

void renderMines (void) {
	for(uint8_t i = 1; i < NUM_MINES; i++) {
		if(mines_coords[i].available == true && mines_coords[i].x < tunnelWidth) {
			screenObj.drawSun(mines_coords[i].x + MINE_SPEED_X, mines_coords[i].y, mineWidth, BLACK);
			screenObj.drawSun(mines_coords[i].x, mines_coords[i].y, mineWidth, WHITE);
		}
		else {
			APP_DBG_SIG("CLEAR MINE!\n");
			screenObj.drawSun(mines_coords[i].x + MINE_SPEED_X, mines_coords[i].y, mineWidth, BLACK);
			screenObj.drawSun(mines_coords[i].x, mines_coords[i].y, mineWidth, BLACK);
		}
	}
}

void updateMines (void) {
	uint8_t mine_check = minePassScr();
	if(mine_check != NUM_MINES) {
		mines_coords[mine_check].x = tunnelWidth + mineWidth - 2 + (rand() % (tunnelWidth - MINE_MIN_DIST_X + 1)) + MINE_MIN_DIST_X;
		mines_coords[mine_check].y = rand() % (BOT_TUNNEL_HIGHEST - TOP_TUNNEL_LOWEST + 1) + TOP_TUNNEL_LOWEST;
		mines_coords[mine_check].available = true;
	}
}
