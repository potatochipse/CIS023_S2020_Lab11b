// Module:	CIS023_S2020_Lab11b Miguel Antonio Logarta.cpp
// Author:	Miguel Antonio Logarta
// Date:	February 26, 2020
// Purpose: Use a base class with its default methods and members
//			Derive a class from the base class
//			Expand a base class with methods and members in a derived class
//			Interact with the derived class

#include "framework.h"
#include "CIS023_S2020_Lab11b Miguel Antonio Logarta.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Handles to main window controls
HWND hWnd_FirstName;
HWND hWnd_LastName;
HWND hWnd_FullName;
HWND hWnd_Initials;
HWND hWnd_Go;
HWND hWnd_Comma;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CIS023S2020LAB11BMIGUELANTONIOLOGARTA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CIS023S2020LAB11BMIGUELANTONIOLOGARTA));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CIS023S2020LAB11BMIGUELANTONIOLOGARTA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);											// COLOR_WINDOW value is 0 for gray;
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CIS023S2020LAB11BMIGUELANTONIOLOGARTA);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 350, 350, nullptr, nullptr, hInstance, nullptr);			// 350 by 350 window

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case BN_CLICKED:
				{
					if (LOWORD(lParam) == (WORD)hWnd_Go)
					{
						TCHAR szFirstName[TCHAR_SIZE];									// Input from first name control
						TCHAR szLastName[TCHAR_SIZE];									// Input from last name control
						PeopleClass pcFirstName;										// Object of derived class
						PeopleClass pcLastName;											// Object of derived class
						string strOutput;												// Generate text
						TCHAR* szOutput;												// Dispaly TCHAR

						GetWindowText(													// Get text from edit box
							hWnd_FirstName,												// Get first name
							szFirstName,												// Destination TCHAR
							TCHAR_SIZE);												// Max chars to get

						GetWindowText(													// Get text from edit box
							hWnd_LastName,												// Get first name
							szLastName,													// Destination TCHAR
							TCHAR_SIZE);												// Max chars to get

						// Convert TCHAR to string, store in derived objects
						pcFirstName.append(pcFirstName.TCHARToString(szFirstName));		
						pcLastName.append(pcLastName.TCHARToString(szLastName));	

						// Generate "Full" name
						strOutput = pcFirstName;										// Insert first name

						if (pcFirstName.length() > 0)									// Is there a first name
							strOutput += " ";											// Add a space 

						strOutput += pcLastName;										// Append last name

						// Convert to TCHAR and display
						szOutput = pcFirstName.StringToTCHAR(strOutput);
						SetWindowText(hWnd_FullName, szOutput);

						// Generate "Formal" name
						strOutput = pcLastName;											// Start with last name

						if ((pcFirstName.length() > 0) && (pcLastName.length() > 0))	// If both names are not empty
							strOutput += ", ";											// Comma between the names

						strOutput += pcFirstName;										// End with first name

						// Convert to TCHAR and display
						szOutput = pcFirstName.StringToTCHAR(strOutput);
						SetWindowText(hWnd_Comma, szOutput);	

						// Generate "Initials" string
						strOutput.clear();												// Empty the output string

						if (pcLastName.length() > 0)									// Don't insert blank text
							strOutput.insert(0, 1,										// Insert 1st char, set to uppercase
								toupper(pcLastName.at(0)));

						if (pcFirstName.length() > 0)									// Don't insert blank text
							strOutput.insert(0, 1,										// Insert 1st char, set to uppercase
								toupper(pcFirstName.at(0)));						

						SetWindowText(hWnd_Initials,									// Send text to the output label
							pcFirstName.StringToTCHAR(strOutput));						
					}
				}
				break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_CREATE:
		{
			// labels
			CreateWindow( // create control
				TEXT("STATIC"), // label
				TEXT("First Name"), // text on label
				WS_VISIBLE | WS_CHILD, // options
				10, 10, 80, 20, // xy xy
				hWnd, NULL, NULL, NULL); // parent

			CreateWindow( // create control
				TEXT("STATIC"), // label
				TEXT("Last Name"), // text on label
				WS_VISIBLE | WS_CHILD, // options
				10, 50, 80, 20, // xy xy
				hWnd, NULL, NULL, NULL); // parent

			CreateWindow( // create control
				TEXT("STATIC"), // label
				TEXT("Full"), // text on label
				WS_VISIBLE | WS_CHILD, // options
				10, 150, 80, 20, // xy xy
				hWnd, NULL, NULL, NULL); // parent

			CreateWindow( // create control
				TEXT("STATIC"), // label
				TEXT("Formal"), // text on label
				WS_VISIBLE | WS_CHILD, // options
				10, 190, 80, 20, // xy xy
				hWnd, NULL, NULL, NULL); // parent

			CreateWindow( // create control
				TEXT("STATIC"), // label
				TEXT("Initials"), // text on label
				WS_VISIBLE | WS_CHILD, // options
				10, 230, 80, 20, // xy xy
				hWnd, NULL, NULL, NULL); // parent

				// inputs
			hWnd_FirstName = CreateWindow( // edit control for first name
				TEXT("EDIT"), // input box
				TEXT(""), // text on label
				WS_VISIBLE | WS_CHILD | // options
				ES_AUTOHSCROLL | WS_BORDER,
				100, 10, 200, 20, // xy xy
				hWnd, NULL, NULL, NULL); // parent

			hWnd_LastName = CreateWindow( // edit control for last name
				TEXT("EDIT"), // input box
				TEXT(""), // text on label
				WS_VISIBLE | WS_CHILD | // options
				ES_AUTOHSCROLL | WS_BORDER,
				100, 50, 200, 20, // xy xy
				hWnd, NULL, NULL, NULL); // parent

				// button
			hWnd_Go = CreateWindow( // go button
				TEXT("BUTTON"), // button
				TEXT("GO"), // left arrow
				WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // options
				100, 90, 60, 30, // xy xy
				hWnd, NULL, NULL, NULL); // parent

				// outputs
			hWnd_FullName = CreateWindow( // label for full name
				TEXT("STATIC"), // output label
				TEXT(""), // text on label
				WS_VISIBLE | WS_CHILD, // options
				100, 150, 200, 20, // xy xy
				hWnd, NULL, NULL, NULL); // parent

			hWnd_Comma = CreateWindow( // label for last name, first name
				TEXT("STATIC"), // output label
				TEXT(""), // text on label
				WS_VISIBLE | WS_CHILD, // options
				100, 190, 200, 20, // xy xy
				hWnd, NULL, NULL, NULL); // parent

			hWnd_Initials = CreateWindow( // label for initials
				TEXT("STATIC"), // output label
				TEXT(""), // text on label
				WS_VISIBLE | WS_CHILD, // options
				100, 230, 200, 20, // xy xy
				hWnd, NULL, NULL, NULL); // parent
		}
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
