#include "include.h"

inline D3DCOLOR ImColor_D3D(ImColor Input)
{
	return D3DCOLOR_RGBA(
		(int)(Input.Value.x * 255.0f),
		(int)(Input.Value.y * 255.0f),
		(int)(Input.Value.z * 255.0f),
		(int)(Input.Value.w * 255.0f)
	);
}

class USettings
{
public:
	bool EnableBhop = false;

	bool EnableTriggerbot = false;
	int TriggerbotDelay = 0;

	bool EnableRecoilControl = false;
	float EnableRecoilControlAmount = 1.0f;

	bool EnableRecoilCrosshair = false;
	bool RecoilCrosshairLine = false;
	bool RecolCrosshairCircle = false;
	int RecoilCrosshairThickness = 1;
	int RecoilCrosshairLength = 1;
	ImColor RecoulCrosshairColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	bool EnableCustomFOV = false;
	int CustomDesiredFOV = 90;

	bool Global_Antialias = true;



};