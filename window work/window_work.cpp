// window_work.cpp : Defines the entry point for the application.
//
#include <windows.h>
#include <tchar.h>
#include <ctime>

//прототип оконной процедуры
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение"); /* Имя класса окна */

INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASSEX wcl;

	/* 1. Определение класса окна  */
	wcl.cbSize = sizeof(wcl);	// размер структуры WNDCLASSEX 
	wcl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	// окно сможет получать сообщения о двойном щелчке (DBLCLK)
	wcl.lpfnWndProc = WindowProc;	// адрес оконной процедуры
	wcl.cbClsExtra = 0;		// используется Windows 
	wcl.cbWndExtra = 0; 	// используется Windows 
	wcl.hInstance = hInst;	// дескриптор данного приложения
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// загрузка стандартной иконки
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);		// загрузка стандартного курсора
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//заполнение окна белым цветом			
	wcl.lpszMenuName = NULL;	// приложение не содержит меню
	wcl.lpszClassName = szClassWindow;	// имя класса окна
	wcl.hIconSm = NULL;	// отсутствие маленькой иконки для связи с классом окна


	/*  2. Регистрация класса окна  */
	if (!RegisterClassEx(&wcl))
		return 0;	// при неудачной регистрации - выход

	/*  3. Создание окна  */
	// создается окно и  переменной hWnd присваивается дескриптор окна
	hWnd = CreateWindowEx(
		0,		// расширенный стиль окна
		szClassWindow,	// имя класса окна
		TEXT("Каркас  Windows приложения"),	// заголовок окна
		/* Заголовок, рамка, позволяющая менять размеры, системное меню,
			кнопки развёртывания и свёртывания окна  */
		WS_OVERLAPPEDWINDOW,	// стиль окна
		CW_USEDEFAULT,	// х-координата левого верхнего угла окна
		CW_USEDEFAULT,	// y-координата левого верхнего угла окна
		CW_USEDEFAULT,	// ширина окна
		CW_USEDEFAULT,	// высота окна
		NULL,			// дескриптор родительского окна
		NULL,			// дескриптор меню окна
		hInst,		// идентификатор приложения, создавшего окно
		NULL);		// указатель на область данных приложения


	/* 4. Отображение окна */
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);	// перерисовка окна


	/* 5. Запуск цикла обработки сообщений  */
	// получение очередного сообщения из очереди сообщений
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);	// трансляция сообщения
		DispatchMessage(&Msg);	// диспетчеризация сообщений
	}
	return Msg.wParam;
}


// Оконная процедура вызывается операционной системой и получает в качестве 
// параметров сообщения из очереди сообщений данного приложения	
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	srand(time(0));

	TCHAR str_q1[50] = TEXT("Are you human ?");
	TCHAR str_q2[50] = TEXT("Are you 18 year old ?");
	TCHAR str_q3[50] = TEXT("Are you from Ukraine ?");
	TCHAR str_q4[50] = TEXT("Is your favorite green color ?");
	TCHAR* mas[] = { str_q1, str_q2, str_q3, str_q4 };
	TCHAR str[50];

	int num = 0, min = 0, max = 100;
	TCHAR str_num[50];
	int answer = IDNO;

	switch (uMessage) {
	case WM_LBUTTONDOWN: {
		int rez = MessageBox(0, TEXT("Хотите поиграть ?"), TEXT("Вопрос"), MB_OKCANCEL | MB_ICONQUESTION);
		if (rez == IDOK) {
			MessageBox(0, TEXT("Загадайте число от 1 до 100"), "", MB_OK | MB_ICONINFORMATION);
			while (answer != IDYES) {
				num = rand() % (max - min) + min;
				wsprintf(str_num, "Ваше число = %d ?", num);
				answer = MessageBox(0, str_num, "", MB_YESNO | MB_ICONQUESTION);
			}
			if (answer == IDYES) {
				MessageBox(0, TEXT("Я угадал !"), "Win box", MB_OK);
			}
		}
		else {
			MessageBox(0, "Как хотите :(", "", MB_OK | MB_ICONHAND);
		}
		break;
	}

	case WM_CHAR: {
		for (int i = 0; i < 4; i++) {
			MessageBox(hWnd, mas[i], TEXT("WM_CHAR"), MB_OKCANCEL | MB_ICONINFORMATION);
		}
		size_t sizeStr = strlen(str_q1);
		sizeStr += strlen(str_q2);
		sizeStr += strlen(str_q3);
		sizeStr += strlen(str_q4);
		sizeStr /= 4;

		wsprintf(str, TEXT("Среднее число символов: %d"), sizeStr);
		MessageBox(hWnd, str, TEXT("Counter"), MB_OK | MB_ICONINFORMATION);
		break;
	}

	case WM_DESTROY: // сообщение о завершении программы
		PostQuitMessage(0);	// посылка сообщения WM_QUIT
		break;

	default:
		// все сообщения, которые не обрабатываются в данной оконной 
		// функции направляются обратно Windows на обработку по умолчанию
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}
