//
// Created by EDGAR 3.0 on 16.10.2025.
//

#include "main.h"
#include "patch.h"
#include "CLoadingScreen.h"

void (*LoadingScreen)(const char *, const char *, const char *);
void LoadingScreen__hook(const char *text, const char *text1, const char *text2)
{
    //LOGI(MAKEOBF("CLoadingScreen::LoadingScreen: text: %s, text1: %s, text2: %s"), text, text1, text2);
    return LoadingScreen(text, text1, text2);
}

int (*LoadingScreenLoadingFile)(const char *);
int LoadingScreenLoadingFile__hook(const char *text) {
    //LOGI(MAKEOBF("CLoadingScreen::LoadingScreenLoadingFile: text: %s"), text);
    return LoadingScreenLoadingFile(text);
}

int CLoadingScreen::ResetLoadingScreenBar() { // РАБОТАЕТ!
    return CHook::CallFunction<int>(OBF("_Z21ResetLoadingScreenBarv"));
}

void CLoadingScreen::InjectHooks() {
    CHook::InlineHook(OBF("_Z13LoadingScreenPKcS0_S0_"), &LoadingScreen__hook, &LoadingScreen);
    CHook::InlineHook(OBF("_Z24LoadingScreenLoadingFilePKc"), &LoadingScreenLoadingFile__hook, &LoadingScreenLoadingFile);
    //CHook::InlineHook(OBF("_Z21ResetLoadingScreenBarv"), &ResetLoadingScreenBar__hook, &ResetLoadingScreenBar); - НЕ РАБОТАЕТ
}