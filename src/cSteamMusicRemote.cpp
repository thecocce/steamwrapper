//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"

// Service Definition
bool SteamMusicRemote_RegisterSteamMusicRemote( const char *Name ){return SteamMusicRemote()->RegisterSteamMusicRemote(Name);};
bool SteamMusicRemote_DeregisterSteamMusicRemote(){return SteamMusicRemote()->DeregisterSteamMusicRemote();};
bool SteamMusicRemote_IsCurrentMusicRemote(){return SteamMusicRemote()->BIsCurrentMusicRemote();};
bool SteamMusicRemote_ActivationSuccess( bool Value ){return SteamMusicRemote()->BActivationSuccess(Value);};

bool SteamMusicRemote_SetDisplayName( const char *DisplayName ){return SteamMusicRemote()->SetDisplayName(DisplayName);};
bool SteamMusicRemote_SetPNGIcon_64x64( void *Buffer, uint32 BufferLength ){return SteamMusicRemote()->SetPNGIcon_64x64(Buffer,BufferLength);};

// Abilities for the user interface
bool SteamMusicRemote_EnablePlayPrevious(bool Value){return SteamMusicRemote()->EnablePlayPrevious(Value);};
bool SteamMusicRemote_EnablePlayNext( bool Value ){return SteamMusicRemote()->EnablePlayNext(Value);};
bool SteamMusicRemote_EnableShuffled( bool Value ){return SteamMusicRemote()->EnableShuffled(Value);};
bool SteamMusicRemote_EnableLooped( bool Value ){return SteamMusicRemote()->EnableLooped(Value);};
bool SteamMusicRemote_EnableQueue( bool Value ){return SteamMusicRemote()->EnableQueue(Value);};
bool SteamMusicRemote_EnablePlaylists( bool Value ){return SteamMusicRemote()->EnablePlaylists(Value);};

// Status
bool SteamMusicRemote_UpdatePlaybackStatus( AudioPlayback_Status Status ){return SteamMusicRemote()->UpdatePlaybackStatus(Status);};
bool SteamMusicRemote_UpdateShuffled( bool Value ){return SteamMusicRemote()->UpdateShuffled(Value);};
bool SteamMusicRemote_UpdateLooped( bool Value ){return SteamMusicRemote()->UpdateLooped(Value);};
bool SteamMusicRemote_UpdateVolume( float Value ){return SteamMusicRemote()->UpdateVolume(Value);}; // volume is between 0.0 and 1.0

// Current Entry
bool SteamMusicRemote_CurrentEntryWillChange(){return SteamMusicRemote()->CurrentEntryWillChange();};
bool SteamMusicRemote_CurrentEntryIsAvailable( bool Available ){return SteamMusicRemote()->CurrentEntryIsAvailable(Available);};
bool SteamMusicRemote_UpdateCurrentEntryText( const char *Text ){return SteamMusicRemote()->UpdateCurrentEntryText(Text);};
bool SteamMusicRemote_UpdateCurrentEntryElapsedSeconds( int Value ){return SteamMusicRemote()->UpdateCurrentEntryElapsedSeconds(Value);};
bool SteamMusicRemote_UpdateCurrentEntryCoverArt( void *Buffer, uint32 BufferLength ){return SteamMusicRemote()->UpdateCurrentEntryCoverArt(Buffer,BufferLength);};
bool SteamMusicRemote_CurrentEntryDidChange(){return SteamMusicRemote()->CurrentEntryDidChange();};

// Queue
bool SteamMusicRemote_QueueWillChange(){return SteamMusicRemote()->QueueWillChange();};
bool SteamMusicRemote_ResetQueueEntries(){return SteamMusicRemote()->ResetQueueEntries();};
bool SteamMusicRemote_SetQueueEntry( int ID, int Position, const char *EntryText ){return SteamMusicRemote()->SetQueueEntry(ID,Position,EntryText);};
bool SteamMusicRemote_SetCurrentQueueEntry( int ID ){return SteamMusicRemote()->SetCurrentQueueEntry(ID);};
bool SteamMusicRemote_QueueDidChange(){return SteamMusicRemote()->QueueDidChange();};

// Playlist
bool SteamMusicRemote_PlaylistWillChange(){return SteamMusicRemote()->PlaylistWillChange();};
bool SteamMusicRemote_ResetPlaylistEntries(){return SteamMusicRemote()->ResetPlaylistEntries();};
bool SteamMusicRemote_SetPlaylistEntry( int ID, int Position, const char *EntryText ){return SteamMusicRemote()->SetPlaylistEntry(ID,Position,EntryText);};
bool SteamMusicRemote_SetCurrentPlaylistEntry( int ID ){return SteamMusicRemote()->SetCurrentPlaylistEntry(ID);};
bool SteamMusicRemote_PlaylistDidChange(){return SteamMusicRemote()->PlaylistDidChange();};