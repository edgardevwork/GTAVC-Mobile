//
// Created by EDGAR 3.0 on 17.10.2025.
//
/*
    Plugin-SDK (Grand Theft Auto Vice City) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "main.h"
#include "patch.h"
#include "CMenuManager.h"
#include <chrono>

CMenuManager& FrontEndMenuManager = *(CMenuManager *)0x0;
CMenuScreen* aScreens = (CMenuScreen*)0x0;

void CMenuManager::MessageScreen(const char* pText, bool bFullscreen) {
    return CHook::CallFunction<void>("_ZN12CMenuManager13MessageScreenEPKcb", this, pText, bFullscreen);
}

int CMenuManager::FadeIn(int alpha) {
    return std::min(m_nMenuFadeAlpha, alpha);
}

bool CMenuManager::CheckHover(int x1, int x2, int y1, int y2) {
    bool x = m_nMousePosX > x1 && m_nMousePosX < x2;
    bool y = m_nMousePosY > y1 && m_nMousePosY < y2;
    return x && y;
}

int CMenuManager::DisplayHelperText(const char* text) {
    return CHook::CallFunction<int>("_ZN12CMenuManager17DisplayHelperTextEPc", this, text);
}

void CMenuManager::RequestFrontEndShutDown() {
    m_bShutDownFrontEndRequested = true;
}

void CMenuManager::RequestFrontEndStartUp() {
    m_bStartUpFrontEndRequested = true;
}

void CMenuManager::SwitchMenuOnAndOff() {
    return CHook::CallFunction<void>("_ZN12CMenuManager18SwitchMenuOnAndOffEv", this);
}

int CMenuManager::CheckSliderMovement(char value) {
    return CHook::CallFunction<int>("_ZN12CMenuManager19CheckSliderMovementEf", this, value);
}

void CMenuManager::Draw() {
    return CHook::CallFunction<void>("_ZN12CMenuManager4DrawEv", this);
}

void CMenuManager::PrintMap() {
    return CHook::CallFunction<void>("_ZN12CMenuManager8PrintMapEv", this);
}

void CMenuManager::SaveSettings() {
    return CHook::CallFunction<void>("_ZN12CMenuManager12SaveSettingsEv", this);
}

void CMenuManager::LoadSettings() {
    return CHook::CallFunction<void>("_ZN12CMenuManager12LoadSettingsEv", this);
}

// Hook functions
void (*CMenuManager__Draw)(CMenuManager*);
void CMenuManager__Draw__hook(CMenuManager* this_) {
    //LOGI(MAKEOBF("CMenuManager::Draw called at %p"), this_);
    return CMenuManager__Draw(this_);
}

void (*CMenuManager__PrintMap)(CMenuManager*);
void CMenuManager__PrintMap__hook(CMenuManager* this_) {
    //LOGI(MAKEOBF("CMenuManager::PrintMap called at %p"), this_);
    return CMenuManager__PrintMap(this_);
}

void (*CMenuManager__SaveSettings)(CMenuManager*);
void CMenuManager__SaveSettings__hook(CMenuManager* this_) {
    //LOGI(MAKEOBF("CMenuManager::SaveSettings called at %p"), this_);
    return CMenuManager__SaveSettings(this_);
}

void (*CMenuManager__LoadSettings)(CMenuManager*);
void CMenuManager__LoadSettings__hook(CMenuManager* this_) {
    //LOGI(MAKEOBF("CMenuManager::LoadSettings called at %p"), this_);
    return CMenuManager__LoadSettings(this_);
}

void (*CMenuManager__ProcessButtonPresses)(uintptr_t);

static std::chrono::steady_clock::time_point lastLogTime = std::chrono::steady_clock::now();
static bool gameInitialized = false;

void CMenuManager__ProcessButtonPresses__hook(uintptr_t thiz)
{
    auto now = std::chrono::steady_clock::now();
    //LOGI(MAKEOBF("aGameState: %i"), *(int*)(g_libGTAVC + 0x991E84));

    // Таймер 1 секунда
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - lastLogTime).count();
    if (elapsed >= 1) {
        if (!gameInitialized) {
            //int updated = CHook::CallFunction<int>("_Z14InitialiseGamev");
            //*(int *) (g_libGTAVC + 0x991E84) = 9;
            *(char*)(g_libGTAVC + 0x79B4B8) = 0;
            // Set word_79B48C to 0x0100 to make HIBYTE(word_79B48C) non-zero and !(_BYTE)word_79B48C true for LABEL_35
            *(short*)(g_libGTAVC + 0x79B48C) = 0x0100;
            // Set byte_79B491 to 1 to make the condition !(_BYTE)word_79B48C || byte_79B491 true
            *(char*)(g_libGTAVC + 0x79B491) = 1;
            // Set dword_991C3C to 0 for return condition
            *(int*)(g_libGTAVC + 0x991C3C) = 0;
            /**(short*)(g_libGTAVC + 0x6E00C0) = 0;
            *(int*)(g_libGTAVC + 0x6E0098) = 0;
            *(char*)(g_libGTAVC + 0x6E00D9) = 0;*/
            LOGI(MAKEOBF("Timer 1s: Updated: %i, aGameState: %i, char: %s"), 1,
                 *(int *) (g_libGTAVC + 0x991E84), *(char *) (g_libGTAVC + 0x79B4B8));
            gameInitialized = true;
        }
        lastLogTime = now;
    }

    //LOGI(MAKEOBF("CMenuManager::ProcessButtonPresses called at %p"), thiz);
    return CMenuManager__ProcessButtonPresses(thiz);
}

void (*CMenuManager__DrawLoadingScreen)(uintptr_t);
void CMenuManager__DrawLoadingScreen__hook(uintptr_t thiz)
{
    //LOGI(MAKEOBF("CMenuManager::DrawLoadingScreen called at %p"), thiz);
    return CMenuManager__DrawLoadingScreen(thiz);
}

void (*CMenuManager__MessageScreen)(CMenuManager*, const char*, bool);
void CMenuManager__MessageScreen__hook(CMenuManager* this_, const char* pText, bool bFullscreen) {
    //LOGI(MAKEOBF("CMenuManager::MessageScreen called at %p with text=%s, fullscreen=%d"), this_, pText, bFullscreen);
    return CMenuManager__MessageScreen(this_, pText, bFullscreen);
}

int (*CMenuManager__FadeIn)(CMenuManager*, int);
int CMenuManager__FadeIn__hook(CMenuManager* this_, int alpha) {
    //LOGI(MAKEOBF("CMenuManager::FadeIn called at %p with alpha=%d"), this_, alpha);
    return CMenuManager__FadeIn(this_, alpha);
}

bool (*CMenuManager__CheckHover)(CMenuManager*, int, int, int, int);
bool CMenuManager__CheckHover__hook(CMenuManager* this_, int x1, int x2, int y1, int y2) {
    //LOGI(MAKEOBF("CMenuManager::CheckHover called at %p with x1=%d, x2=%d, y1=%d, y2=%d"), this_, x1, x2, y1, y2);
    return CMenuManager__CheckHover(this_, x1, x2, y1, y2);
}

int (*CMenuManager__DisplayHelperText)(CMenuManager*, const char*);
int CMenuManager__DisplayHelperText__hook(CMenuManager* this_, const char* text) {
    //LOGI(MAKEOBF("CMenuManager::DisplayHelperText called at %p with text=%s"), this_, text);
    return CMenuManager__DisplayHelperText(this_, text);
}

void (*CMenuManager__RequestFrontEndShutDown)(CMenuManager*);
void CMenuManager__RequestFrontEndShutDown__hook(CMenuManager* this_) {
    //LOGI(MAKEOBF("CMenuManager::RequestFrontEndShutDown called at %p"), this_);
    return CMenuManager__RequestFrontEndShutDown(this_);
}

void (*CMenuManager__RequestFrontEndStartUp)(CMenuManager*);
void CMenuManager__RequestFrontEndStartUp__hook(CMenuManager* this_) {
    //LOGI(MAKEOBF("CMenuManager::RequestFrontEndStartUp called at %p"), this_);
    return CMenuManager__RequestFrontEndStartUp(this_);
}

void (*CMenuManager__SwitchMenuOnAndOff)(CMenuManager*);
void CMenuManager__SwitchMenuOnAndOff__hook(CMenuManager* this_) {
    //LOGI(MAKEOBF("CMenuManager::SwitchMenuOnAndOff called at %p"), this_);
    return CMenuManager__SwitchMenuOnAndOff(this_);
}

int (*CMenuManager__CheckSliderMovement)(CMenuManager*, float);
int CMenuManager__CheckSliderMovement__hook(CMenuManager* this_, float value) {
    //LOGI(MAKEOBF("CMenuManager::CheckSliderMovement called at %p with value=%f"), this_, value);
    return CMenuManager__CheckSliderMovement(this_, value);
}

void (*CMenuManager__Process)(CMenuManager*);
void CMenuManager__Process__hook(CMenuManager* this_) {
    //LOGI(MAKEOBF("CMenuManager::Process called at %p"), this_);
    return CMenuManager__Process(this_);
}

void CMenuManager::InjectHooks() {
    CHook::InlineHook(OBF("_ZN12CMenuManager4DrawEv"), &CMenuManager__Draw__hook, &CMenuManager__Draw);
    CHook::InlineHook(OBF("_ZN12CMenuManager8PrintMapEv"), &CMenuManager__PrintMap__hook, &CMenuManager__PrintMap);
    CHook::InlineHook(OBF("_ZN12CMenuManager12SaveSettingsEv"), &CMenuManager__SaveSettings__hook, &CMenuManager__SaveSettings);
    CHook::InlineHook(OBF("_ZN12CMenuManager12LoadSettingsEv"), &CMenuManager__LoadSettings__hook, &CMenuManager__LoadSettings);
    CHook::InlineHook(OBF("_ZN12CMenuManager13MessageScreenEPKcb"), &CMenuManager__MessageScreen__hook, &CMenuManager__MessageScreen);
    CHook::InlineHook(OBF("_ZN12CMenuManager20ProcessButtonPressesEv"), &CMenuManager__ProcessButtonPresses__hook, &CMenuManager__ProcessButtonPresses);
    CHook::InlineHook(OBF("_ZN12CMenuManager17DrawLoadingScreenEv"), &CMenuManager__DrawLoadingScreen__hook, &CMenuManager__DrawLoadingScreen);
    CHook::InlineHook(OBF("_ZN12CMenuManager6FadeInEi"), &CMenuManager__FadeIn__hook, &CMenuManager__FadeIn);
    CHook::InlineHook(OBF("_ZN12CMenuManager10CheckHoverEiiii"), &CMenuManager__CheckHover__hook, &CMenuManager__CheckHover);
    CHook::InlineHook(OBF("_ZN12CMenuManager17DisplayHelperTextEPc"), &CMenuManager__DisplayHelperText__hook, &CMenuManager__DisplayHelperText);
    CHook::InlineHook(OBF("_ZN12CMenuManager23RequestFrontEndShutDownEv"), &CMenuManager__RequestFrontEndShutDown__hook, &CMenuManager__RequestFrontEndShutDown);
    CHook::InlineHook(OBF("_ZN12CMenuManager22RequestFrontEndStartUpEv"), &CMenuManager__RequestFrontEndStartUp__hook, &CMenuManager__RequestFrontEndStartUp);
    CHook::InlineHook(OBF("_ZN12CMenuManager18SwitchMenuOnAndOffEv"), &CMenuManager__SwitchMenuOnAndOff__hook, &CMenuManager__SwitchMenuOnAndOff);
    CHook::InlineHook(OBF("_ZN12CMenuManager19CheckSliderMovementEf"), &CMenuManager__CheckSliderMovement__hook, &CMenuManager__CheckSliderMovement);
    CHook::InlineHook(OBF("_ZN12CMenuManager7ProcessEv"), &CMenuManager__Process__hook, &CMenuManager__Process);
}
