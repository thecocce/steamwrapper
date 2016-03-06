//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#pragma warning (disable: 4996 4800)
#include "steam_api.h"
#include "isteamgameserver.h"
#include "steam_gameserver.h"
#include "isteamgameserverstats.h"
#include "openvr.h"
#include <vector>

///////////////////////////////////////////////////////////////////// CALLBACKS DEF
// server
typedef void (*tOnComputeNewPlayerCompatibilityResult)(EResult	m_eResult, int m_cPlayersThatDontLikeCandidate,	int m_cPlayersThatCandidateDoesntLike,int m_cClanPlayersThatDontLikeCandidate,	CSteamID m_SteamIDCandidate );
typedef void (*tOnAssociateWithClanResult)(EResult	m_eResult);
typedef void (*tOnGSReputation)(EResult m_eResult, uint32 m_unReputationScore, bool	m_bBanned, uint32 m_unBannedIP,	uint16	m_usBannedPort,	uint64	m_ulBannedGameID,	uint32	m_unBanExpires);
typedef void (*tOnGSClientGroupStatus)(CSteamID m_SteamIDUser,	CSteamID m_SteamIDGroup, bool m_bMember, bool m_bOfficer);
typedef void (*tOnGSGameplayStats)(EResult m_eResult, int32 m_nRank, uint32	m_unTotalConnects, uint32	m_unTotalMinutesPlayed);
typedef void (*tOnGSPolicyResponse)(uint8 m_bSecure);
typedef void (*tOnGSClientAchievementStatus)(uint64 m_SteamID,	char m_pchAchievement[128],	bool m_bUnlocked);
typedef void (*tOnGSClientKick)(CSteamID m_SteamID, EDenyReason m_eDenyReason);
typedef void (*tOnGSClientDeny)(CSteamID m_SteamID,	EDenyReason m_eDenyReason,char m_rgchOptionalText[128]);
typedef void (*tOnGSClientApprove)(CSteamID m_SteamID,	CSteamID m_OwnerSteamID);
// server stats
typedef void (*tOnGSStatsReceived)(EResult	m_eResult,CSteamID m_steamIDUser);
typedef void (*tOnGSStatsStored)(EResult m_eResult,CSteamID m_steamIDUser);
typedef void (*tOnGSStatsUnloaded)(CSteamID m_steamIDUser);
// user
typedef void (*tOnSteamServersConnected)();
typedef void (*tOnSteamServerConnectFailure)(EResult m_eResult);
typedef void (*tOnSteamServersDisconnected)(EResult m_eResult);
typedef void (*tOnClientGameServerDeny)(uint32 m_uAppID,uint32 m_unGameServerIP,uint16 m_usGameServerPort,bool m_bSecure,uint32 m_uReason);
typedef void (*tOnIPCFailure)(uint8 FailureType);
typedef void (*tOnValidateAuthTicketResponse)(CSteamID m_SteamID,EAuthSessionResponse m_eAuthSessionResponse,CSteamID m_OwnerSteamID);
typedef void (*tOnMicroTxnAuthorizationResponse)(uint32 m_unAppID,	uint64 m_ulOrderID,	uint8 m_bAuthorized);
typedef void (*tOnEncryptedAppTicketResponse)(EResult m_eResult);
typedef void (*tOnGetAuthSessionTicketResponse)(HAuthTicket m_hAuthTicket,EResult m_eResult);
typedef void (*tOnGameWebCallback)(char m_szURL[256]);
// matchmaking
typedef void (*tOnFavoritesListChanged)(uint32 m_nIP,uint32 m_nQueryPort,uint32 m_nConnPort,uint32 m_nAppID,uint32 m_nFlags, bool m_bAdd, AccountID_t m_unAccountId);
typedef void (*tOnLobbyInvite)(uint64 m_ulSteamIDUser,	uint64 m_ulSteamIDLobby,uint64 m_ulGameID);
typedef void (*tOnLobbyEnter)(	uint64 m_ulSteamIDLobby,uint32 m_rgfChatPermissions,	bool m_bLocked,	uint32 m_EChatRoomEnterResponse);
typedef void (*tOnLobbyDataUpdate)(uint64 m_ulSteamIDLobby,uint64 m_ulSteamIDMember,uint8 m_bSuccess);
typedef void (*tOnLobbyChatUpdate)(uint64 m_ulSteamIDLobby,uint64 m_ulSteamIDUserChanged,uint64 m_ulSteamIDMakingChange,uint32 m_rgfChatMemberStateChange);
typedef void (*tOnLobbyChatMsg)(uint64 m_ulSteamIDLobby,uint64 m_ulSteamIDUser,uint8 m_eChatEntryType,	uint32 m_iChatID);
typedef void (*tOnLobbyGameCreated)(uint64 m_ulSteamIDLobby, uint64 m_ulSteamIDGameServer,uint32 m_unIP,uint16 m_usPort);
typedef void (*tOnLobbyMatchList)(uint32 m_nLobbiesMatching);
typedef void (*tOnLobbyKicked)(uint64 m_ulSteamIDLobby,uint64 m_ulSteamIDAdmin,uint8 m_bKickedDueToDisconnect);
typedef void (*tOnLobbyCreated)(EResult m_eResult,	uint64 m_ulSteamIDLobby);
typedef void (*tOnPSNGameBootInviteResult)(bool m_bGameBootInviteExists,CSteamID m_steamIDLobby);
typedef void (*tOnFavoritesListAccountsUpdated)(EResult m_eResult);
// user stats
typedef void (*tOnUserStatsReceived)(uint64 m_nGameID,EResult m_eResult,CSteamID m_steamIDUser);
typedef void (*tOnUserStatsStored)(uint64 m_nGameID,EResult m_eResult);
typedef void (*tOnUserAchievementStored)(uint64 m_nGameID,bool m_bGroupAchievement,char m_rgchAchievementName[k_cchStatNameMax],uint32 m_nCurProgress,uint32 m_nMaxProgress);
typedef void (*tOnLeaderboardFindResult)(SteamLeaderboard_t m_hSteamLeaderboard,uint8 m_bLeaderboardFound);
typedef void (*tOnLeaderboardScoresDownloaded)(SteamLeaderboard_t m_hSteamLeaderboard,	SteamLeaderboardEntries_t m_hSteamLeaderboardEntries,int m_cEntryCount);
typedef void (*tOnLeaderboardScoreUploaded)(uint8 m_bSuccess,SteamLeaderboard_t m_hSteamLeaderboard,int32 m_nScore,uint8 m_bScoreChanged,int m_nGlobalRankNew,int m_nGlobalRankPrevious);
typedef void (*tOnNumberOfCurrentPlayers)(uint8 m_bSuccess,int32 m_cPlayers);
typedef void (*tOnUserStatsUnloaded)(CSteamID	m_steamIDUser);
typedef void (*tOnUserAchievementIconFetched)(CGameID	m_nGameID,char m_rgchAchievementName[k_cchStatNameMax],bool m_bAchieved,int m_nIconHandle);
typedef void (*tOnGlobalAchievementPercentagesReady)(uint64 m_nGameID,	EResult	m_eResult);
typedef void (*tOnLeaderboardUGCSet)(EResult m_eResult,SteamLeaderboard_t m_hSteamLeaderboard);
typedef void (*tOnGlobalStatsReceived)(uint64	m_nGameID,EResult m_eResult);
// apps
typedef void (*tOnDlcInstalled)(AppId_t m_nAppID);
typedef void (*tOnRegisterActivationCodeResponse)(ERegisterActivationCodeResult m_eResult,uint32 m_unPackageRegistered);
typedef void (*tOnAppProofOfPurchaseKeyResponse)(EResult m_eResult,uint32	m_nAppID,char m_rgchKey[ k_cubAppProofOfPurchaseKeyMax ]);
typedef void (*tOnNewLaunchQueryParameters)();
// networking
typedef void (*tOnP2PSessionRequest)(CSteamID m_steamIDRemote);
typedef void (*tOnP2PSessionConnectFail)(CSteamID m_steamIDRemote,uint8 m_eP2PSessionError);
typedef void (*tOnSocketStatusCallback)(SNetSocket_t m_hSocket,SNetListenSocket_t m_hListenSocket,CSteamID m_steamIDRemote,int m_eSNetSocketState);
// remote storage
typedef void (*tOnRemoteStorageAppSyncedClient)(AppId_t m_nAppID,EResult m_eResult,int m_unNumDownloads);
typedef void (*tOnRemoteStorageAppSyncedServer)(AppId_t m_nAppID,EResult m_eResult,int m_unNumUploads);
typedef void (*tOnRemoteStorageAppSyncProgress)(char m_rgchCurrentFile[k_cchFilenameMax],AppId_t m_nAppID,uint32 m_uBytesTransferredThisChunk,double m_dAppPercentComplete,bool m_bUploading);
typedef void (*tOnRemoteStorageAppSyncStatusCheck)(AppId_t m_nAppID,EResult m_eResult);
typedef void (*tOnRemoteStorageConflictResolution)(AppId_t m_nAppID,EResult m_eResult);
typedef void (*tOnRemoteStorageFileShareResult)(EResult m_eResult,UGCHandle_t m_hFile,char m_rgchFilename[k_cchFilenameMax]);
typedef void (*tOnRemoteStoragePublishFileResult)(EResult m_eResult,PublishedFileId_t m_nPublishedFileId,bool m_bUserNeedsToAcceptWorkshopLegalAgreement);
typedef void (*tOnRemoteStorageDeletePublishedFileResult)(EResult m_eResult,PublishedFileId_t m_nPublishedFileId);
typedef void (*tOnRemoteStorageEnumerateUserPublishedFilesResult)(EResult m_eResult,int32 m_nResultsReturned,int32 m_nTotalResultCount,PublishedFileId_t m_rgPublishedFileId[ k_unEnumeratePublishedFilesMaxResults ]);
typedef void (*tOnRemoteStorageSubscribePublishedFileResult)(EResult m_eResult,PublishedFileId_t m_nPublishedFileId);
typedef void (*tOnRemoteStorageEnumerateUserSubscribedFilesResult)(EResult m_eResult,int32 m_nResultsReturned,int32 m_nTotalResultCount,PublishedFileId_t m_rgPublishedFileId[ k_unEnumeratePublishedFilesMaxResults ],uint32 m_rgRTimeSubscribed[ k_unEnumeratePublishedFilesMaxResults ]);
typedef void (*tOnRemoteStorageUnsubscribePublishedFileResult)(EResult m_eResult,PublishedFileId_t m_nPublishedFileId);
typedef void (*tOnRemoteStorageUpdatePublishedFileResult)(EResult m_eResult,PublishedFileId_t m_nPublishedFileId,bool m_bUserNeedsToAcceptWorkshopLegalAgreement);
typedef void (*tOnRemoteStorageDownloadUGCResult)(EResult m_eResult,UGCHandle_t m_hFile,AppId_t m_nAppID,int32 m_nSizeInBytes,char m_pchFileName[k_cchFilenameMax],uint64 m_ulSteamIDOwner);
typedef void (*tOnRemoteStorageGetPublishedFileDetailsResult)(EResult m_eResult,PublishedFileId_t m_nPublishedFileId,AppId_t m_nCreatorAppID,AppId_t m_nConsumerAppID,char m_rgchTitle[k_cchPublishedDocumentTitleMax],char m_rgchDescription[k_cchPublishedDocumentDescriptionMax],UGCHandle_t m_hFile,UGCHandle_t m_hPreviewFile,uint64 m_ulSteamIDOwner,uint32 m_rtimeCreated,uint32 m_rtimeUpdated,ERemoteStoragePublishedFileVisibility m_eVisibility,bool m_bBanned,char m_rgchTags[k_cchTagListMax],bool m_bTagsTruncated,char m_pchFileName[k_cchFilenameMax],int32 m_nFileSize,int32 m_nPreviewFileSize,char m_rgchURL[k_cchPublishedFileURLMax],EWorkshopFileType m_eFileType,bool m_bAcceptedForUse);
typedef void (*tOnRemoteStorageEnumerateWorkshopFilesResult)(EResult m_eResult,int32 m_nResultsReturned,int32 m_nTotalResultCount,PublishedFileId_t m_rgPublishedFileId[ k_unEnumeratePublishedFilesMaxResults ],float m_rgScore[ k_unEnumeratePublishedFilesMaxResults ],AppId_t m_nAppId,uint32 m_unStartIndex);
typedef void (*tOnRemoteStorageGetPublishedItemVoteDetailsResult)(EResult m_eResult,PublishedFileId_t m_unPublishedFileId,int32 m_nVotesFor,int32 m_nVotesAgainst,int32 m_nReports,float m_fScore);
typedef void (*tOnRemoteStoragePublishedFileSubscribed)(PublishedFileId_t m_nPublishedFileId,AppId_t m_nAppID);
typedef void (*tOnRemoteStoragePublishedFileUnsubscribed)(PublishedFileId_t m_nPublishedFileId,AppId_t m_nAppID);
typedef void (*tOnRemoteStoragePublishedFileDeleted)(PublishedFileId_t m_nPublishedFileId,AppId_t m_nAppID);
typedef void (*tOnRemoteStorageUpdateUserPublishedItemVoteResult)(EResult m_eResult,PublishedFileId_t m_nPublishedFileId);
typedef void (*tOnRemoteStorageUserVoteDetails)(EResult m_eResult,PublishedFileId_t m_nPublishedFileId,EWorkshopVote m_eVote);
typedef void (*tOnRemoteStorageEnumerateUserSharedWorkshopFilesResult)(EResult m_eResult,int32 m_nResultsReturned,int32 m_nTotalResultCount,PublishedFileId_t m_rgPublishedFileId[ k_unEnumeratePublishedFilesMaxResults ]);
typedef void (*tOnRemoteStorageSetUserPublishedFileActionResult)(EResult m_eResult,PublishedFileId_t m_nPublishedFileId,EWorkshopFileAction m_eAction);
typedef void (*tOnRemoteStorageEnumeratePublishedFilesByUserActionResult)(EResult m_eResult,EWorkshopFileAction m_eAction,int32 m_nResultsReturned,int32 m_nTotalResultCount,PublishedFileId_t m_rgPublishedFileId[ k_unEnumeratePublishedFilesMaxResults ],uint32 m_rgRTimeUpdated[ k_unEnumeratePublishedFilesMaxResults ]);
typedef void (*tOnRemoteStoragePublishFileProgress)(double m_dPercentFile,bool m_bPreview);
typedef void (*tOnRemoteStoragePublishedFileUpdated)(PublishedFileId_t m_nPublishedFileId,AppId_t m_nAppID,UGCHandle_t m_hFile);
// screenshots
typedef void (*tOnScreenshotReady)(ScreenshotHandle m_hLocal,EResult m_eResult);
typedef void (*tOnScreenshotRequested)();
// HTTP
typedef void (*tOnHTTPRequestCompleted)(HTTPRequestHandle m_hRequest,uint64 m_ulContextValue,bool m_bRequestSuccessful,EHTTPStatusCode m_eStatusCode);
typedef void (*tOnHTTPRequestHeadersReceived)(HTTPRequestHandle m_hRequest,uint64 m_ulContextValue);
typedef void (*tOnHTTPRequestDataReceived)(HTTPRequestHandle m_hRequest,uint64 m_ulContextValue,uint32 m_cOffset,uint32 m_cBytesReceived);
// unified messages
typedef void (*tOnSteamUnifiedMessagesSendMethodResult)(ClientUnifiedMessageHandle m_hHandle,uint64 m_unContext,EResult m_eResult,uint32 m_unResponseSize);
// UGC
typedef void (*tOnSteamUGCQueryCompleted)(UGCQueryHandle_t m_handle,EResult m_eResult,uint32 m_unNumResultsReturned,uint32 m_unTotalMatchingResults,bool m_bCachedData);
typedef void (*tOnSteamUGCRequestUGCDetailsResult)(SteamUGCDetails_t m_details,bool m_bCachedData);
typedef void (*tOnCreateItemResult)(EResult m_eResult,PublishedFileId_t m_nPublishedFileId,bool m_bUserNeedsToAcceptWorkshopLegalAgreement);
typedef void (*tOnSubmitItemUpdateResult)(EResult m_eResult,bool m_bUserNeedsToAcceptWorkshopLegalAgreement);
typedef void (*tOnItemInstalled)(AppId_t m_unAppID,	PublishedFileId_t m_nPublishedFileId);
// app list
typedef void (*tOnSteamAppInstalled)(AppId_t m_nAppID);
typedef void (*tOnSteamAppUninstalled)(AppId_t m_nAppID);
// music player
typedef void (*tOnPlaybackStatusHasChanged)();
typedef void (*tOnVolumeHasChanged)(float NewVolume);
// music player remote
typedef void (*tOnMusicPlayerRemoteWillActivate)();
typedef void (*tOnMusicPlayerRemoteWillDeactivate)();
typedef void (*tOnMusicPlayerRemoteToFront)();
typedef void (*tOnMusicPlayerWillQuit)();
typedef void (*tOnMusicPlayerWantsPlay)();
typedef void (*tOnMusicPlayerWantsPause)();
typedef void (*tOnMusicPlayerWantsPlayPrevious)();
typedef void (*tOnMusicPlayerWantsPlayNext)();
typedef void (*tOnMusicPlayerWantsShuffled)(bool Shuffled);
typedef void (*tOnMusicPlayerWantsLooped)(bool Looped);
typedef void (*tOnMusicPlayerWantsVolume)( float NewVolume);
typedef void (*tOnMusicPlayerSelectsQueueEntry)( int ID);
typedef void (*tOnMusicPlayerSelectsPlaylistEntry)(int ID);
// HTML surface
typedef void (*tOnCloseBrowser)();
typedef void (*tOnNeedsPaint)( const char * pBGRA, uint32 unWide,uint32 unTall,uint32 unUpdateX,uint32 unUpdateY,uint32 unUpdateWide, uint32 unUpdateTall, uint32 unScrollX, uint32 unScrollY, float flPageScale, uint32 unPageSerial);
typedef void (*tOnStartRequest)( const char * pchURL, const char * pchTarget, const char * pchPostData, bool bIsRedirect);
typedef void (*tOnFinishedRequest)( const char * pchURL,const char * pchPageTitle);
typedef void (*tOnURLChanged)( const char *pchURL,const char *pchPostData,bool bIsRedirect,const char *pchPageTitle,bool bNewNavigation );
typedef void (*tOnOpenLinkInNewTab)(const char *pchURL );
typedef void (*tOnChangedTitle)(const char *pchTitle );
typedef void (*tOnSearchResults)(uint32 unResults,uint32 unCurrentMatch );
typedef void (*tOnCanGoBackAndForward)(bool bCanGoBack,bool bCanGoForward );
typedef void (*tOnHorizontalScroll)(uint32 unScrollMax, uint32 unScrollCurrent, float flPageScale, bool bVisible, uint32 unPageSize );
typedef void (*tOnVerticalScroll)(uint32 unScrollMax, uint32 unScrollCurrent, float flPageScale, bool bVisible, uint32 unPageSize );
typedef void (*tOnLinkAtPosition)(uint32 x , uint32 y , const char *pchURL, bool bInput, bool bLiveLink );
typedef void (*tOnJSAlert)(const char *pchMessage );
typedef void (*tOnJSConfirm)(const char *pchMessage );
typedef void (*tOnFileOpenDialog)(const char *pchTitle,const char *pchInitialFile );
typedef void (*tOnComboNeedsPaint)(const char *pBGRA,uint32 unWide,uint32 unTall );
typedef void (*tOnShowPopup)();
typedef void (*tOnHidePopup)();
typedef void (*tOnSizePopup)(uint32 unX, uint32 unY, uint32 unWide, uint32 unTall );
typedef void (*tOnNewWindow)( const char *pchURL, uint32 unX, uint32 unY, uint32 unWide, uint32 unTall );
typedef void (*tOnSetCursor)( uint32 eMouseCursor );
typedef void (*tOnStatusText)( const char *pchMsg );
typedef void (*tOnShowToolTip)(const char *pchMsg );
typedef void (*tOnUpdateToolTip)( const char *pchMsg );
typedef void (*tOnHideToolTip)();
typedef void (*tOnBrowserReady)(bool bIOFailure);
// utils
typedef void (*tOnIPCountry)();
typedef void (*tOnLowBatteryPower)(uint8 m_nMinutesBatteryLeft);
typedef void (*tOnSteamAPICallCompleted)(SteamAPICall_t m_hAsyncCall);
typedef void (*tOnSteamShutdown)();
typedef void (*tOnCheckFileSignature)(ECheckFileSignature m_eCheckFileSignature);
typedef void (*tOnGamepadTextInputDismissed)(bool m_bSubmitted,uint32 m_unSubmittedText);
// friends
typedef void (*tOnPersonaStateChange)(uint64 m_ulSteamID,	int m_nChangeFlags);
typedef void (*tOnGameOverlayActivated)(uint8 m_bActive);
typedef void (*tOnGameServerChangeRequested)(char m_rgchServer[64],	char m_rgchPassword[64]);
typedef void (*tOnGameLobbyJoinRequested)(CSteamID m_steamIDLobby,CSteamID m_steamIDFriend);
typedef void (*tOnAvatarImageLoaded)(CSteamID m_steamID,	int m_iImage,int m_iWide,int m_iTall);
typedef void (*tOnClanOfficerListResponse)(CSteamID m_steamIDClan,int m_cOfficers,uint8 m_bSuccess);
typedef void (*tOnFriendRichPresenceUpdate)(CSteamID m_steamIDFriend,AppId_t m_nAppID);
typedef void (*tOnGameRichPresenceJoinRequested)(CSteamID m_steamIDFriend,char m_rgchConnect[k_cchMaxRichPresenceValueLength]);
typedef void (*tOnGameConnectedClanChatMsg)(CSteamID m_steamIDClanChat,	CSteamID m_steamIDUser,	int m_iMessageID);
typedef void (*tOnGameConnectedChatJoin)(CSteamID m_steamIDClanChat,	CSteamID m_steamIDUser);
typedef void (*tOnGameConnectedChatLeave)(CSteamID m_steamIDClanChat,CSteamID m_steamIDUser,	bool m_bKicked,	bool m_bDropped);
typedef void (*tOnDownloadClanActivityCountsResult)(bool m_bSuccess);
typedef void (*tOnJoinClanChatRoomCompletionResult)(CSteamID m_steamIDClanChat,	EChatRoomEnterResponse m_eChatRoomEnterResponse);
typedef void (*tOnGameConnectedFriendChatMsg)(CSteamID m_steamIDUser,	int m_iMessageID);
typedef void (*tOnFriendsGetFollowerCount)(EResult m_eResult,CSteamID m_steamID,int m_nCount);
typedef void (*tOnFriendsIsFollowing)(EResult m_eResult,CSteamID m_steamID,bool m_bIsFollowing);
typedef void (*tOnFriendsEnumerateFollowingList)(EResult m_eResult,CSteamID m_rgSteamID[ k_cEnumerateFollowersMax ],int32 m_nResultsReturned,int32 m_nTotalResultCount);
typedef void (*tOnSetPersonaNameResponse)(bool m_bSuccess,bool m_bLocalSuccess,EResult m_result);


///////////////////////////////////////////////////////////////////// CALLBACKS


struct cSteamCallbacks
{
	// server
	tOnComputeNewPlayerCompatibilityResult OnComputeNewPlayerCompatibilityResult;
	tOnAssociateWithClanResult OnAssociateWithClanResult;
	tOnGSReputation OnGSReputation;
	tOnGSClientGroupStatus OnGSClientGroupStatus;
	tOnGSGameplayStats OnGSGameplayStats;
	tOnGSPolicyResponse OnGSPolicyResponse;
	tOnGSClientAchievementStatus OnGSClientAchievementStatus;
	tOnGSClientKick OnGSClientKick;
	tOnGSClientDeny OnGSClientDeny;
	tOnGSClientApprove OnGSClientApprove;
	// server stats
	tOnGSStatsReceived OnGSStatsReceived;
	tOnGSStatsStored OnGSStatsStored;
	tOnGSStatsUnloaded OnGSStatsUnloaded;
	// user
	tOnSteamServersConnected OnSteamServersConnected;
	tOnSteamServerConnectFailure OnSteamServerConnectFailure;
	tOnSteamServersDisconnected OnSteamServersDisconnected;
	tOnClientGameServerDeny OnClientGameServerDeny;
	tOnIPCFailure OnIPCFailure;
	tOnValidateAuthTicketResponse OnValidateAuthTicketResponse;
	tOnMicroTxnAuthorizationResponse OnMicroTxnAuthorizationResponse;
	tOnEncryptedAppTicketResponse OnEncryptedAppTicketResponse;
	tOnGetAuthSessionTicketResponse OnGetAuthSessionTicketResponse;
	tOnGameWebCallback OnGameWebCallback;
	// matchmaking
	tOnFavoritesListChanged OnFavoritesListChanged;
	tOnLobbyInvite OnLobbyInvite;
	tOnLobbyEnter OnLobbyEnter;
	tOnLobbyDataUpdate OnLobbyDataUpdate;
	tOnLobbyChatUpdate OnLobbyChatUpdate;
	tOnLobbyChatMsg OnLobbyChatMsg;
	tOnLobbyGameCreated OnLobbyGameCreated;
	tOnLobbyMatchList OnLobbyMatchList;
	tOnLobbyKicked OnLobbyKicked;
	tOnLobbyCreated OnLobbyCreated;
	tOnPSNGameBootInviteResult OnPSNGameBootInviteResult;
	tOnFavoritesListAccountsUpdated OnFavoritesListAccountsUpdated;
	// matchmaking servers
	tOnFavoritesListChanged OnFavoritesListChanged_ms;
	tOnLobbyInvite OnLobbyInvite_ms;
	tOnLobbyEnter OnLobbyEnter_ms;
	tOnLobbyDataUpdate OnLobbyDataUpdate_ms;
	tOnLobbyChatUpdate OnLobbyChatUpdate_ms;
	tOnLobbyChatMsg OnLobbyChatMsg_ms;
	tOnLobbyGameCreated OnLobbyGameCreated_ms;
	tOnLobbyMatchList OnLobbyMatchList_ms;
	tOnLobbyKicked OnLobbyKicked_ms;
	tOnLobbyCreated OnLobbyCreated_ms;
	tOnPSNGameBootInviteResult OnPSNGameBootInviteResult_ms;
	tOnFavoritesListAccountsUpdated OnFavoritesListAccountsUpdated_ms;
	// user stats
	tOnUserStatsReceived OnUserStatsReceived;
	tOnUserStatsStored OnUserStatsStored;
	tOnUserAchievementStored OnUserAchievementStored;
	tOnLeaderboardFindResult OnLeaderboardFindResult;
	tOnLeaderboardScoresDownloaded OnLeaderboardScoresDownloaded;
	tOnLeaderboardScoreUploaded OnLeaderboardScoreUploaded;
	tOnNumberOfCurrentPlayers OnNumberOfCurrentPlayers;
	tOnUserStatsUnloaded OnUserStatsUnloaded;
	tOnUserAchievementIconFetched OnUserAchievementIconFetched;
	tOnGlobalAchievementPercentagesReady OnGlobalAchievementPercentagesReady;
	tOnLeaderboardUGCSet OnLeaderboardUGCSet;
	tOnGlobalStatsReceived OnGlobalStatsReceived;
	// apps
	tOnDlcInstalled OnDlcInstalled;
	tOnRegisterActivationCodeResponse OnRegisterActivationCodeResponse;
	tOnAppProofOfPurchaseKeyResponse OnAppProofOfPurchaseKeyResponse;
	tOnNewLaunchQueryParameters OnNewLaunchQueryParameters;
	// networking
	tOnP2PSessionRequest OnP2PSessionRequest;
	tOnP2PSessionConnectFail OnP2PSessionConnectFail;
	tOnSocketStatusCallback OnSocketStatusCallback;
	// remote storage
	tOnRemoteStorageAppSyncedClient OnRemoteStorageAppSyncedClient;
	tOnRemoteStorageAppSyncedServer OnRemoteStorageAppSyncedServer;
	tOnRemoteStorageAppSyncProgress OnRemoteStorageAppSyncProgress;
	tOnRemoteStorageAppSyncStatusCheck OnRemoteStorageAppSyncStatusCheck;
	tOnRemoteStorageConflictResolution OnRemoteStorageConflictResolution;
	tOnRemoteStorageFileShareResult OnRemoteStorageFileShareResult;
	tOnRemoteStoragePublishFileResult OnRemoteStoragePublishFileResult;
	tOnRemoteStorageDeletePublishedFileResult OnRemoteStorageDeletePublishedFileResult;
	tOnRemoteStorageEnumerateUserPublishedFilesResult OnRemoteStorageEnumerateUserPublishedFilesResult;
	tOnRemoteStorageSubscribePublishedFileResult OnRemoteStorageSubscribePublishedFileResult;
	tOnRemoteStorageEnumerateUserSubscribedFilesResult OnRemoteStorageEnumerateUserSubscribedFilesResult;
	tOnRemoteStorageUnsubscribePublishedFileResult OnRemoteStorageUnsubscribePublishedFileResult;
	tOnRemoteStorageUpdatePublishedFileResult OnRemoteStorageUpdatePublishedFileResult;
	tOnRemoteStorageDownloadUGCResult OnRemoteStorageDownloadUGCResult;
	tOnRemoteStorageGetPublishedFileDetailsResult OnRemoteStorageGetPublishedFileDetailsResult;
	tOnRemoteStorageEnumerateWorkshopFilesResult OnRemoteStorageEnumerateWorkshopFilesResult;
	tOnRemoteStorageGetPublishedItemVoteDetailsResult OnRemoteStorageGetPublishedItemVoteDetailsResult;
	tOnRemoteStoragePublishedFileSubscribed OnRemoteStoragePublishedFileSubscribed;
	tOnRemoteStoragePublishedFileUnsubscribed OnRemoteStoragePublishedFileUnsubscribed;
	tOnRemoteStoragePublishedFileDeleted OnRemoteStoragePublishedFileDeleted;
	tOnRemoteStorageUpdateUserPublishedItemVoteResult OnRemoteStorageUpdateUserPublishedItemVoteResult;
	tOnRemoteStorageUserVoteDetails OnRemoteStorageUserVoteDetails;
	tOnRemoteStorageEnumerateUserSharedWorkshopFilesResult OnRemoteStorageEnumerateUserSharedWorkshopFilesResult;
	tOnRemoteStorageSetUserPublishedFileActionResult OnRemoteStorageSetUserPublishedFileActionResult;
	tOnRemoteStorageEnumeratePublishedFilesByUserActionResult OnRemoteStorageEnumeratePublishedFilesByUserActionResult;
	tOnRemoteStoragePublishFileProgress OnRemoteStoragePublishFileProgress;
	tOnRemoteStoragePublishedFileUpdated OnRemoteStoragePublishedFileUpdated;
	// screenshots
	tOnScreenshotReady OnScreenshotReady;
	tOnScreenshotRequested OnScreenshotRequested;
	// HTTP
	tOnHTTPRequestCompleted OnHTTPRequestCompleted;
	tOnHTTPRequestHeadersReceived OnHTTPRequestHeadersReceived;
	tOnHTTPRequestDataReceived OnHTTPRequestDataReceived;
	// unified messages
	tOnSteamUnifiedMessagesSendMethodResult OnSteamUnifiedMessagesSendMethodResult;
	// UGC
	tOnSteamUGCQueryCompleted OnSteamUGCQueryCompleted;
	tOnSteamUGCRequestUGCDetailsResult OnSteamUGCRequestUGCDetailsResult;
	tOnCreateItemResult OnCreateItemResult;
	tOnSubmitItemUpdateResult OnSubmitItemUpdateResult;
	tOnItemInstalled OnItemInstalled;
	// app list
	tOnSteamAppInstalled OnSteamAppInstalled;
	tOnSteamAppUninstalled OnSteamAppUninstalled;
	// music player
	tOnPlaybackStatusHasChanged OnPlaybackStatusHasChanged;
	tOnVolumeHasChanged OnVolumeHasChanged;
	// music player remote
	tOnMusicPlayerRemoteWillActivate OnMusicPlayerRemoteWillActivate;
	tOnMusicPlayerRemoteWillDeactivate OnMusicPlayerRemoteWillDeactivate;
	tOnMusicPlayerRemoteToFront OnMusicPlayerRemoteToFront;
	tOnMusicPlayerWillQuit OnMusicPlayerWillQuit;
	tOnMusicPlayerWantsPlay OnMusicPlayerWantsPlay;
	tOnMusicPlayerWantsPause OnMusicPlayerWantsPause;
	tOnMusicPlayerWantsPlayPrevious OnMusicPlayerWantsPlayPrevious;
	tOnMusicPlayerWantsPlayNext OnMusicPlayerWantsPlayNext;
	tOnMusicPlayerWantsShuffled OnMusicPlayerWantsShuffled;
	tOnMusicPlayerWantsLooped OnMusicPlayerWantsLooped;
	tOnMusicPlayerWantsVolume OnMusicPlayerWantsVolume;
	tOnMusicPlayerSelectsQueueEntry OnMusicPlayerSelectsQueueEntry;
	tOnMusicPlayerSelectsPlaylistEntry OnMusicPlayerSelectsPlaylistEntry;
	// utils
	tOnIPCountry OnIPCountry;
	tOnLowBatteryPower OnLowBatteryPower;
	tOnSteamAPICallCompleted OnSteamAPICallCompleted;
	tOnSteamShutdown OnSteamShutdown;
	tOnCheckFileSignature OnCheckFileSignature;
	tOnGamepadTextInputDismissed OnGamepadTextInputDismissed;
	// friends
	tOnPersonaStateChange OnPersonaStateChange;
	tOnGameOverlayActivated OnGameOverlayActivated;
	tOnGameServerChangeRequested OnGameServerChangeRequested;
	tOnGameLobbyJoinRequested OnGameLobbyJoinRequested;
	tOnAvatarImageLoaded OnAvatarImageLoaded;
	tOnClanOfficerListResponse OnClanOfficerListResponse;
	tOnFriendRichPresenceUpdate OnFriendRichPresenceUpdate;
	tOnGameRichPresenceJoinRequested OnGameRichPresenceJoinRequested;
	tOnGameConnectedClanChatMsg OnGameConnectedClanChatMsg;
	tOnGameConnectedChatJoin OnGameConnectedChatJoin;
	tOnGameConnectedChatLeave OnGameConnectedChatLeave;
	tOnDownloadClanActivityCountsResult OnDownloadClanActivityCountsResult;
	tOnJoinClanChatRoomCompletionResult OnJoinClanChatRoomCompletionResult;
	tOnGameConnectedFriendChatMsg OnGameConnectedFriendChatMsg;
	tOnFriendsGetFollowerCount OnFriendsGetFollowerCount;
	tOnFriendsIsFollowing OnFriendsIsFollowing;
	tOnFriendsEnumerateFollowingList OnFriendsEnumerateFollowingList;
	tOnSetPersonaNameResponse OnSetPersonaNameResponse;	
};

class cSteamCallbacksHandler 
{
private:
	cSteamCallbacks cb;	

	// friends
	STEAM_CALLBACK( cSteamCallbacksHandler, OnPersonaStateChange, PersonaStateChange_t, m_PersonaStateChange );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGameOverlayActivated, GameOverlayActivated_t, m_GameOverlayActivated );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGameServerChangeRequested, GameServerChangeRequested_t, m_GameServerChangeRequested );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGameLobbyJoinRequested, GameLobbyJoinRequested_t, m_GameLobbyJoinRequested );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnAvatarImageLoaded, AvatarImageLoaded_t, m_AvatarImageLoaded );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnClanOfficerListResponse, ClanOfficerListResponse_t, m_ClanOfficerListResponse );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnFriendRichPresenceUpdate, FriendRichPresenceUpdate_t, m_FriendRichPresenceUpdate );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGameRichPresenceJoinRequested, GameRichPresenceJoinRequested_t, m_GameRichPresenceJoinRequested );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGameConnectedClanChatMsg, GameConnectedClanChatMsg_t, m_GameConnectedClanChatMsg );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGameConnectedChatJoin, GameConnectedChatJoin_t, m_GameConnectedChatJoin );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGameConnectedChatLeave, GameConnectedChatLeave_t, m_GameConnectedChatLeave );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnDownloadClanActivityCountsResult, DownloadClanActivityCountsResult_t, m_DownloadClanActivityCountsResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnJoinClanChatRoomCompletionResult, JoinClanChatRoomCompletionResult_t, m_JoinClanChatRoomCompletionResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGameConnectedFriendChatMsg, GameConnectedFriendChatMsg_t, m_GameConnectedFriendChatMsg );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnFriendsGetFollowerCount, FriendsGetFollowerCount_t, m_FriendsGetFollowerCount );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnFriendsIsFollowing, FriendsIsFollowing_t, m_FriendsIsFollowing );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnFriendsEnumerateFollowingList, FriendsEnumerateFollowingList_t, m_FriendsEnumerateFollowingList );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnSetPersonaNameResponse, SetPersonaNameResponse_t, m_SetPersonaNameResponse );
// server
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGSClientApprove, GSClientApprove_t, m_GSClientApprove );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGSClientDeny, GSClientDeny_t, m_GSClientDeny );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGSClientKick, GSClientKick_t, m_GSClientKick );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGSClientAchievementStatus, GSClientAchievementStatus_t, m_GSClientAchievementStatus );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGSPolicyResponse, GSPolicyResponse_t, m_GSPolicyResponse );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGSGameplayStats, GSGameplayStats_t, m_GSGameplayStats );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGSClientGroupStatus, GSClientGroupStatus_t, m_GSClientGroupStatus );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGSReputation, GSReputation_t, m_GSReputation );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnAssociateWithClanResult, AssociateWithClanResult_t, m_AssociateWithClanResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnComputeNewPlayerCompatibilityResult, ComputeNewPlayerCompatibilityResult_t, m_ComputeNewPlayerCompatibilityResult );
	
// server stats
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGSStatsReceived, GSStatsReceived_t, m_GSStatsReceived );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGSStatsStored, GSStatsStored_t, m_GSStatsStored );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGSStatsUnloaded, GSStatsUnloaded_t, m_GSStatsUnloaded );
// user	
	STEAM_CALLBACK( cSteamCallbacksHandler, OnSteamServersConnected, SteamServersConnected_t, m_SteamServersConnected );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnSteamServerConnectFailure, SteamServerConnectFailure_t, m_SteamServerConnectFailure );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnSteamServersDisconnected, SteamServersDisconnected_t, m_SteamServersDisconnected );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnClientGameServerDeny, ClientGameServerDeny_t, m_ClientGameServerDeny );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnIPCFailure, IPCFailure_t, m_IPCFailure );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnValidateAuthTicketResponse, ValidateAuthTicketResponse_t, m_ValidateAuthTicketResponse );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnMicroTxnAuthorizationResponse, MicroTxnAuthorizationResponse_t, m_MicroTxnAuthorizationResponse );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnEncryptedAppTicketResponse, EncryptedAppTicketResponse_t, m_EncryptedAppTicketResponse );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGetAuthSessionTicketResponse, GetAuthSessionTicketResponse_t, m_GetAuthSessionTicketResponse );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGameWebCallback, GameWebCallback_t, m_GameWebCallback );
// utils
	STEAM_CALLBACK( cSteamCallbacksHandler, OnIPCountry, IPCountry_t, m_IPCountry );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLowBatteryPower, LowBatteryPower_t, m_LowBatteryPower );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnSteamAPICallCompleted, SteamAPICallCompleted_t, m_SteamAPICallCompleted );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnSteamShutdown, SteamShutdown_t, m_SteamShutdown );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnCheckFileSignature, CheckFileSignature_t, m_CheckFileSignature );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGamepadTextInputDismissed, GamepadTextInputDismissed_t, m_GamepadTextInputDismissed );
// matchmaking
	STEAM_CALLBACK( cSteamCallbacksHandler, OnFavoritesListChanged, FavoritesListChanged_t, m_FavoritesListChanged );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyInvite, LobbyInvite_t, m_LobbyInvite );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyEnter, LobbyEnter_t, m_LobbyEnter );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyDataUpdate, LobbyDataUpdate_t, m_LobbyDataUpdate );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyChatUpdate, LobbyChatUpdate_t, m_LobbyChatUpdate );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyChatMsg, LobbyChatMsg_t, m_LobbyChatMsg );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyGameCreated, LobbyGameCreated_t, m_LobbyGameCreated );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyMatchList, LobbyMatchList_t, m_LobbyMatchList );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyKicked, LobbyKicked_t, m_LobbyKicked );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyCreated, LobbyCreated_t, m_LobbyCreated );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnPSNGameBootInviteResult, PSNGameBootInviteResult_t, m_PSNGameBootInviteResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnFavoritesListAccountsUpdated, FavoritesListAccountsUpdated_t, m_FavoritesListAccountsUpdated );
// userstats
	STEAM_CALLBACK( cSteamCallbacksHandler, OnUserStatsReceived, UserStatsReceived_t, m_UserStatsReceived );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnUserStatsStored, UserStatsStored_t, m_UserStatsStored );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnUserAchievementStored, UserAchievementStored_t, m_UserAchievementStored );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLeaderboardFindResult, LeaderboardFindResult_t, m_LeaderboardFindResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLeaderboardScoresDownloaded, LeaderboardScoresDownloaded_t, m_LeaderboardScoresDownloaded );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLeaderboardScoreUploaded, LeaderboardScoreUploaded_t, m_LeaderboardScoreUploaded );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnNumberOfCurrentPlayers, NumberOfCurrentPlayers_t, m_NumberOfCurrentPlayers );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnUserStatsUnloaded, UserStatsUnloaded_t, m_UserStatsUnloaded );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnUserAchievementIconFetched, UserAchievementIconFetched_t, m_UserAchievementIconFetched );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGlobalAchievementPercentagesReady, GlobalAchievementPercentagesReady_t, m_GlobalAchievementPercentagesReady );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLeaderboardUGCSet, LeaderboardUGCSet_t, m_LeaderboardUGCSet );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnGlobalStatsReceived, GlobalStatsReceived_t, m_GlobalStatsReceived );
// apps
	STEAM_CALLBACK( cSteamCallbacksHandler, OnDlcInstalled, DlcInstalled_t, m_DlcInstalled );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRegisterActivationCodeResponse, RegisterActivationCodeResponse_t, m_RegisterActivationCodeResponse );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnAppProofOfPurchaseKeyResponse, AppProofOfPurchaseKeyResponse_t, m_AppProofOfPurchaseKeyResponse );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnNewLaunchQueryParameters, NewLaunchQueryParameters_t, m_NewLaunchQueryParameters );
// networking
	STEAM_CALLBACK( cSteamCallbacksHandler, OnP2PSessionRequest, P2PSessionRequest_t, m_P2PSessionRequest );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnP2PSessionConnectFail, P2PSessionConnectFail_t, m_P2PSessionConnectFail );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnSocketStatusCallback, SocketStatusCallback_t, m_SocketStatusCallback );
// matchmaking servers
	STEAM_CALLBACK( cSteamCallbacksHandler, OnFavoritesListChanged_ms, FavoritesListChanged_t, m_FavoritesListChanged_ms );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyInvite_ms, LobbyInvite_t, m_LobbyInvite_ms );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyEnter_ms, LobbyEnter_t, m_LobbyEnter_ms );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyDataUpdate_ms, LobbyDataUpdate_t, m_LobbyDataUpdate_ms );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyChatUpdate_ms, LobbyChatUpdate_t, m_LobbyChatUpdate_ms );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyChatMsg_ms, LobbyChatMsg_t, m_LobbyChatMsg_ms );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyGameCreated_ms, LobbyGameCreated_t, m_LobbyGameCreated_ms );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyMatchList_ms, LobbyMatchList_t, m_LobbyMatchList_ms );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyKicked_ms, LobbyKicked_t, m_LobbyKicked_ms );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnLobbyCreated_ms, LobbyCreated_t, m_LobbyCreated_ms );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnPSNGameBootInviteResult_ms, PSNGameBootInviteResult_t, m_PSNGameBootInviteResult_ms );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnFavoritesListAccountsUpdated_ms, FavoritesListAccountsUpdated_t, m_FavoritesListAccountsUpdated_ms );
// remote storage
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageAppSyncedClient, RemoteStorageAppSyncedClient_t, m_RemoteStorageAppSyncedClient );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageAppSyncedServer, RemoteStorageAppSyncedServer_t, m_RemoteStorageAppSyncedServer );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageAppSyncProgress, RemoteStorageAppSyncProgress_t, m_RemoteStorageAppSyncProgress );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageAppSyncStatusCheck, RemoteStorageAppSyncStatusCheck_t, m_RemoteStorageAppSyncStatusCheck );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageConflictResolution, RemoteStorageConflictResolution_t, m_RemoteStorageConflictResolution );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageFileShareResult, RemoteStorageFileShareResult_t, m_RemoteStorageFileShareResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStoragePublishFileResult, RemoteStoragePublishFileResult_t, m_RemoteStoragePublishFileResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageDeletePublishedFileResult, RemoteStorageDeletePublishedFileResult_t, m_RemoteStorageDeletePublishedFileResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageEnumerateUserPublishedFilesResult, RemoteStorageEnumerateUserPublishedFilesResult_t, m_RemoteStorageEnumerateUserPublishedFilesResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageSubscribePublishedFileResult, RemoteStorageSubscribePublishedFileResult_t, m_RemoteStorageSubscribePublishedFileResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageEnumerateUserSubscribedFilesResult, RemoteStorageEnumerateUserSubscribedFilesResult_t, m_RemoteStorageEnumerateUserSubscribedFilesResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageUnsubscribePublishedFileResult, RemoteStorageUnsubscribePublishedFileResult_t, m_RemoteStorageUnsubscribePublishedFileResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageUpdatePublishedFileResult, RemoteStorageUpdatePublishedFileResult_t, m_RemoteStorageUpdatePublishedFileResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageDownloadUGCResult, RemoteStorageDownloadUGCResult_t, m_RemoteStorageDownloadUGCResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageGetPublishedFileDetailsResult, RemoteStorageGetPublishedFileDetailsResult_t, m_RemoteStorageGetPublishedFileDetailsResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageEnumerateWorkshopFilesResult, RemoteStorageEnumerateWorkshopFilesResult_t, m_RemoteStorageEnumerateWorkshopFilesResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageGetPublishedItemVoteDetailsResult, RemoteStorageGetPublishedItemVoteDetailsResult_t, m_RemoteStorageGetPublishedItemVoteDetailsResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStoragePublishedFileSubscribed, RemoteStoragePublishedFileSubscribed_t, m_RemoteStoragePublishedFileSubscribed );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStoragePublishedFileUnsubscribed, RemoteStoragePublishedFileUnsubscribed_t, m_RemoteStoragePublishedFileUnsubscribed );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStoragePublishedFileDeleted, RemoteStoragePublishedFileDeleted_t, m_RemoteStoragePublishedFileDeleted );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageUpdateUserPublishedItemVoteResult, RemoteStorageUpdateUserPublishedItemVoteResult_t, m_RemoteStorageUpdateUserPublishedItemVoteResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageUserVoteDetails, RemoteStorageUserVoteDetails_t, m_RemoteStorageUserVoteDetails );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageEnumerateUserSharedWorkshopFilesResult, RemoteStorageEnumerateUserSharedWorkshopFilesResult_t, m_RemoteStorageEnumerateUserSharedWorkshopFilesResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageSetUserPublishedFileActionResult, RemoteStorageSetUserPublishedFileActionResult_t, m_RemoteStorageSetUserPublishedFileActionResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStorageEnumeratePublishedFilesByUserActionResult, RemoteStorageEnumeratePublishedFilesByUserActionResult_t, m_RemoteStorageEnumeratePublishedFilesByUserActionResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStoragePublishFileProgress, RemoteStoragePublishFileProgress_t, m_RemoteStoragePublishFileProgress );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnRemoteStoragePublishedFileUpdated, RemoteStoragePublishedFileUpdated_t, m_RemoteStoragePublishedFileUpdated );
// screenshots
	STEAM_CALLBACK( cSteamCallbacksHandler, OnScreenshotReady, ScreenshotReady_t, m_ScreenshotReady );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnScreenshotRequested, ScreenshotRequested_t, m_ScreenshotRequested );	
// HTTP
	STEAM_CALLBACK( cSteamCallbacksHandler, OnHTTPRequestCompleted, HTTPRequestCompleted_t, m_HTTPRequestCompleted );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnHTTPRequestHeadersReceived, HTTPRequestHeadersReceived_t, m_HTTPRequestHeadersReceived );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnHTTPRequestDataReceived, HTTPRequestDataReceived_t, m_HTTPRequestDataReceived );
// unified messages
	STEAM_CALLBACK( cSteamCallbacksHandler, OnSteamUnifiedMessagesSendMethodResult, SteamUnifiedMessagesSendMethodResult_t, m_SteamUnifiedMessagesSendMethodResult );
// UGC
	STEAM_CALLBACK( cSteamCallbacksHandler, OnSteamUGCQueryCompleted, SteamUGCQueryCompleted_t, m_SteamUGCQueryCompleted );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnSteamUGCRequestUGCDetailsResult, SteamUGCRequestUGCDetailsResult_t, m_SteamUGCRequestUGCDetailsResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnCreateItemResult, CreateItemResult_t, m_CreateItemResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnSubmitItemUpdateResult, SubmitItemUpdateResult_t, m_SubmitItemUpdateResult );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnItemInstalled, ItemInstalled_t, m_ItemInstalled );
// applist
	STEAM_CALLBACK( cSteamCallbacksHandler, OnSteamAppInstalled, SteamAppInstalled_t, m_SteamAppInstalled );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnSteamAppUninstalled, SteamAppUninstalled_t, m_SteamAppUninstalled );
// music player
	STEAM_CALLBACK( cSteamCallbacksHandler, OnPlaybackStatusHasChanged, PlaybackStatusHasChanged_t, m_PlaybackStatusHasChanged );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnVolumeHasChanged, VolumeHasChanged_t, m_VolumeHasChanged );
// music player remote
	STEAM_CALLBACK( cSteamCallbacksHandler, OnMusicPlayerRemoteWillActivate, MusicPlayerRemoteWillActivate_t, m_MusicPlayerRemoteWillActivate );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnMusicPlayerRemoteWillDeactivate, MusicPlayerRemoteWillDeactivate_t, m_MusicPlayerRemoteWillDeactivate );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnMusicPlayerRemoteToFront, MusicPlayerRemoteToFront_t, m_MusicPlayerRemoteToFront );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnMusicPlayerWillQuit, MusicPlayerWillQuit_t, m_MusicPlayerWillQuit );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnMusicPlayerWantsPlay, MusicPlayerWantsPlay_t, m_MusicPlayerWantsPlay );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnMusicPlayerWantsPause, MusicPlayerWantsPause_t, m_MusicPlayerWantsPause );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnMusicPlayerWantsPlayPrevious, MusicPlayerWantsPlayPrevious_t, m_MusicPlayerWantsPlayPrevious );
    STEAM_CALLBACK( cSteamCallbacksHandler, OnMusicPlayerWantsPlayNext, MusicPlayerWantsPlayNext_t, m_MusicPlayerWantsPlayNext );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnMusicPlayerWantsShuffled, MusicPlayerWantsShuffled_t, m_MusicPlayerWantsShuffled );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnMusicPlayerWantsLooped, MusicPlayerWantsLooped_t, m_MusicPlayerWantsLooped );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnMusicPlayerWantsVolume, MusicPlayerWantsVolume_t, m_MusicPlayerWantsVolume );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnMusicPlayerSelectsQueueEntry, MusicPlayerSelectsQueueEntry_t, m_MusicPlayerSelectsQueueEntry );
	STEAM_CALLBACK( cSteamCallbacksHandler, OnMusicPlayerSelectsPlaylistEntry, MusicPlayerSelectsPlaylistEntry_t, m_MusicPlayerSelectsPlaylistEntry );
public:
    cSteamCallbacksHandler(cSteamCallbacks callbacks);
};

/*--------------------------------------------------------
Name:    CHTMLSurface
--------------------------------------------------------*/
struct cHTMLSurfaceCallbacksHandler
{
	tOnCloseBrowser OnCloseBrowser;
	tOnNeedsPaint OnNeedsPaint;
	tOnStartRequest OnStartRequest;
	tOnFinishedRequest OnFinishedRequest;
	tOnURLChanged OnURLChanged;
	tOnOpenLinkInNewTab OnOpenLinkInNewTab;
	tOnChangedTitle OnChangedTitle;
	tOnSearchResults OnSearchResults;
	tOnCanGoBackAndForward OnCanGoBackAndForward;
	tOnHorizontalScroll OnHorizontalScroll;
	tOnVerticalScroll OnVerticalScroll;
	tOnLinkAtPosition OnLinkAtPosition;
	tOnJSAlert OnJSAlert;
	tOnJSConfirm OnJSConfirm;
	tOnFileOpenDialog OnFileOpenDialog;
	tOnComboNeedsPaint OnComboNeedsPaint;
	tOnShowPopup OnShowPopup;
	tOnHidePopup OnHidePopup;
	tOnSizePopup OnSizePopup;
	tOnNewWindow OnNewWindow;
	tOnSetCursor OnSetCursor;
	tOnStatusText OnStatusText;
	tOnShowToolTip OnShowToolTip;
	tOnUpdateToolTip OnUpdateToolTip;
	tOnHideToolTip OnHideToolTip;
	tOnBrowserReady OnBrowserReady;
};

class CHTMLSurface 
{
public:
	CHTMLSurface( cHTMLSurfaceCallbacksHandler handler, const char* UserAgent, const char* UserCSS);
	~CHTMLSurface(){SteamHTMLSurface()->RemoveBrowser( Handle);};
	cHTMLSurfaceCallbacksHandler cb;
	HHTMLBrowser Handle;
private:
	STEAM_CALLBACK( CHTMLSurface, OnCloseBrowser, HTML_CloseBrowser_t, m_CloseBrowser );
	STEAM_CALLBACK( CHTMLSurface, OnNeedsPaint, HTML_NeedsPaint_t, m_NeedsPaint );
	STEAM_CALLBACK( CHTMLSurface, OnStartRequest, HTML_StartRequest_t, m_StartRequest );
	STEAM_CALLBACK( CHTMLSurface, OnFinishedRequest, HTML_FinishedRequest_t, m_FinishedRequest );
	STEAM_CALLBACK( CHTMLSurface, OnURLChanged, HTML_URLChanged_t, m_URLChanged );
	STEAM_CALLBACK( CHTMLSurface, OnOpenLinkInNewTab, HTML_OpenLinkInNewTab_t, m_OpenLinkInNewTab );
	STEAM_CALLBACK( CHTMLSurface, OnChangedTitle, HTML_ChangedTitle_t, m_ChangedTitle );
	STEAM_CALLBACK( CHTMLSurface, OnSearchResults, HTML_SearchResults_t, m_SearchResults );
	STEAM_CALLBACK( CHTMLSurface, OnCanGoBackAndForward, HTML_CanGoBackAndForward_t, m_CanGoBackAndForward );
	STEAM_CALLBACK( CHTMLSurface, OnHorizontalScroll, HTML_HorizontalScroll_t, m_HorizontalScroll );
	STEAM_CALLBACK( CHTMLSurface, OnVerticalScroll, HTML_VerticalScroll_t, m_VerticalScroll );
	STEAM_CALLBACK( CHTMLSurface, OnLinkAtPosition, HTML_LinkAtPosition_t, m_LinkAtPosition );
	STEAM_CALLBACK( CHTMLSurface, OnJSAlert, HTML_JSAlert_t, m_JSAlert );
	STEAM_CALLBACK( CHTMLSurface, OnJSConfirm, HTML_JSConfirm_t, m_JSConfirm );
	STEAM_CALLBACK( CHTMLSurface, OnFileOpenDialog, HTML_FileOpenDialog_t, m_FileOpenDialog );
	
	/*TODO
	STEAM_CALLBACK( CHTMLSurface, OnComboNeedsPaint, HTML_ComboNeedsPaint_t, m_ComboNeedsPaint );
	STEAM_CALLBACK( CHTMLSurface, OnShowPopup, HTML_ShowPopup_t, m_ShowPopup );
	STEAM_CALLBACK( CHTMLSurface, OnHidePopup, HTML_HidePopup_t, m_HidePopup );
	STEAM_CALLBACK( CHTMLSurface, OnSizePopup, HTML_SizePopup_t, m_SizePopup );
	*/

	STEAM_CALLBACK( CHTMLSurface, OnNewWindow, HTML_NewWindow_t, m_NewWindow );
	STEAM_CALLBACK( CHTMLSurface, OnSetCursor, HTML_SetCursor_t, m_SetCursor );
	STEAM_CALLBACK( CHTMLSurface, OnStatusText, HTML_StatusText_t, m_StatusText );
	STEAM_CALLBACK( CHTMLSurface, OnShowToolTip, HTML_ShowToolTip_t, m_ShowToolTip );
	STEAM_CALLBACK( CHTMLSurface, OnUpdateToolTip, HTML_UpdateToolTip_t, m_UpdateToolTip );
	STEAM_CALLBACK( CHTMLSurface, OnHideToolTip, HTML_HideToolTip_t, m_HideToolTip ); 

	void OnBrowserReady( HTML_BrowserReady_t *pBrowserReady, bool bIOFailure );
	CCallResult< CHTMLSurface, HTML_BrowserReady_t > m_SteamCallResultBrowserReady;	
};

typedef void (*tOnServerResponded)(HServerListRequest hReq, int iServer);
typedef void (*tOnServerFailedToRespond)(HServerListRequest hReq, int iServer);
typedef void (*tOnServerRefreshComplete)(HServerListRequest hReq, EMatchMakingServerResponse response);

/*--------------------------------------------------------
Name:    SteamMatchmakingServerListResponse
--------------------------------------------------------*/
class CSteamMatchmakingServerListResponse : public ISteamMatchmakingServerListResponse
{
private:
    tOnServerResponded OnServerRespondedCallback;
    tOnServerFailedToRespond OnServerFailedToRespondCallback;
    tOnServerRefreshComplete OnServerRefreshCompleteCallback;
public:
	CSteamMatchmakingServerListResponse(tOnServerResponded a,tOnServerFailedToRespond b,tOnServerRefreshComplete c);
	void ServerResponded( HServerListRequest hReq, int iServer );
	void ServerFailedToRespond( HServerListRequest hReq, int iServer );
	void RefreshComplete( HServerListRequest hReq, EMatchMakingServerResponse response );
};