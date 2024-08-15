#include "threading.h"
#include "ui.h"
#include "get_url.h"


int main(void){

  //get urls
  URL * url =  (URL *) malloc(sizeof(URL));
  get_url_names(url);
  int len = url->urlcount;

  //urls for recs to be displayed
  char ** rec_url = (char ** ) calloc(len , sizeof(char *));
  for(int i = 0 ; i < len ; i++){
    rec_url[i] = (char * ) calloc(strlen(url->urlname[i]),sizeof(char));
    strcpy(rec_url[i], url->urlname[i]);
  }

  
  
  //fetch data
  DATA_SET * dataset;
  DATA_SET * copy_of_dataset;
  init_dataset( &dataset , url);
  init_dataset( &copy_of_dataset , url);

  THREAD_SUBSET * subset;
  init_thread_subsets(&subset , &dataset , len );

  //threading data collection
  spawn_collector_threads(&subset , len );

  //window init 
  InitWindow(800, 600, "WEBMONITOR");
  SetWindowState(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

  //graphics related stuff
  DYNAMIC * dynamic_val = ( DYNAMIC *) malloc(sizeof(DYNAMIC));
  init_dynamic(dynamic_val ,40 , GetScreenHeight() , GetScreenWidth() );

  Rectangle * rec = (Rectangle *) calloc(len , sizeof(Rectangle));
  

  //gameloop
  while (!WindowShouldClose())
    {
      //logic
      dynamic(dynamic_val , GetScreenHeight() , GetScreenWidth() );
      scroll(dynamic_val  , len);
      get_rectangles(rec , dynamic_val , len );
      check_and_copy(&copy_of_dataset , &subset , len );
      check_and_join(&subset  , len );
      check_and_respawn(&subset , len);

      //drawing
      BeginDrawing();
      ClearBackground(BACKWHITE);

      draw_rectangles(rec , len );
      draw_text_on_recs(rec , len  , rec_url );
      draw_site_status(rec , copy_of_dataset , len );
      
      EndDrawing();
    }


  //cleanup
  kill_collector_threads(&subset , len);
  printf("Threads killed \n");
  CloseWindow();
  clear_url_names(url);

  return 0;
}


