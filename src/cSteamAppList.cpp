//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"

uint32 SteamAppList_GetNumInstalledApps(){return SteamAppList()->GetNumInstalledApps();};
uint32 SteamAppList_GetInstalledApps( AppId_t *AppID, uint32 MaxAppIDs ){return SteamAppList()->GetInstalledApps(AppID,MaxAppIDs);};
// returns -1 if no name was found
int  SteamAppList_GetAppName( AppId_t AppID, char *Name, int NameMax){return SteamAppList()->GetAppName(AppID,Name,NameMax);}; 
// returns -1 if no dir was found
int  SteamAppList_GetAppInstallDir( AppId_t AppID, char *Directory, int NameMax ){return SteamAppList()->GetAppInstallDir(AppID,Directory,NameMax);}; 
// return the buildid of this app, may change at any time based on backend updates to the game
int SteamAppList_GetAppBuildId( AppId_t AppID ){return SteamAppList()->GetAppBuildId(AppID);}; 