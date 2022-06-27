#include "include.h"

void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR col)
{
	D3DRECT rect = { x, y, x + w, y + h };
	DXDEVICE->Clear(1, &rect, D3DCLEAR_TARGET, col, 0, 0);
}
void DrawLine(int x1, int y1, int x2, int y2, int thickness, bool antialias, D3DCOLOR col)
{
	ID3DXLine* lineL;
	D3DXCreateLine(DXDEVICE, &lineL);

	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2(x1, y1);
	Line[1] = D3DXVECTOR2(x2, y2);
	
	lineL->SetWidth(thickness);
	lineL->SetAntialias(antialias);
	lineL->Draw(Line, 2, col);
	lineL->Release();
}

void DrawCircle(float x, float y, float radius, float sides, int thickness, bool antialias, D3DCOLOR color)
{
	float PI = 3.14159f;
	float Step = PI * 2 / sides;
	int Count = 0;
	for (float a = 0; a < PI * 2; a += Step)
	{
		float X1 = radius * cos(a) + x;
		float Y1 = radius * sin(a) + y;

		float X2 = radius * cos(a + Step) + x;
		float Y2 = radius * sin(a + Step) + y;

		DrawLine(X1, Y1, X2, Y2, thickness, antialias, color);

		Count += 2;
	}
}