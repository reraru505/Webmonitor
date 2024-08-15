#pragma once

#include "stdlib.h"
#include "raylib.h"
#include "fetch_data.h"



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

  int sheight;
  int swidth;
  
  int scroll;
  
}DYNAMIC;




void init_dynamic(DYNAMIC * dynamic ,int scale , int sheight , int swidth);

void dynamic(DYNAMIC * dynamic, int sheight , int swidth );//dont forget to run this in a loop 

Vector2 get_rectangle_size(DYNAMIC * dynamic);

void scroll(DYNAMIC * dynamic , int num );

void get_rectangles(Rectangle * rec , DYNAMIC * dynamic , int num);

void draw_rectangles(Rectangle * rec , int num);

void draw_text_on_recs(Rectangle * rec , int num , char ** text);

void draw_site_status(Rectangle * rec , DATA_SET * copy_of_dataset , int num);


