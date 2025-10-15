#include "main.h"
#include "CHooks.h"
#include <iostream>

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
#include "patch.h"
#include "game/hooks.h"
#include "dependencies/Dobby/include/dobby.h"
void CHooks::InitHooksEdgar() {
    CHook::InlineHook("_Z13LoadingScreenPKcS0_S0_", &LoadingScreen_hook, &LoadingScreen);
    CHook::InlineHook("_ZN12CMenuManager20ProcessButtonPressesEv", &CMenuManager_ProcessButtonPresses_hook, &CMenuManager_ProcessButtonPresses);
    CHook::InlineHook("_ZN12CMenuManager17DrawLoadingScreenEv", &CMenuManager_DrawLoadingScreen_hook, &CMenuManager_DrawLoadingScreen);
    CHook::InlineHook("_Z18OS_ServiceOpenLinkPKc", &OS_ServiceOpenLink_hook, &OS_ServiceOpenLink);
    CHook::InlineHook("_ZN4CHud4DrawEv", &CHud_Draw_hook, &CHud_Draw);

    /*#ifdef IS_ARM64
    DobbyHook((void *)GTA(0x206490), (void *)CMenuManager_ProcessButtonPresses_hook, (void **)&CMenuManager_ProcessButtonPresses);
    DobbyHook((void *)GTA(0x201F00), (void *)CMenuManager_DrawLoadingScreen_hook, (void **)&CMenuManager_DrawLoadingScreen);
    DobbyHook((void *)GTA(0x1F8CC8), (void *)LoadingScreen_hook, (void **)&LoadingScreen);
    DobbyHook((void *)GTA(0x2C317C), (void *)CHud_Draw_hook, (void **)&CHud_Draw);
    //DobbyHook((void *)GTA(0x45CE04), (void *)NvUtilInit_hook, (void **)NvUtilInit);
    DobbyHook((void *)GTA(0x4609CC), (void *)OS_ServiceOpenLink_hook, (void **)&OS_ServiceOpenLink);

    #elif defined(IS_ARM32)
    CHook::InlineHook("_Z13LoadingScreenPKcS0_S0_", &LoadingScreen_hook, &LoadingScreen);
    CHook::InlineHook("_ZN12CMenuManager20ProcessButtonPressesEv", &CMenuManager_ProcessButtonPresses_hook, &CMenuManager_ProcessButtonPresses);
    CHook::InlineHook("_ZN12CMenuManager17DrawLoadingScreenEv", &CMenuManager_DrawLoadingScreen_hook, &CMenuManager_DrawLoadingScreen);
    CHook::InlineHook("_Z18OS_ServiceOpenLinkPKc", &OS_ServiceOpenLink_hook, &OS_ServiceOpenLink);
    CHook::InlineHook("_ZN4CHud4DrawEv", &CHud_Draw_hook, &CHud_Draw);
    //CHook::InlineHook("_Z10NvUtilInitv", (void *)NvUtilInit_hook, (void **)NvUtilInit);
    LOGI("32");
    #endif*/
}
