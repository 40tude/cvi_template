#ifdef _MSC_VER
  #define _CRT_SECURE_NO_WARNINGS
  #define CRTDBG_MAP_ALLOC
  #include <crtdbg.h>
#endif //_MSC_VER

#include <windows.h>
#include <utility.h>  // Profiler

#ifdef _MSC_VER      
  #include <cvirte.h>
#endif // _MSC_VER

#include <userint.h>

#include "../assets/frontend.h"

// Keep in mind macros like
// #ifdef _CVI_  
// #if _CVI_PROFILE_LEVEL_ > 0
// #if defined (_WIN64)

// TESTING : sdfsdf
// TODO : fsdfsdf
// DONE : sdfsdfsdf

// ----------------------------------------------------------------------------
int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {

#ifdef _MSC_VER
  if (InitCVIRTE (0, 0, 0) == 0) return -1;
#endif // _MSC_VER
  
  CVIProfSetCurrentThreadProfiling (1);
  
  int panelHandle=-1; 
  if ((panelHandle = LoadPanel (0, "../assets/frontend.uir", PANEL)) < 0) return -1;
  
  DisplayPanel (panelHandle);
  RunUserInterface ();
  DiscardPanel (panelHandle);
  
  // Not needed
  // CVIProfSetCurrentThreadProfiling (0);
  
  {
    size_t Bytes;
    size_t Blocks;
    // View info in Debug Output Window
    CVIDynamicMemoryInfo ("", &Blocks, &Bytes, DYNAMIC_MEMORY_SHOW_ALLOCATED_MEMORY_SUMMARY);
  }
  
#ifdef _MSC_VER
  _CrtDumpMemoryLeaks();
#endif // _MSC_VER
  
  return 0;
}

// ----------------------------------------------------------------------------
int CVICALLBACK QuitCallback (int panel, int control, int event, void *callbackData, int eventData1, int eventData2) {
 
  switch (event) {
    case EVENT_COMMIT:
      QuitUserInterface (0);
    break;
  }
  return 0;
}
