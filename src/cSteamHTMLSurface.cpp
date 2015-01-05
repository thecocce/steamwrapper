//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"

bool SteamHTMLSurface_Init(){return SteamHTMLSurface()->Init();};
bool SteamHTMLSurface_Shutdown(){return SteamHTMLSurface()->Shutdown();};

using namespace std;




CHTMLSurface::CHTMLSurface( cHTMLSurfaceCallbacksHandler handler, const char* UserAgent, const char* UserCSS) :
	m_CloseBrowser( this, &CHTMLSurface::OnCloseBrowser ),
	m_NeedsPaint( this, &CHTMLSurface::OnNeedsPaint ),
	m_StartRequest( this, &CHTMLSurface::OnStartRequest ),
	m_FinishedRequest( this, &CHTMLSurface::OnFinishedRequest ),
	m_URLChanged ( this, &CHTMLSurface::OnURLChanged ),
	m_OpenLinkInNewTab ( this, &CHTMLSurface::OnOpenLinkInNewTab),
	m_ChangedTitle ( this, &CHTMLSurface::OnChangedTitle),
	m_SearchResults ( this, &CHTMLSurface::OnSearchResults ),
	m_CanGoBackAndForward ( this, &CHTMLSurface::OnCanGoBackAndForward ),
	m_HorizontalScroll ( this, &CHTMLSurface::OnHorizontalScroll ),
	m_VerticalScroll ( this, &CHTMLSurface::OnVerticalScroll ),
	m_LinkAtPosition ( this, &CHTMLSurface::OnLinkAtPosition ),
	m_JSAlert ( this, &CHTMLSurface::OnJSAlert ),
	m_JSConfirm ( this, &CHTMLSurface::OnJSConfirm ),
	m_FileOpenDialog ( this, &CHTMLSurface::OnFileOpenDialog ),
	m_ComboNeedsPaint ( this, &CHTMLSurface::OnComboNeedsPaint ),
	m_ShowPopup ( this, &CHTMLSurface::OnShowPopup ),
	m_HidePopup ( this, &CHTMLSurface::OnHidePopup ),
	m_SizePopup ( this, &CHTMLSurface::OnSizePopup ),
	m_NewWindow ( this, &CHTMLSurface::OnNewWindow ),
	m_SetCursor ( this, &CHTMLSurface::OnSetCursor ),
	m_StatusText ( this, &CHTMLSurface::OnStatusText ),
	m_ShowToolTip ( this, &CHTMLSurface::OnShowToolTip ),
	m_UpdateToolTip ( this, &CHTMLSurface::OnUpdateToolTip ),
	m_HideToolTip ( this, &CHTMLSurface::OnHideToolTip)
{
	Handle = INVALID_HTTMLBROWSER;
	SteamAPICall_t hSteamAPICall = SteamHTMLSurface()->CreateBrowser( UserAgent, UserCSS );
	m_SteamCallResultBrowserReady.Set( hSteamAPICall, this, &CHTMLSurface::OnBrowserReady );
	cb=handler;
}

//---------------------------------------------------------------------------------------------------- CALLBACKS
void CHTMLSurface::OnCloseBrowser( HTML_CloseBrowser_t *pParam  )
{
	if (cb.OnCloseBrowser!=nullptr){ cb.OnCloseBrowser(); };
}
void CHTMLSurface::OnNeedsPaint( HTML_NeedsPaint_t *pParam  )
{
	if (cb.OnNeedsPaint!=nullptr){ cb.OnNeedsPaint(pParam->pBGRA, pParam->unWide,pParam->unTall,pParam->unUpdateX,pParam->unUpdateY,pParam->unUpdateWide, pParam->unUpdateTall, pParam->unScrollX, pParam->unScrollY, pParam->flPageScale, pParam->unPageSerial); };
}
void CHTMLSurface::OnStartRequest( HTML_StartRequest_t *pParam )
{
	if (cb.OnStartRequest!=nullptr){ cb.OnStartRequest(pParam->pchURL, pParam->pchTarget, pParam->pchPostData, pParam->bIsRedirect); };
}
void CHTMLSurface::OnFinishedRequest( HTML_FinishedRequest_t *pParam )
{
	if (cb.OnFinishedRequest!=nullptr){ cb.OnFinishedRequest(pParam->pchURL,pParam->pchPageTitle); };
}
void CHTMLSurface::OnURLChanged(HTML_URLChanged_t *pParam)
{
	if (cb.OnURLChanged!=nullptr){ cb.OnURLChanged(pParam->pchURL,pParam->pchPostData,pParam->bIsRedirect,pParam->pchPageTitle,pParam->bNewNavigation ); };
}
void CHTMLSurface::OnOpenLinkInNewTab(HTML_OpenLinkInNewTab_t *pParam)
{
	if (cb.OnOpenLinkInNewTab!=nullptr){ cb.OnOpenLinkInNewTab(pParam->pchURL); };
}
void CHTMLSurface::OnChangedTitle(HTML_ChangedTitle_t *pParam)
{
	if (cb.OnChangedTitle!=nullptr){ cb.OnChangedTitle(pParam->pchTitle); };
}
void CHTMLSurface::OnSearchResults(HTML_SearchResults_t *pParam)
{
	if (cb.OnSearchResults!=nullptr){ cb.OnSearchResults(pParam->unResults,pParam->unCurrentMatch ); };
}
void CHTMLSurface::OnCanGoBackAndForward(HTML_CanGoBackAndForward_t *pParam)
{
	if (cb.OnCanGoBackAndForward!=nullptr){ cb.OnCanGoBackAndForward(pParam->bCanGoBack,pParam->bCanGoForward); };
}
void CHTMLSurface::OnHorizontalScroll(HTML_HorizontalScroll_t *pParam)
{
	if (cb.OnHorizontalScroll!=nullptr){ cb.OnHorizontalScroll(pParam->unScrollMax, pParam->unScrollCurrent, pParam->flPageScale, pParam->bVisible, pParam->unPageSize ); };
}
void CHTMLSurface::OnVerticalScroll(HTML_VerticalScroll_t *pParam)
{
	if (cb.OnVerticalScroll!=nullptr){ cb.OnVerticalScroll(pParam->unScrollMax, pParam->unScrollCurrent, pParam->flPageScale, pParam->bVisible, pParam->unPageSize ); };
}
void CHTMLSurface::OnLinkAtPosition(HTML_LinkAtPosition_t *pParam)
{
	if (cb.OnLinkAtPosition!=nullptr){ cb.OnLinkAtPosition(pParam->x , pParam->y , pParam->pchURL, pParam->bInput, pParam->bLiveLink ); };
}
void CHTMLSurface::OnJSAlert(HTML_JSAlert_t *pParam)
{
	if (cb.OnJSAlert!=nullptr){ cb.OnJSAlert(pParam->pchMessage); };
}
void CHTMLSurface::OnJSConfirm(HTML_JSConfirm_t *pParam)
{
	if (cb.OnJSConfirm!=nullptr){ cb.OnJSConfirm(pParam->pchMessage); };
}
void CHTMLSurface::OnFileOpenDialog(HTML_FileOpenDialog_t *pParam)
{
	if (cb.OnFileOpenDialog!=nullptr){ cb.OnFileOpenDialog(pParam->pchTitle,pParam->pchInitialFile ); };
}
void CHTMLSurface::OnComboNeedsPaint(HTML_ComboNeedsPaint_t *pParam)
{
	if (cb.OnComboNeedsPaint!=nullptr){ cb.OnComboNeedsPaint(pParam->pBGRA,pParam->unWide,pParam->unTall ); };
}
void CHTMLSurface::OnShowPopup(HTML_ShowPopup_t *pParam)
{
	if (cb.OnShowPopup!=nullptr){ cb.OnShowPopup(); };
}
void CHTMLSurface::OnHidePopup(HTML_HidePopup_t *pParam)
{
	if (cb.OnHidePopup!=nullptr){ cb.OnHidePopup(); };
}
void CHTMLSurface::OnSizePopup(HTML_SizePopup_t *pParam)
{
	if (cb.OnSizePopup!=nullptr){ cb.OnSizePopup(pParam->unX, pParam->unY, pParam->unWide, pParam->unTall); };
}
void CHTMLSurface::OnNewWindow(HTML_NewWindow_t *pParam)
{
	if (cb.OnNewWindow!=nullptr){ cb.OnNewWindow(pParam->pchURL, pParam->unX, pParam->unY, pParam->unWide, pParam->unTall); };
}
void CHTMLSurface::OnSetCursor(HTML_SetCursor_t *pParam)
{
	if (cb.OnSetCursor!=nullptr){ cb.OnSetCursor(pParam->eMouseCursor); };
}
void CHTMLSurface::OnStatusText(HTML_StatusText_t *pParam)
{
	if (cb.OnStatusText!=nullptr){ cb.OnStatusText(pParam->pchMsg); };
}
void CHTMLSurface::OnShowToolTip(HTML_ShowToolTip_t *pParam)
{
	if (cb.OnShowToolTip!=nullptr){ cb.OnShowToolTip(pParam->pchMsg); };
}
void CHTMLSurface::OnUpdateToolTip(HTML_UpdateToolTip_t *pParam)
{
	if (cb.OnUpdateToolTip!=nullptr){ cb.OnUpdateToolTip(pParam->pchMsg); };
}
void CHTMLSurface::OnHideToolTip(HTML_HideToolTip_t *pParam)
{
	if (cb.OnHideToolTip!=nullptr){ cb.OnHideToolTip(); };
}
void CHTMLSurface::OnBrowserReady( HTML_BrowserReady_t *pBrowserReady, bool IOFailure )
{
		if (cb.OnBrowserReady!=nullptr){cb.OnBrowserReady(IOFailure);}
		Handle=pBrowserReady->unBrowserHandle;
};


//---------------------------------------------------------------------------------------------------- EXPORTED FUNCTIONS
std::vector<CHTMLSurface*> HTMLSurfaces;

int SteamHTMLSurface_CreateBrowser(cHTMLSurfaceCallbacksHandler handler, const char* UserAgent, const char* UserCSS)
{
	HTMLSurfaces.push_back(new CHTMLSurface(handler,UserAgent,UserCSS));
	return HTMLSurfaces.size()-1;
};
void SteamHTMLSurface_LoadURL(int ID, const char *URL, const char *PostData){SteamHTMLSurface()->LoadURL( HTMLSurfaces[ID]->Handle, URL, PostData );};
void SteamHTMLSurface_Resize(int ID, uint32 Width, uint32 Height){SteamHTMLSurface()->SetSize( HTMLSurfaces[ID]->Handle,Width, Height);};
void SteamHTMLSurface_RemoveBrowser(int ID){HTMLSurfaces[ID]->~CHTMLSurface();};

// Mouse click and mouse movement commands
void SteamHTMLSurface_MouseUp(int ID, ISteamHTMLSurface::EHTMLMouseButton eMouseButton ){SteamHTMLSurface()->MouseUp(HTMLSurfaces[ID]->Handle, eMouseButton );};
void SteamHTMLSurface_MouseDown(int ID, ISteamHTMLSurface::EHTMLMouseButton eMouseButton ){SteamHTMLSurface()->MouseDown(HTMLSurfaces[ID]->Handle, eMouseButton );};
void SteamHTMLSurface_MouseDoubleClick(int ID, ISteamHTMLSurface::EHTMLMouseButton eMouseButton ){SteamHTMLSurface()->MouseDoubleClick(HTMLSurfaces[ID]->Handle, eMouseButton );};
// x and y are relative to the HTML bounds
void SteamHTMLSurface_MouseMove(int ID, int x, int y ){SteamHTMLSurface()->MouseMove(HTMLSurfaces[ID]->Handle, x,y );};
// Delta is pixels of scroll
void SteamHTMLSurface_MouseWheel(int ID, int32 Delta ){SteamHTMLSurface()->MouseWheel(HTMLSurfaces[ID]->Handle, Delta );};

// keyboard interactions, native keycode is the virtual key code value from your OS
void SteamHTMLSurface_KeyDown(int ID, uint32 nNativeKeyCode, ISteamHTMLSurface::EHTMLKeyModifiers eHTMLKeyModifiers ){SteamHTMLSurface()->KeyDown(HTMLSurfaces[ID]->Handle, nNativeKeyCode,eHTMLKeyModifiers );};
void SteamHTMLSurface_KeyUp(int ID, uint32 nNativeKeyCode, ISteamHTMLSurface::EHTMLKeyModifiers eHTMLKeyModifiers ){SteamHTMLSurface()->KeyUp(HTMLSurfaces[ID]->Handle, nNativeKeyCode,eHTMLKeyModifiers );};
// cUnicodeChar is the unicode character point for this keypress (and potentially multiple chars per press)
void SteamHTMLSurface_KeyChar(int ID, uint32 cUnicodeChar, ISteamHTMLSurface::EHTMLKeyModifiers eHTMLKeyModifiers ){SteamHTMLSurface()->KeyChar(HTMLSurfaces[ID]->Handle, cUnicodeChar,eHTMLKeyModifiers );};

// CALLBACKS
//
//  These set of functions are used as responses to callback requests
//
// You MUST call this in response to a HTML_StartRequest_t callback
//  Set bAllowed to true to allow this navigation, false to cancel it and stay 
// on the current page. You can use this feature to limit the valid pages
// allowed in your HTML surface.
void SteamHTMLSurface_AllowStartRequest( int ID, bool Allowed ) { SteamHTMLSurface()->AllowStartRequest( HTMLSurfaces[ID]->Handle, Allowed ); }; 
// You MUST call this in response to a HTML_JSAlert_t or HTML_JSConfirm_t callback
//  Set bResult to true for the OK option of a confirm, use false otherwise
void SteamHTMLSurface_JSDialogResponse( int ID, bool Result ) { SteamHTMLSurface()->JSDialogResponse( HTMLSurfaces[ID]->Handle, Result ); }; 
// You MUST call this in response to a HTML_FileOpenDialog_t callback
void SteamHTMLSurface_FileLoadDialogResponse( int ID, const char **SelectedFiles ) { SteamHTMLSurface()->FileLoadDialogResponse( HTMLSurfaces[ID]->Handle, SelectedFiles ); }; 

// Stop the load of the current html page
void SteamHTMLSurface_StopLoad( int ID ){SteamHTMLSurface()->StopLoad(HTMLSurfaces[ID]->Handle);};
// Reload (most likely from local cache) the current page
void SteamHTMLSurface_Reload( int ID ){SteamHTMLSurface()->Reload(HTMLSurfaces[ID]->Handle );};
// navigate back in the page history
void SteamHTMLSurface_GoBack( int ID ){SteamHTMLSurface()->GoBack(HTMLSurfaces[ID]->Handle);};
// navigate forward in the page history
void SteamHTMLSurface_GoForward( int ID ){SteamHTMLSurface()->GoForward(HTMLSurfaces[ID]->Handle);};

// add this header to any url requests from this browser
void SteamHTMLSurface_AddHeader( int ID, const char *Key, const char *Value ){SteamHTMLSurface()->AddHeader(HTMLSurfaces[ID]->Handle,Key,Value );};
// run this javascript script in the currently loaded page
void SteamHTMLSurface_ExecuteJavascript( int ID, const char *Script ){SteamHTMLSurface()->ExecuteJavascript(HTMLSurfaces[ID]->Handle,Script );};
	
// programmatically scroll this many pixels on the page
void SteamHTMLSurface_SetHorizontalScroll( int ID, uint32 AbsolutePixelScroll ){SteamHTMLSurface()->SetHorizontalScroll(HTMLSurfaces[ID]->Handle,AbsolutePixelScroll );};
void SteamHTMLSurface_SetVerticalScroll( int ID, uint32 AbsolutePixelScroll ){SteamHTMLSurface()->SetVerticalScroll(HTMLSurfaces[ID]->Handle,AbsolutePixelScroll );};

// tell the html control if it has key focus currently, controls showing the I-beam cursor in text controls amongst other things
void SteamHTMLSurface_SetKeyFocus( int ID, bool HasKeyFocus ){SteamHTMLSurface()->SetKeyFocus(HTMLSurfaces[ID]->Handle,HasKeyFocus );};

// open the current pages html code in the local editor of choice, used for debugging
void SteamHTMLSurface_ViewSource( int ID ){SteamHTMLSurface()->ViewSource(HTMLSurfaces[ID]->Handle);};
// copy the currently selected text on the html page to the local clipboard
void SteamHTMLSurface_CopyToClipboard( int ID ){SteamHTMLSurface()->CopyToClipboard(HTMLSurfaces[ID]->Handle);};
// paste from the local clipboard to the current html page
void SteamHTMLSurface_PasteFromClipboard( int ID ){SteamHTMLSurface()->PasteFromClipboard(HTMLSurfaces[ID]->Handle);};

// find this string in the browser, if bCurrentlyInFind is true then instead cycle to the next matching element
void SteamHTMLSurface_Find( int ID, const char *SearchStr, bool CurrentlyInFind, bool Reverse ){SteamHTMLSurface()->Find(HTMLSurfaces[ID]->Handle,SearchStr,CurrentlyInFind,Reverse );};
// cancel a currently running find
void SteamHTMLSurface_StopFind( int ID ){SteamHTMLSurface()->StopFind(HTMLSurfaces[ID]->Handle);};

// return details about the link at position x,y on the current page
void SteamHTMLSurface_GetLinkAtPosition(  int ID, int x, int y ){SteamHTMLSurface()->GetLinkAtPosition(HTMLSurfaces[ID]->Handle,x,y );};

// set a webcookie for the hostname in question
void SteamHTMLSurface_SetCookie( const char *Hostname, const char *Key, const char *Value, const char *Path, RTime32 Expires) {SteamHTMLSurface()->SetCookie(Hostname,Key,Value,Path,Expires);};

// Zoom the current page by flZoom ( from 0.0 to 4.0, so to zoom to 120% use 1.2 ), zooming around point X,Y in the page (use 0,0 if you don't care)
void SteamHTMLSurface_SetPageScaleFactor( int ID, float Zoom, int PointX, int PointY ){SteamHTMLSurface()->SetPageScaleFactor(HTMLSurfaces[ID]->Handle, Zoom,PointX,PointY);};	
