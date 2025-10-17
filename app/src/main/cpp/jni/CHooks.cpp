#include "main.h"
#include "CHooks.h"
#include <iostream>
#include "patch.h"

void (*TouchEvent)(int, int, int posX, int posY);
void TouchEvent_hook(int type, int num, int posX, int posY) {
    return TouchEvent(type, num, posX, posY);
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

void (*CHud_Draw)(uintptr_t);
void CHud_Draw_hook(uintptr_t thiz)
{
    //LOGI("libGTAVC.so: Patching the game...");
    return CHud_Draw(thiz);
    //return;
}
int (*OS_MovieIsPlaying)(int *);
int OS_MovieIsPlaying__hook(int *i) {
    LOGI(MAKEOBF("OS_MovieIsPlaying__hook: %i"), i);
    return 0;
}

#include "game/hooks.h"
#include "vendor/Dobby/include/dobby.h"
void CHooks::InitHooksEdgar() {
    CHook::InlineHook(OBF("_Z14AND_TouchEventiiii"), &TouchEvent_hook, &TouchEvent);
    CHook::InlineHook(OBF("_Z18OS_ServiceOpenLinkPKc"), &OS_ServiceOpenLink_hook, &OS_ServiceOpenLink);
    CHook::InlineHook(OBF("_ZN4CHud4DrawEv"), &CHud_Draw_hook, &CHud_Draw);
    CHook::InlineHook(OBF("_Z17OS_MovieIsPlayingPi"), &OS_MovieIsPlaying__hook, &OS_MovieIsPlaying);
}
