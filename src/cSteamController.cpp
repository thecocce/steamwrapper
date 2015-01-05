//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"

// Must call init and shutdown when starting/ending use of the interface
bool SteamController_Init( const char *AbsolutePathToControllerConfigVDF ){return SteamController()->Init(AbsolutePathToControllerConfigVDF);};
bool SteamController_Shutdown(){return SteamController()->Shutdown();};

// Get the state of the specified controller, returns false if that controller is not connected
bool SteamController_GetState( uint32 ControllerIndex, SteamControllerState_t *State ){return SteamController()->GetControllerState(ControllerIndex,State);};

// Trigger a haptic pulse on the controller
void SteamController_TriggerHapticPulse( uint32 ControllerIndex, ESteamControllerPad TargetPad, unsigned short DurationMicroSec ){SteamController()->TriggerHapticPulse(ControllerIndex,TargetPad,DurationMicroSec);};

// Set the override mode which is used to choose to use different base/legacy bindings from your config file
void SteamController_SetOverrideMode( const char *Mode ){SteamController()->SetOverrideMode(Mode);};