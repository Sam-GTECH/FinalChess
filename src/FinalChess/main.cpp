#include "pch.h"
#include "main.h"

#ifndef SFML_STATIC
int main()
{
	Board* game = new Board();

#ifdef LOG
	Logger* log = new Logger();
	game->log = log;
	log->Info("Logger is activated!");
#endif

	game->createGame();

	game->update();

	delete game;
#ifdef LOG
	delete log;
#endif

	return 0;
}
#else
Board* game;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP));
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = nullptr;
	wcex.lpszClassName  = L"WinAppClass";
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	if ( RegisterClassExW(&wcex)==0 )
		return 0;

	// Apparently, Windows counts the top bar as part of the dimension so this take care of it
	RECT rect = { 0, 0, 142 * SCALE, 142 * SCALE };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	HWND hWnd = CreateWindowW(L"WinAppClass", L"Chess", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, 0, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);
	if ( hWnd==NULL )
		return 0;

#ifdef _DEBUG
	AllocConsole();
	FILE* pNewStdout = nullptr;
	FILE* pNewStderr = nullptr;
	FILE* pNewStdin = nullptr;

	::freopen_s(&pNewStdout, "CONOUT$", "w", stdout);
	::freopen_s(&pNewStderr, "CONOUT$", "w", stderr);
	::freopen_s(&pNewStdin, "CONIN$", "r", stdin);
#endif

	std::ofstream file("../../../sfml-log.txt");
	std::streambuf* previous = sf::err().rdbuf(file.rdbuf());

	game = new Board();

#ifdef LOG
	Logger* log = new Logger();
	game->log = log;
	log->Info("Logger is activated!");
#endif

	game->createGame(hWnd);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (game->getWindow()->isOpen())
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		game->getWindow()->clear();
		game->update();
		game->getWindow()->display();
	}

	delete game;

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_COMMAND:
		{
			int id = LOWORD(wParam);
			int notif = HIWORD(wParam);
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
		case WM_LBUTTONDOWN:
		{
			if (!game->mouse_held)
			{
				game->mouse_held = true;
				game->mousePressed(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			}
			break;
		}
		case WM_LBUTTONUP:
		{
			game->mouse_held = false;
			game->mouseReleased(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;
		}
		case WM_MOUSEMOVE:
		{
			if (game->mouse_held)
				game->mouseHeld(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_CLOSE:
		{
			game->getWindow()->close();
			PostQuitMessage(0);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
	}
	return 0;
}
#endif