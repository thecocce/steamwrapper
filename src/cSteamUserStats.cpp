//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"

extern cSteamCallbacksHandler *CallbacksHandler;

// Ask the server to send down this user's data and achievements for this game
bool SteamUserStats_RequestCurrentStats(){return SteamUserStats()->RequestCurrentStats();};

// Data accessors
bool SteamUserStats_GetStatInt32( const char *Name, int32 *Data ){return SteamUserStats()->GetStat(Name,Data);};
bool SteamUserStats_GetStatFloat( const char *Name, float *Data ){return SteamUserStats()->GetStat(Name,Data);};

// Set / update data
bool SteamUserStats_SetStatInt32( const char *Name, int32 Data ){return SteamUserStats()->SetStat(Name,Data);};
bool SteamUserStats_SetStatFloat( const char *Name, float Data ){return SteamUserStats()->SetStat(Name,Data);};
bool SteamUserStats_UpdateAvgRateStat( const char *Name, float CountThisSession, double SessionLength ){return SteamUserStats()->UpdateAvgRateStat(Name,CountThisSession,SessionLength);};

// Achievement flag accessors
bool SteamUserStats_GetAchievement( const char *Name, bool *Achieved ){return SteamUserStats()->GetAchievement(Name,Achieved);};
bool SteamUserStats_SetAchievement( const char *Name ){return SteamUserStats()->SetAchievement(Name);};
bool SteamUserStats_ClearAchievement( const char *Name ){return SteamUserStats()->ClearAchievement(Name);};

// Get the achievement status, and the time it was unlocked if unlocked.
// If the return value is true, but the unlock time is zero, that means it was unlocked before Steam 
// began tracking achievement unlock times (December 2009). Time is seconds since January 1, 1970.
bool SteamUserStats_GetAchievementAndUnlockTime( const char *Name, bool *Achieved, uint32 *UnlockTime ){return SteamUserStats()->GetAchievementAndUnlockTime(Name,Achieved,UnlockTime);};

// Store the current data on the server, will get a callback when set
// And one callback for every new achievement
//
// If the callback has a result of k_EResultInvalidParam, one or more stats 
// uploaded has been rejected, either because they broke constraints
// or were out of date. In this case the server sends back updated values.
// The stats should be re-iterated to keep in sync.
bool SteamUserStats_StoreStats(){return SteamUserStats()->StoreStats();};

// Achievement / GroupAchievement metadata

// Gets the icon of the achievement, which is a handle to be used in SteamUtils-GetImageRGBA(), or 0 if none set. 
// A return value of 0 may indicate we are still fetching data, and you can wait for the UserAchievementIconFetched_t callback
// which will notify you when the bits are ready. If the callback still returns zero, then there is no image set for the
// specified achievement.
int SteamUserStats_GetAchievementIcon( const char *Name ){return SteamUserStats()->GetAchievementIcon(Name);};

// Get general attributes for an achievement. Accepts the following keys:
// - "name" and "desc" for retrieving the localized achievement name and description (returned in UTF8)
// - "hidden" for retrieving if an achievement is hidden (returns "0" when not hidden, "1" when hidden)
const char *SteamUserStats_GetAchievementDisplayAttribute( const char *Name, const char *Key ){return SteamUserStats()->GetAchievementDisplayAttribute(Name,Key);};

// Achievement progress - triggers an AchievementProgress callback, that is all.
// Calling this w/ N out of N progress will NOT set the achievement, the game must still do that.
bool SteamUserStats_IndicateAchievementProgress( const char *Name, uint32 CurProgress, uint32 MaxProgress ){return SteamUserStats()->IndicateAchievementProgress(Name,CurProgress,MaxProgress);};

// Used for iterating achievements. In general games should not need these functions because they should have a
// list of existing achievements compiled into them
uint32 SteamUserStats_GetNumAchievements(){return SteamUserStats()->GetNumAchievements();};
// Get achievement name iAchievement in [0,GetNumAchievements)
const char *SteamUserStats_GetAchievementName( uint32 Achievement ){return SteamUserStats()->GetAchievementName(Achievement);};

// Friends stats & achievements

// downloads stats for the user
// returns a UserStatsReceived_t received when completed
// if the other user has no stats, UserStatsReceived_t.m_eResult will be set to k_EResultFail
// these stats won't be auto-updated; you'll need to call RequestUserStats() again to refresh any data
SteamAPICall_t SteamUserStats_RequestUserStats( CSteamID steamIDUser ){return SteamUserStats()->RequestUserStats(steamIDUser);};

// requests stat information for a user, usable after a successful call to RequestUserStats()
bool SteamUserStats_GetUserStatInt32( CSteamID steamIDUser, const char *Name, int32 *Data ){return SteamUserStats()->GetUserStat(steamIDUser,Name, Data);};
bool SteamUserStats_GetUserStatFloat( CSteamID steamIDUser, const char *Name, float *Data ){return SteamUserStats()->GetUserStat(steamIDUser,Name, Data);};
bool SteamUserStats_GetUserAchievement( CSteamID steamIDUser, const char *Name, bool *Achieved ){return SteamUserStats()->GetUserAchievement(steamIDUser, Name, Achieved);};
// See notes for GetAchievementAndUnlockTime above
bool SteamUserStats_GetUserAchievementAndUnlockTime( CSteamID steamIDUser, const char *Name, bool *Achieved, uint32 *UnlockTime ){return SteamUserStats()->GetUserAchievementAndUnlockTime(steamIDUser, Name, Achieved, UnlockTime);};

// Reset stats 
bool SteamUserStats_ResetAllStats( bool AchievementsToo ){return SteamUserStats()->ResetAllStats(AchievementsToo);};

// Leaderboard functions

// asks the Steam back-end for a leaderboard by name, and will create it if it's not yet
// This call is asynchronous, with the result returned in LeaderboardFindResult_t
SteamAPICall_t SteamUserStats_FindOrCreateLeaderboard( const char *LeaderboardName, ELeaderboardSortMethod LeaderboardSortMethod, ELeaderboardDisplayType LeaderboardDisplayType ){
		LogToFile("SteamUserStats_FindOrCreateLeaderboard");
		SteamAPICall_t hSteamAPICall = SteamUserStats()->FindOrCreateLeaderboard(LeaderboardName,LeaderboardSortMethod,LeaderboardDisplayType);
		if (CallbacksHandler != nullptr)
			CallbacksHandler->m_SteamCallResultCreateLeaderboard.Set( hSteamAPICall, CallbacksHandler, &cSteamCallbacksHandler::OnFindLeaderboard );
		return hSteamAPICall;
};

// as above, but won't create the leaderboard if it's not found
// This call is asynchronous, with the result returned in LeaderboardFindResult_t
SteamAPICall_t SteamUserStats_FindLeaderboard( const char *LeaderboardName ){
	LogToFile("SteamUserStats_FindLeaderboard");
	SteamAPICall_t hSteamAPICall =  SteamUserStats()->FindLeaderboard(LeaderboardName);
	if (CallbacksHandler != nullptr)
			CallbacksHandler->m_SteamCallResultCreateLeaderboard.Set( hSteamAPICall, CallbacksHandler, &cSteamCallbacksHandler::OnFindLeaderboard );
		return hSteamAPICall;
};

// returns the name of a leaderboard
const char *SteamUserStats_GetLeaderboardName( SteamLeaderboard_t SteamLeaderboard ){return SteamUserStats()->GetLeaderboardName(SteamLeaderboard);};

// returns the total number of entries in a leaderboard, as of the last request
int SteamUserStats_GetLeaderboardEntryCount( SteamLeaderboard_t SteamLeaderboard ){return SteamUserStats()->GetLeaderboardEntryCount(SteamLeaderboard);};

// returns the sort method of the leaderboard
ELeaderboardSortMethod SteamUserStats_GetLeaderboardSortMethod( SteamLeaderboard_t SteamLeaderboard ){return SteamUserStats()->GetLeaderboardSortMethod(SteamLeaderboard);};

// returns the display type of the leaderboard
ELeaderboardDisplayType SteamUserStats_GetLeaderboardDisplayType( SteamLeaderboard_t SteamLeaderboard ){return SteamUserStats()->GetLeaderboardDisplayType(SteamLeaderboard);};

// Asks the Steam back-end for a set of rows in the leaderboard.
// This call is asynchronous, with the result returned in LeaderboardScoresDownloaded_t
// LeaderboardScoresDownloaded_t will contain a handle to pull the results from GetDownloadedLeaderboardEntries() (below)
// You can ask for more entries than exist, and it will return as many as do exist.
// k_ELeaderboardDataRequestGlobal requests rows in the leaderboard from the full table, with nRangeStart & nRangeEnd in the range [1, TotalEntries]
// k_ELeaderboardDataRequestGlobalAroundUser requests rows around the current user, RangeStart being negate
//   e.g. DownloadLeaderboardEntries( hLeaderboard, k_ELeaderboardDataRequestGlobalAroundUser, -3, 3 ) will return 7 rows, 3 before the user, 3 after
// k_ELeaderboardDataRequestFriends requests all the rows for friends of the current user 
SteamAPICall_t SteamUserStats_DownloadLeaderboardEntries( SteamLeaderboard_t SteamLeaderboard, ELeaderboardDataRequest LeaderboardDataRequest, int RangeStart, int RangeEnd ){return SteamUserStats()->DownloadLeaderboardEntries(SteamLeaderboard, LeaderboardDataRequest, RangeStart, RangeEnd );};
// as above, but downloads leaderboard entries for an arbitrary set of users - ELeaderboardDataRequest is k_ELeaderboardDataRequestUsers
// if a user doesn't have a leaderboard entry, they won't be included in the result
// a max of 100 users can be downloaded at a time, with only one outstanding call at a time
SteamAPICall_t SteamUserStats_DownloadLeaderboardEntriesForUsers( SteamLeaderboard_t SteamLeaderboard, CSteamID *Users, int cUsers ){return SteamUserStats()->DownloadLeaderboardEntriesForUsers(SteamLeaderboard,Users,cUsers);};

// Returns data about a single leaderboard entry
// use a for loop from 0 to LeaderboardScoresDownloaded_t-EntryCount to get all the downloaded entries
bool SteamUserStats_GetDownloadedLeaderboardEntry( SteamLeaderboardEntries_t SteamLeaderboardEntries, int index, LeaderboardEntry_t *LeaderboardEntry, int32 *Details, int DetailsMax ){return SteamUserStats()->GetDownloadedLeaderboardEntry(SteamLeaderboardEntries, index, LeaderboardEntry, Details, DetailsMax);};

// Uploads a user score to the Steam back-end.
// This call is asynchronous, with the result returned in LeaderboardScoreUploaded
// Details are extra game-defined information regarding how the user got that score
// pScoreDetails points to an array of int32's, cScoreDetailsCount is the number of int32's in the list
SteamAPICall_t SteamUserStats_UploadLeaderboardScore( SteamLeaderboard_t SteamLeaderboard, ELeaderboardUploadScoreMethod LeaderboardUploadScoreMethod, int32 Score, const int32 *ScoreDetails, int ScoreDetailsCount ){return SteamUserStats()->UploadLeaderboardScore(SteamLeaderboard, LeaderboardUploadScoreMethod, Score, ScoreDetails, ScoreDetailsCount);};

// Attaches a piece of user generated content the user's entry on a leaderboard.
// hContent is a handle to a piece of user generated content that was shared using ISteamUserRemoteStorage::FileShare().
// This call is asynchronous, with the result returned in LeaderboardUGCSet_t.
SteamAPICall_t SteamUserStats_AttachLeaderboardUGC( SteamLeaderboard_t SteamLeaderboard, UGCHandle_t UGC ){return SteamUserStats()->AttachLeaderboardUGC(SteamLeaderboard,UGC);};

// Retrieves the number of players currently playing your game (online + offline)
// This call is asynchronous, with the result returned in NumberOfCurrentPlayers
SteamAPICall_t SteamUserStats_GetNumberOfCurrentPlayers(){return SteamUserStats()->GetNumberOfCurrentPlayers();};

// Requests that Steam fetch data on the percentage of players who have received each achievement
// for the game globally.
// This call is asynchronous, with the result returned in GlobalAchievementPercentagesReady_t.
SteamAPICall_t SteamUserStats_RequestGlobalAchievementPercentages(){return SteamUserStats()->RequestGlobalAchievementPercentages();};

// Get the info on the most achieved achievement for the game, returns an iterator index you can use to fetch
// the next most achieved afterwards.  Will return -1 if there is no data on achievement 
// percentages (ie, you haven't called RequestGlobalAchievementPercentages and waited on the callback).
int SteamUserStats_GetMostAchievedAchievementInfo( char *Name, uint32 NameBufLen, float *Percent, bool *Achieved ){return SteamUserStats()->GetMostAchievedAchievementInfo(Name, NameBufLen, Percent, Achieved);};

// Get the info on the next most achieved achievement for the game. Call this after GetMostAchievedAchievementInfo or another
// GetNextMostAchievedAchievementInfo call passing the iterator from the previous call. Returns -1 after the last
// achievement has been iterated.
int SteamUserStats_GetNextMostAchievedAchievementInfo( int IteratorPrevious, char *Name, uint32 NameBufLen, float *Percent, bool *Achieved ){return SteamUserStats()->GetNextMostAchievedAchievementInfo(IteratorPrevious,Name,NameBufLen,Percent,Achieved);};

// Returns the percentage of users who have achieved the specified achievement.
bool SteamUserStats_GetAchievementAchievedPercent( const char *Name, float *Percent ){return SteamUserStats()->GetAchievementAchievedPercent(Name,Percent);};

// Requests global stats data, which is available for stats marked as "aggregated".
// This call is asynchronous, with the results returned in GlobalStatsReceived.
// nHistoryDays specifies how many days of day-by-day history to retrieve in addition
// to the overall totals. The limit is 60.
SteamAPICall_t SteamUserStats_RequestGlobalStats( int HistoryDays ){return SteamUserStats()->RequestGlobalStats(HistoryDays);};

// Gets the lifetime totals for an aggregated stat
bool SteamUserStats_GetGlobalStatInt64( const char *StatName, int64 *Data ){return SteamUserStats()->GetGlobalStat(StatName,Data);};
bool SteamUserStats_GetGlobalStatDouble( const char *StatName, double *Data ){return SteamUserStats()->GetGlobalStat(StatName,Data);};

// Gets history for an aggregated stat. Data will be filled with daily values, starting with today.
// So when called, Data[0] will be today, Data[1] will be yesterday, and Data[2] will be two days ago, 
// etc. cData is the size in bytes of the pubData buffer. Returns the number of 
// elements actually set.
int32 SteamUserStats_GetGlobalStatHistoryInt64( const char *StatName, int64 *Data, uint32 cData ){return SteamUserStats()->GetGlobalStatHistory(StatName,Data,cData);};
int32 SteamUserStats_GetGlobalStatHistoryDouble( const char *StatName, double *Data, uint32 cData ){return SteamUserStats()->GetGlobalStatHistory(StatName,Data,cData);};