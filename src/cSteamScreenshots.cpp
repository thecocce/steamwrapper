//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"

// Writes a screenshot to the user's screenshot library given the raw image data, which must be in RGB format.
// The return value is a handle that is valid for the duration of the game process and can be used to apply tags.
ScreenshotHandle SteamScreenshots_WriteScreenshot( void *RGB, uint32 cRGB, int Width, int Height ){return SteamScreenshots()->WriteScreenshot(RGB,cRGB,Width,Height);};

// Adds a screenshot to the user's screenshot library from disk.  If a thumbnail is provided, it must be 200 pixels wide and the same aspect ratio
// as the screenshot, otherwise a thumbnail will be generated if the user uploads the screenshot.  The screenshots must be in either JPEG or TGA format.
// The return value is a handle that is valid for the duration of the game process and can be used to apply tags.
// JPEG, TGA, and PNG formats are supported.
ScreenshotHandle SteamScreenshots_AddScreenshotToLibrary( const char *Filename, const char *ThumbnailFilename, int Width, int Height ){return SteamScreenshots()->AddScreenshotToLibrary(Filename,ThumbnailFilename,Width,Height);};

// Causes the Steam overlay to take a screenshot.  If screenshots are being hooked by the game then a ScreenshotRequested callback is sent back to the game instead. 
void SteamScreenshots_TriggerScreenshot(){SteamScreenshots()->TriggerScreenshot();};

// Toggles whether the overlay handles screenshots when the user presses the screenshot hotkey, or the game handles them.  If the game is hooking screenshots,
// then the ScreenshotRequested_t callback will be sent if the user presses the hotkey, and the game is expected to call WriteScreenshot or AddScreenshotToLibrary
// in response.
void SteamScreenshots_HookScreenshots( bool Hook ){SteamScreenshots()->HookScreenshots(Hook);};

// Sets metadata about a screenshot's location (for example, the name of the map)
bool SteamScreenshots_SetLocation( ScreenshotHandle Screenshot, const char *Location ){return SteamScreenshots()->SetLocation(Screenshot, Location);};

// Tags a user as being visible in the screenshot
bool SteamScreenshots_TagUser( ScreenshotHandle Screenshot, CSteamID steamID ){return SteamScreenshots()->TagUser(Screenshot, steamID);};

// Tags a published file as being visible in the screenshot
bool SteamScreenshots_TagPublishedFile( ScreenshotHandle Screenshot, PublishedFileId_t PublishedFileID ){return SteamScreenshots()->TagPublishedFile(Screenshot, PublishedFileID);};