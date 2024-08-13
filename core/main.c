#include "threading.h"
#include "ui.h"
#include "get_url.h"


int main(void){

  //get urls
  URL * url =  (URL *) malloc(sizeof(URL));
  get_url_names(url);
  int len = url->urlcount;
  
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
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

  //gameloop
  while (!WindowShouldClose())
    {
      //logic
      // check_and_copy(copy_of_set , set , subset);
      //check_and_kill(set, subset);

      //drawing
      BeginDrawing();
      ClearBackground(RAYWHITE);
      
      EndDrawing();
    }


  //cleanup
  kill_collector_threads(&subset , len);
  printf("Threads killed \n");
  CloseWindow();
  clear_url_names(url);

  return 0;
}


