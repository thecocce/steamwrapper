//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"

// Init Steam game server
bool SteamServer_Init( uint32 IP, uint16 GamePort, uint16 QueryPort, uint32 Flags, EServerMode ServerMode, const char *VersionString ){return SteamGameServer_Init(IP,GamePort,QueryPort,Flags,ServerMode,VersionString);};
// Shutdown
void SteamServer_Shutdown(){SteamGameServer_Shutdown();};

//---------------------------------------------
// Basic server data.  These properties, if set, must be set before before calling LogOn.  They
// may not be changed after logged in.

// Game product identifier.  This is currently used by the master server for version checking purposes.
// It's a required field, but will eventually will go away, and the AppID will be used for this purpose.
void SteamServer_SetProduct( const char *Product ){SteamGameServer()->SetProduct(Product);};
// Description of the game.  This is a required field and is displayed in the steam server browser....for now.
// This is a required field, but it will go away eventually, as the data should be determined from the AppID.
void SteamServer_SetGameDescription( const char *GameDescription ){SteamGameServer()->SetGameDescription(GameDescription);};
// If your game is a "mod," pass the string that identifies it.  The default is an empty string, meaning
// this application is the original game, not a mod.
//
// see k_cbMaxSteamGameServer()GameDir
void SteamServer_SetModDir( const char *ModDir ){SteamGameServer()->SetModDir(ModDir);};
// Is this is a dedicated server?  The default value is false.
void SteamServer_SetDedicatedServer( bool Dedicated ){SteamGameServer()->SetDedicatedServer(Dedicated);};

//---------------------------------------------
// Login

// Begin process to login to a persistent game server account
//
// You need to register for callbacks to determine the result of this operation.
// see SteamServersConnected,SteamServerConnectFailure,SteamServersDisconnected
void SteamServer_LogOn( const char *Token ){return SteamGameServer()->LogOn(Token);};

// Login to a generic, anonymous account.
//
// Note: in previous versions of the SDK, this was automatically,
// but this is no longer the case.
void SteamServer_LogOnAnonymous(){SteamGameServer()->LogOnAnonymous();};

// Begin process of logging game server out of steam
void SteamServer_LogOff(){SteamGameServer()->LogOff();};

// status functions
bool SteamServer_IsLoggedOn(){return SteamGameServer()->BLoggedOn();};
bool SteamServer_IsSecure(){return SteamGameServer()->BSecure();}; 
CSteamID SteamServer_GetSteamID(){return SteamGameServer()->GetSteamID();};

// Returns true if the master server has requested a restart.
// Only returns true once per request.
bool SteamServer_WasRestartRequested(){return SteamGameServer()->WasRestartRequested();};

//---------------------------------------------
// Server state.  These properties may be changed at any time.

// Max player count that will be reported to server browser and client queries
void SteamServer_SetMaxPlayerCount( int PlayersMax ){SteamGameServer()->SetMaxPlayerCount(PlayersMax);};

// Number of bots.  Default value is zero
void SteamServer_SetBotPlayerCount( int Botplayers ){SteamGameServer()->SetBotPlayerCount(Botplayers);};

// Set the name of server as it will appear in the server browser
//
// see k_cbMaxSteamGameServer()Name
void SteamServer_SetServerName( const char *ServerName ){return SteamGameServer()->SetServerName(ServerName);};

// Set name of map to report in the server browser
//
// see k_cbMaxSteamGameServer()Name
void SteamServer_SetMapName( const char *MapName ){SteamGameServer()->SetMapName(MapName);};

// Let people know if your server will require a password
void SteamServer_SetPasswordProtected( bool PasswordProtected ){SteamGameServer()->SetPasswordProtected(PasswordProtected);};

// Spectator server. The default value is zero, meaning the service
// is not used.
void SteamServer_SetSpectatorPort( uint16 SpectatorPort ){SteamGameServer()->SetSpectatorPort(SpectatorPort);};

// Name of the spectator server.  (Only used if spectator port is nonzero.)
//
// see k_cbMaxSteamGameServer()MapName
void SteamServer_SetSpectatorServerName( const char *SpectatorServerName ){SteamGameServer()->SetSpectatorServerName(SpectatorServerName);};

// Call this to clear the whole list of key/values that are sent in rules queries.
void SteamServer_ClearAllKeyValues(){SteamGameServer()->ClearAllKeyValues();};

// Call this to add/update a key/value pair.
void SteamServer_SetKeyValue( const char *Key, const char *Value ){SteamGameServer()->SetKeyValue(Key,Value);};

// Sets a string defining the "gametags" for this server, this is optional, but if it is set
// it allows users to filter in the matchmaking/server-browser interfaces based on the value
//
// see k_cbMaxSteamGameServer()Tags
void SteamServer_SetGameTags( const char *GameTags ){SteamGameServer()->SetGameTags(GameTags);};

// Sets a string defining the "gamedata" for this server, this is optional, but if it is set
// it allows users to filter in the matchmaking/server-browser interfaces based on the value
// don't set this unless it actually changes, its only uploaded to the master once (when
// acknowledged)
//
// see k_cbMaxSteamGameServer()GameData
void SteamServer_SetGameData( const char *GameData ){return SteamGameServer()->SetGameData(GameData);};

// Region identifier.  This is an optional field, the default value is empty, meaning the "world" region
void SteamServer_SetRegion( const char *Region ){SteamGameServer()->SetRegion(Region);};

//---------------------------------------------
// Player list management / authentication

// Handles receiving a new connection from a Steam user.  This call will ask the Steam
// servers to validate the users identity, app ownership, and VAC status.  If the Steam servers 
// are off-line, then it will validate the cached ticket itself which will validate app ownership 
// and identity.  The AuthBlob here should be acquired on the game client using SteamUser->InitiateGameConnection()
// and must then be sent up to the game server for authentication.
//
// Return Value: returns true if the users ticket passes basic checks. pSteamIDUser will contain the Steam ID of this user. pSteamIDUser must NOT be NULL
// If the call succeeds then you should expect a GSClientApprove_t or GSClientDeny_t callback which will tell you whether authentication
// for the user has succeeded or failed (the steamid in the callback will match the one returned by this call)
bool SteamServer_SendUserConnectAndAuthenticate( uint32 unIPClient, const void *AuthBlob, uint32 AuthBlobSize, CSteamID *SteamIDUser ){return SteamGameServer()->SendUserConnectAndAuthenticate(unIPClient,AuthBlob,AuthBlobSize,SteamIDUser);};

// Creates a fake user (ie, a bot) which will be listed as playing on the server, but skips validation.  
// 
// Return Value: Returns a SteamID for the user to be tracked with, you should call HandleUserDisconnect()
// when this user leaves the server just like you would for a real user.
CSteamID SteamServer_CreateUnauthenticatedUserConnection(){return SteamGameServer()->CreateUnauthenticatedUserConnection();};

// Should be called whenever a user leaves our game server, this lets Steam internally
// track which users are currently on which servers for the purposes of preventing a single
// account being logged into multiple servers, showing who is currently on a server, etc.
void SteamServer_SendUserDisconnect( CSteamID steamIDUser ){return SteamGameServer()->SendUserDisconnect(steamIDUser);};

// Update the data to be displayed in the server browser and matchmaking interfaces for a user
// currently connected to the server.  For regular users you must call this after you receive a
// GSUserValidationSuccess callback.
// 
// Return Value: true if successful, false if failure (ie, steamIDUser wasn't for an active player)
bool SteamServer_UpdateUserData( CSteamID steamIDUser, const char *PlayerName, uint32 Score ){return SteamGameServer()->BUpdateUserData(steamIDUser,PlayerName,Score);};

// New auth system APIs - do not mix with the old auth system APIs.
// ----------------------------------------------------------------

// Retrieve ticket to be sent to the entity who wishes to authenticate you ( using BeginAuthSession API ). 
// cTicket retrieves the length of the actual ticket.
HAuthTicket SteamServer_GetAuthSessionTicket( void *Ticket, int MaxTicket, uint32 *cTicket ){return SteamGameServer()->GetAuthSessionTicket(Ticket,MaxTicket,cTicket);};

// Authenticate ticket ( from GetAuthSessionTicket ) from entity steamID to be sure it is valid and isnt reused
// Registers for callbacks if the entity goes offline or cancels the ticket ( see ValidateAuthTicketResponse_t callback and EAuthSessionResponse )
EBeginAuthSessionResult SteamServer_BeginAuthSession( const void *AuthTicket, int cAuthTicket, CSteamID steamID ){return SteamGameServer()->BeginAuthSession(AuthTicket,cAuthTicket,steamID);};

// Stop tracking started by BeginAuthSession - called when no longer playing game with this entity
void SteamServer_EndAuthSession( CSteamID steamID ){return SteamGameServer()->EndAuthSession(steamID);};

// Cancel auth ticket from GetAuthSessionTicket, called when no longer playing game with the entity you gave the ticket to
void SteamServer_CancelAuthTicket( HAuthTicket AuthTicket ){return SteamGameServer()->CancelAuthTicket(AuthTicket);};

// After receiving a user's authentication data, and passing it to SendUserConnectAndAuthenticate, use this function
// to determine if the user owns downloadable content specified by the provided AppID.
EUserHasLicenseForAppResult SteamServer_UserHasLicenseForApp( CSteamID steamID, AppId_t appID ){return SteamGameServer()->UserHasLicenseForApp(steamID,appID);};

// Ask if a user in in the specified group, results returns async by GSUserGroupStatus_t
// returns false if we're not connected to the steam servers and thus cannot ask
bool SteamServer_RequestUserGroupStatus( CSteamID steamIDUser, CSteamID steamIDGroup ){return SteamGameServer()->RequestUserGroupStatus(steamIDUser,steamIDGroup);};

// Returns the public IP of the server according to Steam, useful when the server is 
// behind NAT and you want to advertise its IP in a lobby for other clients to directly
// connect to
uint32 SteamServer_GetPublicIP(){return SteamGameServer()->GetPublicIP();};

// These are in GameSocketShare mode, where instead of SteamGameServer creating its own
// socket to talk to the master server on, it lets the game use its socket to forward messages
// back and forth. This prevents us from requiring server ops to open up yet another port
// in their firewalls.
//
// the IP address and port should be in host order, i.e 127.0.0.1 == 0x7f000001

// These are used when you've elected to multiplex the game server's UDP socket
// rather than having the master server updater use its own sockets.
// 
// Source games use this to simplify the job of the server admins, so they 
// don't have to open up more ports on their firewalls.

// Call this when a packet that starts with 0xFFFFFFFF comes in. That means
// it's for us.
bool SteamServer_HandleIncomingPacket( const void *Data, int cData, uint32 srcIP, uint16 srcPort ){return SteamGameServer()->HandleIncomingPacket(Data,cData,srcIP,srcPort);};

// AFTER calling HandleIncomingPacket for any packets that came in that frame, call this.
// This gets a packet that the master server updater needs to send out on UDP.
// It returns the length of the packet it wants to send, or 0 if there are no more packets to send.
// Call this each frame until it returns 0.
int SteamServer_GetNextOutgoingPacket( void *Out, int cMaxOut, uint32 *NetAdr, uint16 *Port ){return SteamGameServer()->GetNextOutgoingPacket(Out,cMaxOut,NetAdr,Port);};

//---------------------------------------------
// Control heartbeats / advertisement with master server

// Call this as often as you like to tell the master server updater whether or not
// you want it to be active (default: off).
void SteamServer_EnableHeartbeats( bool Active ){SteamGameServer()->EnableHeartbeats(Active);};

// You usually don't need to modify this.
// Pass -1 to use the default value for iHeartbeatInterval.
// Some mods change this.
void SteamServer_SetHeartbeatInterval( int HeartbeatInterval ){SteamGameServer()->SetHeartbeatInterval(HeartbeatInterval);};

// Force a heartbeat to steam at the next opportunity
void SteamServer_ForceHeartbeat(){return SteamGameServer()->ForceHeartbeat();};

// associate this game server with this clan for the purposes of computing player compat
SteamAPICall_t SteamServer_AssociateWithClan( CSteamID steamIDClan ){return SteamGameServer()->AssociateWithClan(steamIDClan);};

// ask if any of the current players dont want to play with this new player - or vice versa
SteamAPICall_t SteamServer_ComputeNewPlayerCompatibility( CSteamID steamIDNewPlayer ){return SteamGameServer()->ComputeNewPlayerCompatibility(steamIDNewPlayer);};