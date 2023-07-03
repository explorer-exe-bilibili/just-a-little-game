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
};//状态
state p1;
float sj()/*随机*/ {
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
			wprintf(stmp, L"你升级了，现在%d级", p1.lel);
			TextOut(hdc, 300, 100, stmp, wcslen(stmp));
		}
		return p1.lel;
	}
	else {
		tps = tep - p1.xp;
		wprintf(stmp, L"距离下次升级还有%d经验", tps);
		TextOut(hdc, 300, 100, stmp, wcslen(stmp));
		return tps;
	}
}
double hit(HDC hdc)/*攻击*/
{
	ctmp = rand();
	if (ctmp == 255) {
		ftmp = p1.tool + 20 * p1.lel;
		wprintf(stmp,L"幸运儿！超级暴击！打出了%g点伤害",ftmp);
		TextOut(hdc, 300, 100, stmp, wcslen(stmp));
		return ftmp;
	}
	else if (ctmp >= 200 && ctmp != 255) {
		ftmp = p1.tool + 5 * p1.lel;
		wprintf(stmp, L"暴击！打出了%g点伤害", ftmp);
		TextOut(hdc, 300, 100, stmp, wcslen(stmp));
		return ftmp;
	}
	else if (ctmp < 200 && ctmp >= 100) {
		ftmp = p1.tool + 2 * p1.lel;
		wprintf(stmp, L"平平无奇的攻击，打出了%g点伤害", ftmp);
		TextOut(hdc, 300, 100, stmp, wcslen(stmp));
		return ftmp;
	}
	else if (ctmp < 100 && ctmp >= 20) {
		ftmp = p1.tool + 1 * p1.lel;
		wprintf(stmp, L"弱弱的攻击，打出了%g点伤害", ftmp);
		TextOut(hdc, 300, 100, stmp, wcslen(stmp));
		return ftmp;

	}
	else {
		wprintf(stmp, L"攻击miss啦");
		TextOut(hdc, 300, 100, stmp, wcslen(stmp));
		return 0;
	}
}
void death(HDC hdc) {
	if (p1.blood <= 0) {
		print(hdc,150,400,L"你逝了，这么简单都打不过，泰拉了！\n");
		Sleep(3000);
		system("start taskkill /f /t /im hello world.exe");
		Sleep(10000);
	}
}
float act()
{
	int active = 0;
	printf("你的回合\n输入1攻击\n输入2魔法回血(doge)\n输入3逃跑\n");
	scanf_s("%d", &active);
	system("cls");
	if (active == 1)return hit();
	else if (active == 2)
	{
		tps = sj() * lel - 2;
		blood = blood + 2 * tps;
		if (blood >= 100)blood = 100;
		printf("你回复了%.1f点血量\n", tps);
		return -1;
	}
	else if (active == 3) {
		printf("逃跑失败\n");
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
	else printf("            请重新输入\n");
}
void slime(HDC hdc)
{
	ml = 20 + p1.lel * 5;
	print(hdc,150,200,L"你遇到了一只slime\n");
	while (ml > 0) {
		tep = act();
		if (tep != -1)ml = ml - tep;
		tps = sj() / 4 * lel;
		printf("slime对你造成了%.2f点伤害\n", tps);
		blood = blood - tps;
		printf("你的血量剩余 %.2f \nslime的血量剩余 %.1f \n", blood, ml);
		death();
	}
	printf("你打败了slime，获得了2coins和10点xp\n");
	coin = coin + 2;
	xp = xp + 10;
	level();
	printf("现在拥有%dcoins\n", coin);
	if (sj() == 5) {
		printf("恭喜你捡到一个攻击力+1的武器，是否装备？(目前武器伤害%.1f)\n输入1表示装备，否则丢弃\n", tool);
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
}      //打印
void newpage() {
	GetClientRect(hWnd, recth);
	InvalidateRect(hWnd, recth, TRUE);
	UpdateWindow(hWnd);
}//刷新页面
void end() {
	PostQuitMessage(0);
}//退出程序 