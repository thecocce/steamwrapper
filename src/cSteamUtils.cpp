//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"

// return the number of seconds since the user 
uint32 SteamUtils_GetSecondsSinceAppActive(){return SteamUtils()->GetSecondsSinceAppActive();};
uint32 SteamUtils_GetSecondsSinceComputerActive(){return SteamUtils()->GetSecondsSinceComputerActive();};

// the universe this client is connecting to
EUniverse SteamUtils_GetConnectedUniverse(){return SteamUtils()->GetConnectedUniverse();};

// Steam server time - in PST, number of seconds since January 1, 1970 (i.e unix time)
uint32 SteamUtils_GetServerRealTime(){return SteamUtils()->GetServerRealTime();};

// returns the 2 digit ISO 3166-1-alpha-2 format country code this client is running in (as looked up via an IP-to-location database)
// e.g "US" or "UK".
const char *SteamUtils_GetIPCountry(){return SteamUtils()->GetIPCountry();};

// returns true if the image exists, and valid sizes were filled out
bool SteamUtils_GetImageSize( int Image, uint32 *Width, uint32 *Height ){return SteamUtils()->GetImageSize(Image,Width,Height);};

// returns true if the image exists, and the buffer was successfully filled out
// results are returned in RGBA format
// the destination buffer size should be 4 * height * width * sizeof(char)
bool SteamUtils_GetImageRGBA( int Image, uint8 *Dest, int DestBufferSize ){return SteamUtils()->GetImageRGBA(Image,Dest,DestBufferSize);};

// returns the IP of the reporting server for valve - currently only used in Source engine games
bool SteamUtils_GetCSERIPPort( uint32 *IP, uint16 *Port ){return SteamUtils()->GetCSERIPPort(IP,Port);};

// return the amount of battery power left in the current system in % [0..100], 255 for being on AC power
uint8 SteamUtils_GetCurrentBatteryPower(){return SteamUtils()->GetCurrentBatteryPower();};

// returns the appID of the current process
uint32 SteamUtils_GetAppID(){return SteamUtils()->GetAppID();};

// Sets the position where the overlay instance for the currently calling game should show notifications.
// This position is per-game and if this function is called from outside of a game context it will do nothing.
void SteamUtils_SetOverlayNotificationPosition( ENotificationPosition NotificationPosition ){return SteamUtils()->SetOverlayNotificationPosition(NotificationPosition);};

// API asynchronous call results
// can be used directly, but more commonly used via the callback dispatch API
bool SteamUtils_IsAPICallCompleted( SteamAPICall_t SteamAPICall, bool *Failed ){return SteamUtils()->IsAPICallCompleted(SteamAPICall,Failed);};
ESteamAPICallFailure SteamUtils_GetAPICallFailureReason( SteamAPICall_t SteamAPICall ){return SteamUtils()->GetAPICallFailureReason(SteamAPICall);};
bool SteamUtils_GetAPICallResult( SteamAPICall_t SteamAPICall, void *Callback, int cCallback, int CallbackExpected, bool *Failed ){return SteamUtils()->GetAPICallResult(SteamAPICall, Callback, cCallback, CallbackExpected, Failed);};

// returns the number of IPC calls made since the last time this function was called
// Used for perf debugging so you can understand how many IPC calls your game makes per frame
// Every IPC call is at minimum a thread context switch if not a process one so you want to rate
// control how often you do them.
uint32 SteamUtils_GetIPCCallCount(){return SteamUtils()->GetIPCCallCount();};

// API warning handling
// 'int' is the severity; 0 for msg, 1 for warning
// 'const char *' is the text of the message
// callbacks will occur directly after the API function is called that generated the warning or message
void SteamUtils_SetWarningMessageHook( SteamAPIWarningMessageHook_t Function ){return SteamUtils()->SetWarningMessageHook(Function);};

// Returns true if the overlay is running & the user can access it. The overlay process could take a few seconds to
// start & hook the game process, so this function will initially return false while the overlay is loading.
bool SteamUtils_IsOverlayEnabled(){return SteamUtils()->IsOverlayEnabled();};

// Normally this call is unneeded if your game has a constantly running frame loop that calls the 
// D3D Present API, or OGL SwapBuffers API every frame.
//
// However, if you have a game that only refreshes the screen on an event driven basis then that can break 
// the overlay, as it uses your Present/SwapBuffers calls to drive it's internal frame loop and it may also
// need to Present() to the screen any time an even needing a notification happens or when the overlay is
// brought up over the game by a user.  You can use this API to ask the overlay if it currently need a present
// in that case, and then you can check for this periodically (roughly 33hz is desirable) and make sure you
// refresh the screen with Present or SwapBuffers to allow the overlay to do it's work.
bool SteamUtils_OverlayNeedsPresent(){return SteamUtils()->BOverlayNeedsPresent();};

// Activates the Big Picture text input dialog which only supports gamepad input
bool SteamUtils_ShowGamepadTextInput( EGamepadTextInputMode InputMode, EGamepadTextInputLineMode LineInputMode, const char *Description, uint32 CharMax, const char *ExistingText ){return SteamUtils()->ShowGamepadTextInput(InputMode, LineInputMode, Description, CharMax, ExistingText);};

// Returns previously entered text & length
uint32 SteamUtils_GetEnteredGamepadTextLength(){return SteamUtils()->GetEnteredGamepadTextLength();};
bool SteamUtils_GetEnteredGamepadTextInput( char *Text, uint32 cText ){return SteamUtils()->GetEnteredGamepadTextInput(Text,cText);};

// returns the language the steam client is running in, you probably want ISteamApps::GetCurrentGameLanguage instead, this is for very special usage cases
const char *SteamUtils_GetSteamUILanguage(){return SteamUtils()->GetSteamUILanguage();};

// returns true if Steam itself is running in VR mode
bool SteamUtils_IsSteamRunningInVR(){return SteamUtils()->IsSteamRunningInVR();};