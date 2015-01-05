//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"

// returns the local players name - guaranteed to not be NULL.
// this is the same name as on the users community profile page
// this is stored in UTF-8 format
// like all the other interface functions that return a char *, it's important that this pointer is not saved
// off; it will eventually be free'd or re-allocated
const char *SteamFriends_GetPersonaName(){return SteamFriends()->GetPersonaName();};

// Sets the player name, stores it on the server and publishes the changes to all friends who are online.
// Changes take place locally immediately, and a PersonaStateChange_t is posted, presuming success.
//
// The final results are available through the return value SteamAPICall_t, using SetPersonaNameResponse_t.
//
// If the name change fails to happen on the server, then an additional global PersonaStateChange_t will be posted
// to change the name back, in addition to the SetPersonaNameResponse_t callback.
SteamAPICall_t SteamFriends_SetPersonaName( const char *PersonaName ){return SteamFriends()->SetPersonaName(PersonaName);};

// gets the status of the current user
EPersonaState SteamFriends_GetPersonaState(){return SteamFriends()->GetPersonaState();};

// friend iteration
// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
// then GetFriendByIndex() can then be used to return the id's of each of those users
int SteamFriends_GetFriendCount( int FriendFlags ){return SteamFriends()->GetFriendCount(FriendFlags);};

// returns the steamID of a user
// Friend is a index of range [0, GetFriendCount())
// FriendsFlags must be the same value as used in GetFriendCount()
// the returned CSteamID can then be used by all the functions below to access details about the user
CSteamID SteamFriends_GetFriendByIndex( int Friend, int FriendFlags ){return SteamFriends()->GetFriendByIndex(Friend,FriendFlags);};

// returns a relationship to a user
EFriendRelationship SteamFriends_GetFriendRelationship( CSteamID steamIDFriend ){return SteamFriends()->GetFriendRelationship(steamIDFriend);};

// returns the current status of the specified user
// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
EPersonaState SteamFriends_GetFriendPersonaState( CSteamID steamIDFriend ){return SteamFriends()->GetFriendPersonaState(steamIDFriend);};

// returns the name another user - guaranteed to not be NULL.
// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
// 
const char *SteamFriends_GetFriendPersonaName( CSteamID steamIDFriend ){return SteamFriends()->GetFriendPersonaName(steamIDFriend);};

// returns true if the friend is actually in a game, and fills in FriendGameInfo with an extra details 
bool SteamFriends_GetFriendGamePlayed( CSteamID steamIDFriend, FriendGameInfo_t *FriendGameInfo ){return SteamFriends()->GetFriendGamePlayed(steamIDFriend,FriendGameInfo);};
// accesses old friends names - returns an empty string when their are no more items in the history
const char *SteamFriends_GetFriendPersonaNameHistory( CSteamID steamIDFriend, int PersonaName ){return SteamFriends()->GetFriendPersonaNameHistory(steamIDFriend,PersonaName);};

// Returns nickname the current user has set for the specified player. Returns NULL if the no nickname has been set for that player.
const char *SteamFriends_GetPlayerNickname( CSteamID steamIDPlayer ){return SteamFriends()->GetPlayerNickname(steamIDPlayer);};

// returns true if the specified user meets any of the criteria specified in FriendFlags
// FriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
bool SteamFriends_HasFriend( CSteamID steamIDFriend, int FriendFlags ){return SteamFriends()->HasFriend(steamIDFriend,FriendFlags);};

// clan (group) iteration and access functions
int SteamFriends_GetClanCount(){return SteamFriends()->GetClanCount();};
CSteamID SteamFriends_GetClanByIndex( int Clan ){return SteamFriends()->GetClanByIndex(Clan);};
const char *SteamFriends_GetClanName( CSteamID steamIDClan ){return SteamFriends()->GetClanName(steamIDClan);};
const char *SteamFriends_GetClanTag( CSteamID steamIDClan ){return SteamFriends()->GetClanTag(steamIDClan);};
// returns the most recent information we have about what's happening in a clan
bool SteamFriends_GetClanActivityCounts( CSteamID steamIDClan, int *Online, int *InGame, int *Chatting ){return SteamFriends()->GetClanActivityCounts(steamIDClan,Online,InGame,Chatting);};
// for clans a user is a member of, they will have reasonably up-to-date information, but for others you'll have to download the info to have the latest
SteamAPICall_t SteamFriends_DownloadClanActivityCounts( CSteamID *steamIDClans, int ClansToRequest ){return SteamFriends()->DownloadClanActivityCounts(steamIDClans,ClansToRequest);};

// iterators for getting users in a chat room, lobby, game server or clan
// note that large clans that cannot be iterated by the local user
// note that the current user must be in a lobby to retrieve CSteamIDs of other users in that lobby
// steamIDSource can be the steamID of a group, game server, lobby or chat room
int SteamFriends_GetFriendCountFromSource( CSteamID steamIDSource ){return SteamFriends()->GetFriendCountFromSource(steamIDSource);};
CSteamID SteamFriends_GetFriendFromSourceByIndex( CSteamID steamIDSource, int Friend ){return SteamFriends()->GetFriendFromSourceByIndex(steamIDSource,Friend);};

// returns true if the local user can see that steamIDUser is a member or in steamIDSource
bool SteamFriends_IsUserInSource( CSteamID steamIDUser, CSteamID steamIDSource ){return SteamFriends()->IsUserInSource(steamIDUser,steamIDSource);};

// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
void SteamFriends_SetInGameVoiceSpeaking( CSteamID steamIDUser, bool Speaking ){return SteamFriends()->SetInGameVoiceSpeaking(steamIDUser,Speaking);};

// activates the game overlay, with an optional dialog to open 
// valid options are "Friends", "Community", "Players", "Settings", "OfficialGameGroup", "Stats", "Achievements"
void SteamFriends_ActivateGameOverlay( const char *Dialog ){return SteamFriends()->ActivateGameOverlay(Dialog);};

// activates game overlay to a specific place
// valid options are
//"steamid" - opens the overlay web browser to the specified user or groups profile
//"chat" - opens a chat window to the specified user, or joins the group chat 
//"jointrade" - opens a window to a Steam Trading session that was started with the ISteamEconomy/StartTrade Web API
//"stats" - opens the overlay web browser to the specified user's stats
//"achievements" - opens the overlay web browser to the specified user's achievements
//"friendadd" - opens the overlay in minimal mode prompting the user to add the target user as a friend
//"friendremove" - opens the overlay in minimal mode prompting the user to remove the target friend
//"friendrequestaccept" - opens the overlay in minimal mode prompting the user to accept an incoming friend invite
//"friendrequestignore" - opens the overlay in minimal mode prompting the user to ignore an incoming friend invite
void SteamFriends_ActivateGameOverlayToUser( const char *Dialog, CSteamID steamID ){return SteamFriends()->ActivateGameOverlayToUser(Dialog,steamID);};

// activates game overlay web browser directly to the specified URL
// full address with protocol type is required, e.g. http://www.steamgames.com/
void SteamFriends_ActivateGameOverlayToWebPage( const char *URL ){return SteamFriends()->ActivateGameOverlayToWebPage(URL);};

// activates game overlay to store page for app
void SteamFriends_ActivateGameOverlayToStore( AppId_t AppID, EOverlayToStoreFlag Flag ){return SteamFriends()->ActivateGameOverlayToStore(AppID,Flag);};

// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
// in game 
void SteamFriends_SetPlayedWith( CSteamID steamIDUserPlayedWith ){return SteamFriends()->SetPlayedWith(steamIDUserPlayedWith);};

// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
void SteamFriends_ActivateGameOverlayInviteDialog( CSteamID steamIDLobby ){return SteamFriends()->ActivateGameOverlayInviteDialog(steamIDLobby);};

// gets the small (32x32) avatar of the current user, which is a handle to be used in Utils-GetImageRGBA(), or 0 if none set
int SteamFriends_GetSmallFriendAvatar( CSteamID steamIDFriend ){return SteamFriends()->GetSmallFriendAvatar(steamIDFriend);};

// gets the medium (64x64) avatar of the current user, which is a handle to be used in Utils-GetImageRGBA(), or 0 if none set
int SteamFriends_GetMediumFriendAvatar( CSteamID steamIDFriend ){return SteamFriends()->GetMediumFriendAvatar(steamIDFriend);};

// gets the large (184x184) avatar of the current user, which is a handle to be used in Utils-GetImageRGBA(), or 0 if none set
// returns -1 if this image has yet to be loaded, in this case wait for a AvatarImageLoaded callback and then call this again
int SteamFriends_GetLargeFriendAvatar( CSteamID steamIDFriend ){return SteamFriends()->GetLargeFriendAvatar(steamIDFriend);};

// requests information about a user - persona name & avatar
// if RequireNameOnly is set, then the avatar of a user isn't downloaded 
// - it's a lot slower to download avatars and churns the local cache, so if you don't need avatars, don't request them
// if returns true, it means that data is being requested, and a PersonaStateChanged callback will be posted when it's retrieved
// if returns false, it means that we already have all the details about that user, and functions can be called immediately
bool SteamFriends_RequestUserInformation( CSteamID steamIDUser, bool RequireNameOnly ){return SteamFriends()->RequestUserInformation(steamIDUser,RequireNameOnly);};

// requests information about a clan officer list
// when complete, data is returned in ClanOfficerListResponse call result
// this makes available the calls below
// you can only ask about clans that a user is a member of
// note that this won't download avatars automatically; if you get an officer,
// and no avatar image is available, call RequestUserInformation( steamID, false ) to download the avatar
SteamAPICall_t SteamFriends_RequestClanOfficerList( CSteamID steamIDClan ){return SteamFriends()->RequestClanOfficerList(steamIDClan);};

// iteration of clan officers - can only be done when a RequestClanOfficerList() call has completed

// returns the steamID of the clan owner
CSteamID SteamFriends_GetClanOwner( CSteamID steamIDClan ){return SteamFriends()->GetClanOwner(steamIDClan);};
// returns the number of officers in a clan (including the owner)
int SteamFriends_GetClanOfficerCount( CSteamID steamIDClan ){return SteamFriends()->GetClanOfficerCount(steamIDClan);};
// returns the steamID of a clan officer, by index, of range [0,GetClanOfficerCount)
CSteamID SteamFriends_GetClanOfficerByIndex( CSteamID steamIDClan, int Officer ){return SteamFriends()->GetClanOfficerByIndex(steamIDClan,Officer);};
// if current user is chat restricted, he can't send or receive any text/voice chat messages.
// the user can't see custom avatars. But the user can be online and send/recv game invites.
// a chat restricted user can't add friends or join any groups.
uint32 SteamFriends_GetUserRestrictions(){return SteamFriends()->GetUserRestrictions();};

// Rich Presence data is automatically shared between friends who are in the same game
// Each user has a set of Key/Value pairs
// Up to 20 different keys can be set
// There are two magic keys:
// "status"  - a UTF-8 string that will show up in the 'view game info' dialog in the Steam friends list
// "connect" - a UTF-8 string that contains the command-line for how a friend can connect to a game
// GetFriendRichPresence() returns an empty string "" if no value is set
// SetRichPresence() to a NULL or an empty string deletes the key
// You can iterate the current set of keys for a friend with GetFriendRichPresenceKeyCount()
// and GetFriendRichPresenceKeyByIndex() (typically only used for debugging)
bool SteamFriends_SetRichPresence( const char *Key, const char *Value ){return SteamFriends()->SetRichPresence(Key,Value);};
void SteamFriends_ClearRichPresence(){SteamFriends()->ClearRichPresence();};
const char *SteamFriends_GetFriendRichPresence( CSteamID steamIDFriend, const char *Key ){return SteamFriends()->GetFriendRichPresence(steamIDFriend,Key);};
int SteamFriends_GetFriendRichPresenceKeyCount( CSteamID steamIDFriend ){return SteamFriends()->GetFriendRichPresenceKeyCount(steamIDFriend);};
const char *SteamFriends_GetFriendRichPresenceKeyByIndex( CSteamID steamIDFriend, int Key ){return SteamFriends()->GetFriendRichPresenceKeyByIndex(steamIDFriend,Key);};
// Requests rich presence for a specific user.
void SteamFriends_RequestFriendRichPresence( CSteamID steamIDFriend ){SteamFriends()->RequestFriendRichPresence(steamIDFriend);};

// rich invite support
// if the target accepts the invite, the pchConnectString gets added to the command-line for launching the game
// if the game is already running, a GameRichPresenceJoinRequested callback is posted containing the connect string
// invites can only be sent to friends
bool SteamFriends_InviteUserToGame( CSteamID steamIDFriend, const char *ConnectString ){return SteamFriends()->InviteUserToGame(steamIDFriend,ConnectString);};

// recently-played-with friends iteration
// this iterates the entire list of users recently played with, across games
// GetFriendCoplayTime() returns as a unix time
int SteamFriends_GetCoplayFriendCount(){return SteamFriends()->GetCoplayFriendCount();};
CSteamID SteamFriends_GetCoplayFriend( int CoplayFriend ){return SteamFriends()->GetCoplayFriend(CoplayFriend);};
int SteamFriends_GetFriendCoplayTime( CSteamID steamIDFriend ){return SteamFriends()->GetFriendCoplayTime(steamIDFriend);};
AppId_t SteamFriends_GetFriendCoplayGame( CSteamID steamIDFriend ){return SteamFriends()->GetFriendCoplayGame(steamIDFriend);};

// chat interface for games
// this allows in-game access to group (clan) chats from in the game
// the behavior is somewhat sophisticated, because the user may or may not be already in the group chat from outside the game or in the overlay
// use ActivateGameOverlayToUser( "chat", steamIDClan ) to open the in-game overlay version of the chat
SteamAPICall_t SteamFriends_JoinClanChatRoom( CSteamID steamIDClan ){return SteamFriends()->JoinClanChatRoom(steamIDClan);};
bool SteamFriends_LeaveClanChatRoom( CSteamID steamIDClan ){return SteamFriends()->LeaveClanChatRoom(steamIDClan);};
int SteamFriends_GetClanChatMemberCount( CSteamID steamIDClan ){return SteamFriends()->GetClanChatMemberCount(steamIDClan);};
CSteamID SteamFriends_GetChatMemberByIndex( CSteamID steamIDClan, int User ){return SteamFriends()->GetChatMemberByIndex(steamIDClan,User);};
bool SteamFriends_SendClanChatMessage( CSteamID steamIDClanChat, const char *Text ){return SteamFriends()->SendClanChatMessage(steamIDClanChat,Text);};
int SteamFriends_GetClanChatMessage( CSteamID steamIDClanChat, int Message, void *Text, int TextMax, EChatEntryType *ChatEntryType, CSteamID *steamidChatter ){return SteamFriends()->GetClanChatMessage(steamIDClanChat,Message,Text,TextMax,ChatEntryType,steamidChatter);};
bool SteamFriends_IsClanChatAdmin( CSteamID steamIDClanChat, CSteamID steamIDUser ){return SteamFriends()->IsClanChatAdmin(steamIDClanChat,steamIDUser);};

// interact with the Steam (game overlay / desktop)
bool SteamFriends_IsClanChatWindowOpenInSteam( CSteamID steamIDClanChat ){return SteamFriends()->IsClanChatWindowOpenInSteam(steamIDClanChat);};
bool SteamFriends_OpenClanChatWindowInSteam( CSteamID steamIDClanChat ){return SteamFriends()->OpenClanChatWindowInSteam(steamIDClanChat);};
bool SteamFriends_CloseClanChatWindowInSteam( CSteamID steamIDClanChat ){return SteamFriends()->CloseClanChatWindowInSteam(steamIDClanChat);};

// peer-to-peer chat interception
// this is so you can show P2P chats inline in the game
bool SteamFriends_SetListenForFriendsMessages( bool InterceptEnabled ){return SteamFriends()->SetListenForFriendsMessages(InterceptEnabled);};
bool SteamFriends_ReplyToFriendMessage( CSteamID steamIDFriend, const char *MsgToSend ){return SteamFriends()->ReplyToFriendMessage(steamIDFriend,MsgToSend);};
int SteamFriends_GetFriendMessage( CSteamID steamIDFriend, int MessageID, void *Data, int cData, EChatEntryType *ChatEntryType ){return SteamFriends()->GetFriendMessage(steamIDFriend,MessageID,Data,cData,ChatEntryType);};

// following apis
SteamAPICall_t SteamFriends_GetFollowerCount( CSteamID steamID ){return SteamFriends()->GetFollowerCount(steamID);};
SteamAPICall_t SteamFriends_IsFollowing( CSteamID steamID ){return SteamFriends()->IsFollowing(steamID);};
SteamAPICall_t SteamFriends_EnumerateFollowingList( uint32 StartIndex ){return SteamFriends()->EnumerateFollowingList(StartIndex);};