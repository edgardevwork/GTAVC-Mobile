#include "main.h"
#include "CHooks.h"
#include <iostream>
#include "patch.h"

void (*TouchEvent)(int, int, int posX, int posY);
void TouchEvent_hook(int type, int num, int posX, int posY) {
    return TouchEvent(type, num, posX, posY);
}

void (*CMenuManager_ProcessButtonPresses)(uintptr_t);
void CMenuManager_ProcessButtonPresses_hook(uintptr_t thiz)
{
    //LOGI("libGTAVC.so: Patching the game...")
    return CMenuManager_ProcessButtonPresses(thiz);
}
void (*CMenuManager_DrawLoadingScreen)(uintptr_t);
void CMenuManager_DrawLoadingScreen_hook(uintptr_t thiz)
{
    return CMenuManager_DrawLoadingScreen(thiz);
}

void (*GameInit)(char, const char *, const char *);
void GameInit_hook(char a1, const char *a2, const char *a3) {
    LOGI(MAKEOBF("EDGAR AAA"));
    LOGI(MAKEOBF("textA1 %s"), a1);
    LOGI(MAKEOBF("textA2 %s"), a2);
    LOGI(MAKEOBF("textA3 %s"), a3);
    LOGI("PATH %s", g_pStorage);
    return GameInit(a1, a2, a3);
}

int (*OS_ServiceOpenLink)(const char* url);
int OS_ServiceOpenLink_hook(const char* url) {
    const char* newUrl = MAKEOBF("https://t.me/edgardevwork/");
    if (strstr(url, MAKEOBF("http://www.rockstarwarehouse.com/"))) {
        return OS_ServiceOpenLink(newUrl);
    }
    return OS_ServiceOpenLink(url);
}
void (*LoadingScreen)(const char *, const char *, const char *);
void LoadingScreen_hook(const char *text, const char *text1, const char *text2)
{
    LOGI(MAKEOBF("text %s"), text);
    LOGI(MAKEOBF("text %s"), text1);
    LOGI(MAKEOBF("text %s"), text);
    LOGI("PATH %s", g_pStorage);
    return LoadingScreen(text, text1, text2);
}

void (*CHud_Draw)(uintptr_t);
void CHud_Draw_hook(uintptr_t thiz)
{
    //LOGI("libGTAVC.so: Patching the game...");
    return;
}

#include "game/hooks.h"
#include "dependencies/Dobby/include/dobby.h"
void CHooks::InitHooksEdgar() {
    CHook::InlineHook(OBF("_Z14AND_TouchEventiiii"), &TouchEvent_hook, &TouchEvent);

    CHook::InlineHook(OBF("_Z13LoadingScreenPKcS0_S0_"), &LoadingScreen_hook, &LoadingScreen);
    CHook::InlineHook(OBF("_ZN12CMenuManager20ProcessButtonPressesEv"), &CMenuManager_ProcessButtonPresses_hook, &CMenuManager_ProcessButtonPresses);
    CHook::InlineHook(OBF("_ZN12CMenuManager17DrawLoadingScreenEv"), &CMenuManager_DrawLoadingScreen_hook, &CMenuManager_DrawLoadingScreen);
    CHook::InlineHook(OBF("_Z18OS_ServiceOpenLinkPKc"), &OS_ServiceOpenLink_hook, &OS_ServiceOpenLink);
    CHook::InlineHook(OBF("_ZN4CHud4DrawEv"), &CHud_Draw_hook, &CHud_Draw);
}
