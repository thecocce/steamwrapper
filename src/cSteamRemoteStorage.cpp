//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"

// NOTE
//
// Filenames are case-insensitive, and will be converted to lowercase automatically.
// So "foo.bar" and "Foo.bar" are the same file, and if you write "Foo.bar" then
// iterate the files, the filename returned will be "foo.bar".
//

// file operations
bool	SteamRemoteStorage_FileWrite( const char *File, const void *Data, int32 ñData ){return SteamRemoteStorage()->FileWrite(File,Data, ñData);};
int32	SteamRemoteStorage_FileRead( const char *File, void *Data, int32 ñDataToRead ){return SteamRemoteStorage()->FileRead(File, Data, ñDataToRead);};
bool	SteamRemoteStorage_FileForget( const char *File ){return SteamRemoteStorage()->FileForget(File);};
bool	SteamRemoteStorage_FileDelete( const char *File ){return SteamRemoteStorage()->FileDelete(File);};
SteamAPICall_t SteamRemoteStorage_FileShare( const char *File ){return SteamRemoteStorage()->FileShare(File);};
bool	SteamRemoteStorage_SetSyncPlatforms( const char *File, ERemoteStoragePlatform RemoteStoragePlatform ){return SteamRemoteStorage()->SetSyncPlatforms(File,RemoteStoragePlatform);};

// file operations that cause network IO
UGCFileWriteStreamHandle_t SteamRemoteStorage_FileWriteStreamOpen( const char *File ){return SteamRemoteStorage()->FileWriteStreamOpen(File);};
bool SteamRemoteStorage_FileWriteStreamWriteChunk( UGCFileWriteStreamHandle_t writeHandle, const void *Data, int32 ñData ){return SteamRemoteStorage()->FileWriteStreamWriteChunk(writeHandle,Data,ñData);};
bool SteamRemoteStorage_FileWriteStreamClose( UGCFileWriteStreamHandle_t writeHandle ){return SteamRemoteStorage()->FileWriteStreamClose(writeHandle);};
bool SteamRemoteStorage_FileWriteStreamCancel( UGCFileWriteStreamHandle_t writeHandle ){return SteamRemoteStorage()->FileWriteStreamCancel(writeHandle);};

// file information
bool	SteamRemoteStorage_FileExists( const char *File ){return SteamRemoteStorage()->FileExists(File);};
bool	SteamRemoteStorage_FilePersisted( const char *File ){return SteamRemoteStorage()->FilePersisted(File);};
int32	SteamRemoteStorage_GetFileSize( const char *File ){return SteamRemoteStorage()->GetFileSize(File);};
int64	SteamRemoteStorage_GetFileTimestamp( const char *File ){return SteamRemoteStorage()->GetFileTimestamp(File);};
ERemoteStoragePlatform SteamRemoteStorage_GetSyncPlatforms( const char *File ){return SteamRemoteStorage()->GetSyncPlatforms(File);};

// iteration
int32 SteamRemoteStorage_GetFileCount(){return SteamRemoteStorage()->GetFileCount();};
const char *SteamRemoteStorage_GetFileNameAndSize( int File, int32 *FileSizeInBytes ){return SteamRemoteStorage()->GetFileNameAndSize(File,FileSizeInBytes);};

// configuration management
bool SteamRemoteStorage_GetQuota( int32 *TotalBytes, int32 *AvailableBytes ){return SteamRemoteStorage()->GetQuota(TotalBytes,AvailableBytes);};
bool SteamRemoteStorage_IsCloudEnabledForAccount(){return SteamRemoteStorage()->IsCloudEnabledForAccount();};
bool SteamRemoteStorage_IsCloudEnabledForApp(){return SteamRemoteStorage()->IsCloudEnabledForApp();};
void SteamRemoteStorage_SetCloudEnabledForApp( bool Val ){return SteamRemoteStorage()->SetCloudEnabledForApp(Val);};

// user generated content

// Downloads a UGC file.  A priority value of 0 will download the file immediately,
// otherwise it will wait to download the file until all downloads with a lower priority
// value are completed.  Downloads with equal priority will occur simultaneously.
SteamAPICall_t SteamRemoteStorage_UGCDownload( UGCHandle_t Content, uint32 Priority ){return SteamRemoteStorage()->UGCDownload(Content,Priority);};

// Gets the amount of data downloaded so far for a piece of content. BytesExpected can be 0 if function returns false
// or if the transfer hasn't started yet, so be careful to check for that before dividing to get a percentage
bool SteamRemoteStorage_GetUGCDownloadProgress( UGCHandle_t Content, int32 *BytesDownloaded, int32 *BytesExpected ){return SteamRemoteStorage()->GetUGCDownloadProgress(Content,BytesDownloaded,BytesExpected);};

// Gets metadata for a file after it has been downloaded. This is the same metadata given in the RemoteStorageDownloadUGCResult_t call result
bool SteamRemoteStorage_GetUGCDetails( UGCHandle_t Content, AppId_t *AppID, char **Name, int32 *FileSizeInBytes, CSteamID *SteamIDOwner ){return SteamRemoteStorage()->GetUGCDetails(Content,AppID,Name,FileSizeInBytes,SteamIDOwner);};

// After download, gets the content of the file.  
// Small files can be read all at once by calling this function with an offset of 0 and ñDataToRead equal to the size of the file.
// Larger files can be read in chunks to reduce memory usage (since both sides of the IPC client and the game itself must allocate
// enough memory for each chunk).  Once the last byte is read, the file is implicitly closed and further calls to UGCRead will fail
// unless UGCDownload is called again.
// For especially large files (anything over 100MB) it is a requirement that the file is read in chunks.
int32 SteamRemoteStorage_UGCRead( UGCHandle_t Content, void *Data, int32 DataToRead, uint32 Offset, EUGCReadAction Action ){return SteamRemoteStorage()->UGCRead(Content,Data,DataToRead,Offset,Action);};

// Functions to iterate through UGC that has finished downloading but has not yet been read via UGCRead()
int32 SteamRemoteStorage_GetCachedUGCCount(){return SteamRemoteStorage()->GetCachedUGCCount();};
UGCHandle_t SteamRemoteStorage_GetCachedUGCHandle( int32 CachedContent ){return SteamRemoteStorage()->GetCachedUGCHandle(CachedContent);};

// publishing UGC
SteamAPICall_t SteamRemoteStorage_PublishWorkshopFile( const char *File, const char *PreviewFile, AppId_t ConsumerAppId, const char *Title, const char *Description, ERemoteStoragePublishedFileVisibility Visibility, SteamParamStringArray_t *Tags, EWorkshopFileType WorkshopFileType ){return SteamRemoteStorage()->PublishWorkshopFile(File, PreviewFile, ConsumerAppId, Title, Description, Visibility, Tags, WorkshopFileType);};
PublishedFileUpdateHandle_t SteamRemoteStorage_CreatePublishedFileUpdateRequest( PublishedFileId_t unPublishedFileId ){return SteamRemoteStorage()->CreatePublishedFileUpdateRequest(unPublishedFileId);};
bool SteamRemoteStorage_UpdatePublishedFileFile( PublishedFileUpdateHandle_t updateHandle, const char *File ){return SteamRemoteStorage()->UpdatePublishedFileFile(updateHandle,File);};
bool SteamRemoteStorage_UpdatePublishedFilePreviewFile( PublishedFileUpdateHandle_t updateHandle, const char *PreviewFile ){return SteamRemoteStorage()->UpdatePublishedFilePreviewFile(updateHandle,PreviewFile);};
bool SteamRemoteStorage_UpdatePublishedFileTitle( PublishedFileUpdateHandle_t updateHandle, const char *Title ){return SteamRemoteStorage()->UpdatePublishedFileTitle(updateHandle,Title);};
bool SteamRemoteStorage_UpdatePublishedFileDescription( PublishedFileUpdateHandle_t updateHandle, const char *Description ){return SteamRemoteStorage()->UpdatePublishedFileDescription(updateHandle,Description);};
bool SteamRemoteStorage_UpdatePublishedFileVisibility( PublishedFileUpdateHandle_t updateHandle, ERemoteStoragePublishedFileVisibility Visibility ){return SteamRemoteStorage()->UpdatePublishedFileVisibility(updateHandle,Visibility);};
bool SteamRemoteStorage_UpdatePublishedFileTags( PublishedFileUpdateHandle_t updateHandle, SteamParamStringArray_t *Tags ){return SteamRemoteStorage()->UpdatePublishedFileTags(updateHandle,Tags);};
SteamAPICall_t SteamRemoteStorage_CommitPublishedFileUpdate( PublishedFileUpdateHandle_t updateHandle ){return SteamRemoteStorage()->CommitPublishedFileUpdate(updateHandle);};
// Gets published file details for the given publishedfileid.  If MaxSecondsOld is greater than 0,
// cached data may be returned, depending on how long ago it was cached.  A value of 0 will force a refresh.
// A value of k_WorkshopForceLoadPublishedFileDetailsFromCache will use cached data if it exists, no matter how old it is.
SteamAPICall_t SteamRemoteStorage_GetPublishedFileDetails( PublishedFileId_t PublishedFileId, uint32 MaxSecondsOld ){return SteamRemoteStorage()->GetPublishedFileDetails(PublishedFileId,MaxSecondsOld);};
SteamAPICall_t SteamRemoteStorage_DeletePublishedFile( PublishedFileId_t PublishedFileId ){return SteamRemoteStorage()->DeletePublishedFile(PublishedFileId);};
// enumerate the files that the current user published with this app
SteamAPICall_t SteamRemoteStorage_EnumerateUserPublishedFiles( uint32 StartIndex ){return SteamRemoteStorage()->EnumerateUserPublishedFiles(StartIndex);};
SteamAPICall_t SteamRemoteStorage_SubscribePublishedFile( PublishedFileId_t PublishedFileId ){return SteamRemoteStorage()->SubscribePublishedFile(PublishedFileId);};
SteamAPICall_t SteamRemoteStorage_EnumerateUserSubscribedFiles( uint32 StartIndex ){return SteamRemoteStorage()->EnumerateUserSubscribedFiles(StartIndex);};
SteamAPICall_t SteamRemoteStorage_UnsubscribePublishedFile( PublishedFileId_t PublishedFileId ){return SteamRemoteStorage()->UnsubscribePublishedFile(PublishedFileId);};
bool SteamRemoteStorage_UpdatePublishedFileSetChangeDescription( PublishedFileUpdateHandle_t updateHandle, const char *ChangeDescription ){return SteamRemoteStorage()->UpdatePublishedFileSetChangeDescription(updateHandle,ChangeDescription);};
SteamAPICall_t SteamRemoteStorage_GetPublishedItemVoteDetails( PublishedFileId_t PublishedFileId ){return SteamRemoteStorage()->GetPublishedItemVoteDetails(PublishedFileId);};
SteamAPICall_t SteamRemoteStorage_UpdateUserPublishedItemVote( PublishedFileId_t PublishedFileId, bool VoteUp ){return SteamRemoteStorage()->UpdateUserPublishedItemVote(PublishedFileId,VoteUp);};
SteamAPICall_t SteamRemoteStorage_GetUserPublishedItemVoteDetails( PublishedFileId_t PublishedFileId ){return SteamRemoteStorage()->GetUserPublishedItemVoteDetails(PublishedFileId);};
SteamAPICall_t SteamRemoteStorage_EnumerateUserSharedWorkshopFiles( CSteamID steamId, uint32 StartIndex, SteamParamStringArray_t *RequiredTags, SteamParamStringArray_t *ExcludedTags ){return SteamRemoteStorage()->EnumerateUserSharedWorkshopFiles(steamId, StartIndex, RequiredTags, ExcludedTags);};
SteamAPICall_t SteamRemoteStorage_PublishVideo( EWorkshopVideoProvider VideoProvider, const char *VideoAccount, const char *VideoIdentifier, const char *PreviewFile, AppId_t ConsumerAppId, const char *Title, const char *Description, ERemoteStoragePublishedFileVisibility Visibility, SteamParamStringArray_t *Tags ){return SteamRemoteStorage()->PublishVideo(VideoProvider, VideoAccount, VideoIdentifier, PreviewFile, ConsumerAppId, Title, Description, Visibility, Tags);};
SteamAPICall_t SteamRemoteStorage_SetUserPublishedFileAction( PublishedFileId_t PublishedFileId, EWorkshopFileAction Action ){return SteamRemoteStorage()->SetUserPublishedFileAction(PublishedFileId,Action);};
SteamAPICall_t SteamRemoteStorage_EnumeratePublishedFilesByUserAction( EWorkshopFileAction Action, uint32 StartIndex ){return SteamRemoteStorage()->EnumeratePublishedFilesByUserAction(Action,StartIndex);};
// this method enumerates the public view of workshop files
SteamAPICall_t SteamRemoteStorage_EnumeratePublishedWorkshopFiles( EWorkshopEnumerationType EnumerationType, uint32 StartIndex, uint32 Count, uint32 Days, SteamParamStringArray_t *Tags, SteamParamStringArray_t *UserTags ){return SteamRemoteStorage()->EnumeratePublishedWorkshopFiles(EnumerationType, StartIndex, Count, Days, Tags, UserTags);};
SteamAPICall_t SteamRemoteStorage_UGCDownloadToLocation( UGCHandle_t Content, const char *Location, uint32 Priority ){return SteamRemoteStorage()->UGCDownloadToLocation(Content,Location,Priority);};