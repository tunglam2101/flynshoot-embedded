﻿#include "app.h"
#include "task_list.h"
#include "Adafruit_ssd1306syp.h"
#include "message.h"
#include "timer.h"

#include "flynshoot_ship.h"
#include "flynshoot_missile.h"
#include "flynshoot_mines.h"
#include "flynshoot_display.h"
#include "flynshoot_game_control.h"

// prototype
void spawnMissile(uint8_t shipX, uint8_t shipY);
void clearMissile(void);
void renderMissile(void);
bool MISSILE_HIT_TUNNEL(void);
bool MISSILE_HIT_MINE(void);

uint8_t missile_bmp[MISSILE_LENGTH];
uint8_t missileX, missileY;
uint8_t score;
static bool initBmp = false;

void task_control_missile(ak_msg_t* msg) {
	switch(msg->sig) {
		case(AC_MISSILE_ARMED): {
			spawnMissile((uint8_t)shipx, (uint8_t)shipy);
		}
			break;

		case(AC_MISSILE_FLYING): {
			if(missileX + MISSILE_SPEED_X < tunnelWidth) {
				missileX += MISSILE_SPEED_X;
				timer_set(AC_MISSILE_ID, AC_MISSILE_FLYING, DEFAULT_TIME_TICK, TIMER_PERIODIC);
				renderMissile();
			}

			else if (MISSILE_HIT_MINE()) {
				score++;
				task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_EXPLODING);
			}

			else if  (MISSILE_HIT_TUNNEL()) {
				task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_EXPLODING);
			}

			else {
				task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_ARMED);
			}
		}
			break;

		case(AC_MISSILE_EXPLODING) : {
			clearMissile();
			renderMissile();
			task_post_pure_msg(AC_MISSILE_ID, AC_MISSILE_ARMED);
			break;
		}

		default:
			break;
	}
}


void spawnMissile(uint8_t shipX, uint8_t shipY){
	if(!initBmp) {
		for(uint8_t i = 0; i < MISSILE_LENGTH; i++) {
			missile_bmp[i] = 1;
		}
		initBmp = true;
	}
	missileX = shipX;
	missileY = shipY;
}

void clearMissile (void) {
	initBmp = false;
	for(uint8_t i = 0; i < MISSILE_LENGTH; i++) {
		missile_bmp[i] = 0;
	}
}

void renderMissile (void) {
	for(uint8_t i = 0; i < MISSILE_LENGTH; i++) {
		screenObj.drawPixel(missileX + i, missileY, WHITE);
	}
}

bool MISSILE_HIT_TUNNEL (void) {
	// TODO: check if missile hits tunnel
	// return true if yes, otw false
}

bool MISSILE_HIT_MINE(void) {
	// TODO: check if missile hits mine
	// return true if yes, otw false
}

