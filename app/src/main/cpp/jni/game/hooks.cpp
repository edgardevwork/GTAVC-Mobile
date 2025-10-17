//
// Created by vadim on 11.06.2025.
//
#include "../main.h"
#include "patches.h"
#include "CHooks.h"
#include "dependencies/armhook/patch.h"
#include "hooks.h"
#include "game/RW/RenderWare.h"
#include "game/RW/immedi.h"
#include "CLoadingScreen.h"
#include "CMenuManager.h"

struct CHID;

int(*Render2dStuff)();
int Render2dStuff_hook()
{
    //LOGI(MAKEOBF("aGameState: %i"), *(int*)(g_libGTAVC + 0x991E84));
    return Render2dStuff();
}

bool(*MainGameTick)(float, CHID*);
bool MainGameTick_hook(float a1, CHID *a2)
{
    //LOGI(MAKEOBF("MainGameTick called with a1: %f"), a1);
    return MainGameTick(a1, a2);
}

void Hooks::InstallCHooks()
{
    InjectHooks();
    CHooks::InitHooksEdgar();
    CHook::InlineHook("_Z13Render2dStuffv", &Render2dStuff_hook, &Render2dStuff);
    CHook::InlineHook("_Z12MainGameTickf", &MainGameTick_hook, &MainGameTick);
    ((void (*)()) (g_libGTAVC + (VER_x32 ? 0x1D6F2C + 1 : 0x2ACDC4)))(); // CCoronas::DoSunAndMoon()

//#if VER_x32
    //CHook::InlineHook(g_libGTAVC + 0x1DD490, &CDraw__SetFOV_hook, &CDraw__SetFOV);
//#else
    //CHook::InlineHook(g_libGTAVC + 0x109050, &CDraw__SetFOV_hook, &CDraw__SetFOV);
//#endif
}

void Hooks::InjectHooks() {
    CLoadingScreen::InjectHooks();
    CMenuManager::InjectHooks();
}
