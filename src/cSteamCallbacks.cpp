//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------

#include "libMain.h"

cSteamCallbacksHandler *CallbacksHandler;

void System_RegisterCallbacks(cSteamCallbacks callbacks){LogToFile("System_RegisterCallbacks");if (CallbacksHandler==nullptr){CallbacksHandler = new cSteamCallbacksHandler(callbacks);}; }; 

cSteamCallbacksHandler::cSteamCallbacksHandler(cSteamCallbacks callbacks):
// server
m_GSClientApprove( this, &cSteamCallbacksHandler::OnGSClientApprove ),
	m_GSClientDeny( this, &cSteamCallbacksHandler::OnGSClientDeny ),
	m_GSClientKick( this, &cSteamCallbacksHandler::OnGSClientKick ),
	m_GSClientAchievementStatus( this, &cSteamCallbacksHandler::OnGSClientAchievementStatus ),
	m_GSPolicyResponse( this, &cSteamCallbacksHandler::OnGSPolicyResponse ),
	m_GSGameplayStats( this, &cSteamCallbacksHandler::OnGSGameplayStats ),
	m_GSClientGroupStatus( this, &cSteamCallbacksHandler::OnGSClientGroupStatus ),
	m_GSReputation( this, &cSteamCallbacksHandler::OnGSReputation ),
	m_AssociateWithClanResult( this, &cSteamCallbacksHandler::OnAssociateWithClanResult ),
	m_ComputeNewPlayerCompatibilityResult( this, &cSteamCallbacksHandler::OnComputeNewPlayerCompatibilityResult ),
	// server stats
	m_GSStatsReceived( this, &cSteamCallbacksHandler::OnGSStatsReceived ),
	m_GSStatsStored( this, &cSteamCallbacksHandler::OnGSStatsStored ),
	m_GSStatsUnloaded( this, &cSteamCallbacksHandler::OnGSStatsUnloaded ),
	// user
	m_SteamServersConnected( this, &cSteamCallbacksHandler::OnSteamServersConnected ),
	m_SteamServerConnectFailure( this, &cSteamCallbacksHandler::OnSteamServerConnectFailure ),
	m_SteamServersDisconnected( this, &cSteamCallbacksHandler::OnSteamServersDisconnected ),
	m_ClientGameServerDeny( this, &cSteamCallbacksHandler::OnClientGameServerDeny ),
	m_IPCFailure( this, &cSteamCallbacksHandler::OnIPCFailure ),
	m_ValidateAuthTicketResponse( this, &cSteamCallbacksHandler::OnValidateAuthTicketResponse ),
	m_MicroTxnAuthorizationResponse( this, &cSteamCallbacksHandler::OnMicroTxnAuthorizationResponse ),
	m_EncryptedAppTicketResponse( this, &cSteamCallbacksHandler::OnEncryptedAppTicketResponse ),
	m_GetAuthSessionTicketResponse( this, &cSteamCallbacksHandler::OnGetAuthSessionTicketResponse ),
	m_GameWebCallback( this, &cSteamCallbacksHandler::OnGameWebCallback ),
	// matchmaking
	m_FavoritesListChanged( this, &cSteamCallbacksHandler::OnFavoritesListChanged ),
	m_LobbyInvite( this, &cSteamCallbacksHandler::OnLobbyInvite ),
	m_LobbyEnter( this, &cSteamCallbacksHandler::OnLobbyEnter ),
	m_LobbyDataUpdate( this, &cSteamCallbacksHandler::OnLobbyDataUpdate ),
	m_LobbyChatUpdate( this, &cSteamCallbacksHandler::OnLobbyChatUpdate ),	
	m_LobbyChatMsg( this, &cSteamCallbacksHandler::OnLobbyChatMsg ),
	m_LobbyGameCreated( this, &cSteamCallbacksHandler::OnLobbyGameCreated ),
	m_LobbyMatchList( this, &cSteamCallbacksHandler::OnLobbyMatchList ),
	m_LobbyKicked( this, &cSteamCallbacksHandler::OnLobbyKicked ),
	m_LobbyCreated( this, &cSteamCallbacksHandler::OnLobbyCreated ),	
	m_PSNGameBootInviteResult( this, &cSteamCallbacksHandler::OnPSNGameBootInviteResult ),
	m_FavoritesListAccountsUpdated( this, &cSteamCallbacksHandler::OnFavoritesListAccountsUpdated ),
	// user stats
	m_UserStatsReceived( this, &cSteamCallbacksHandler::OnUserStatsReceived ),
	m_UserStatsStored( this, &cSteamCallbacksHandler::OnUserStatsStored ),
	m_UserAchievementStored( this, &cSteamCallbacksHandler::OnUserAchievementStored ),
	m_LeaderboardFindResult( this, &cSteamCallbacksHandler::OnLeaderboardFindResult ),
	m_LeaderboardScoresDownloaded( this, &cSteamCallbacksHandler::OnLeaderboardScoresDownloaded ),
	m_LeaderboardScoreUploaded( this, &cSteamCallbacksHandler::OnLeaderboardScoreUploaded ),
	m_NumberOfCurrentPlayers( this, &cSteamCallbacksHandler::OnNumberOfCurrentPlayers ),
	m_UserStatsUnloaded( this, &cSteamCallbacksHandler::OnUserStatsUnloaded ),
	m_UserAchievementIconFetched( this, &cSteamCallbacksHandler::OnUserAchievementIconFetched ),
	m_GlobalAchievementPercentagesReady( this, &cSteamCallbacksHandler::OnGlobalAchievementPercentagesReady ),
	m_LeaderboardUGCSet( this, &cSteamCallbacksHandler::OnLeaderboardUGCSet ),
	m_GlobalStatsReceived( this, &cSteamCallbacksHandler::OnGlobalStatsReceived ),
	// apps
	m_DlcInstalled( this, &cSteamCallbacksHandler::OnDlcInstalled ),
	m_RegisterActivationCodeResponse( this, &cSteamCallbacksHandler::OnRegisterActivationCodeResponse ),
	m_AppProofOfPurchaseKeyResponse( this, &cSteamCallbacksHandler::OnAppProofOfPurchaseKeyResponse ),
	m_NewLaunchQueryParameters( this, &cSteamCallbacksHandler::OnNewLaunchQueryParameters ),
	// networking
	m_P2PSessionRequest( this, &cSteamCallbacksHandler::OnP2PSessionRequest ),
	m_P2PSessionConnectFail( this, &cSteamCallbacksHandler::OnP2PSessionConnectFail ),
	m_SocketStatusCallback( this, &cSteamCallbacksHandler::OnSocketStatusCallback ),
	// matchmaking servers
	m_FavoritesListChanged_ms( this, &cSteamCallbacksHandler::OnFavoritesListChanged ),
	m_LobbyInvite_ms( this, &cSteamCallbacksHandler::OnLobbyInvite ),
	m_LobbyEnter_ms( this, &cSteamCallbacksHandler::OnLobbyEnter ),
	m_LobbyDataUpdate_ms( this, &cSteamCallbacksHandler::OnLobbyDataUpdate ),
	m_LobbyChatUpdate_ms( this, &cSteamCallbacksHandler::OnLobbyChatUpdate ),
	m_LobbyChatMsg_ms( this, &cSteamCallbacksHandler::OnLobbyChatMsg ),
	m_LobbyGameCreated_ms( this, &cSteamCallbacksHandler::OnLobbyGameCreated ),
	m_LobbyMatchList_ms( this, &cSteamCallbacksHandler::OnLobbyMatchList ),
	m_LobbyKicked_ms( this, &cSteamCallbacksHandler::OnLobbyKicked ),
	m_LobbyCreated_ms( this, &cSteamCallbacksHandler::OnLobbyCreated ),
	m_PSNGameBootInviteResult_ms( this, &cSteamCallbacksHandler::OnPSNGameBootInviteResult ),
	m_FavoritesListAccountsUpdated_ms( this, &cSteamCallbacksHandler::OnFavoritesListAccountsUpdated ),
	// remote storage
	m_RemoteStorageAppSyncedClient( this, &cSteamCallbacksHandler::OnRemoteStorageAppSyncedClient ),
	m_RemoteStorageAppSyncedServer( this, &cSteamCallbacksHandler::OnRemoteStorageAppSyncedServer ),
	m_RemoteStorageAppSyncProgress( this, &cSteamCallbacksHandler::OnRemoteStorageAppSyncProgress ),
	m_RemoteStorageAppSyncStatusCheck( this, &cSteamCallbacksHandler::OnRemoteStorageAppSyncStatusCheck ),
	m_RemoteStorageConflictResolution( this, &cSteamCallbacksHandler::OnRemoteStorageConflictResolution ),
	m_RemoteStorageFileShareResult( this, &cSteamCallbacksHandler::OnRemoteStorageFileShareResult ),
	m_RemoteStoragePublishFileResult( this, &cSteamCallbacksHandler::OnRemoteStoragePublishFileResult ),
	m_RemoteStorageDeletePublishedFileResult( this, &cSteamCallbacksHandler::OnRemoteStorageDeletePublishedFileResult ),
	m_RemoteStorageEnumerateUserPublishedFilesResult( this, &cSteamCallbacksHandler::OnRemoteStorageEnumerateUserPublishedFilesResult ),
	m_RemoteStorageSubscribePublishedFileResult( this, &cSteamCallbacksHandler::OnRemoteStorageSubscribePublishedFileResult ),
	m_RemoteStorageEnumerateUserSubscribedFilesResult( this, &cSteamCallbacksHandler::OnRemoteStorageEnumerateUserSubscribedFilesResult ),
	m_RemoteStorageUnsubscribePublishedFileResult( this, &cSteamCallbacksHandler::OnRemoteStorageUnsubscribePublishedFileResult ),
	m_RemoteStorageUpdatePublishedFileResult( this, &cSteamCallbacksHandler::OnRemoteStorageUpdatePublishedFileResult ),
	m_RemoteStorageDownloadUGCResult( this, &cSteamCallbacksHandler::OnRemoteStorageDownloadUGCResult ),
	m_RemoteStorageGetPublishedFileDetailsResult( this, &cSteamCallbacksHandler::OnRemoteStorageGetPublishedFileDetailsResult ),
	m_RemoteStorageEnumerateWorkshopFilesResult( this, &cSteamCallbacksHandler::OnRemoteStorageEnumerateWorkshopFilesResult ),
	m_RemoteStorageGetPublishedItemVoteDetailsResult( this, &cSteamCallbacksHandler::OnRemoteStorageGetPublishedItemVoteDetailsResult ),
	m_RemoteStoragePublishedFileSubscribed( this, &cSteamCallbacksHandler::OnRemoteStoragePublishedFileSubscribed ),
	m_RemoteStoragePublishedFileUnsubscribed( this, &cSteamCallbacksHandler::OnRemoteStoragePublishedFileUnsubscribed ),
	m_RemoteStoragePublishedFileDeleted( this, &cSteamCallbacksHandler::OnRemoteStoragePublishedFileDeleted ),
	m_RemoteStorageUpdateUserPublishedItemVoteResult( this, &cSteamCallbacksHandler::OnRemoteStorageUpdateUserPublishedItemVoteResult ),
	m_RemoteStorageUserVoteDetails( this, &cSteamCallbacksHandler::OnRemoteStorageUserVoteDetails ),
	m_RemoteStorageEnumerateUserSharedWorkshopFilesResult( this, &cSteamCallbacksHandler::OnRemoteStorageEnumerateUserSharedWorkshopFilesResult ),
	m_RemoteStorageSetUserPublishedFileActionResult( this, &cSteamCallbacksHandler::OnRemoteStorageSetUserPublishedFileActionResult ),
	m_RemoteStorageEnumeratePublishedFilesByUserActionResult( this, &cSteamCallbacksHandler::OnRemoteStorageEnumeratePublishedFilesByUserActionResult ),
	m_RemoteStoragePublishFileProgress( this, &cSteamCallbacksHandler::OnRemoteStoragePublishFileProgress ),
	m_RemoteStoragePublishedFileUpdated( this, &cSteamCallbacksHandler::OnRemoteStoragePublishedFileUpdated ),
	// screenshots
	m_ScreenshotReady( this, &cSteamCallbacksHandler::OnScreenshotReady ),
	m_ScreenshotRequested( this, &cSteamCallbacksHandler::OnScreenshotRequested ),
	// HTTP
	m_HTTPRequestCompleted( this, &cSteamCallbacksHandler::OnHTTPRequestCompleted ),
	m_HTTPRequestHeadersReceived( this, &cSteamCallbacksHandler::OnHTTPRequestHeadersReceived ),
	m_HTTPRequestDataReceived( this, &cSteamCallbacksHandler::OnHTTPRequestDataReceived ),
	// unified messages
	m_SteamUnifiedMessagesSendMethodResult( this, &cSteamCallbacksHandler::OnSteamUnifiedMessagesSendMethodResult ),
	// UGC
	m_SteamUGCQueryCompleted( this, &cSteamCallbacksHandler::OnSteamUGCQueryCompleted ),
	m_SteamUGCRequestUGCDetailsResult( this, &cSteamCallbacksHandler::OnSteamUGCRequestUGCDetailsResult ),
	m_CreateItemResult( this, &cSteamCallbacksHandler::OnCreateItemResult ),
	m_SubmitItemUpdateResult( this, &cSteamCallbacksHandler::OnSubmitItemUpdateResult ),
	m_ItemInstalled( this, &cSteamCallbacksHandler::OnItemInstalled ),
	// app list
	m_SteamAppInstalled( this, &cSteamCallbacksHandler::OnSteamAppInstalled ),
	m_SteamAppUninstalled( this, &cSteamCallbacksHandler::OnSteamAppUninstalled ),
	// music player
	m_PlaybackStatusHasChanged( this, &cSteamCallbacksHandler::OnPlaybackStatusHasChanged ),
	m_VolumeHasChanged( this, &cSteamCallbacksHandler::OnVolumeHasChanged ),
	// music player remote
	m_MusicPlayerRemoteWillActivate( this, &cSteamCallbacksHandler::OnMusicPlayerRemoteWillActivate ),
	m_MusicPlayerRemoteWillDeactivate( this, &cSteamCallbacksHandler::OnMusicPlayerRemoteWillDeactivate ),
	m_MusicPlayerRemoteToFront( this, &cSteamCallbacksHandler::OnMusicPlayerRemoteToFront ),
	m_MusicPlayerWillQuit( this, &cSteamCallbacksHandler::OnMusicPlayerWillQuit ),
	m_MusicPlayerWantsPlay( this, &cSteamCallbacksHandler::OnMusicPlayerWantsPlay ),
	m_MusicPlayerWantsPause( this, &cSteamCallbacksHandler::OnMusicPlayerWantsPause ),
	m_MusicPlayerWantsPlayPrevious( this, &cSteamCallbacksHandler::OnMusicPlayerWantsPlayPrevious ),
	m_MusicPlayerWantsPlayNext( this, &cSteamCallbacksHandler::OnMusicPlayerWantsPlayNext ),
	m_MusicPlayerWantsShuffled( this, &cSteamCallbacksHandler::OnMusicPlayerWantsShuffled ),
	m_MusicPlayerWantsLooped( this, &cSteamCallbacksHandler::OnMusicPlayerWantsLooped ),
	m_MusicPlayerWantsVolume( this, &cSteamCallbacksHandler::OnMusicPlayerWantsVolume ),
	m_MusicPlayerSelectsQueueEntry( this, &cSteamCallbacksHandler::OnMusicPlayerSelectsQueueEntry ),
	m_MusicPlayerSelectsPlaylistEntry( this, &cSteamCallbacksHandler::OnMusicPlayerSelectsPlaylistEntry ),
	// utils
	m_IPCountry( this, &cSteamCallbacksHandler::OnIPCountry ),
	m_LowBatteryPower( this, &cSteamCallbacksHandler::OnLowBatteryPower ),
	m_SteamAPICallCompleted( this, &cSteamCallbacksHandler::OnSteamAPICallCompleted ),
	m_SteamShutdown( this, &cSteamCallbacksHandler::OnSteamShutdown ),
	m_CheckFileSignature( this, &cSteamCallbacksHandler::OnCheckFileSignature ),
	m_GamepadTextInputDismissed( this, &cSteamCallbacksHandler::OnGamepadTextInputDismissed ),
	// friends
	m_PersonaStateChange( this, &cSteamCallbacksHandler::OnPersonaStateChange ),
	m_GameOverlayActivated( this, &cSteamCallbacksHandler::OnGameOverlayActivated ),
	m_GameServerChangeRequested( this, &cSteamCallbacksHandler::OnGameServerChangeRequested ),
	m_GameLobbyJoinRequested( this, &cSteamCallbacksHandler::OnGameLobbyJoinRequested ),
	m_AvatarImageLoaded( this, &cSteamCallbacksHandler::OnAvatarImageLoaded ),
	m_ClanOfficerListResponse( this, &cSteamCallbacksHandler::OnClanOfficerListResponse ),
	m_FriendRichPresenceUpdate( this, &cSteamCallbacksHandler::OnFriendRichPresenceUpdate ),
	m_GameRichPresenceJoinRequested( this, &cSteamCallbacksHandler::OnGameRichPresenceJoinRequested ),
	m_GameConnectedClanChatMsg( this, &cSteamCallbacksHandler::OnGameConnectedClanChatMsg ),
	m_GameConnectedChatJoin( this, &cSteamCallbacksHandler::OnGameConnectedChatJoin ),
	m_GameConnectedChatLeave( this, &cSteamCallbacksHandler::OnGameConnectedChatLeave ),
	m_DownloadClanActivityCountsResult( this, &cSteamCallbacksHandler::OnDownloadClanActivityCountsResult ),
	m_JoinClanChatRoomCompletionResult( this, &cSteamCallbacksHandler::OnJoinClanChatRoomCompletionResult ),
	m_GameConnectedFriendChatMsg( this, &cSteamCallbacksHandler::OnGameConnectedFriendChatMsg ),
	m_FriendsGetFollowerCount( this, &cSteamCallbacksHandler::OnFriendsGetFollowerCount ),
	m_FriendsIsFollowing( this, &cSteamCallbacksHandler::OnFriendsIsFollowing ),
	m_FriendsEnumerateFollowingList( this, &cSteamCallbacksHandler::OnFriendsEnumerateFollowingList ),
	m_SetPersonaNameResponse( this, &cSteamCallbacksHandler::OnSetPersonaNameResponse )
{
	cb = callbacks;
}

// friends 
void cSteamCallbacksHandler::OnPersonaStateChange(PersonaStateChange_t *pParam)
{
	if (cb.OnPersonaStateChange!=nullptr){ cb.OnPersonaStateChange(pParam->m_ulSteamID,pParam->m_nChangeFlags); };	
}
void cSteamCallbacksHandler::OnGameOverlayActivated(GameOverlayActivated_t *pParam)
{
	if (cb.OnGameOverlayActivated!=nullptr){ cb.OnGameOverlayActivated(pParam->m_bActive); };	
}
void cSteamCallbacksHandler::OnGameServerChangeRequested(GameServerChangeRequested_t *pParam)
{
	if (cb.OnGameServerChangeRequested!=nullptr){ cb.OnGameServerChangeRequested(pParam->m_rgchServer,pParam->m_rgchPassword); };	
}
void cSteamCallbacksHandler::OnGameLobbyJoinRequested(GameLobbyJoinRequested_t *pParam)
{
	if (cb.OnGameLobbyJoinRequested!=nullptr){ cb.OnGameLobbyJoinRequested(pParam->m_steamIDLobby,pParam->m_steamIDFriend); };	
}
void cSteamCallbacksHandler::OnAvatarImageLoaded(AvatarImageLoaded_t *pParam)
{
	if (cb.OnAvatarImageLoaded!=nullptr){ cb.OnAvatarImageLoaded(pParam->m_steamID,	pParam->m_iImage,pParam->m_iWide,pParam->m_iTall); };	
}
void cSteamCallbacksHandler::OnClanOfficerListResponse(ClanOfficerListResponse_t *pParam)
{
	if (cb.OnClanOfficerListResponse!=nullptr){ cb.OnClanOfficerListResponse(pParam->m_steamIDClan,pParam->m_cOfficers,pParam->m_bSuccess); };	
}
void cSteamCallbacksHandler::OnFriendRichPresenceUpdate(FriendRichPresenceUpdate_t *pParam)
{
	if (cb.OnFriendRichPresenceUpdate!=nullptr){ cb.OnFriendRichPresenceUpdate(pParam->m_steamIDFriend, pParam->m_nAppID); };	
}
void cSteamCallbacksHandler::OnGameRichPresenceJoinRequested(GameRichPresenceJoinRequested_t *pParam)
{
	if (cb.OnGameRichPresenceJoinRequested!=nullptr){ cb.OnGameRichPresenceJoinRequested(pParam->m_steamIDFriend,pParam->m_rgchConnect); };	
}
void cSteamCallbacksHandler::OnGameConnectedClanChatMsg(GameConnectedClanChatMsg_t *pParam)
{
	if (cb.OnGameConnectedClanChatMsg!=nullptr){ cb.OnGameConnectedClanChatMsg(pParam->m_steamIDClanChat,pParam->m_steamIDUser,	pParam->m_iMessageID); };	
}
void cSteamCallbacksHandler::OnGameConnectedChatJoin(GameConnectedChatJoin_t *pParam)
{
	if (cb.OnGameConnectedChatJoin!=nullptr){ cb.OnGameConnectedChatJoin(pParam->m_steamIDClanChat,pParam->m_steamIDUser); };	
}
void cSteamCallbacksHandler::OnGameConnectedChatLeave(GameConnectedChatLeave_t *pParam)
{
	if (cb.OnGameConnectedChatLeave!=nullptr){ cb.OnGameConnectedChatLeave(pParam->m_steamIDClanChat, pParam->m_steamIDUser,pParam->m_bKicked,pParam->m_bDropped); };	
}
void cSteamCallbacksHandler::OnDownloadClanActivityCountsResult(DownloadClanActivityCountsResult_t *pParam)
{
	if (cb.OnDownloadClanActivityCountsResult!=nullptr){ cb.OnDownloadClanActivityCountsResult(pParam->m_bSuccess); };	
}
void cSteamCallbacksHandler::OnJoinClanChatRoomCompletionResult(JoinClanChatRoomCompletionResult_t *pParam)
{
	if (cb.OnJoinClanChatRoomCompletionResult!=nullptr){ cb.OnJoinClanChatRoomCompletionResult(pParam->m_steamIDClanChat,pParam->m_eChatRoomEnterResponse); };	
}
void cSteamCallbacksHandler::OnGameConnectedFriendChatMsg(GameConnectedFriendChatMsg_t *pParam)
{
	if (cb.OnGameConnectedFriendChatMsg!=nullptr){ cb.OnGameConnectedFriendChatMsg( pParam->m_steamIDUser,pParam->m_iMessageID); };	
}
void cSteamCallbacksHandler::OnFriendsGetFollowerCount(FriendsGetFollowerCount_t *pParam)
{
	if (cb.OnFriendsGetFollowerCount!=nullptr){ cb.OnFriendsGetFollowerCount(pParam->m_eResult, pParam->m_steamID, pParam->m_nCount); };	
}
void cSteamCallbacksHandler::OnFriendsIsFollowing(FriendsIsFollowing_t *pParam)
{
	if (cb.OnFriendsIsFollowing!=nullptr){ cb.OnFriendsIsFollowing(pParam->m_eResult, pParam->m_steamID,pParam->m_bIsFollowing); };	
}
void cSteamCallbacksHandler::OnFriendsEnumerateFollowingList(FriendsEnumerateFollowingList_t *pParam)
{
	if (cb.OnFriendsEnumerateFollowingList!=nullptr){ cb.OnFriendsEnumerateFollowingList(pParam->m_eResult, pParam->m_rgSteamID,pParam->m_nResultsReturned,pParam->m_nTotalResultCount); };	
}
void cSteamCallbacksHandler::OnSetPersonaNameResponse(SetPersonaNameResponse_t *pParam)
{
	if (cb.OnSetPersonaNameResponse!=nullptr){ cb.OnSetPersonaNameResponse(pParam->m_bSuccess,pParam->m_bLocalSuccess, pParam->m_result); };
}
// utils
void cSteamCallbacksHandler::OnIPCountry(IPCountry_t *pParam)
{	
	if (cb.OnIPCountry!=nullptr){ cb.OnIPCountry(); };
}
void cSteamCallbacksHandler::OnLowBatteryPower(LowBatteryPower_t *pParam)
{
	if (cb.OnLowBatteryPower!=nullptr){ cb.OnLowBatteryPower(pParam->m_nMinutesBatteryLeft); };
}
void cSteamCallbacksHandler::OnSteamAPICallCompleted(SteamAPICallCompleted_t *pParam)
{
	if (cb.OnSteamAPICallCompleted!=nullptr){ cb.OnSteamAPICallCompleted(pParam->m_hAsyncCall); };
}
void cSteamCallbacksHandler::OnSteamShutdown(SteamShutdown_t *pParam)
{
	if (cb.OnSteamShutdown!=nullptr){ cb.OnSteamShutdown(); };
}
void cSteamCallbacksHandler::OnCheckFileSignature(CheckFileSignature_t *pParam)
{
	if (cb.OnCheckFileSignature!=nullptr){ cb.OnCheckFileSignature(pParam->m_eCheckFileSignature); };
}
void cSteamCallbacksHandler::OnGamepadTextInputDismissed(GamepadTextInputDismissed_t *pParam)
{
	if (cb.OnGamepadTextInputDismissed!=nullptr){ cb.OnGamepadTextInputDismissed(pParam->m_bSubmitted,pParam->m_unSubmittedText); };
}

// music player remote
void cSteamCallbacksHandler::OnMusicPlayerRemoteWillActivate(MusicPlayerRemoteWillActivate_t *pParam)
{
	if (cb.OnMusicPlayerRemoteWillActivate!=nullptr){ cb.OnMusicPlayerRemoteWillActivate(); };
}
void cSteamCallbacksHandler::OnMusicPlayerRemoteWillDeactivate(MusicPlayerRemoteWillDeactivate_t *pParam)
{
	if (cb.OnMusicPlayerRemoteWillDeactivate!=nullptr){ cb.OnMusicPlayerRemoteWillDeactivate(); };
}
void cSteamCallbacksHandler::OnMusicPlayerRemoteToFront(MusicPlayerRemoteToFront_t *pParam)
{
	if (cb.OnMusicPlayerRemoteToFront!=nullptr){ cb.OnMusicPlayerRemoteToFront(); };
}
void cSteamCallbacksHandler::OnMusicPlayerWillQuit(MusicPlayerWillQuit_t *pParam)
{
	if (cb.OnMusicPlayerWillQuit!=nullptr){ cb.OnMusicPlayerWillQuit(); };
}
void cSteamCallbacksHandler::OnMusicPlayerWantsPlay(MusicPlayerWantsPlay_t *pParam)
{
	if (cb.OnMusicPlayerWantsPlay!=nullptr){ cb.OnMusicPlayerWantsPlay(); };
}
void cSteamCallbacksHandler::OnMusicPlayerWantsPause(MusicPlayerWantsPause_t *pParam)
{
	if (cb.OnMusicPlayerWantsPause!=nullptr){ cb.OnMusicPlayerWantsPause(); };
}
void cSteamCallbacksHandler::OnMusicPlayerWantsPlayPrevious(MusicPlayerWantsPlayPrevious_t *pParam)
{
	if (cb.OnMusicPlayerWantsPlayPrevious!=nullptr){ cb.OnMusicPlayerWantsPlayPrevious(); };
}
void cSteamCallbacksHandler::OnMusicPlayerWantsPlayNext(MusicPlayerWantsPlayNext_t *pParam)
{
	if (cb.OnMusicPlayerWantsPlayNext!=nullptr){ cb.OnMusicPlayerWantsPlayNext(); };
}
void cSteamCallbacksHandler::OnMusicPlayerWantsShuffled(MusicPlayerWantsShuffled_t *pParam)
{
	if (cb.OnMusicPlayerWantsShuffled!=nullptr){ cb.OnMusicPlayerWantsShuffled(pParam->m_bShuffled); };
}
void cSteamCallbacksHandler::OnMusicPlayerWantsLooped(MusicPlayerWantsLooped_t *pParam)
{
	if (cb.OnMusicPlayerWantsLooped!=nullptr){ cb.OnMusicPlayerWantsLooped(pParam->m_bLooped); };
}
void cSteamCallbacksHandler::OnMusicPlayerWantsVolume(MusicPlayerWantsVolume_t *pParam)
{
	if (cb.OnMusicPlayerWantsVolume!=nullptr){ cb.OnMusicPlayerWantsVolume(pParam->m_flNewVolume); };
}
void cSteamCallbacksHandler::OnMusicPlayerSelectsQueueEntry(MusicPlayerSelectsQueueEntry_t *pParam)
{
	if (cb.OnMusicPlayerSelectsQueueEntry!=nullptr){ cb.OnMusicPlayerSelectsQueueEntry(pParam->nID); };
}
void cSteamCallbacksHandler::OnMusicPlayerSelectsPlaylistEntry(MusicPlayerSelectsPlaylistEntry_t *pParam)
{
	if (cb.OnMusicPlayerSelectsPlaylistEntry!=nullptr){ cb.OnMusicPlayerSelectsPlaylistEntry(pParam->nID); };
}

// music player
void cSteamCallbacksHandler::OnPlaybackStatusHasChanged(PlaybackStatusHasChanged_t *pParam)
{
	if (cb.OnPlaybackStatusHasChanged!=nullptr){ cb.OnPlaybackStatusHasChanged(); };
}
void cSteamCallbacksHandler::OnVolumeHasChanged(VolumeHasChanged_t *pParam)
{
	if (cb.OnVolumeHasChanged!=nullptr){ cb.OnVolumeHasChanged(pParam->m_flNewVolume); };
}

// app list
void cSteamCallbacksHandler::OnSteamAppInstalled(SteamAppInstalled_t *pParam)
{
	if (cb.OnSteamAppInstalled!=nullptr){ cb.OnSteamAppInstalled(pParam->m_nAppID); };
}
void cSteamCallbacksHandler::OnSteamAppUninstalled(SteamAppUninstalled_t *pParam)
{
	if (cb.OnSteamAppUninstalled!=nullptr){ cb.OnSteamAppUninstalled(pParam->m_nAppID); };
}

// UGC
void cSteamCallbacksHandler::OnSteamUGCQueryCompleted(SteamUGCQueryCompleted_t *pParam)
{
	if (cb.OnSteamUGCQueryCompleted!=nullptr){ cb.OnSteamUGCQueryCompleted(pParam->m_handle,pParam->m_eResult,pParam->m_unNumResultsReturned,pParam->m_unTotalMatchingResults,pParam->m_bCachedData); };
}
void cSteamCallbacksHandler::OnSteamUGCRequestUGCDetailsResult(SteamUGCRequestUGCDetailsResult_t *pParam)
{
	if (cb.OnSteamUGCRequestUGCDetailsResult!=nullptr){ cb.OnSteamUGCRequestUGCDetailsResult(pParam->m_details,pParam->m_bCachedData); };
}
void cSteamCallbacksHandler::OnCreateItemResult(CreateItemResult_t *pParam)
{
	if (cb.OnCreateItemResult!=nullptr){ cb.OnCreateItemResult(pParam->m_eResult,pParam->m_nPublishedFileId,pParam->m_bUserNeedsToAcceptWorkshopLegalAgreement); };
}
void cSteamCallbacksHandler::OnSubmitItemUpdateResult(SubmitItemUpdateResult_t *pParam)
{
	if (cb.OnSubmitItemUpdateResult!=nullptr){ cb.OnSubmitItemUpdateResult(pParam->m_eResult,pParam->m_bUserNeedsToAcceptWorkshopLegalAgreement); };
}
void cSteamCallbacksHandler::OnItemInstalled(ItemInstalled_t *pParam)
{
	if (cb.OnItemInstalled!=nullptr){ cb.OnItemInstalled(pParam->m_unAppID,pParam->m_nPublishedFileId); };
}

// unified messages
void cSteamCallbacksHandler::OnSteamUnifiedMessagesSendMethodResult(SteamUnifiedMessagesSendMethodResult_t *pParam)
{
	if (cb.OnSteamUnifiedMessagesSendMethodResult!=nullptr){ cb.OnSteamUnifiedMessagesSendMethodResult(pParam->m_hHandle,pParam->m_unContext,pParam->m_eResult,pParam->m_unResponseSize); };
}

// HTTP
void cSteamCallbacksHandler::OnHTTPRequestCompleted(HTTPRequestCompleted_t *pParam)
{
	if (cb.OnHTTPRequestCompleted!=nullptr){ cb.OnHTTPRequestCompleted(pParam->m_hRequest,pParam->m_ulContextValue,pParam->m_bRequestSuccessful,pParam->m_eStatusCode); };
}
void cSteamCallbacksHandler::OnHTTPRequestHeadersReceived(HTTPRequestHeadersReceived_t *pParam)
{
	if (cb.OnHTTPRequestHeadersReceived!=nullptr){ cb.OnHTTPRequestHeadersReceived(pParam->m_hRequest,pParam->m_ulContextValue); };
}
void cSteamCallbacksHandler::OnHTTPRequestDataReceived(HTTPRequestDataReceived_t *pParam)
{
	if (cb.OnHTTPRequestDataReceived!=nullptr){ cb.OnHTTPRequestDataReceived(pParam->m_hRequest,pParam->m_ulContextValue,pParam->m_cOffset,pParam->m_cBytesReceived); };
}

// screenshots
void cSteamCallbacksHandler::OnScreenshotReady(ScreenshotReady_t *pParam)
{
	if (cb.OnScreenshotReady!=nullptr){ cb.OnScreenshotReady(pParam->m_hLocal,pParam->m_eResult); };
}
void cSteamCallbacksHandler::OnScreenshotRequested(ScreenshotRequested_t *pParam)
{
	if (cb.OnScreenshotRequested!=nullptr){ cb.OnScreenshotRequested(); };
}

// remote storage
void cSteamCallbacksHandler::OnRemoteStorageAppSyncedClient(RemoteStorageAppSyncedClient_t *pParam)
{
	if (cb.OnRemoteStorageAppSyncedClient!=nullptr){ cb.OnRemoteStorageAppSyncedClient(pParam->m_nAppID,pParam->m_eResult,pParam->m_unNumDownloads); };
}
void cSteamCallbacksHandler::OnRemoteStorageAppSyncedServer(RemoteStorageAppSyncedServer_t *pParam)
{
	if (cb.OnRemoteStorageAppSyncedServer!=nullptr){ cb.OnRemoteStorageAppSyncedServer(pParam->m_nAppID,pParam->m_eResult,pParam->m_unNumUploads); };
}
void cSteamCallbacksHandler::OnRemoteStorageAppSyncProgress(RemoteStorageAppSyncProgress_t *pParam)
{
	if (cb.OnRemoteStorageAppSyncProgress!=nullptr){ cb.OnRemoteStorageAppSyncProgress(pParam->m_rgchCurrentFile,pParam->m_nAppID,pParam->m_uBytesTransferredThisChunk,pParam->m_dAppPercentComplete,pParam->m_bUploading); };
}
void cSteamCallbacksHandler::OnRemoteStorageAppSyncStatusCheck(RemoteStorageAppSyncStatusCheck_t *pParam)
{
	if (cb.OnRemoteStorageAppSyncStatusCheck!=nullptr){ cb.OnRemoteStorageAppSyncStatusCheck(pParam->m_nAppID,pParam->m_eResult); };
}
void cSteamCallbacksHandler::OnRemoteStorageConflictResolution(RemoteStorageConflictResolution_t *pParam)
{
	if (cb.OnRemoteStorageConflictResolution!=nullptr){ cb.OnRemoteStorageConflictResolution(pParam->m_nAppID,pParam->m_eResult); };
}
void cSteamCallbacksHandler::OnRemoteStorageFileShareResult(RemoteStorageFileShareResult_t *pParam)
{
	if (cb.OnRemoteStorageFileShareResult!=nullptr){ cb.OnRemoteStorageFileShareResult(pParam->m_eResult,pParam->m_hFile,pParam->m_rgchFilename); };
}
void cSteamCallbacksHandler::OnRemoteStoragePublishFileResult(RemoteStoragePublishFileResult_t *pParam)
{
	if (cb.OnRemoteStoragePublishFileResult!=nullptr){ cb.OnRemoteStoragePublishFileResult(pParam->m_eResult,pParam->m_nPublishedFileId,pParam->m_bUserNeedsToAcceptWorkshopLegalAgreement); };
}
void cSteamCallbacksHandler::OnRemoteStorageDeletePublishedFileResult(RemoteStorageDeletePublishedFileResult_t *pParam)
{
	if (cb.OnRemoteStorageDeletePublishedFileResult!=nullptr){ cb.OnRemoteStorageDeletePublishedFileResult(pParam->m_eResult,pParam->m_nPublishedFileId); };
}
void cSteamCallbacksHandler::OnRemoteStorageEnumerateUserPublishedFilesResult(RemoteStorageEnumerateUserPublishedFilesResult_t *pParam)
{
	if (cb.OnRemoteStorageEnumerateUserPublishedFilesResult!=nullptr){ cb.OnRemoteStorageEnumerateUserPublishedFilesResult(pParam->m_eResult,pParam->m_nResultsReturned,pParam->m_nTotalResultCount,pParam->m_rgPublishedFileId); };
}
void cSteamCallbacksHandler::OnRemoteStorageSubscribePublishedFileResult(RemoteStorageSubscribePublishedFileResult_t *pParam)
{
	if (cb.OnRemoteStorageSubscribePublishedFileResult!=nullptr){ cb.OnRemoteStorageSubscribePublishedFileResult(pParam->m_eResult,pParam->m_nPublishedFileId);};
}
void cSteamCallbacksHandler::OnRemoteStorageEnumerateUserSubscribedFilesResult(RemoteStorageEnumerateUserSubscribedFilesResult_t *pParam)
{
	if (cb.OnRemoteStorageEnumerateUserSubscribedFilesResult!=nullptr){ cb.OnRemoteStorageEnumerateUserSubscribedFilesResult(pParam->m_eResult,pParam->m_nResultsReturned,pParam->m_nTotalResultCount,pParam->m_rgPublishedFileId,pParam->m_rgRTimeSubscribed); };
}
void cSteamCallbacksHandler::OnRemoteStorageUnsubscribePublishedFileResult(RemoteStorageUnsubscribePublishedFileResult_t *pParam)
{
	if (cb.OnRemoteStorageUnsubscribePublishedFileResult!=nullptr){ cb.OnRemoteStorageUnsubscribePublishedFileResult (pParam->m_eResult,pParam->m_nPublishedFileId);};
}
void cSteamCallbacksHandler::OnRemoteStorageUpdatePublishedFileResult(RemoteStorageUpdatePublishedFileResult_t *pParam)
{
	if (cb.OnRemoteStorageUpdatePublishedFileResult!=nullptr){ cb.OnRemoteStorageUpdatePublishedFileResult (pParam->m_eResult,pParam->m_nPublishedFileId,pParam->m_bUserNeedsToAcceptWorkshopLegalAgreement);};
}
void cSteamCallbacksHandler::OnRemoteStorageDownloadUGCResult(RemoteStorageDownloadUGCResult_t *pParam)
{
	if (cb.OnRemoteStorageDownloadUGCResult!=nullptr){ cb.OnRemoteStorageDownloadUGCResult(pParam->m_eResult,pParam->m_hFile,pParam->m_nAppID,pParam->m_nSizeInBytes,pParam->m_pchFileName,pParam->m_ulSteamIDOwner); };
}
void cSteamCallbacksHandler::OnRemoteStorageGetPublishedFileDetailsResult(RemoteStorageGetPublishedFileDetailsResult_t *pParam)
{
	if (cb.OnRemoteStorageGetPublishedFileDetailsResult!=nullptr){ cb.OnRemoteStorageGetPublishedFileDetailsResult(pParam->m_eResult, pParam->m_nPublishedFileId, pParam->m_nCreatorAppID, pParam->m_nConsumerAppID, pParam->m_rgchTitle, pParam->m_rgchDescription, pParam->m_hFile, pParam->m_hPreviewFile, pParam->m_ulSteamIDOwner, pParam->m_rtimeCreated, pParam->m_rtimeUpdated, pParam->m_eVisibility, pParam->m_bBanned, pParam->m_rgchTags, pParam->m_bTagsTruncated, pParam->m_pchFileName, pParam->m_nFileSize, pParam->m_nPreviewFileSize, pParam->m_rgchURL, pParam->m_eFileType, pParam->m_bAcceptedForUse); };
}
void cSteamCallbacksHandler::OnRemoteStorageEnumerateWorkshopFilesResult(RemoteStorageEnumerateWorkshopFilesResult_t *pParam)
{
	if (cb.OnRemoteStorageEnumerateWorkshopFilesResult!=nullptr){ cb.OnRemoteStorageEnumerateWorkshopFilesResult(pParam->m_eResult, pParam->m_nResultsReturned, pParam->m_nTotalResultCount, pParam->m_rgPublishedFileId, pParam->m_rgScore, pParam->m_nAppId, pParam->m_unStartIndex); };
}
void cSteamCallbacksHandler::OnRemoteStorageGetPublishedItemVoteDetailsResult(RemoteStorageGetPublishedItemVoteDetailsResult_t *pParam)
{
	if (cb.OnRemoteStorageGetPublishedItemVoteDetailsResult!=nullptr){ cb.OnRemoteStorageGetPublishedItemVoteDetailsResult(pParam->m_eResult, pParam->m_unPublishedFileId, pParam->m_nVotesFor, pParam->m_nVotesAgainst, pParam->m_nReports, pParam->m_fScore); };
}
void cSteamCallbacksHandler::OnRemoteStoragePublishedFileSubscribed(RemoteStoragePublishedFileSubscribed_t *pParam)
{
	if (cb.OnRemoteStoragePublishedFileSubscribed!=nullptr){ cb.OnRemoteStoragePublishedFileSubscribed(pParam->m_nPublishedFileId,pParam->m_nAppID); };
}
void cSteamCallbacksHandler::OnRemoteStoragePublishedFileUnsubscribed(RemoteStoragePublishedFileUnsubscribed_t *pParam)
{
	if (cb.OnRemoteStoragePublishedFileUnsubscribed!=nullptr){ cb.OnRemoteStoragePublishedFileUnsubscribed(pParam->m_nPublishedFileId,pParam->m_nAppID); };
}
void cSteamCallbacksHandler::OnRemoteStoragePublishedFileDeleted(RemoteStoragePublishedFileDeleted_t *pParam)
{
	if (cb.OnRemoteStoragePublishedFileDeleted!=nullptr){ cb.OnRemoteStoragePublishedFileDeleted(pParam->m_nPublishedFileId,pParam->m_nAppID); };
}
void cSteamCallbacksHandler::OnRemoteStorageUpdateUserPublishedItemVoteResult(RemoteStorageUpdateUserPublishedItemVoteResult_t *pParam)
{
	if (cb.OnRemoteStorageUpdateUserPublishedItemVoteResult!=nullptr){ cb.OnRemoteStorageUpdateUserPublishedItemVoteResult(pParam->m_eResult,pParam->m_nPublishedFileId); };
}
void cSteamCallbacksHandler::OnRemoteStorageUserVoteDetails(RemoteStorageUserVoteDetails_t *pParam)
{
	if (cb.OnRemoteStorageUserVoteDetails!=nullptr){ cb.OnRemoteStorageUserVoteDetails(pParam->m_eResult,pParam->m_nPublishedFileId,pParam->m_eVote); };
}
void cSteamCallbacksHandler::OnRemoteStorageEnumerateUserSharedWorkshopFilesResult(RemoteStorageEnumerateUserSharedWorkshopFilesResult_t *pParam)
{
	if (cb.OnRemoteStorageEnumerateUserSharedWorkshopFilesResult!=nullptr){ cb.OnRemoteStorageEnumerateUserSharedWorkshopFilesResult(pParam->m_eResult,pParam->m_nResultsReturned,pParam->m_nTotalResultCount,pParam->m_rgPublishedFileId); };
}
void cSteamCallbacksHandler::OnRemoteStorageSetUserPublishedFileActionResult(RemoteStorageSetUserPublishedFileActionResult_t *pParam)
{
	if (cb.OnRemoteStorageSetUserPublishedFileActionResult!=nullptr){ cb.OnRemoteStorageSetUserPublishedFileActionResult(pParam->m_eResult,pParam->m_nPublishedFileId,pParam->m_eAction); };
}
void cSteamCallbacksHandler::OnRemoteStorageEnumeratePublishedFilesByUserActionResult(RemoteStorageEnumeratePublishedFilesByUserActionResult_t *pParam)
{
	if (cb.OnRemoteStorageEnumeratePublishedFilesByUserActionResult!=nullptr){ cb.OnRemoteStorageEnumeratePublishedFilesByUserActionResult(pParam->m_eResult,pParam->m_eAction,pParam->m_nResultsReturned,pParam->m_nTotalResultCount,pParam->m_rgPublishedFileId,pParam->m_rgRTimeUpdated); };
}
void cSteamCallbacksHandler::OnRemoteStoragePublishFileProgress(RemoteStoragePublishFileProgress_t *pParam)
{
	if (cb.OnRemoteStoragePublishFileProgress!=nullptr){ cb.OnRemoteStoragePublishFileProgress(pParam->m_dPercentFile,pParam->m_bPreview); };
}
void cSteamCallbacksHandler::OnRemoteStoragePublishedFileUpdated(RemoteStoragePublishedFileUpdated_t *pParam)
{
	if (cb.OnRemoteStoragePublishedFileUpdated!=nullptr){ cb.OnRemoteStoragePublishedFileUpdated(pParam->m_nPublishedFileId,pParam->m_nAppID,pParam->m_hFile); };
}

// matchmaking servers
void cSteamCallbacksHandler::OnFavoritesListChanged_ms(FavoritesListChanged_t *pParam)
{
	if (cb.OnFavoritesListChanged_ms!=nullptr){ cb.OnFavoritesListChanged_ms(pParam->m_nIP,pParam->m_nQueryPort,pParam->m_nConnPort,pParam->m_nAppID,pParam->m_nFlags,pParam->m_bAdd,pParam->m_unAccountId); };
}
void cSteamCallbacksHandler::OnLobbyInvite_ms(LobbyInvite_t *pParam)
{
	if (cb.OnLobbyInvite_ms!=nullptr){ cb.OnLobbyInvite_ms(pParam->m_ulSteamIDUser,pParam->m_ulSteamIDLobby,pParam->m_ulGameID); };
}
void cSteamCallbacksHandler::OnLobbyEnter_ms(LobbyEnter_t *pParam)
{
	if (cb.OnLobbyEnter_ms!=nullptr){ cb.OnLobbyEnter_ms(pParam->m_ulSteamIDLobby,pParam->m_rgfChatPermissions,pParam->m_bLocked,pParam->m_EChatRoomEnterResponse); };
}
void cSteamCallbacksHandler::OnLobbyDataUpdate_ms(LobbyDataUpdate_t *pParam)
{
	if (cb.OnLobbyDataUpdate_ms!=nullptr){ cb.OnLobbyDataUpdate_ms(pParam->m_ulSteamIDMember,pParam->m_ulSteamIDLobby,pParam->m_bSuccess); };
}
void cSteamCallbacksHandler::OnLobbyChatUpdate_ms(LobbyChatUpdate_t *pParam)
{
	if (cb.OnLobbyChatUpdate_ms!=nullptr){ cb.OnLobbyChatUpdate_ms(pParam->m_ulSteamIDUserChanged,pParam->m_ulSteamIDMakingChange,pParam->m_ulSteamIDLobby,pParam->m_rgfChatMemberStateChange); };
}
void cSteamCallbacksHandler::OnLobbyChatMsg_ms(LobbyChatMsg_t *pParam)
{
	if (cb.OnLobbyChatMsg_ms!=nullptr){ cb.OnLobbyChatMsg_ms( pParam->m_ulSteamIDLobby,pParam->m_ulSteamIDUser,pParam->m_eChatEntryType,pParam->m_iChatID); };
}
void cSteamCallbacksHandler::OnLobbyGameCreated_ms(LobbyGameCreated_t *pParam)
{
	if (cb.OnLobbyGameCreated_ms!=nullptr){ cb.OnLobbyGameCreated_ms(pParam->m_ulSteamIDLobby,pParam->m_ulSteamIDGameServer,pParam->m_unIP,pParam->m_usPort); };
}
void cSteamCallbacksHandler::OnLobbyMatchList_ms(LobbyMatchList_t *pParam)
{
	if (cb.OnLobbyMatchList_ms!=nullptr){ cb.OnLobbyMatchList_ms(pParam->m_nLobbiesMatching); };
}
void cSteamCallbacksHandler::OnLobbyKicked_ms(LobbyKicked_t *pParam)
{
	if (cb.OnLobbyKicked_ms!=nullptr){ cb.OnLobbyKicked_ms(pParam->m_ulSteamIDLobby,pParam->m_ulSteamIDAdmin,pParam->m_bKickedDueToDisconnect); };
}
void cSteamCallbacksHandler::OnLobbyCreated_ms(LobbyCreated_t *pParam)
{
	if (cb.OnLobbyCreated_ms!=nullptr){ cb.OnLobbyCreated_ms(pParam->m_eResult,pParam->m_ulSteamIDLobby); };
}
void cSteamCallbacksHandler::OnPSNGameBootInviteResult_ms(PSNGameBootInviteResult_t *pParam)
{
	if (cb.OnPSNGameBootInviteResult_ms!=nullptr){ cb.OnPSNGameBootInviteResult_ms(pParam->m_bGameBootInviteExists,pParam->m_steamIDLobby); };
}
void cSteamCallbacksHandler::OnFavoritesListAccountsUpdated_ms(FavoritesListAccountsUpdated_t *pParam)
{
	if (cb.OnFavoritesListAccountsUpdated_ms!=nullptr){ cb.OnFavoritesListAccountsUpdated_ms(pParam->m_eResult); };
}

// networking
void cSteamCallbacksHandler::OnP2PSessionRequest(P2PSessionRequest_t *pParam)
{
	if (cb.OnP2PSessionRequest!=nullptr){ cb.OnP2PSessionRequest(pParam->m_steamIDRemote); };
}
void cSteamCallbacksHandler::OnP2PSessionConnectFail(P2PSessionConnectFail_t *pParam)
{
	if (cb.OnP2PSessionConnectFail!=nullptr){ cb.OnP2PSessionConnectFail(pParam->m_steamIDRemote,pParam->m_eP2PSessionError); };
}
void cSteamCallbacksHandler::OnSocketStatusCallback(SocketStatusCallback_t *pParam)
{
	if (cb.OnSocketStatusCallback!=nullptr){ cb.OnSocketStatusCallback(pParam->m_hSocket,pParam->m_hListenSocket,pParam->m_steamIDRemote,pParam->m_eSNetSocketState); };
}

// apps
void cSteamCallbacksHandler::OnDlcInstalled(DlcInstalled_t *pParam)
{
	if (cb.OnDlcInstalled!=nullptr){ cb.OnDlcInstalled(pParam->m_nAppID); };
}
void cSteamCallbacksHandler::OnRegisterActivationCodeResponse(RegisterActivationCodeResponse_t *pParam)
{
	if (cb.OnRegisterActivationCodeResponse!=nullptr){ cb.OnRegisterActivationCodeResponse(pParam->m_eResult,pParam->m_unPackageRegistered); };
}
void cSteamCallbacksHandler::OnAppProofOfPurchaseKeyResponse(AppProofOfPurchaseKeyResponse_t *pParam)
{
	if (cb.OnAppProofOfPurchaseKeyResponse!=nullptr){ cb.OnAppProofOfPurchaseKeyResponse(pParam->m_eResult,pParam->m_nAppID,pParam->m_rgchKey); };
}
void cSteamCallbacksHandler::OnNewLaunchQueryParameters(NewLaunchQueryParameters_t *pParam)
{
	if (cb.OnNewLaunchQueryParameters!=nullptr){ cb.OnNewLaunchQueryParameters(); };
}

// user stats
void cSteamCallbacksHandler::OnUserStatsReceived(UserStatsReceived_t *pParam)
{
	if (cb.OnUserStatsReceived!=nullptr){ cb.OnUserStatsReceived(pParam->m_nGameID,pParam->m_eResult,pParam->m_steamIDUser); };
}
void cSteamCallbacksHandler::OnUserStatsStored(UserStatsStored_t *pParam)
{
	if (cb.OnUserStatsStored!=nullptr){ cb.OnUserStatsStored(pParam->m_nGameID,pParam->m_eResult); };
}
void cSteamCallbacksHandler::OnUserAchievementStored(UserAchievementStored_t *pParam)
{
	if (cb.OnUserAchievementStored!=nullptr){ cb.OnUserAchievementStored(pParam->m_nGameID,pParam->m_bGroupAchievement,pParam->m_rgchAchievementName,pParam->m_nCurProgress,pParam->m_nMaxProgress); };
}
void cSteamCallbacksHandler::OnLeaderboardFindResult(LeaderboardFindResult_t *pParam)
{	
	LogToFile("OnLeaderboardFindResult");
	if (cb.OnLeaderboardFindResult!=nullptr){ cb.OnLeaderboardFindResult(pParam->m_hSteamLeaderboard,pParam->m_bLeaderboardFound); };
}
void cSteamCallbacksHandler::OnLeaderboardScoresDownloaded(LeaderboardScoresDownloaded_t *pParam)
{
	if (cb.OnLeaderboardScoresDownloaded!=nullptr){ cb.OnLeaderboardScoresDownloaded(pParam->m_hSteamLeaderboard,pParam->m_hSteamLeaderboardEntries,pParam->m_cEntryCount); };
}
void cSteamCallbacksHandler::OnLeaderboardScoreUploaded(LeaderboardScoreUploaded_t *pParam)
{
	if (cb.OnLeaderboardScoreUploaded!=nullptr){ cb.OnLeaderboardScoreUploaded(pParam->m_bSuccess,pParam->m_hSteamLeaderboard,pParam->m_nScore,pParam->m_bScoreChanged,pParam->m_nGlobalRankNew,pParam->m_nGlobalRankPrevious); };
}
void cSteamCallbacksHandler::OnNumberOfCurrentPlayers(NumberOfCurrentPlayers_t *pParam)
{
	if (cb.OnNumberOfCurrentPlayers!=nullptr){ cb.OnNumberOfCurrentPlayers(pParam->m_bSuccess,pParam->m_cPlayers); };
}
void cSteamCallbacksHandler::OnUserStatsUnloaded(UserStatsUnloaded_t *pParam)
{
	if (cb.OnUserStatsUnloaded!=nullptr){ cb.OnUserStatsUnloaded(pParam->m_steamIDUser); };
}
void cSteamCallbacksHandler::OnUserAchievementIconFetched(UserAchievementIconFetched_t *pParam)
{
	if (cb.OnUserAchievementIconFetched!=nullptr){ cb.OnUserAchievementIconFetched(pParam->m_nGameID,pParam->m_rgchAchievementName,pParam->m_bAchieved,pParam->m_nIconHandle); };
}
void cSteamCallbacksHandler::OnGlobalAchievementPercentagesReady(GlobalAchievementPercentagesReady_t *pParam)
{
	if (cb.OnGlobalAchievementPercentagesReady!=nullptr){ cb.OnGlobalAchievementPercentagesReady(pParam->m_nGameID,pParam->m_eResult); };
}
void cSteamCallbacksHandler::OnLeaderboardUGCSet(LeaderboardUGCSet_t *pParam)
{
	if (cb.OnLeaderboardUGCSet!=nullptr){ cb.OnLeaderboardUGCSet(pParam->m_eResult,pParam->m_hSteamLeaderboard); };
}
void cSteamCallbacksHandler::OnGlobalStatsReceived(GlobalStatsReceived_t *pParam)
{
	if (cb.OnGlobalStatsReceived!=nullptr){ cb.OnGlobalStatsReceived(pParam->m_nGameID,pParam->m_eResult); };
}

// matchmaking
void cSteamCallbacksHandler::OnFavoritesListChanged(FavoritesListChanged_t *pParam)
{
	if (cb.OnFavoritesListChanged!=nullptr){ cb.OnFavoritesListChanged(pParam->m_nIP,pParam->m_nQueryPort,pParam->m_nConnPort,pParam->m_nAppID,pParam->m_nFlags,pParam->m_bAdd,pParam->m_unAccountId); };
}
void cSteamCallbacksHandler::OnLobbyInvite(LobbyInvite_t *pParam)
{
	if (cb.OnLobbyInvite!=nullptr){ cb.OnLobbyInvite(pParam->m_ulSteamIDUser,pParam->m_ulSteamIDLobby,pParam->m_ulGameID); };
}
void cSteamCallbacksHandler::OnLobbyEnter(LobbyEnter_t *pParam)
{
	if (cb.OnLobbyEnter!=nullptr){ cb.OnLobbyEnter(pParam->m_ulSteamIDLobby,pParam->m_rgfChatPermissions,pParam->m_bLocked,pParam->m_EChatRoomEnterResponse); };
}
void cSteamCallbacksHandler::OnLobbyDataUpdate(LobbyDataUpdate_t *pParam)
{
	if (cb.OnLobbyDataUpdate!=nullptr){ cb.OnLobbyDataUpdate(pParam->m_ulSteamIDLobby,pParam->m_ulSteamIDMember,pParam->m_bSuccess); };
}
void cSteamCallbacksHandler::OnLobbyChatUpdate(LobbyChatUpdate_t *pParam)
{
	if (cb.OnLobbyChatUpdate!=nullptr){ cb.OnLobbyChatUpdate(pParam->m_ulSteamIDLobby,pParam->m_ulSteamIDUserChanged,pParam->m_ulSteamIDMakingChange,pParam->m_rgfChatMemberStateChange); };
}
void cSteamCallbacksHandler::OnLobbyChatMsg(LobbyChatMsg_t *pParam)
{
	if (cb.OnLobbyChatMsg!=nullptr){ cb.OnLobbyChatMsg(pParam->m_ulSteamIDLobby,pParam->m_ulSteamIDUser,pParam->m_eChatEntryType,pParam->m_iChatID); };
}
void cSteamCallbacksHandler::OnLobbyGameCreated(LobbyGameCreated_t *pParam)
{
	if (cb.OnLobbyGameCreated!=nullptr){ cb.OnLobbyGameCreated(pParam->m_ulSteamIDLobby,pParam->m_ulSteamIDGameServer,pParam->m_unIP,pParam->m_usPort); };
}
void cSteamCallbacksHandler::OnLobbyMatchList(LobbyMatchList_t *pParam)
{
	if (cb.OnLobbyMatchList!=nullptr){ cb.OnLobbyMatchList(pParam->m_nLobbiesMatching); };
}
void cSteamCallbacksHandler::OnLobbyKicked(LobbyKicked_t *pParam)
{
	if (cb.OnLobbyKicked!=nullptr){ cb.OnLobbyKicked(pParam->m_ulSteamIDLobby,pParam->m_ulSteamIDAdmin,pParam->m_bKickedDueToDisconnect); };
}
void cSteamCallbacksHandler::OnLobbyCreated(LobbyCreated_t *pParam)
{
	if (cb.OnLobbyCreated!=nullptr){ cb.OnLobbyCreated(pParam->m_eResult,pParam->m_ulSteamIDLobby); };
}
void cSteamCallbacksHandler::OnPSNGameBootInviteResult(PSNGameBootInviteResult_t *pParam)
{
	if (cb.OnPSNGameBootInviteResult!=nullptr){ cb.OnPSNGameBootInviteResult(pParam->m_bGameBootInviteExists,pParam->m_steamIDLobby); };
}
void cSteamCallbacksHandler::OnFavoritesListAccountsUpdated(FavoritesListAccountsUpdated_t *pParam)
{
	if (cb.OnFavoritesListAccountsUpdated!=nullptr){ cb.OnFavoritesListAccountsUpdated(pParam->m_eResult); };
}

// user
void cSteamCallbacksHandler::OnSteamServersConnected(SteamServersConnected_t *pParam)
{
	if (cb.OnSteamServersConnected!=nullptr){ cb.OnSteamServersConnected(); };
}
void cSteamCallbacksHandler::OnSteamServerConnectFailure(SteamServerConnectFailure_t *pParam)
{
	if (cb.OnSteamServerConnectFailure!=nullptr){ cb.OnSteamServerConnectFailure(pParam->m_eResult); };
}
void cSteamCallbacksHandler::OnSteamServersDisconnected(SteamServersDisconnected_t *pParam)
{
	if (cb.OnSteamServersDisconnected!=nullptr){ cb.OnSteamServersDisconnected(pParam->m_eResult); };
}
void cSteamCallbacksHandler::OnClientGameServerDeny(ClientGameServerDeny_t *pParam)
{
	if (cb.OnClientGameServerDeny!=nullptr){ cb.OnClientGameServerDeny(pParam->m_uAppID,pParam->m_unGameServerIP,pParam->m_usGameServerPort,pParam->m_bSecure,pParam->m_uReason); };
}
void cSteamCallbacksHandler::OnIPCFailure(IPCFailure_t *pParam)
{
	if (cb.OnIPCFailure!=nullptr){ cb.OnIPCFailure(pParam->m_eFailureType); };
}
void cSteamCallbacksHandler::OnValidateAuthTicketResponse(ValidateAuthTicketResponse_t *pParam)
{
	if (cb.OnValidateAuthTicketResponse!=nullptr){ cb.OnValidateAuthTicketResponse(pParam->m_SteamID,pParam->m_eAuthSessionResponse,pParam->m_OwnerSteamID); };
}
void cSteamCallbacksHandler::OnMicroTxnAuthorizationResponse(MicroTxnAuthorizationResponse_t *pParam)
{
	if (cb.OnMicroTxnAuthorizationResponse!=nullptr){ cb.OnMicroTxnAuthorizationResponse(pParam->m_unAppID,pParam->m_ulOrderID,pParam->m_bAuthorized); };
}
void cSteamCallbacksHandler::OnEncryptedAppTicketResponse(EncryptedAppTicketResponse_t *pParam)
{
	if (cb.OnEncryptedAppTicketResponse!=nullptr){ cb.OnEncryptedAppTicketResponse(pParam->m_eResult); };
}
void cSteamCallbacksHandler::OnGetAuthSessionTicketResponse(GetAuthSessionTicketResponse_t *pParam)
{
	if (cb.OnGetAuthSessionTicketResponse!=nullptr){ cb.OnGetAuthSessionTicketResponse(pParam->m_hAuthTicket,pParam->m_eResult); };
}
void cSteamCallbacksHandler::OnGameWebCallback(GameWebCallback_t *pParam)
{
	if (cb.OnGameWebCallback!=nullptr){ cb.OnGameWebCallback(pParam->m_szURL); };
}

// server stats
void cSteamCallbacksHandler::OnGSStatsReceived(GSStatsReceived_t *pParam)
{
	if (cb.OnGSStatsReceived!=nullptr){ cb.OnGSStatsReceived(pParam->m_eResult,pParam->m_steamIDUser); };
}
void cSteamCallbacksHandler::OnGSStatsStored(GSStatsStored_t *pParam)
{
	if (cb.OnGSStatsStored!=nullptr){ cb.OnGSStatsStored(pParam->m_eResult,pParam->m_steamIDUser); };
}
void cSteamCallbacksHandler::OnGSStatsUnloaded(GSStatsUnloaded_t *pParam)
{
	if (cb.OnGSStatsUnloaded!=nullptr){ cb.OnGSStatsUnloaded(pParam->m_steamIDUser); };	
}

// server
void cSteamCallbacksHandler::OnGSClientApprove(GSClientApprove_t *pParam)
{
	if (cb.OnGSClientApprove!=nullptr){ cb.OnGSClientApprove(pParam->m_SteamID,pParam->m_OwnerSteamID); };	
}
void cSteamCallbacksHandler::OnGSClientDeny(GSClientDeny_t *pParam)
{
	if (cb.OnGSClientDeny!=nullptr){ cb.OnGSClientDeny(pParam->m_SteamID,pParam->m_eDenyReason,pParam->m_rgchOptionalText); };	
}
void cSteamCallbacksHandler::OnGSClientKick(GSClientKick_t *pParam)
{
	if (cb.OnGSClientKick!=nullptr){ cb.OnGSClientKick(pParam->m_SteamID,pParam->m_eDenyReason); };	
}
void cSteamCallbacksHandler::OnGSClientAchievementStatus(GSClientAchievementStatus_t *pParam)
{
	if (cb.OnGSClientAchievementStatus!=nullptr){ cb.OnGSClientAchievementStatus(pParam->m_SteamID,pParam->m_pchAchievement,pParam->m_bUnlocked); };	
}
void cSteamCallbacksHandler::OnGSPolicyResponse(GSPolicyResponse_t *pParam)
{
	if (cb.OnGSPolicyResponse!=nullptr){ cb.OnGSPolicyResponse(pParam->m_bSecure); };	
}
void cSteamCallbacksHandler::OnGSGameplayStats(GSGameplayStats_t *pParam)
{
	if (cb.OnGSGameplayStats!=nullptr){ cb.OnGSGameplayStats(pParam->m_eResult,pParam->m_nRank,pParam->m_unTotalConnects,pParam->m_unTotalMinutesPlayed); };	
}
void cSteamCallbacksHandler::OnGSClientGroupStatus(GSClientGroupStatus_t *pParam)
{
	if (cb.OnGSClientGroupStatus!=nullptr){ cb.OnGSClientGroupStatus(pParam->m_SteamIDUser,pParam->m_SteamIDGroup,pParam->m_bMember,pParam->m_bOfficer); }	;
}
void cSteamCallbacksHandler::OnGSReputation(GSReputation_t *pParam)
{
	if (cb.OnGSReputation!=nullptr){ cb.OnGSReputation(pParam->m_eResult,pParam->m_unReputationScore,pParam->m_bBanned,pParam->m_unBannedIP,pParam->m_usBannedPort,pParam->m_ulBannedGameID,pParam->m_unBanExpires	); };	
}
void cSteamCallbacksHandler::OnAssociateWithClanResult(AssociateWithClanResult_t *pParam)
{
	if (cb.OnAssociateWithClanResult!=nullptr){ cb.OnAssociateWithClanResult(pParam->m_eResult); };	
}
void cSteamCallbacksHandler::OnComputeNewPlayerCompatibilityResult(ComputeNewPlayerCompatibilityResult_t *pParam)
{
	if (cb.OnComputeNewPlayerCompatibilityResult!=nullptr){ cb.OnComputeNewPlayerCompatibilityResult(pParam->m_eResult, pParam->m_cPlayersThatDontLikeCandidate,pParam->m_cPlayersThatCandidateDoesntLike,pParam->m_cClanPlayersThatDontLikeCandidate,pParam->m_SteamIDCandidate);  };	
}