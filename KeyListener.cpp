#include <thread>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include < Winuser.h>
class KeyLitener
{
private:
	bool flag[43] = { false };//A~Z 0~9 �»���� (ȭ��ǥ) shift ctrl alt enter 
	bool klf = 1;//���α׷� �����
public:
	bool keycheck(int key)
	{
		if (flag[key])//Ű�Է��� �޾Ҵµ� �ѹ��� ���۵� ���� �ʴ� ���� �����ϱ� ����
		{
			flag[key] = 0;
			return 1;
		}
		else { return 0; }
	}
	void keyinput(int key)
	{
		flag[key] = 1;
	}
	void reset()//����� �ؽ�Ʈ�� �޴´ٴ��� ���� ���� �����̶���� ���� �Է��� �����ؾ��ϴ� ��Ȳ���� ���
	{
		for (int i = 0; i < 43; i++)
		{
			flag[i] = false;
		}
	}
	bool ReturnF()
	{
		return klf;
	}
	void exit()
	{
		klf = 0;
	}
};
KeyLitener klc;
void KeyLitenerThread()//
{
	int i;
	while (klc.ReturnF)
	{
		if (GetAsyncKeyState(0xA2)|| GetAsyncKeyState(0xA3))
		{
		}
		for (i = 0x41; i < 0x5B; i++)//A~Z
		{
			if (GetAsyncKeyState(i))
			{
				klc.keyinput(i - 0x41);
			}
		}
		for (i = 0x30; i < 0x3A; i++)//0~9
		{
			if (GetAsyncKeyState(i))
			{
				klc.keyinput(i - 0x30 + 26);
			}
		}
		if (GetAsyncKeyState(0xA0) || GetAsyncKeyState(0xA1))//shift
		{
			klc.keyinput(40);
		}
		if (GetAsyncKeyState(0xA2) || GetAsyncKeyState(0xA3))//ctrl
		{
			klc.keyinput(41);
		}
		if (GetAsyncKeyState(0xA4) || GetAsyncKeyState(0xA5))//Alt
		{
			klc.keyinput(42);
		}
		if (GetAsyncKeyState(0x0D))//enter
		{
			klc.keyinput(43);
		}
		for (i = 0x25; i < 0x29; i++)//�»����
		{
			if (GetAsyncKeyState(i))
			{
				klc.keyinput(i - 0x25 + 36);
			}
		}
	}
}
int main()
{
	std::thread t(KeyLitenerThread);
	t.join();
}