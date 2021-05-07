#include  "GraphicEngine.h"



Console::Console() {
	screen_width = 80;
	screen_height = 30;
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

int Console::make_console(int width, int height, int fontw, int fonth) {
	screen_width = width;
	screen_height = height;
	//screen buffer�� size ����
	COORD coord = { (short)screen_width,(short)screen_height };
	if (!SetConsoleScreenBufferSize(m_hConsole, coord)) printf("ERROR1");
	if (!SetConsoleActiveScreenBuffer(m_hConsole)) printf("ERROR2");

	//font size�� �ֿܼ� assign
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontw;
	cfi.dwFontSize.Y = fonth;
	cfi.FontFamily = FF_DONTCARE;//��Ʈ
	cfi.FontWeight = FW_NORMAL;//����
	wcscpy_s(cfi.FaceName, L"Consolas");//��Ʈ

	if (!SetCurrentConsoleFontEx(m_hConsole, false, &cfi)) printf("ERROR3");

	// Get screen buffer info and check the maximum allowed window size. Return
	// error if exceeded, so user knows their dimensions/fontsize are too large
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(m_hConsole, &csbi)) printf("ERROR4");
	if (screen_height > csbi.dwMaximumWindowSize.Y) printf("ERROR5");//screen/font height too big
	if (screen_width > csbi.dwMaximumWindowSize.X) printf("ERROR6"); //screen/font width too big 

	//�ܼ�â ������ ����
	m_rectWindow = { 0,0,(short)screen_width - 1,(short)screen_height - 1 };
	SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow);

	//��ũ�����ۿ� �޸� �Ҵ�
	bufScreen = new CHAR_INFO[screen_width * screen_height];
	memset(bufScreen, 0, sizeof(CHAR_INFO) * screen_width * screen_height);

	return 1;
}

void Console::draw(int x, int y, short c, short col ) {
	if (x >= 0 && x < screen_width && y >= 0 && y < screen_height)
	{
		bufScreen[y * screen_width + x].Char.UnicodeChar = c;
		bufScreen[y * screen_width + x].Attributes = col;
	}
}
void Console::draw_circle(int rx, int ry, int r, short c, short col) {
	int x = 0;
	int y = r;
	while (y >= x) {

		draw(rx - x, ry - y, c, col);
		draw(rx - y, ry - x, c, col);
		draw(rx + y, ry - x, c, col);
		draw(rx + x, ry - y, c, col);
		draw(rx - x, ry + y, c, col);
		draw(rx - y, ry + x, c, col);
		draw(rx + y, ry + x, c, col);
		draw(rx + x, ry + y, c, col);
		x++;
		y=(int)(std::pow(r * r - x * x, 1 / 2.)+0.5);
	}


}
void Console::update() { //����ϴ� �Լ�
		WriteConsoleOutput(m_hConsole, bufScreen, { (short)screen_width, (short)screen_height }, { 0,0 }, &m_rectWindow);
	}