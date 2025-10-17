//
// Created by AORUS on 17.10.2025.
//

#include "CFileMgr.h"
#include "patch.h"

int (*CFileMgr__OpenUserFile)(CFileMgr*, const char*, const char*);
int CFileMgr__OpenUserFile__hook(CFileMgr* thiz, const char* a1, const char* a2)
{
    LOGI(MAKEOBF("Open Files %s"), (const char *)thiz);
    if(!strncmp((const char *)thiz, "GTA3sf", 6))
    {
        LOGI(MAKEOBF("Подмена файла: - > %s"), (const char *)thiz);
        //thiz = VER_x32 ? (CFileMgr*)"GTA3sf32.b" : (CFileMgr*)"GTA3sf64.b";
        thiz = (CFileMgr*)"GTA3sfONLY.b";
        LOGI(MAKEOBF("На: - > %s"), (const char *)thiz);
    }
    return CFileMgr__OpenUserFile(thiz, a1, a2);
}

void CFileMgr::InjectHooks() {
    CHook::InlineHook("_ZN8CFileMgr12OpenUserFileEPKcS1_", &CFileMgr__OpenUserFile__hook, &CFileMgr__OpenUserFile);
}
