#include "task_list.h"
#include "timer.h"

task_t app_task_table[] = {
	/*************************************************************************/
	/* SYSTEM TASK */
	/*************************************************************************/
	{TASK_TIMER_TICK_ID,		TASK_PRI_LEVEL_7,		task_timer_tick		},

	/*************************************************************************/
	/* APP TASK */
	/*************************************************************************/
	{AC_TASK_FW_ID			,	TASK_PRI_LEVEL_2	,	task_fw				},
	{AC_TASK_SHELL_ID		,	TASK_PRI_LEVEL_2	,	task_shell			},
	{AC_TASK_LIFE_ID		,	TASK_PRI_LEVEL_6	,	task_life			},
	{AC_TASK_IF_ID			,	TASK_PRI_LEVEL_4	,	task_if				},
	{AC_TASK_RF24_IF_ID		,	TASK_PRI_LEVEL_4	,	task_rf24_if		},
	{AC_TASK_UART_IF_ID		,	TASK_PRI_LEVEL_4	,	task_uart_if		},
	{AC_TASK_DBG_ID			,	TASK_PRI_LEVEL_4	,	task_dbg			},
	{AC_TASK_ZIGBEE_ID		,	TASK_PRI_LEVEL_4	,	task_zigbee			},

	{AC_GAME_CONTROL_ID		,	TASK_PRI_LEVEL_4	,	task_control_game	},
	{AC_SHIP_ID				,	TASK_PRI_LEVEL_4	,	task_control_ship	},
	{AC_MISSILE_ID			,	TASK_PRI_LEVEL_4	,	task_control_missile},
	{AC_MINES_ID			,	TASK_PRI_LEVEL_4	,	task_control_mines	},
	{AC_DISPLAY_ID			,	TASK_PRI_LEVEL_4	,	task_control_display},
	/*************************************************************************/
	/* RF24 NETWORK TASK */
	/*************************************************************************/
	#if defined (IF_NETWORK_NRF24_EN)
	{AC_RF24_PHY_ID			,	TASK_PRI_LEVEL_3	,	task_rf24_phy		},
	{AC_RF24_MAC_ID			,	TASK_PRI_LEVEL_4	,	task_rf24_mac		},
	{AC_RF24_NWK_ID			,	TASK_PRI_LEVEL_5	,	task_rf24_nwk		},
	#endif

	/*************************************************************************/
	/* LINK TASK */
	/*************************************************************************/
	#if defined (IF_LINK_UART_EN)
	{AC_LINK_PHY_ID			,	TASK_PRI_LEVEL_3	,	task_link_phy		},
	{AC_LINK_MAC_ID			,	TASK_PRI_LEVEL_4	,	task_link_mac		},
	{AC_LINK_ID				,	TASK_PRI_LEVEL_5	,	task_link			},
	#endif

	/*************************************************************************/
	/* END OF TABLE */
	/*************************************************************************/
	{AK_TASK_EOT_ID,			TASK_PRI_LEVEL_0,		(pf_task)0			}
};
