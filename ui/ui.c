#include "ui.h"
#include "stdio.h"

void init_dynamic(DYNAMIC * dynamic ,int scale , int sheight , int swidth){

  if(swidth > 800){
    dynamic->rows = 2;
  }else{
    dynamic->rows = 1;
  }

  dynamic->scale = scale;
  dynamic->marginx = (swidth/scale);
  dynamic->marginy = (sheight/scale);

  dynamic->sheight = sheight;
  dynamic->swidth = swidth;
  
  
}


void dynamic(DYNAMIC * dynamic, int sheight , int swidth ){


  if(swidth > 800){
    dynamic->rows = 2;
  }else{
    dynamic->rows = 1;
  }

  
  dynamic->marginx = swidth/dynamic->scale;
  dynamic->marginy = sheight/dynamic->scale;

  
  dynamic->sheight = sheight;
  dynamic->swidth = swidth;
  
}


Vector2 get_rectangle_size(DYNAMIC * dynamic ){

  Vector2 retval;

  if(dynamic->rows == 1){
    retval.x = dynamic->swidth - (2 * dynamic->marginx);
    retval.y = 4 * dynamic->marginy;
  }else{
    retval.x = (dynamic->swidth/2) - dynamic->marginx;
    retval.y = 4 * dynamic->marginy;
  }

  return retval;
  
}


void scroll(DYNAMIC * dynamic , int num  ){

  if(dynamic->scroll > -(dynamic->marginy * (num - 2) * 5)){
    if( GetMouseWheelMove() < 0){
      dynamic->scroll -= 70;
      printf("scroll = %d \n",dynamic->scroll);
    }

  }
  

  if(dynamic->scroll < 1){
    if( GetMouseWheelMove() > 0){
    dynamic->scroll += 70;
    printf("scroll = %d \n",dynamic->scroll);
  }

  }
  
  
}


void get_rectangles(Rectangle * rec , DYNAMIC * dynamic , int num){

  Vector2 size = get_rectangle_size(dynamic);
  
  int vertical_step = 5 * dynamic->marginy;

  int first_vertical_step = dynamic->marginy + dynamic->scroll;
  
  for(int i = 0 ; i < num ; i++){

    rec[i].x = dynamic->marginx;
    rec[i].y = first_vertical_step;
    rec[i].width = size.x;
    rec[i].height = size.y;

    first_vertical_step = first_vertical_step + vertical_step;
    
  }

  
}


void draw_rectangles(Rectangle * rec , int num){

  for(int i = 0 ; i < num ; i++){

    DrawRectangleRec(rec[i] , ITEMGRAY);
    
  }
   
  
}

void draw_text_on_recs(Rectangle * rec , int num , char ** text){

  for( int i = 0 ;  i < num ; i++){

    DrawText(text[i], rec[i].x + 10 , rec[i].y + 10 , 20 , BLACK);
    
  }
  
  
}

void draw_site_status(Rectangle * rec , DATA_SET * copy_of_dataset , int num){

  for( int i = 0 ; i < num ; i++){

    if(copy_of_dataset[i].status == UNKNOWN){
      
      DrawCircle(rec[i].width - 25, rec[i].y + 25 , 20 ,YELLOW);
      
    }else if(copy_of_dataset[i].status == UP){
      
      DrawCircle(rec[i].width - 25, rec[i].y + 25 , 20 ,GREEN);
      
    }else if(copy_of_dataset[i].status == DOWN){
      
      DrawCircle(rec[i].width - 25, rec[i].y + 25 , 20 ,RED);

    }
  }
  
}
