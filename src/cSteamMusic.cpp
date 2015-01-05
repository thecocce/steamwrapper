//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"

bool SteamMusic_IsEnabled(){return SteamMusic()->BIsEnabled();};
bool SteamMusic_IsPlaying(){return SteamMusic()->BIsPlaying();};
	
AudioPlayback_Status SteamMusic_GetPlaybackStatus(){return SteamMusic()->GetPlaybackStatus();}; 

void SteamMusic_Play(){SteamMusic()->Play();};
void SteamMusic_Pause(){SteamMusic()->Pause();};
void SteamMusic_PlayPrevious(){SteamMusic()->PlayPrevious();};
void SteamMusic_PlayNext(){SteamMusic()->PlayNext();};

// volume is between 0.0 and 1.0
void SteamMusic_SetVolume( float Volume ){SteamMusic()->SetVolume(Volume);};
float SteamMusic_GetVolume(){return SteamMusic()->GetVolume();};