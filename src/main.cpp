#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("Rhymr");

HWND hwndButton;
HWND static_label;
enum { ID_LABEL = 1,ID_IMAGE,ID_EDIT,ID_LIST,ID_BUTTON,ID_COMBO, ID_BUTTON2 };

int WINAPI WinMain( HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */

    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Rhymr"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           600,                 /* The programs width */
           400,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0)){
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch( message){                 /* handle the messages */
    case WM_CREATE:
      hwndButton = CreateWindow(
            "BUTTON", "OK", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 10, 100, 100, hwnd, (HMENU)ID_BUTTON, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

      static_label = CreateWindow("Static", "Please Enter A Number",WS_CHILD | WS_VISIBLE,
            40, 15, 200, 25, hwnd, 0, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), 0);
      break;
    case WM_COMMAND: //Command from Child windows and menus are under this message
      switch(wParam){
        case ID_BUTTON:
            SetWindowText(static_label,"You clicked the button");
            break;
      }
      break;
    case WM_DESTROY:
      PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
      break;
    default:                       /* for messages that we don't deal with */
      return DefWindowProc (hwnd, message, wParam, lParam);
  }
  return 0;
}
