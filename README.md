# ᐳ GTAVC-Source for GTA: Vice City Android

## ᐳ Description
> * **AArch**: `armeabi-v7a`, `arm64-v8a`  
> * **Platform**: `Android NDK`  
> * **Security / Hooking**: `DobbyHook`, `ShadowHook`  
> * **Status**: Work in Progress (WIP)

## ᐳ Features
> * Reverse-engineered RenderWare engine components: `RwWorld`, `RpSkin`, `RwCore`, `rphanim`, and more  
> * Game loop, camera, script handling  
> * Hooking via `CHooks`, `ARMHook`  
> * Native integration through `JNI_OnLoad`  
> * TODO: Online multiplayer support via plugin

## > CACHE
> * Чтобы запустить надо файл GTA3sfONLY.b акинуть в корень папки files/
> * И не обязательно поместить cache/data/main.txt/main.scm в files/data

## ᐳ Credits
> - [**EDGAR**](https://github.com/edgardevwork) — Main author
> - [**DobbyHook**](https://github.com/jmpews/Dobby) — Lightweight inline hook framework  
> - [**ShadowHook**](https://github.com/bytedance/android-inline-hook) — Android function hooking library by ByteDance
