#pragma once
//pva.h
#include "framework.h"
#include "resource.h"
HWND hWndh;
UINT messageh;
WPARAM putinh;
LPARAM lParamh;
RECT* recth;
void print(HDC hdc, int a, int b, const wchar_t tmpstr[128]);
void newpage();
void end();
float ml = 0, ftmp = 0;
int coin = 0;
unsigned char ctmp = 0;
float tps = 0;
int tep = 0;
wchar_t stmp[128] = {0};
struct state{
	bool alive;
	float blood = 100, tool = 0;
	int coin = 0, lel = 0,xp=0;
};//״̬
state p1;
float sj()/*���*/ {
	ctmp = rand();
	if (ctmp == 255)return 1;
	else if (ctmp >= 200 && ctmp != 255)return 2;
	else if (ctmp < 200 && ctmp >= 100)return 3;
	else if (ctmp < 100 && ctmp >= 20)return 4;
	else return 5;
}
int level(HDC hdc) {
	tep = (p1.lel + 5) * 10;
	if (p1.xp >= tep) {
		while (p1.xp >= tep) {
			p1.lel++;
			p1.xp = p1.xp - tep;
			tep = (p1.lel + 5) * 10;
			wprintf(stmp, L"�������ˣ�����%d��", p1.lel);
			TextOut(hdc, 300, 100, stmp, wcslen(stmp));
		}
		return p1.lel;
	}
	else {
		tps = tep - p1.xp;
		wprintf(stmp, L"�����´���������%d����", tps);
		TextOut(hdc, 300, 100, stmp, wcslen(stmp));
		return tps;
	}
}
double hit(HDC hdc)/*����*/
{
	ctmp = rand();
	if (ctmp == 255) {
		ftmp = p1.tool + 20 * p1.lel;
		wprintf(stmp,L"���˶������������������%g���˺�",ftmp);
		TextOut(hdc, 300, 100, stmp, wcslen(stmp));
		return ftmp;
	}
	else if (ctmp >= 200 && ctmp != 255) {
		ftmp = p1.tool + 5 * p1.lel;
		wprintf(stmp, L"�����������%g���˺�", ftmp);
		TextOut(hdc, 300, 100, stmp, wcslen(stmp));
		return ftmp;
	}
	else if (ctmp < 200 && ctmp >= 100) {
		ftmp = p1.tool + 2 * p1.lel;
		wprintf(stmp, L"ƽƽ����Ĺ����������%g���˺�", ftmp);
		TextOut(hdc, 300, 100, stmp, wcslen(stmp));
		return ftmp;
	}
	else if (ctmp < 100 && ctmp >= 20) {
		ftmp = p1.tool + 1 * p1.lel;
		wprintf(stmp, L"�����Ĺ����������%g���˺�", ftmp);
		TextOut(hdc, 300, 100, stmp, wcslen(stmp));
		return ftmp;

	}
	else {
		wprintf(stmp, L"����miss��");
		TextOut(hdc, 300, 100, stmp, wcslen(stmp));
		return 0;
	}
}
void death(HDC hdc) {
	if (p1.blood <= 0) {
		print(hdc,150,400,L"�����ˣ���ô�򵥶��򲻹���̩���ˣ�\n");
		Sleep(3000);
		system("start taskkill /f /t /im hello world.exe");
		Sleep(10000);
	}
}
float act()
{
	int active = 0;
	printf("��Ļغ�\n����1����\n����2ħ����Ѫ(doge)\n����3����\n");
	scanf_s("%d", &active);
	system("cls");
	if (active == 1)return hit();
	else if (active == 2)
	{
		tps = sj() * lel - 2;
		blood = blood + 2 * tps;
		if (blood >= 100)blood = 100;
		printf("��ظ���%.1f��Ѫ��\n", tps);
		return -1;
	}
	else if (active == 3) {
		printf("����ʧ��\n");
		return -1;
	}
	else if (active == 114514) {
		blood = 0;
		return -1;
	}
	else if (active == 114) {
		blood = 999;
		return 0;
	}
	else printf("            ����������\n");
}
void slime(HDC hdc)
{
	ml = 20 + p1.lel * 5;
	print(hdc,150,200,L"��������һֻslime\n");
	while (ml > 0) {
		tep = act();
		if (tep != -1)ml = ml - tep;
		tps = sj() / 4 * lel;
		printf("slime���������%.2f���˺�\n", tps);
		blood = blood - tps;
		printf("���Ѫ��ʣ�� %.2f \nslime��Ѫ��ʣ�� %.1f \n", blood, ml);
		death();
	}
	printf("������slime�������2coins��10��xp\n");
	coin = coin + 2;
	xp = xp + 10;
	level();
	printf("����ӵ��%dcoins\n", coin);
	if (sj() == 5) {
		printf("��ϲ���һ��������+1���������Ƿ�װ����(Ŀǰ�����˺�%.1f)\n����1��ʾװ����������\n", tool);
		scanf_s("%d", &tep);
		if (tep == 1)tool = 1;
	}
}
void print(HDC hdc, int a, int b, const wchar_t tmpstr[128])
{
	wchar_t buffer[128];
	wsprintf(buffer, tmpstr);
	TextOutW(hdc, a, b, buffer, wcslen(buffer));
	return;
}      //��ӡ
void newpage() {
	GetClientRect(hWnd, recth);
	InvalidateRect(hWnd, recth, TRUE);
	UpdateWindow(hWnd);
}//ˢ��ҳ��
void end() {
	PostQuitMessage(0);
}//�˳����� 