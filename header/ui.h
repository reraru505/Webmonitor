#pragma once

#include "stdlib.h"
#include "raylib.h"



typedef enum GAME_STATE{

  MENU = 0,
  MENU_ITEM_SELECTED,
  ITEM_NO_MENU
  
}GAME_STATE;

typedef struct DYNAMIC{

  int rows;
  int scale;
  int marginx;
  int marginy;
  
}DYNAMIC;




void init_dynamic(DYNAMIC * dynamic ,int scale , int rows , int sheight , int swidth);//TODO DEFINITION

void dynamic(DYNAMIC * dynamic);//TODO DEFINITION //dont forget to run this in a loop 

Vector2 get_rectangle_size(DYNAMIC * dynamic);//TODO DEFINITION

void get_rectangles();
