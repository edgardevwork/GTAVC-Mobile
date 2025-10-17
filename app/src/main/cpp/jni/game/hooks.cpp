//
// Created by vadim on 11.06.2025.
//
#include "main.h"
#include "patches.h"
#include "CHooks.h"
#include "vendor/armhook/patch.h"
#include "hooks.h"
#include "game/RW/RenderWare.h"
#include "game/RW/immedi.h"
#include "CLoadingScreen.h"
#include "CMenuManager.h"
#include "CFileMgr.h"

struct CHID;

int (*Render2dStuff)();
int Render2dStuff_hook()
{
    //LOGI(MAKEOBF("aGameState: %i"), *(int *)(g_libGTAVC + (VER_x32 ? 0x7152BC : 0x991E84)));
    return Render2dStuff();
}

#include <string.h>
void (*NvUtilInit)(void);
void NvUtilInit_hook(void)
{
    NvUtilInit();
    //char* path = (char*)(g_libGTAVC + (VER_x32 ? 0x39476C : 0x577028));

    const size_t BUFFER_SIZE = 512; // Размер буфера заранее известен
    char* StorageRootBuffer = (char*)((uintptr_t)g_libGTAVC + (VER_x32 ? 0x751838 : 0x9C8E58));

    // Записываем строку с контролем длины
    strncpy(StorageRootBuffer, OBF("/storage/emulated/0/EdgarVC/"), BUFFER_SIZE - 1);
    StorageRootBuffer[BUFFER_SIZE - 1] = '\0';

    g_pStorage = (char *)(g_libGTAVC + (VER_x32 ? 0x751838 : 0x9C8E58));
    LOGI(MAKEOBF("PATH %s"),(char *)(g_libGTAVC + (VER_x32 ? 0x751838 : 0x9C8E58)));
}

bool(*MainGameTick)(float, CHID*);
static bool gameInitialized = true;
bool a7 = false;
bool MainGameTick_hook(float a1, CHID *a2)
{
    if (*(int *)(g_libGTAVC + (VER_x32 ? 0x7152BC : 0x991E84)) == 7) {
        if (a7) {
            if (!gameInitialized) { // EDGAR 3.0 StartGame
                    //int updated = CHook::CallFunction<int>("_Z14InitialiseGamev");
                    *(int *) (g_libGTAVC + (VER_x32 ? 0x7152BC : 0x991E84)) = 8; // gGameState
                    *(char *) (g_libGTAVC + (VER_x32 ? 0x5A9A6C : 0x79B4B8)) = 0; // byte_79B4B8
                    *(short *) (g_libGTAVC + (VER_x32 ? 0x5A9A40 : 0x79B48C)) = 0x0100; // if ( !(_BYTE)word_79B48C || byte_79B491 )
                    *(int *) (g_libGTAVC + (VER_x32 ? 0x714F20 : 0x991C3C)) = 0; // dword_991C3C / Показ легал
                    *(int *) (g_libGTAVC + (VER_x32 ? 0x5AA028 : 0x79B424)) = 1; // shownLegalScreen (true0/1false) / Легал
                    *(int *) (g_libGTAVC + (VER_x32 ? 0x39B5F0 : 0x57EF74)) = 0; // dword_57EF74
                    *(char *) (g_libGTAVC + (VER_x32 ? 0x5A9A45 : 0x79B491)) = 1; // byte_79B491
                    gameInitialized = true;
                    a7 = false;
                    return MainGameTick(a1, a2);
            }
        }
        if (!a7) {
            gameInitialized = false;
            a7 = true;
        }
    }
    //LOGI(MAKEOBF("MainGameTick called with a1: %f"), a1);
    return MainGameTick(a1, a2);
}

void Hooks::InstallCHooks()
{
    InjectHooks();
    CHooks::InitHooksEdgar();
    CHook::InlineHook(OBF("_Z10NvUtilInitv"), &NvUtilInit_hook, &NvUtilInit);
    CHook::InlineHook(OBF("_Z13Render2dStuffv"), &Render2dStuff_hook, &Render2dStuff);
    CHook::InlineHook(OBF("_Z12MainGameTickf"), &MainGameTick_hook, &MainGameTick);
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
    CFileMgr::InjectHooks();
}
