#include "include.h"

DWORD WINAPI TriggerbotThread(HMODULE hMod)
{
	Localplayer L;
	Entity E;


	while (!GetAsyncKeyState(UNINJECT_KB))
	{
		int CrosshairID = L.CrosshairID();
		int LocalTeam = L.GetTeam();
		int LocalHealth = L.GetHealth();

		if (CrosshairID > 0 && CrosshairID < 64)
		{
			DWORD Entity = E.Get(CrosshairID - 1);
			int EntityTeam = E.GetTeam(Entity);
			int EntityHealth = E.GetHealth(Entity);

			if (EntityTeam != LocalTeam && Settings.EnableTriggerbot)
			{
				if (EntityHealth > 0 && EntityHealth < 101)
				{
					if (LocalHealth > 0 && LocalHealth < 101)
					{
						Sleep(Settings.TriggerbotDelay);
						L.ForceAttack();
						Sleep(20);
						L.StopAttack();

					}
				}
			}
		}
		Sleep(3);
	}
	FreeLibraryAndExitThread(hMod, 0);
}