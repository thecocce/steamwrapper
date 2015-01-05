//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"

// Sends a service method (in binary serialized form) using the Steam Client.
// Returns a unified message handle (k_InvalidUnifiedMessageHandle if could not send the message).
ClientUnifiedMessageHandle SteamUnifiedMessages_SendMethod( const char *ServiceMethod, const void *RequestBuffer, uint32 RequestBufferSize, uint64 Context ){return SteamUnifiedMessages()->SendMethod(ServiceMethod,RequestBuffer,RequestBufferSize,Context);};

// Gets the size of the response and the EResult. Returns false if the response is not ready yet.
bool SteamUnifiedMessages_GetMethodResponseInfo( ClientUnifiedMessageHandle Handle, uint32 *ResponseSize, EResult *Result ){return SteamUnifiedMessages()->GetMethodResponseInfo(Handle,ResponseSize,Result);};

// Gets a response in binary serialized form (and optionally release the corresponding allocated memory).
bool SteamUnifiedMessages_GetMethodResponseData( ClientUnifiedMessageHandle Handle, void *ResponseBuffer, uint32 ResponseBufferSize, bool AutoRelease ){return SteamUnifiedMessages()->GetMethodResponseData(Handle,ResponseBuffer,ResponseBufferSize,AutoRelease);};

// Releases the message and its corresponding allocated memory.
bool SteamUnifiedMessages_ReleaseMethod( ClientUnifiedMessageHandle Handle ){return SteamUnifiedMessages()->ReleaseMethod(Handle);};

// Sends a service notification (in binary serialized form) using the Steam Client.
// Returns true if the notification was sent successfully.
bool SteamUnifiedMessages_SendNotification( const char *ServiceNotification, const void *NotificationBuffer, uint32 NotificationBufferSize ){return SteamUnifiedMessages()->SendNotification(ServiceNotification,NotificationBuffer,NotificationBufferSize);};