#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <cstdio>

#include "RhymeList.h"
#include "stringParser.h"

RhymeList theRhymes;

std::string oldWord = "";

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("Rhymr");

HWND ebEditor;
HWND lblRhymes, lblFiltered;
HWND lbRhymes, lbFiltered;
HWND hwnd;

enum { ID_EBEDITOR = 55, ID_LBLRHYMES, ID_LBLFILTERED, ID_LBRHYMES, ID_LBFILTERED};



// Update rhymes
void updateRhymes( bool nextLine){
  // The buffer
  char buff[2048];
  GetWindowText( ebEditor, buff, 2048);

  // Gets iterpos
  DWORD firstChar, lastChar;
  SendMessage( ebEditor, EM_GETSEL, (WPARAM) &firstChar, (LPARAM) &lastChar);
  SendMessage( ebEditor, EM_GETLINE, (WPARAM) &firstChar, (LPARAM) &lastChar);

  // Parse edit text and split by line
  int currentLine = 0;
  std::vector<std::string> allLines;
  stringParser::getSentences( buff, firstChar, &currentLine, &allLines);

  // Finds last word of previous line
  if( (!nextLine && allLines.size() > 0 && currentLine >= 0  && currentLine <= allLines.size()) ||
      ( nextLine && allLines.size() > 1 && currentLine > 0  && currentLine <= allLines.size()) ){
    std::string lastWord2 = stringParser::lastWord(allLines.at(currentLine - 1));

    if( lastWord2 != oldWord){
      // Clear boxes
      SendDlgItemMessage( hwnd, ID_LBRHYMES, LB_RESETCONTENT, 0, 0);
      SendDlgItemMessage( hwnd, ID_LBFILTERED, LB_RESETCONTENT, 0, 0);

      // Current rhyme word
      SendMessage( lbFiltered, LB_ADDSTRING, 0, (LPARAM)(lastWord2.c_str()));

      // All words
      WordArray syllableWords = theRhymes.getWords( lastWord2.c_str());
      for( unsigned int i = 0; i < syllableWords.size(); i++){
        int pos = SendDlgItemMessage( hwnd, ID_LBRHYMES, LB_ADDSTRING, 0, (LPARAM)(syllableWords[i] -> text));
        SendDlgItemMessage( hwnd, ID_LBRHYMES, LB_SETITEMDATA, (WPARAM)pos, (LPARAM)i);
      }
      oldWord = lastWord2;
    }
  }
}


/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch( msg){
    // Init
    case WM_CREATE:
    {
      // List box lables
      lblRhymes = CreateWindow( "Static", "Rhymes", WS_CHILD | WS_VISIBLE,
                                0, 0, 200, 20, hwnd, (HMENU)ID_LBLRHYMES, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), 0);

      lblFiltered = CreateWindow( "Static", "Word", WS_CHILD | WS_VISIBLE,
                                  0, 0, 200, 20, hwnd, (HMENU)ID_LBLFILTERED, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), 0);

      // Main text box
      ebEditor = CreateWindowEx( 0, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
                                 0, 0, 0, 0, hwnd, (HMENU)ID_EBEDITOR, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), 0);

      // List boxes
      lbRhymes = CreateWindow ( "LISTBOX", "Hello World", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL,
                                 0, 0, 100, 0, hwnd, (HMENU)ID_LBRHYMES, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), 0);

      lbFiltered = CreateWindow ( "LISTBOX", "Test Box", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL,
                                 0, 0, 100, 0, hwnd, (HMENU)ID_LBFILTERED, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), 0);

      // Load rhymes
      if(theRhymes.loadDict("dict.txt"))
        std::cout << "Could not load dict.txt!\n";
      else
        std::cout << "Loaded dict.txt\n";
    }
    break;

    // Mouse
    case WM_LBUTTONDOWN:
      std::cout << "Loaded dict.txt\n";
      updateRhymes( false);
    break;

    // Command from Child windows and menus are under this message
    case WM_COMMAND:
    {
      switch( LOWORD(wParam)){
        case ID_EBEDITOR:
          updateRhymes( true);
        break;

        case ID_LBRHYMES:
        {
          std::cout << LOWORD(wParam) << " " << HIWORD(wParam) << " lparam:" << lParam << "\n";
          //switch (HIWORD(wParam)){
            /*case LBN_SELCHANGE:
            {
              HWND hList = GetDlgItem( hwnd, ID_LBRHYMES);
              int num = SendMessage( hList, LB_GETSELCOUNT, 0, 0);

              //int *buf = GlobalAlloc(GPTR, (sizeof(int) * num));
              //SendMessage(hList, LB_GETSELITEMS, (WPARAM)num, (LPARAM)buf);

              int data = SendMessage(hList, LB_GETITEMDATA, (WPARAM)0, 0);
              std::cout << data << "\n";

              //GlobalFree(buf);

              std::cout << "swaggger\n";
              break;
            }*/
            /*default:
              std::cout << LOWORD(wParam) << " " << HIWORD(wParam) << " lparam:" << lParam << "\n";
            break;
          }*/
        }
        break;

        default:
          std::cout << LOWORD(wParam) << " " << HIWORD(wParam) << " lparam:" << lParam << "\n";
      }
    }
    break;

    case WM_CLOSE:
      DestroyWindow(hwnd);
    break;

    case WM_DESTROY:
      PostQuitMessage(0);
    break;

    // Resize window
    case WM_SIZE:
      // Edit area
      MoveWindow( ebEditor, 10, 10, LOWORD(lParam) - 20, HIWORD(lParam) / 2, TRUE);

      // Lables for list boxes
      MoveWindow( lblRhymes  , 10                    , HIWORD(lParam) / 2 + 20, LOWORD(lParam) / 2 - 15, 15, TRUE);
      MoveWindow( lblFiltered, LOWORD(lParam) / 2 + 5, HIWORD(lParam) / 2 + 20, LOWORD(lParam) / 2 - 15, 15, TRUE);

      // List boxes
      MoveWindow( lbRhymes  , 10                    , HIWORD(lParam) / 2 + 40, LOWORD(lParam) / 2 - 15, HIWORD(lParam) / 2 - 40, TRUE);
      MoveWindow( lbFiltered, LOWORD(lParam) / 2 + 5, HIWORD(lParam) / 2 + 40, LOWORD(lParam) / 2 - 15, HIWORD(lParam) / 2 - 40, TRUE);
    return 0;

    default:
      return DefWindowProc( hwnd, msg, wParam, lParam);
  }
  return 0;
}


int WINAPI WinMain( HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow){
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WndProc;      /* This function is called by windows */
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
           WS_EX_CLIENTEDGE,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Rhymr"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           600,                 /* The programs width */
           400,                 /* and height in pixels */
           NULL,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0)){
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}
