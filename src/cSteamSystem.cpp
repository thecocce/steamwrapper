//----------------------------------------------------
// © 2015 Andrey Volia
// © 2016-2020 Francesco Balzani - thecocce
// 
// License: MIT
// Site: https://github.com/thecocce/steamwrapper
//----------------------------------------------------
#include "libMain.h"

using namespace std;

Log *pLog = new Log("debug.log");

// init and start wrapper
bool System_InitWrapper()
{
	//pLog = new Log("debug.log");
	LogToFile("System_InitWrapper");
	return SteamAPI_Init();
};

// shutdown wrapper
void System_ShutdownWrapper(){SteamAPI_Shutdown();};
// checks if a local Steam client is running 
bool System_IsSteamRunning(){return SteamAPI_IsSteamRunning();/*глючит проверь*/};
// Detects if your executable was launched through the Steam client, and restarts your game through 
// the client if necessary. The Steam client will be started if it is not running.
//
// Returns: true if your executable was NOT launched through the Steam client. This function will
//          then start your application through the client. Your current process should exit.
//
//          false if your executable was started through the Steam client or a steam_appid.txt file
//          is present in your game's directory (for development). Your current process should continue.
//
// NOTE: This function should be used only if you are using CEG or not using Steam's DRM. Once applied
//       to your executable, Steam's DRM will handle restarting through Steam if necessary.
bool System_RestartAppIfNecessary(uint32 OwnAppID){return SteamAPI_RestartAppIfNecessary(OwnAppID);};
// crash dump recording functions
void System_WriteMiniDump(uint32 StructuredExceptionCode, void* ExceptionInfo, uint32 BuildID){SteamAPI_WriteMiniDump(StructuredExceptionCode,ExceptionInfo,BuildID);};
void System_SetMiniDumpComment(const char *Msg){SteamAPI_SetMiniDumpComment(Msg);};
// To dispatch callbacks to registered listeners, call the function SteamAPI_RunCallbacks(). 
// It's best to call this at >10Hz, the more time between calls, the more potential latency 
// between receiving events or results from the Steam API. Most games call this once per render-frame. 
// All registered listener functions will be invoked during this call, in the callers thread context.
void System_RunCallbacks(){SteamAPI_RunCallbacks();};

void LogToFile(string str){
	pLog->Write(str);
}