#include "include.h"

class Localplayer
{
public:
	DWORD Get();

	bool Exists();

	int GetHealth();
	int GetTeam();

	int CrosshairID();

	void ForceJump();
	void ForceAttack();
	void StopAttack();


	void SetViewAngels(Vector3 Input);
	Vector3 GetViewAngels();

};