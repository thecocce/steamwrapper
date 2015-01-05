//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"

// Initializes a new HTTP request, returning a handle to use in further operations on it.  Requires
// the method (GET or POST) and the absolute URL for the request.  Only http requests (ie, not https) are
// currently supported, so this string must start with http:// or https:// and should look like http://store.steampowered.com/app/250/ 
// or such.
HTTPRequestHandle SteamHTTP_CreateHTTPRequest( EHTTPMethod HTTPRequestMethod, const char *AbsoluteURL ){return SteamHTTP()->CreateHTTPRequest(HTTPRequestMethod,AbsoluteURL);};

// Set a context value for the request, which will be returned in the HTTPRequestCompleted_t callback after
// sending the request.  This is just so the caller can easily keep track of which callbacks go with which request data.
bool SteamHTTP_SetHTTPRequestContextValue( HTTPRequestHandle Request, uint64 ContextValue ){return SteamHTTP()->SetHTTPRequestContextValue(Request,ContextValue);};

// Set a timeout in seconds for the HTTP request, must be called prior to sending the request.  Default
// timeout is 60 seconds if you don't call this.  Returns false if the handle is invalid, or the request
// has already been sent.
bool SteamHTTP_SetHTTPRequestNetworkActivityTimeout( HTTPRequestHandle Request, uint32 TimeoutSeconds ){return SteamHTTP()->SetHTTPRequestNetworkActivityTimeout(Request,TimeoutSeconds);};

// Set a request header value for the request, must be called prior to sending the request.  Will 
// return false if the handle is invalid or the request is already sent.
bool SteamHTTP_SetHTTPRequestHeaderValue( HTTPRequestHandle Request, const char *HeaderName, const char *HeaderValue ){return SteamHTTP()->SetHTTPRequestHeaderValue(Request,HeaderName,HeaderValue);};

// Set a GET or POST parameter value on the request, which is set will depend on the EHTTPMethod specified
// when creating the request.  Must be called prior to sending the request.  Will return false if the 
// handle is invalid or the request is already sent.
bool SteamHTTP_SetHTTPRequestGetOrPostParameter( HTTPRequestHandle Request, const char *ParamName, const char *ParamValue ){return SteamHTTP()->SetHTTPRequestGetOrPostParameter(Request,ParamName,ParamValue);};

// Sends the HTTP request, will return false on a bad handle, otherwise use SteamCallHandle to wait on
// asynchronous response via callback.
//
// Note: If the user is in offline mode in Steam, then this will add a only-if-cached cache-control 
// header and only do a local cache lookup rather than sending any actual remote request.
bool SteamHTTP_SendHTTPRequest( HTTPRequestHandle Request, SteamAPICall_t *CallHandle ){return SteamHTTP()->SendHTTPRequest(Request,CallHandle);};

// Sends the HTTP request, will return false on a bad handle, otherwise use SteamCallHandle to wait on
// asynchronous response via callback for completion, and listen for HTTPRequestHeadersReceived and 
// HTTPRequestDataReceived_t callbacks while streaming.
bool SteamHTTP_SendHTTPRequestAndStreamResponse( HTTPRequestHandle Request, SteamAPICall_t *CallHandle ){return SteamHTTP()->SendHTTPRequestAndStreamResponse(Request,CallHandle);};

// Defers a request you have sent, the actual HTTP client code may have many requests queued, and this will move
// the specified request to the tail of the queue.  Returns false on invalid handle, or if the request is not yet sent.
bool SteamHTTP_DeferHTTPRequest( HTTPRequestHandle Request ){return SteamHTTP()->DeferHTTPRequest(Request);};

// Prioritizes a request you have sent, the actual HTTP client code may have many requests queued, and this will move
// the specified request to the head of the queue.  Returns false on invalid handle, or if the request is not yet sent.
bool SteamHTTP_PrioritizeHTTPRequest( HTTPRequestHandle Request ){return SteamHTTP()->PrioritizeHTTPRequest(Request);};

// Checks if a response header is present in a HTTP response given a handle from HTTPRequestCompleted_t, also 
// returns the size of the header value if present so the caller and allocate a correctly sized buffer for
// GetHTTPResponseHeaderValue.
bool SteamHTTP_GetHTTPResponseHeaderSize( HTTPRequestHandle Request, const char *HeaderName, uint32 *ResponseHeaderSize ){return SteamHTTP()->GetHTTPResponseHeaderSize(Request,HeaderName,ResponseHeaderSize);};

// Gets header values from a HTTP response given a handle from HTTPRequestCompleted, will return false if the
// header is not present or if your buffer is too small to contain it's value.  You should first call 
// BGetHTTPResponseHeaderSize to check for the presence of the header and to find out the size buffer needed.
bool SteamHTTP_GetHTTPResponseHeaderValue( HTTPRequestHandle Request, const char *HeaderName, uint8 *HeaderValueBuffer, uint32 BufferSize ){return SteamHTTP()->GetHTTPResponseHeaderValue(Request,HeaderName,HeaderValueBuffer,BufferSize);};

// Gets the size of the body data from a HTTP response given a handle from HTTPRequestCompleted_t, will return false if the 
// handle is invalid.
bool SteamHTTP_GetHTTPResponseBodySize( HTTPRequestHandle Request, uint32 *BodySize ){return SteamHTTP()->GetHTTPResponseBodySize(Request,BodySize);};

// Gets the body data from a HTTP response given a handle from HTTPRequestCompleted, will return false if the 
// handle is invalid or is to a streaming response, or if the provided buffer is not the correct size.  Use GetHTTPResponseBodySize first to find out
// the correct buffer size to use.
bool SteamHTTP_GetHTTPResponseBodyData( HTTPRequestHandle Request, uint8 *BodyDataBuffer, uint32 BufferSize ){return SteamHTTP()->GetHTTPResponseBodyData(Request,BodyDataBuffer,BufferSize);};

// Gets the body data from a streaming HTTP response given a handle from HTTPRequestDataReceived_t. Will return false if the 
// handle is invalid or is to a non-streaming response (meaning it wasn't sent with SendHTTPRequestAndStreamResponse), or if the buffer size and offset 
// do not match the size and offset sent in HTTPRequestDataReceived.
bool SteamHTTP_GetHTTPStreamingResponseBodyData( HTTPRequestHandle Request, uint32 Offset, uint8 *BodyDataBuffer, uint32 BufferSize ){return SteamHTTP()->GetHTTPStreamingResponseBodyData(Request,Offset,BodyDataBuffer,BufferSize);};

// Releases an HTTP response handle, should always be called to free resources after receiving a HTTPRequestCompleted
// callback and finishing using the response.
bool SteamHTTP_ReleaseHTTPRequest( HTTPRequestHandle Request ){return SteamHTTP()->ReleaseHTTPRequest(Request);};

// Gets progress on downloading the body for the request.  This will be zero unless a response header has already been
// received which included a content-length field.  For responses that contain no content-length it will report
// zero for the duration of the request as the size is unknown until the connection closes.
bool SteamHTTP_GetHTTPDownloadProgressPct( HTTPRequestHandle Request, float *PercentOut ){return SteamHTTP()->GetHTTPDownloadProgressPct(Request,PercentOut);};

// Sets the body for an HTTP Post request.  Will fail and return false on a GET request, and will fail if POST params
// have already been set for the request.  Setting this raw body makes it the only contents for the post, the pchContentType
// parameter will set the content-type header for the request so the server may know how to interpret the body.
bool SteamHTTP_SetHTTPRequestRawPostBody( HTTPRequestHandle Request, const char *ContentType, uint8 *Body, uint32 BodyLen ){return SteamHTTP()->SetHTTPRequestRawPostBody(Request,ContentType,Body,BodyLen);};