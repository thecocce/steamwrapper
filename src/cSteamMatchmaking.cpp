//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"




// Purpose: Callback from Steam telling us about a server that has responded
void CSteamMatchmakingServerListResponse::ServerResponded( HServerListRequest hReq, int iServer ) { OnServerFailedToRespondCallback(hReq,iServer); };

// Purpose: Callback from Steam telling us about a server that has failed to respond
void CSteamMatchmakingServerListResponse::ServerFailedToRespond( HServerListRequest hReq, int iServer ) { OnServerFailedToRespondCallback(hReq,iServer); };

// Purpose: Callback from Steam telling us a refresh is complete
void CSteamMatchmakingServerListResponse::RefreshComplete( HServerListRequest hReq, EMatchMakingServerResponse response ) { OnServerRefreshCompleteCallback(hReq,response); };

CSteamMatchmakingServerListResponse::CSteamMatchmakingServerListResponse(tOnServerResponded a,tOnServerFailedToRespond b,tOnServerRefreshComplete c)
{
	OnServerRespondedCallback = a;
	OnServerFailedToRespondCallback = b;
	OnServerRefreshCompleteCallback = c;
}

std::vector<CSteamMatchmakingServerListResponse*> ServerBrowsers;

//------------------------------
// matchmaking

// game server favorites storage
// saves basic details about a multiplayer game server locally
// returns the number of favorites servers the user has stored
int SteamMatchmaking_GetFavoriteGameCount(){return SteamMatchmaking()->GetFavoriteGameCount();};

// returns the details of the game server
// iGame is of range [0,GetFavoriteGameCount())
// *IP, *ConnPort are filled in the with IP:port of the game server
// *Flags specify whether the game server was stored as an explicit favorite or in the history of connections
// *RTime32LastPlayedOnServer is filled in the with the Unix time the favorite was added
bool SteamMatchmaking_GetFavoriteGame( int Game, AppId_t *AppID, uint32 *IP, uint16 *ConnPort, uint16 *QueryPort, uint32 *Flags, uint32 *RTime32LastPlayedOnServer ){return SteamMatchmaking()->GetFavoriteGame(Game, AppID, IP, ConnPort, QueryPort, Flags, RTime32LastPlayedOnServer);};

// adds the game server to the local list; updates the time played of the server if it already exists in the list
int SteamMatchmaking_AddFavoriteGame( AppId_t AppID, uint32 IP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer ){return SteamMatchmaking()->AddFavoriteGame( AppID, IP, nConnPort, nQueryPort, unFlags, rTime32LastPlayedOnServer);};

// removes the game server from the local storage; returns true if one was removed
bool SteamMatchmaking_RemoveFavoriteGame( AppId_t AppID, uint32 IP, uint16 ConnPort, uint16 QueryPort, uint32 Flags ){return SteamMatchmaking()->RemoveFavoriteGame(AppID, IP, ConnPort, QueryPort, Flags);};

///////
// Game lobby functions

// Get a list of relevant lobbies
// this is an asynchronous request
// results will be returned by LobbyMatchList callback & call result, with the number of lobbies found
// this will never return lobbies that are full
// to add more filter, the filter calls below need to be call before each and every RequestLobbyList() call
SteamAPICall_t SteamMatchmaking_RequestLobbyList(){return SteamMatchmaking()->RequestLobbyList();};
// filters for lobbies
// this needs to be called before RequestLobbyList() to take effect
// these are cleared on each call to RequestLobbyList()
void SteamMatchmaking_AddRequestLobbyListStringFilter( const char *KeyToMatch, const char *ValueToMatch, ELobbyComparison ComparisonType ){return SteamMatchmaking()->AddRequestLobbyListStringFilter(KeyToMatch, ValueToMatch, ComparisonType);};
// numerical comparison
void SteamMatchmaking_AddRequestLobbyListNumericalFilter( const char *KeyToMatch, int ValueToMatch, ELobbyComparison ComparisonType ){return SteamMatchmaking()->AddRequestLobbyListNumericalFilter(KeyToMatch, ValueToMatch, ComparisonType);};
// returns results closest to the specified value. Multiple near filters can be added, with early filters taking precedence
void SteamMatchmaking_AddRequestLobbyListNearValueFilter( const char *KeyToMatch, int ValueToBeCloseTo ){return SteamMatchmaking()->AddRequestLobbyListNearValueFilter(KeyToMatch,ValueToBeCloseTo);};
// returns only lobbies with the specified number of slots available
void SteamMatchmaking_AddRequestLobbyListFilterSlotsAvailable( int SlotsAvailable ){return SteamMatchmaking()->AddRequestLobbyListFilterSlotsAvailable(SlotsAvailable);};
// sets the distance for which we should search for lobbies (based on users IP address to location map on the Steam backed)
void SteamMatchmaking_AddRequestLobbyListDistanceFilter( ELobbyDistanceFilter LobbyDistanceFilter ){return SteamMatchmaking()->AddRequestLobbyListDistanceFilter(LobbyDistanceFilter);};
// sets how many results to return, the lower the count the faster it is to download the lobby results & details to the client
void SteamMatchmaking_AddRequestLobbyListResultCountFilter( int cMaxResults ){return SteamMatchmaking()->AddRequestLobbyListResultCountFilter(cMaxResults);};

void SteamMatchmaking_AddRequestLobbyListCompatibleMembersFilter( CSteamID steamIDLobby ){return SteamMatchmaking()->AddRequestLobbyListCompatibleMembersFilter(steamIDLobby);};

// returns the CSteamID of a lobby, as retrieved by a RequestLobbyList call
// should only be called after a LobbyMatchList callback is received
// Lobby is of the range [0, LobbyMatchList-LobbiesMatching)
// the returned CSteamID::IsValid() will be false if iLobby is out of range
CSteamID SteamMatchmaking_GetLobbyByIndex( int Lobby ){return SteamMatchmaking()->GetLobbyByIndex(Lobby);};

// Create a lobby on the Steam servers.
// If private, then the lobby will not be returned by any RequestLobbyList() call; the CSteamID
// of the lobby will need to be communicated via game channels or via InviteUserToLobby()
// this is an asynchronous request
// results will be returned by LobbyCreated callback and call result; lobby is joined & ready to use at this point
// a LobbyEnter callback will also be received (since the local user is joining their own lobby)
SteamAPICall_t SteamMatchmaking_CreateLobby( ELobbyType LobbyType, int MaxMembers ){return SteamMatchmaking()->CreateLobby(LobbyType,MaxMembers);};

// Joins an existing lobby
// this is an asynchronous request
// results will be returned by LobbyEnter callback & call result, check m_EChatRoomEnterResponse to see if was successful
// lobby metadata is available to use immediately on this call completing
SteamAPICall_t SteamMatchmaking_JoinLobby( CSteamID steamIDLobby ){return SteamMatchmaking()->JoinLobby(steamIDLobby);};

// Leave a lobby; this will take effect immediately on the client side
// other users in the lobby will be notified by a LobbyChatUpdate callback
void SteamMatchmaking_LeaveLobby( CSteamID steamIDLobby ){SteamMatchmaking()->LeaveLobby(steamIDLobby);};

// Invite another user to the lobby
// the target user will receive a LobbyInvite callback
// will return true if the invite is successfully sent, whether or not the target responds
// returns false if the local user is not connected to the Steam servers
// if the other user clicks the join link, a GameLobbyJoinRequested will be posted if the user is in-game,
// or if the game isn't running yet the game will be launched with the parameter +connect_lobby <64-bit lobby id>
bool SteamMatchmaking_InviteUserToLobby( CSteamID steamIDLobby, CSteamID steamIDInvitee ){return SteamMatchmaking()->InviteUserToLobby(steamIDLobby,steamIDInvitee);};

// Lobby iteration, for viewing details of users in a lobby
// only accessible if the lobby user is a member of the specified lobby
// persona information for other lobby members (name, avatar, etc.) will be asynchronously received
// and accessible via SteamFriends

// returns the number of users in the specified lobby
int SteamMatchmaking_GetNumLobbyMembers( CSteamID steamIDLobby ){return SteamMatchmaking()->GetNumLobbyMembers(steamIDLobby);};
// returns the CSteamID of a user in the lobby
// iMember is of range [0,GetNumLobbyMembers())
// note that the current user must be in a lobby to retrieve CSteamIDs of other users in that lobby
CSteamID SteamMatchmaking_GetLobbyMemberByIndex( CSteamID steamIDLobby, int Member ){return SteamMatchmaking()->GetLobbyMemberByIndex(steamIDLobby,Member);};

// Get data associated with this lobby
// takes a simple key, and returns the string associated with it
// "" will be returned if no value is set, or if steamIDLobby is invalid
const char *SteamMatchmaking_GetLobbyData( CSteamID steamIDLobby, const char *Key ){return SteamMatchmaking()->GetLobbyData(steamIDLobby,Key);};
// Sets a key/value pair in the lobby metadata
// each user in the lobby will be broadcast this new value, and any new users joining will receive any existing data
// this can be used to set lobby names, map, etc.
// to reset a key, just set it to ""
// other users in the lobby will receive notification of the lobby data change via a LobbyDataUpdate callback
bool SteamMatchmaking_SetLobbyData( CSteamID steamIDLobby, const char *Key, const char *Value ){return SteamMatchmaking()->SetLobbyData(steamIDLobby,Key,Value);};

// returns the number of metadata keys set on the specified lobby
int SteamMatchmaking_GetLobbyDataCount( CSteamID steamIDLobby ){return SteamMatchmaking()->GetLobbyDataCount(steamIDLobby);};

// returns a lobby metadata key/values pair by index, of range [0, GetLobbyDataCount())
bool SteamMatchmaking_GetLobbyDataByIndex( CSteamID steamIDLobby, int LobbyData, char *Key, int KeyBufferSize, char *Value, int ValueBufferSize ){return SteamMatchmaking()->GetLobbyDataByIndex(steamIDLobby, LobbyData, Key, KeyBufferSize, Value, ValueBufferSize);};

// removes a metadata key from the lobby
bool SteamMatchmaking_DeleteLobbyData( CSteamID steamIDLobby, const char *Key ){return SteamMatchmaking()->DeleteLobbyData(steamIDLobby,Key);};

// Gets per-user metadata for someone in this lobby
const char *SteamMatchmaking_GetLobbyMemberData( CSteamID steamIDLobby, CSteamID steamIDUser, const char *Key ){return SteamMatchmaking()->GetLobbyMemberData(steamIDLobby,steamIDUser,Key);};
// Sets per-user metadata (for the local user implicitly)
void SteamMatchmaking_SetLobbyMemberData( CSteamID steamIDLobby, const char *Key, const char *Value ){return SteamMatchmaking()->SetLobbyMemberData(steamIDLobby,Key,Value);};

// Broadcasts a chat message to the all the users in the lobby
// users in the lobby (including the local user) will receive a LobbyChatMsg callback
// returns true if the message is successfully sent
// MsgBody can be binary or text data, up to 4k
// if MsgBody is text, cMsgBody should be strlen( text ) + 1, to include the null terminator
bool SteamMatchmaking_SendLobbyChatMsg( CSteamID steamIDLobby, const void *MsgBody, int cMsgBody ){return SteamMatchmaking()->SendLobbyChatMsg(steamIDLobby,MsgBody,cMsgBody);};
// Get a chat message as specified in a LobbyChatMsg callback
// ChatID is the LobbyChatMsg-ChatID value in the callback
// *SteamIDUser is filled in with the CSteamID of the member
// *Data is filled in with the message itself
// return value is the number of bytes written into the buffer
int SteamMatchmaking_GetLobbyChatEntry( CSteamID steamIDLobby, int ChatID, CSteamID *SteamIDUser, void *Data, int cData, EChatEntryType *ChatEntryType ){return SteamMatchmaking()->GetLobbyChatEntry(steamIDLobby,ChatID,SteamIDUser,Data,cData,ChatEntryType);};

// Refreshes metadata for a lobby you're not necessarily in right now
// you never do this for lobbies you're a member of, only if your
// this will send down all the metadata associated with a lobby
// this is an asynchronous call
// returns false if the local user is not connected to the Steam servers
// results will be returned by a LobbyDataUpdate callback
// if the specified lobby doesn't exist, LobbyDataUpdate::m_bSuccess will be set to false
bool SteamMatchmaking_RequestLobbyData( CSteamID steamIDLobby ){return SteamMatchmaking()->RequestLobbyData(steamIDLobby);};

// sets the game server associated with the lobby
// usually at this point, the users will join the specified game server
// either the IP/Port or the steamID of the game server has to be valid, depending on how you want the clients to be able to connect
void SteamMatchmaking_SetLobbyGameServer( CSteamID steamIDLobby, uint32 GameServerIP, uint16 GameServerPort, CSteamID steamIDGameServer ){SteamMatchmaking()->SetLobbyGameServer(steamIDLobby,GameServerIP,GameServerPort,steamIDGameServer);};
// returns the details of a game server set in a lobby - returns false if there is no game server set, or that lobby doesn't exist
bool SteamMatchmaking_GetLobbyGameServer( CSteamID steamIDLobby, uint32 *GameServerIP, uint16 *GameServerPort, CSteamID *steamIDGameServer ){return SteamMatchmaking()->GetLobbyGameServer(steamIDLobby,GameServerIP,GameServerPort,steamIDGameServer);};

// set the limit on the # of users who can join the lobby
bool SteamMatchmaking_SetLobbyMemberLimit( CSteamID steamIDLobby, int MaxMembers ){return SteamMatchmaking()->SetLobbyMemberLimit(steamIDLobby,MaxMembers);};
// returns the current limit on the # of users who can join the lobby; returns 0 if no limit is defined
int SteamMatchmaking_GetLobbyMemberLimit( CSteamID steamIDLobby ){return SteamMatchmaking()->GetLobbyMemberLimit(steamIDLobby);};

// updates which type of lobby it is
// only lobbies that are k_ELobbyTypePublic or k_ELobbyTypeInvisible, and are set to joinable, will be returned by RequestLobbyList() calls
bool SteamMatchmaking_SetLobbyType( CSteamID steamIDLobby, ELobbyType LobbyType ){return SteamMatchmaking()->SetLobbyType(steamIDLobby,LobbyType);};

// sets whether or not a lobby is joinable - defaults to true for a new lobby
// if set to false, no user can join, even if they are a friend or have been invited
bool SteamMatchmaking_SetLobbyJoinable( CSteamID steamIDLobby, bool LobbyJoinable ){return SteamMatchmaking()->SetLobbyJoinable(steamIDLobby,LobbyJoinable);};

// returns the current lobby owner
// you must be a member of the lobby to access this
// there always one lobby owner - if the current owner leaves, another user will become the owner
// it is possible (bur rare) to join a lobby just as the owner is leaving, thus entering a lobby with self as the owner
CSteamID SteamMatchmaking_GetLobbyOwner( CSteamID steamIDLobby ){return SteamMatchmaking()->GetLobbyOwner(steamIDLobby);};

// changes who the lobby owner is
// you must be the lobby owner for this to succeed, and steamIDNewOwner must be in the lobby
// after completion, the local user will no longer be the owner
bool SteamMatchmaking_SetLobbyOwner( CSteamID steamIDLobby, CSteamID steamIDNewOwner ){return SteamMatchmaking()->SetLobbyOwner(steamIDLobby,steamIDNewOwner);};

// link two lobbies for the purposes of checking player compatibility
// you must be the lobby owner of both lobbies
bool SteamMatchmaking_SetLinkedLobby( CSteamID steamIDLobby, CSteamID steamIDLobbyDependent ){return SteamMatchmaking()->SetLinkedLobby(steamIDLobby,steamIDLobbyDependent);};


//------------------------------ 
// matchmaking servers

// Request a new list of servers of a particular type.  These calls each correspond to one of the EMatchMakingType values.
class cSteamMatchmakingServerListResponse : public ISteamMatchmakingServerListResponse
{
private:
    tOnServerResponded OnServerRespondedCallback;
    tOnServerFailedToRespond OnServerFailedToRespondCallback;
    tOnServerRefreshComplete OnServerRefreshCompleteCallback;
public:
	cSteamMatchmakingServerListResponse(tOnServerResponded a,tOnServerFailedToRespond b,tOnServerRefreshComplete c)
	{OnServerRespondedCallback=a;OnServerFailedToRespondCallback=b;OnServerRefreshCompleteCallback=c;};
	void ServerResponded( HServerListRequest Req, int Server ){OnServerRespondedCallback(Req,Server);};
	void ServerFailedToRespond( HServerListRequest Req, int Server ){OnServerFailedToRespondCallback(Req,Server);};
	void RefreshComplete( HServerListRequest Req, EMatchMakingServerResponse Response ){OnServerRefreshCompleteCallback(Req,Response);};
};

cSteamMatchmakingServerListResponse* SteamMatchmakingServerListResponse;

HServerListRequest SteamMatchmaking_RequestInternetServerList( AppId_t App, MatchMakingKeyValuePair_t **Filters, uint32 cFilters, tOnServerResponded a,tOnServerFailedToRespond b,tOnServerRefreshComplete c )
{	
	SteamMatchmakingServerListResponse = new cSteamMatchmakingServerListResponse(a,b,c);
	return SteamMatchmakingServers()->RequestInternetServerList(App,Filters,cFilters,SteamMatchmakingServerListResponse);
};

void* SteamMatchmakingServers_RequestLANServerList( uint32 iApp, tOnServerResponded a,tOnServerFailedToRespond b,tOnServerRefreshComplete c ) 
{ 
	ServerBrowsers.push_back(new CSteamMatchmakingServerListResponse(a,b,c));
	return SteamMatchmakingServers()->RequestLANServerList(iApp,ServerBrowsers.back());
}; 
void* SteamMatchmakingServers_RequestFriendsServerList( uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, tOnServerResponded a,tOnServerFailedToRespond b,tOnServerRefreshComplete c ) 
{ 
	ServerBrowsers.push_back(new CSteamMatchmakingServerListResponse(a,b,c));
	return SteamMatchmakingServers()->RequestFriendsServerList( iApp, ppchFilters, nFilters,ServerBrowsers.back());
}; 
void* SteamMatchmakingServers_RequestFavoritesServerList( uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, tOnServerResponded a,tOnServerFailedToRespond b,tOnServerRefreshComplete c ) 
{ 
	ServerBrowsers.push_back(new CSteamMatchmakingServerListResponse(a,b,c));
	return SteamMatchmakingServers()->RequestFavoritesServerList( iApp, ppchFilters, nFilters,ServerBrowsers.back());
}; 
void* SteamMatchmakingServers_RequestHistoryServerList( uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, tOnServerResponded a,tOnServerFailedToRespond b,tOnServerRefreshComplete c ) 
{ 
	ServerBrowsers.push_back(new CSteamMatchmakingServerListResponse(a,b,c));
	return SteamMatchmakingServers()->RequestHistoryServerList( iApp, ppchFilters, nFilters,ServerBrowsers.back());
}; 
void* SteamMatchmakingServers_RequestSpectatorServerList( uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, tOnServerResponded a,tOnServerFailedToRespond b,tOnServerRefreshComplete c ) 
{ 
	ServerBrowsers.push_back(new CSteamMatchmakingServerListResponse(a,b,c));
	return SteamMatchmakingServers()->RequestSpectatorServerList( iApp, ppchFilters, nFilters,ServerBrowsers.back());
};

// Releases the asynchronous request object and cancels any pending query on it if there's a pending query in progress.
// RefreshComplete callback is not posted when request is released.
void SteamMatchmaking_ReleaseRequest( HServerListRequest ServerListRequest ){return SteamMatchmakingServers()->ReleaseRequest(ServerListRequest);};

struct cServerDetails
{
	const char* Name; 
	uint16 QueryPort;
	uint16 ConnectionPort;
	uint32 IP;
	int Ping;												// current ping time in milliseconds
	bool HadSuccessfulResponse;								// server has responded successfully in the past
	bool DoNotRefresh;										// server is marked as not responding and should no longer be refreshed
	char GameDir[k_cbMaxGameServerGameDir];					// current game directory
	char Map[k_cbMaxGameServerMapName];						// current map
	char GameDescription[k_cbMaxGameServerGameDescription];	// game description
	uint32 AppID;											// Steam App ID of this server
	int Players;											// total number of players currently on the server.  INCLUDES BOTS!
	int MaxPlayers;											// Maximum players that can join this server
	int BotPlayers;											// Number of bots (i.e simulated players) on this server
	bool Password;											// true if this server needs a password to join
	bool Secure;											// Is this server protected by VAC
	uint32 TimeLastPlayed;									// time (in unix time) when this server was last played on (for favorite/history servers)
	int	ServerVersion;										// server version as reported to Steam	
	char GameTags[k_cbMaxGameServerTags];                   // the tags this server exposes
};

void SteamMatchmaking_GetServerDetails( HServerListRequest Request, int Server, cServerDetails &ServerDetails )
{
	gameserveritem_t* rval = new gameserveritem_t();
    
	ServerDetails.ConnectionPort=rval->m_NetAdr.GetConnectionPort();
	ServerDetails.QueryPort=rval->m_NetAdr.GetQueryPort();
	ServerDetails.IP=rval->m_NetAdr.GetIP();

	ServerDetails.AppID=rval->m_nAppID;
	ServerDetails.BotPlayers=rval->m_nBotPlayers;
	ServerDetails.DoNotRefresh=rval->m_bDoNotRefresh;
	memcpy( ServerDetails.GameDescription, rval->m_szGameDescription, sizeof(char)*k_cbMaxGameServerGameDescription );
	memcpy( ServerDetails.GameDir, rval->m_szGameDir, sizeof(char)*k_cbMaxGameServerGameDir );
	memcpy( ServerDetails.GameTags, rval->m_szGameTags, sizeof(char)*k_cbMaxGameServerTags );
	memcpy( ServerDetails.Map, rval->m_szMap, sizeof(char)*k_cbMaxGameServerMapName );
	ServerDetails.HadSuccessfulResponse=rval->m_bHadSuccessfulResponse;
	ServerDetails.MaxPlayers=rval->m_nMaxPlayers;
	ServerDetails.Name=rval->GetName();
	ServerDetails.Password=rval->m_bPassword;
	ServerDetails.Ping=rval->m_nPing;
	ServerDetails.Players=rval->m_nPlayers;
	ServerDetails.Secure=rval->m_bSecure;
	ServerDetails.ServerVersion=rval->m_nPlayers;
	ServerDetails.TimeLastPlayed=rval->m_ulTimeLastPlayed;		
		
	rval=SteamMatchmakingServers()->GetServerDetails(Request,Server);
}; 

void SteamMatchmaking_SetServerDetails( HServerListRequest Request, int Server, uint16 QueryPort, uint16 ConnectionPort, uint32 IP, const char* Name )
{
	gameserveritem_t* val = new gameserveritem_t();
	val=SteamMatchmakingServers()->GetServerDetails(Request,Server);
	val->m_NetAdr.SetConnectionPort(ConnectionPort);
	val->m_NetAdr.SetQueryPort(QueryPort);
	val->m_NetAdr.SetIP(IP);
	val->SetName(Name);
}; 


// Cancel an request which is operation on the given list type.  You should call this to cancel
// any in-progress requests before destructing a callback object that may have been passed 
// to one of the above list request calls.  Not doing so may result in a crash when a callback
// occurs on the destructed object.
// Canceling a query does not release the allocated request handle.
// The request handle must be released using ReleaseRequest( hRequest )
void SteamMatchmaking_CancelQuery( HServerListRequest Request ){return SteamMatchmakingServers()->CancelQuery(Request);}; 

// Ping every server in your list again but don't update the list of servers
// Query callback installed when the server list was requested will be used
// again to post notifications and RefreshComplete, so the callback must remain
// valid until another RefreshComplete is called on it or the request
// is released with ReleaseRequest( hRequest )
void SteamMatchmaking_RefreshQuery( HServerListRequest Request ){return SteamMatchmakingServers()->RefreshQuery(Request);}; 

// Returns true if the list is currently refreshing its server list
bool SteamMatchmaking_IsRefreshing( HServerListRequest Request ){return SteamMatchmakingServers()->IsRefreshing(Request);}; 

// How many servers in the given list, GetServerDetails above takes 0... GetServerCount() - 1
int SteamMatchmaking_GetServerCount( HServerListRequest Request ){return SteamMatchmakingServers()->GetServerCount(Request);}; 

// Refresh a single server inside of a query (rather than all the servers )
void SteamMatchmaking_RefreshServer( HServerListRequest Request, int Server ){return SteamMatchmakingServers()->RefreshServer(Request,Server);}; 


//-----------------------------------------------------------------------------
// Queries to individual servers directly via IP/Port
//-----------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
// Request updated ping time and other details from a single server
class cSteamMatchmakingPingResponse: public ISteamMatchmakingPingResponse
{
public:	
	gameserveritem_t Out_Server;
	bool Out_Failure;
	cSteamMatchmakingPingResponse(){};
	// Server has responded successfully and has updated data
	void ServerResponded( gameserveritem_t &server ){Out_Server = server;Out_Failure=false;};
	// Server failed to respond to the ping request
	void ServerFailedToRespond(){Out_Failure=true;};
};

cSteamMatchmakingPingResponse* GetPingServerRequestServersResponse; 

void SteamMatchmaking_GetPingServer( uint32 IP, uint16 Port, cServerDetails &ServerDetails, bool &IsFailure)
{	
	GetPingServerRequestServersResponse = new cSteamMatchmakingPingResponse(); 

	HServerQuery rval= SteamMatchmakingServers()->PingServer(IP,Port,GetPingServerRequestServersResponse);

	ServerDetails.ConnectionPort=GetPingServerRequestServersResponse->Out_Server.m_NetAdr.GetConnectionPort();
	ServerDetails.QueryPort=GetPingServerRequestServersResponse->Out_Server.m_NetAdr.GetQueryPort();
	ServerDetails.IP=GetPingServerRequestServersResponse->Out_Server.m_NetAdr.GetIP();

	ServerDetails.AppID=GetPingServerRequestServersResponse->Out_Server.m_nAppID;
	ServerDetails.BotPlayers=GetPingServerRequestServersResponse->Out_Server.m_nBotPlayers;
	ServerDetails.DoNotRefresh=GetPingServerRequestServersResponse->Out_Server.m_bDoNotRefresh;
	memcpy( ServerDetails.GameDescription, GetPingServerRequestServersResponse->Out_Server.m_szGameDescription, sizeof(char)*k_cbMaxGameServerGameDescription );
	memcpy( ServerDetails.GameDir, GetPingServerRequestServersResponse->Out_Server.m_szGameDir, sizeof(char)*k_cbMaxGameServerGameDir );
	memcpy( ServerDetails.GameTags, GetPingServerRequestServersResponse->Out_Server.m_szGameTags, sizeof(char)*k_cbMaxGameServerTags );
	memcpy( ServerDetails.Map, GetPingServerRequestServersResponse->Out_Server.m_szMap, sizeof(char)*k_cbMaxGameServerMapName );
	ServerDetails.HadSuccessfulResponse=GetPingServerRequestServersResponse->Out_Server.m_bHadSuccessfulResponse;
	ServerDetails.MaxPlayers=GetPingServerRequestServersResponse->Out_Server.m_nMaxPlayers;
	ServerDetails.Name=GetPingServerRequestServersResponse->Out_Server.GetName();
	ServerDetails.Password=GetPingServerRequestServersResponse->Out_Server.m_bPassword;
	ServerDetails.Ping=GetPingServerRequestServersResponse->Out_Server.m_nPing;
	ServerDetails.Players=GetPingServerRequestServersResponse->Out_Server.m_nPlayers;
	ServerDetails.Secure=GetPingServerRequestServersResponse->Out_Server.m_bSecure;
	ServerDetails.ServerVersion=GetPingServerRequestServersResponse->Out_Server.m_nPlayers;
	ServerDetails.TimeLastPlayed=GetPingServerRequestServersResponse->Out_Server.m_ulTimeLastPlayed;	

	IsFailure = GetPingServerRequestServersResponse->Out_Failure;

	SteamMatchmakingServers()->CancelServerQuery(rval);
}; 

//--------------------------------------------------------------------------------------------------------
// Request the list of players currently playing on a server
typedef void (*tOnAddPlayerToList)(const char *Name, int Score, float TimePlayed);
typedef void (*tSimpleEvent)();

class cSteamMatchmakingPlayersResponse: public ISteamMatchmakingPlayersResponse
{
	tOnAddPlayerToList OnAddPlayerToList;
	tSimpleEvent OnPlayersFailedToRespond;
	tSimpleEvent OnPlayersRefreshComplete;
public:
	cSteamMatchmakingPlayersResponse(tOnAddPlayerToList addPlayerToList, tSimpleEvent playersFailedToRespond, tSimpleEvent playersRefreshComplete)
	{OnAddPlayerToList=addPlayerToList;OnPlayersFailedToRespond=playersFailedToRespond;OnPlayersRefreshComplete=playersRefreshComplete;};
	// Got data on a new player on the server -- you'll get this callback once per player
	// on the server which you have requested player data on.
	void AddPlayerToList( const char *Name, int Score, float TimePlayed ){OnAddPlayerToList(Name,Score,TimePlayed);};
	// The server failed to respond to the request for player details
	void PlayersFailedToRespond(){OnPlayersFailedToRespond();};
	// The server has finished responding to the player details request 
	// (ie, you won't get anymore AddPlayerToList callbacks)
	void PlayersRefreshComplete(){OnPlayersRefreshComplete();};
};

cSteamMatchmakingPlayersResponse *GetPlayerDetailsRequestServersResponse; 

HServerQuery SteamMatchmaking_GetPlayerDetails( uint32 IP, uint16 Port,tOnAddPlayerToList addPlayerToList, tSimpleEvent playersFailedToRespond, tSimpleEvent playersRefreshComplete )
{	
	GetPlayerDetailsRequestServersResponse = new cSteamMatchmakingPlayersResponse(addPlayerToList,playersFailedToRespond,playersRefreshComplete);
	return SteamMatchmakingServers()->PlayerDetails(IP,Port,GetPlayerDetailsRequestServersResponse);
};

//--------------------------------------------------------------------------------------------------------
// Request the list of rules that the server is running (See SteamGameServer-SetKeyValue() to set the rules server side)
typedef void (*tRulesResponded)(const char *Rule, const char *Value);

class cSteamMatchmakingRulesResponse: public ISteamMatchmakingRulesResponse
{
	tRulesResponded OnRulesResponded;
	tSimpleEvent OnRulesFailedToRespond;
	tSimpleEvent OnRulesRefreshComplete;
public:
	cSteamMatchmakingRulesResponse(tRulesResponded rulesResponded, tSimpleEvent rulesFailedToRespond, tSimpleEvent rulesRefreshComplete)
	{OnRulesResponded=rulesResponded;OnRulesFailedToRespond=rulesFailedToRespond;OnRulesRefreshComplete=rulesRefreshComplete;};
	// Got data on a rule on the server -- you'll get one of these per rule defined on
	// the server you are querying
	void RulesResponded( const char *Rule, const char *Value ){ OnRulesResponded(Rule,Value); };
	// The server failed to respond to the request for rule details
	void RulesFailedToRespond(){ OnRulesFailedToRespond(); };
	// The server has finished responding to the rule details request 
	// (ie, you won't get anymore RulesResponded callbacks)
	void RulesRefreshComplete(){ OnRulesRefreshComplete();};
};

cSteamMatchmakingRulesResponse *GetServerRulesRequestServersResponse; 

HServerQuery SteamMatchmaking_GetServerRules( uint32 IP, uint16 Port, tRulesResponded rulesResponded, tSimpleEvent rulesFailedToRespond, tSimpleEvent rulesRefreshComplete )
{	
	GetServerRulesRequestServersResponse = new cSteamMatchmakingRulesResponse(rulesResponded, rulesFailedToRespond, rulesRefreshComplete);
    return SteamMatchmakingServers()->ServerRules(IP,Port,GetServerRulesRequestServersResponse);
}; 

//Cancel server query
void SteamMatchmaking_CancelServerQuery(HServerQuery q){SteamMatchmakingServers()->CancelServerQuery(q);};
