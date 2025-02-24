CFLAGS		+= -I./sources/app
CPPFLAGS	+= -I./sources/app

VPATH += sources/app

# CPP source files
SOURCES_CPP += sources/app/app.cpp
SOURCES_CPP += sources/app/app_data.cpp
SOURCES_CPP += sources/app/app_non_clear_ram.cpp
SOURCES_CPP += sources/app/app_bsp.cpp
SOURCES_CPP += sources/app/rf_remote_ctrl.cpp
SOURCES_CPP += sources/app/shell.cpp

SOURCES_CPP += sources/app/task_shell.cpp
SOURCES_CPP += sources/app/task_life.cpp
SOURCES_CPP += sources/app/task_fw.cpp
SOURCES_CPP += sources/app/task_list.cpp
SOURCES_CPP += sources/app/task_zigbee.cpp

SOURCES_CPP += sources/app/task_if.cpp
SOURCES_CPP += sources/app/task_rf24_if.cpp
SOURCES_CPP += sources/app/task_uart_if.cpp
SOURCES_CPP += sources/app/task_dbg.cpp

SOURCES_CPP += sources/app/flynshoot_game_control.cpp
SOURCES_CPP += sources/app/flynshoot_mines.cpp
SOURCES_CPP += sources/app/flynshoot_missile.cpp
SOURCES_CPP += sources/app/flynshoot_ship.cpp
SOURCES_CPP += sources/app/flynshoot_display.cpp
