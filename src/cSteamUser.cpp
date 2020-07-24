//----------------------------------------------------
// © 2015 Andrey Volia
// © 2016-2020 Francesco Balzani - thecocce
// 
// License: MIT
// Site: https://github.com/thecocce/steamwrapper
//----------------------------------------------------
#include "libMain.h"
#include <string>

using namespace std;

// returns the HSteamUser this interface represents
// this is only used internally by the API, and by a few select interfaces that support multi-user
HSteamUser SteamUser_GetSteamUser(){return SteamUser()->GetHSteamUser();};

// returns true if the Steam client current has a live connection to the Steam servers. 
// If false, it means there is no active connection due to either a networking issue on the local machine, or the Steam server is down/busy.
// The Steam client will automatically be trying to recreate the connection as often as possible.
bool SteamUser_IsLoggedOn(){return SteamUser()->BLoggedOn();};

string genString(uint64_t val)
{
	return std::to_string(val);
}

// returns the CSteamID of the account currently logged into the Steam client
// a CSteamID is a unique identifier for an account, and used to differentiate users in all parts of the Steamworks API
void SteamUser_GetSteamID(CSteamID & sid) {
	sid = SteamUser()->GetSteamID();
	#ifdef _DEBUG
		uint64 val = sid.ConvertToUint64();
		LogToFile("CSteamID:" + genString(val));
	#endif
};

// Multiplayer Authentication functions

// InitiateGameConnection() starts the state machine for authenticating the game client with the game server
// It is the client portion of a three-way handshake between the client, the game server, and the steam servers
//
// Parameters:
// void *AuthBlob - a pointer to empty memory that will be filled in with the authentication token.
// int MaxAuthBlob - the number of bytes of allocated memory in pBlob. Should be at least 2048 bytes.
// CSteamID steamIDGameServer - the steamID of the game server, received from the game server by the client
// CGameID gameID - the ID of the current game. For games without mods, this is just CGameID( <appID> )
// uint32 IPServer, uint16 PortServer - the IP address of the game server
// bool Secure - whether or not the client thinks that the game server is reporting itself as secure (i.e. VAC is running)
//
// return value - returns the number of bytes written to Blob. If the return is 0, then the buffer passed in was too small, and the call has failed
// The contents of Blob should then be sent to the game server, for it to use to complete the authentication process.
int SteamUser_InitiateGameConnection( void *AuthBlob, int MaxAuthBlob, CSteamID steamIDGameServer, uint32 IPServer, uint16 PortServer, bool Secure ){return SteamUser()->InitiateGameConnection(AuthBlob,MaxAuthBlob,steamIDGameServer,IPServer,PortServer,Secure);};

// notify of disconnect
// needs to occur when the game client leaves the specified game server, needs to match with the InitiateGameConnection() call
void SteamUser_TerminateGameConnection( uint32 IPServer, uint16 PortServer ){return SteamUser()->TerminateGameConnection(IPServer,PortServer);};

// Legacy functions

// used by only a few games to track usage events
void SteamUser_TrackAppUsageEvent( CGameID gameID, int AppUsageEvent, const char *ExtraInfo ){return SteamUser()->TrackAppUsageEvent(gameID, AppUsageEvent, ExtraInfo);};

// get the local storage folder for current Steam account to write application data, e.g. save games, configs etc.
// this will usually be something like "C:\Progam Files\Steam\userdata\<SteamID>\<AppID>\local"
bool SteamUser_GetUserDataFolder( char *Buffer, int cBuffer ){return SteamUser()->GetUserDataFolder(Buffer,cBuffer);};

// Starts voice recording. Once started, use GetVoice() to get the data
void SteamUser_StartVoiceRecording( ){return SteamUser()->StartVoiceRecording();};

// Stops voice recording. Because people often release push-to-talk keys early, the system will keep recording for
// a little bit after this function is called. GetVoice() should continue to be called until it returns
// k_eVoiceResultNotRecording
void SteamUser_StopVoiceRecording( ){return SteamUser()->StopVoiceRecording();};

// Determine the amount of captured audio data that is available in bytes.
// This provides both the compressed and uncompressed data. Please note that the uncompressed
// data is not the raw feed from the microphone: data may only be available if audible 
// levels of speech are detected.
// UncompressedVoiceDesiredSampleRate is necessary to know the number of bytes to return in cUncompressed - can be set to 0 if you don't need uncompressed (the usual case)
// If you're upgrading from an older Steamworks API, you'll want to pass in 11025 to nUncompressedVoiceDesiredSampleRate
EVoiceResult SteamUser_GetAvailableVoice( uint32 *Compressed, uint32 *cUncompressed, uint32 UncompressedVoiceDesiredSampleRate ){return SteamUser()->GetAvailableVoice(Compressed, cUncompressed, UncompressedVoiceDesiredSampleRate);};

// Gets the latest voice data from the microphone. Compressed data is an arbitrary format, and is meant to be handed back to 
// DecompressVoice() for playback later as a binary blob. Uncompressed data is 16-bit, signed integer, 11025Hz PCM format.
// Please note that the uncompressed data is not the raw feed from the microphone: data may only be available if audible 
// levels of speech are detected, and may have passed through denoising filters, etc.
// This function should be called as often as possible once recording has started; once per frame at least.
// BytesWritten is set to the number of bytes written to pDestBuffer. 
// UncompressedBytesWritten is set to the number of bytes written to UncompressedDestBuffer. 
// You must grab both compressed and uncompressed here at the same time, if you want both.
// Matching data that is not read during this call will be thrown away.
// GetAvailableVoice() can be used to determine how much data is actually available.
// If you're upgrading from an older Steamworks API, you'll want to pass in 11025 to UncompressedVoiceDesiredSampleRate
EVoiceResult SteamUser_GetVoice( bool WantCompressed, void *DestBuffer, uint32 cDestBufferSize, uint32 *BytesWritten, bool WantUncompressed, void *UncompressedDestBuffer, uint32 cUncompressedDestBufferSize, uint32 *nUncompressBytesWritten, uint32 UncompressedVoiceDesiredSampleRate ){return SteamUser()->GetVoice(WantCompressed, DestBuffer, cDestBufferSize, BytesWritten, WantUncompressed, UncompressedDestBuffer, cUncompressedDestBufferSize, nUncompressBytesWritten, UncompressedVoiceDesiredSampleRate);};

// Decompresses a chunk of compressed data produced by GetVoice().
// nBytesWritten is set to the number of bytes written to DestBuffer unless the return value is k_EVoiceResultBufferTooSmall.
// In that case, BytesWritten is set to the size of the buffer required to decompress the given
// data. The suggested buffer size for the destination buffer is 22 kilobytes.
// The output format of the data is 16-bit signed at the requested samples per second.
// If you're upgrading from an older Steamworks API, you'll want to pass in 11025 to DesiredSampleRate
EVoiceResult SteamUser_DecompressVoice( const void *Compressed, uint32 cCompressed, void *DestBuffer, uint32 DestBufferSize, uint32 *BytesWritten, uint32 DesiredSampleRate ){return SteamUser()->DecompressVoice(Compressed, cCompressed, DestBuffer, DestBufferSize, BytesWritten, DesiredSampleRate);};

// This returns the frequency of the voice data as it's stored internally; calling DecompressVoice() with this size will yield the best results
uint32 SteamUser_GetVoiceOptimalSampleRate(){return SteamUser()->GetVoiceOptimalSampleRate();};

// Retrieve ticket to be sent to the entity who wishes to authenticate you. 
// cTicket retrieves the length of the actual ticket.
HAuthTicket SteamUser_GetAuthSessionTicket( void *Ticket, int MaxTicket, uint32 *cTicket ){return SteamUser()->GetAuthSessionTicket(Ticket, MaxTicket, cTicket);};

// Authenticate ticket from entity steamID to be sure it is valid and isnt reused
// Registers for callbacks if the entity goes offline or cancels the ticket ( see ValidateAuthTicketResponse callback and EAuthSessionResponse )
EBeginAuthSessionResult SteamUser_BeginAuthSession( const void *AuthTicket, int cAuthTicket, CSteamID steamID ){return SteamUser()->BeginAuthSession(AuthTicket,cAuthTicket,steamID);};

// Stop tracking started by BeginAuthSession - called when no longer playing game with this entity
void SteamUser_EndAuthSession( CSteamID steamID ){return SteamUser()->EndAuthSession(steamID);};

// Cancel auth ticket from GetAuthSessionTicket, called when no longer playing game with the entity you gave the ticket to
void SteamUser_CancelAuthTicket( HAuthTicket AuthTicket ){return SteamUser()->CancelAuthTicket(AuthTicket);};

// After receiving a user's authentication data, and passing it to BeginAuthSession, use this function
// to determine if the user owns downloadable content specified by the provided AppID.
EUserHasLicenseForAppResult SteamUser_UserHasLicenseForApp( CSteamID steamID, AppId_t appID ){return SteamUser()->UserHasLicenseForApp(steamID,appID);};

// returns true if this users looks like they are behind a NAT device. Only valid once the user has connected to steam 
// (i.e a SteamServersConnected_t has been issued) and may not catch all forms of NAT.
bool SteamUser_IsBehindNAT(){return SteamUser()->BIsBehindNAT();};

// set data to be replicated to friends so that they can join your game
// CSteamID steamIDGameServer - the steamID of the game server, received from the game server by the client
// uint32 unIPServer, uint16 usPortServer - the IP address of the game server
void SteamUser_AdvertiseGame( CSteamID steamIDGameServer, uint32 IPServer, uint16 PortServer ){return SteamUser()->AdvertiseGame(steamIDGameServer, IPServer, PortServer);};

// Requests a ticket encrypted with an app specific shared key
// DataToInclude, cDataToInclude will be encrypted into the ticket
// ( This is asynchronous, you must wait for the ticket to be completed by the server )
SteamAPICall_t SteamUser_RequestEncryptedAppTicket( void *DataToInclude, int cDataToInclude ){return SteamUser()->RequestEncryptedAppTicket(DataToInclude, cDataToInclude);};

// retrieve a finished ticket
bool SteamUser_GetEncryptedAppTicket( void *Ticket, int MaxTicket, uint32 *cTicket ){return SteamUser()->GetEncryptedAppTicket(Ticket, MaxTicket, cTicket);};

// Trading Card badges data access
// if you only have one set of cards, the series will be 1
// the user has can have two different badges for a series; the regular (max level 5) and the foil (max level 1)
int SteamUser_GetGameBadgeLevel( int Series, bool Foil ){return SteamUser()->GetGameBadgeLevel(Series,Foil);};

// gets the Steam Level of the user, as shown on their profile
int SteamUser_GetPlayerSteamLevel(){return SteamUser()->GetPlayerSteamLevel();};