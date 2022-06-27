#include "include.h"

DWORD Entity::Get(int Index)
{
	return *(DWORD*)(Global_GameModule + dwEntityList + (Index * 0x10));
}

int Entity::GetHealth(DWORD Entity)
{
	return *(int*)(Entity + m_iHealth);
}

int Entity::GetTeam(DWORD Entity)
{
	return *(int*)(Entity + m_iTeamNum);
}