//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"

bool SteamApps_IsSubscribed(){return SteamApps()->BIsSubscribed();};
bool SteamApps_IsLowViolence(){return SteamApps()->BIsLowViolence();};
bool SteamApps_IsCybercafe(){return SteamApps()->BIsCybercafe();};
bool SteamApps_IsVACBanned(){return SteamApps()->BIsVACBanned();};
const char *SteamApps_GetCurrentGameLanguage(){return SteamApps()->GetCurrentGameLanguage();};
const char *SteamApps_GetAvailableGameLanguages(){return SteamApps()->GetAvailableGameLanguages();};

// only use this member if you need to check ownership of another game related to yours, a demo for example
bool SteamApps_IsSubscribedApp( AppId_t appID ){return SteamApps()->BIsSubscribedApp(appID);};

// Takes AppID of DLC and checks if the user owns the DLC & if the DLC is installed
bool SteamApps_IsDlcInstalled( AppId_t appID ){return SteamApps()->BIsDlcInstalled(appID);};

// returns the Unix time of the purchase of the app
uint32 SteamApps_GetEarliestPurchaseUnixTime( AppId_t nAppID ){return SteamApps()->GetEarliestPurchaseUnixTime(nAppID);};

// Checks if the user is subscribed to the current app through a free weekend
// This function will return false for users who have a retail or other type of license
// Before using, please ask your Valve technical contact how to package and secure your free weekened
bool SteamApps_IsSubscribedFromFreeWeekend(){return SteamApps()->BIsSubscribedFromFreeWeekend();};

// Returns the number of DLC pieces for the running app
int SteamApps_GetDLCCount(){return SteamApps()->GetDLCCount();};

// Returns metadata for DLC by index, of range [0, GetDLCCount()]
bool SteamApps_GetDLCDataByIndex( int DLC, AppId_t *AppID, bool *Available, char *Name, int NameBufferSize ){return SteamApps()->BGetDLCDataByIndex(DLC,AppID,Available,Name,NameBufferSize);};

// Install/Uninstall control for optional DLC
void SteamApps_InstallDLC( AppId_t AppID ){SteamApps()->InstallDLC(AppID); };
void SteamApps_UninstallDLC( AppId_t AppID ){SteamApps()->UninstallDLC(AppID); };

// Request cd-key for yourself or owned DLC. If you are interested in this
// data then make sure you provide us with a list of valid keys to be distributed
// to users when they purchase the game, before the game ships.
// You'll receive an AppProofOfPurchaseKeyResponse callback when
// the key is available (which may be immediately).
void SteamApps_RequestAppProofOfPurchaseKey( AppId_t AppID ){ SteamApps()->RequestAppProofOfPurchaseKey(AppID); };
// returns current beta branch name, 'public' is the default branch
bool SteamApps_GetCurrentBetaName( char *Name, int NameBufferSize ){return SteamApps()->GetCurrentBetaName(Name,NameBufferSize); }; 
// signal Steam that game files seems corrupt or missing
bool SteamApps_MarkContentCorrupt( bool MissingFilesOnly ){return SteamApps()->MarkContentCorrupt(MissingFilesOnly); }; 
// return installed depots in mount order
uint32 SteamApps_GetInstalledDepots( AppId_t appID, DepotId_t *Depots, uint32 MaxDepots ){return SteamApps()->GetInstalledDepots(appID,Depots,MaxDepots); }; 

// returns current app install folder for AppID, returns folder name length
uint32 SteamApps_GetAppInstallDir( AppId_t appID, char *Folder, uint32 FolderBufferSize ){return SteamApps()->GetAppInstallDir(appID,Folder,FolderBufferSize); };
// returns true if that app is installed (not necessarily owned)
bool SteamApps_IsAppInstalled( AppId_t appID ){return SteamApps()->BIsAppInstalled(appID); }; 

// returns the SteamID of the original owner. If different from current user, it's borrowed
CSteamID SteamApps_GetAppOwner(){return SteamApps()->GetAppOwner(); }; 

// Returns the associated launch param if the game is run via steam://run/<appid>//?param1=value1;param2=value2;param3=value3 etc.
// Parameter names starting with the character '@' are reserved for internal use and will always return and empty string.
// Parameter names starting with an underscore '_' are reserved for steam features -- they can be queried by the game,
// but it is advised that you not param names beginning with an underscore for your own features.
const char *SteamApps_GetLaunchQueryParam( const char *Key ){return SteamApps()->GetLaunchQueryParam(Key); };