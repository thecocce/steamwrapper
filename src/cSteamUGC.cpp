//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"

// Query UGC associated with a user. Creator app id or consumer app id must be valid and be set to the current rning app. Page should start at 1.
UGCQueryHandle_t SteamUGC_CreateQueryUserUGCRequest( AccountID_t AccountID, EUserUGCList ListType, EUGCMatchingUGCType MatchingUGCType, EUserUGCListSortOrder SortOrder, AppId_t CreatorAppID, AppId_t ConsumerAppID, uint32 Page ){return SteamUGC()->CreateQueryUserUGCRequest(AccountID, ListType, MatchingUGCType, SortOrder, CreatorAppID, ConsumerAppID, Page);};

// Query for all matching UGC. Creator app id or consumer app id must be valid and be set to the current rning app. Page should start at 1.
UGCQueryHandle_t SteamUGC_CreateQueryAllUGCRequest( EUGCQuery QueryType, EUGCMatchingUGCType MatchingeMatchingUGCTypeFileType, AppId_t CreatorAppID, AppId_t ConsumerAppID, uint32 Page ){return SteamUGC()->CreateQueryAllUGCRequest(QueryType, MatchingeMatchingUGCTypeFileType, CreatorAppID, ConsumerAppID, Page);};

// Send the query to Steam
SteamAPICall_t SteamUGC_SendQueryUGCRequest( UGCQueryHandle_t handle ){return SteamUGC()->SendQueryUGCRequest(handle);};

// Retrieve an individual result after receiving the callback for querying UGC
bool SteamUGC_GetQueryUGCResult( UGCQueryHandle_t handle, uint32 index, SteamUGCDetails_t *Details ){return SteamUGC()->GetQueryUGCResult(handle,index,Details);};

// Release the request to free up memory, after retrieving results
bool SteamUGC_ReleaseQueryUGCRequest( UGCQueryHandle_t handle ){return SteamUGC()->ReleaseQueryUGCRequest(handle);};

// Options to set for querying UGC
bool SteamUGC_AddRequiredTag( UGCQueryHandle_t handle, const char *TagName ){return SteamUGC()->AddRequiredTag(handle,TagName);};
bool SteamUGC_AddExcludedTag( UGCQueryHandle_t handle, const char *TagName ){return SteamUGC()->AddExcludedTag(handle,TagName);};
bool SteamUGC_SetReturnLongDescription( UGCQueryHandle_t handle, bool ReturnLongDescription ){return SteamUGC()->SetReturnLongDescription(handle,ReturnLongDescription);};
bool SteamUGC_SetReturnTotalOnly( UGCQueryHandle_t handle, bool ReturnTotalOnly ){return SteamUGC()->SetReturnTotalOnly(handle,ReturnTotalOnly);};
bool SteamUGC_SetAllowCachedResponse( UGCQueryHandle_t handle, uint32 MaxAgeSeconds ){return SteamUGC()->SetAllowCachedResponse(handle,MaxAgeSeconds);};

// Options only for querying user UGC
bool SteamUGC_SetCloudFileNameFilter( UGCQueryHandle_t handle, const char *MatchCloudFileName ){return SteamUGC()->SetCloudFileNameFilter(handle,MatchCloudFileName);};

// Options only for querying all UGC
bool SteamUGC_SetMatchAnyTag( UGCQueryHandle_t handle, bool MatchAnyTag ){return SteamUGC()->SetMatchAnyTag(handle,MatchAnyTag);};
bool SteamUGC_SetSearchText( UGCQueryHandle_t handle, const char *SearchText ){return SteamUGC()->SetSearchText(handle,SearchText);};
bool SteamUGC_SetRankedByTrendDays( UGCQueryHandle_t handle, uint32 Days ){return SteamUGC()->SetRankedByTrendDays(handle,Days);};

// Request full details for one piece of UGC
SteamAPICall_t SteamUGC_RequestUGCDetails( PublishedFileId_t PublishedFileID, uint32 MaxAgeSeconds ){return SteamUGC()->RequestUGCDetails(PublishedFileID,MaxAgeSeconds);};

// Steam Workshop Creator API
// create new item for this app with no content attached yet
SteamAPICall_t SteamUGC_CreateItem( AppId_t ConsumerAppId, EWorkshopFileType FileType ){return SteamUGC()->CreateItem(ConsumerAppId,FileType);}; 

// start an UGC item update. Set changed properties before commiting update with CommitItemUpdate()
UGCUpdateHandle_t SteamUGC_StartItemUpdate( AppId_t ConsumerAppId, PublishedFileId_t PublishedFileID ){return SteamUGC()->StartItemUpdate(ConsumerAppId,PublishedFileID);}; 

// change the title of an UGC item
bool SteamUGC_SetItemTitle( UGCUpdateHandle_t handle, const char *Title ){return SteamUGC()->SetItemTitle(handle,Title);}; 
// change the description of an UGC item
bool SteamUGC_SetItemDescription( UGCUpdateHandle_t handle, const char *Description ){return SteamUGC()->SetItemDescription(handle,Description);}; 
// change the visibility of an UGC item
bool SteamUGC_SetItemVisibility( UGCUpdateHandle_t handle, ERemoteStoragePublishedFileVisibility Visibility ){return SteamUGC()->SetItemVisibility(handle,Visibility);}; 
// change the tags of an UGC item
bool SteamUGC_SetItemTags( UGCUpdateHandle_t handle, const SteamParamStringArray_t *Tags ){return SteamUGC()->SetItemTags(handle,Tags);}; 
// update item content from this local folder
bool SteamUGC_SetItemContent( UGCUpdateHandle_t handle, const char *ContentFolder ){return SteamUGC()->SetItemContent(handle,ContentFolder);}; 
//  change preview image file for this item. PreviewFile points to local image file 
bool SteamUGC_SetItemPreview( UGCUpdateHandle_t handle, const char *PreviewFile ){return SteamUGC()->SetItemPreview(handle,PreviewFile);}; 
// commit update process started with StartItemUpdate()
SteamAPICall_t SteamUGC_SubmitItemUpdate( UGCUpdateHandle_t handle, const char *ChangeNote ){return SteamUGC()->SubmitItemUpdate(handle,ChangeNote);}; 
EItemUpdateStatus SteamUGC_GetItemUpdateProgress( UGCUpdateHandle_t handle, uint64 *BytesProcessed, uint64* BytesTotal ){return SteamUGC()->GetItemUpdateProgress(handle,BytesProcessed,BytesTotal);};

// Steam Workshop Consumer API
// subscript to this item, will be installed ASAP
SteamAPICall_t SteamUGC_SubscribeItem( PublishedFileId_t PublishedFileID ){return SteamUGC()->SubscribeItem(PublishedFileID);}; 
 // subscribe from this item, will be installed after game quits
SteamAPICall_t SteamUGC_UnsubscribeItem( PublishedFileId_t PublishedFileID ){return SteamUGC()->UnsubscribeItem(PublishedFileID);};
// number of subscribed items 
uint32 SteamUGC_GetNumSubscribedItems(){return SteamUGC()->GetNumSubscribedItems();}; 
// all subscribed item PublishFileIDs
uint32 SteamUGC_GetSubscribedItems( PublishedFileId_t* PublishedFileID, uint32 MaxEntries ){return SteamUGC()->GetSubscribedItems(PublishedFileID,MaxEntries);}; 

// Get info about the item on disk.  If you are supporting items published through the legacy RemoteStorage APIs then *LegacyItem will be set to true
// and Folder will contain the full path to the file rather than the containing folder.
// returns true if item is installed
/*TODO
bool SteamUGC_GetItemInstallInfo( PublishedFileId_t PublishedFileID, uint64 *SizeOnDisk, char *Folder, uint32 FolderSize, bool *LegacyItem ){return SteamUGC()->GetItemInstallInfo(PublishedFileID,SizeOnDisk,Folder,FolderSize,LegacyItem);}; 
bool SteamUGC_GetItemUpdateInfo( PublishedFileId_t PublishedFileID, bool *NeedsUpdate, bool *IsDownloading, uint64 *BytesDownloaded, uint64 *BytesTotal ){return SteamUGC()->GetItemUpdateInfo(PublishedFileID,NeedsUpdate,IsDownloading,BytesDownloaded,BytesTotal);};
*/