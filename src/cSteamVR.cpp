//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"


namespace vr
{
//TODO	
//	IHmd *HMD;
//
//	void SteamVR_Init( int *peError ) { HMD=VR_Init((HmdError*)peError); }
//	void SteamVR_Shutdown( ) { VR_Shutdown(); };
//	bool SteamVR_IsHmdPresent() { return VR_IsHmdPresent(); };
//	const char *SteamVR_GetStringForHmdError( HmdError error ) { return VR_GetStringForHmdError( (HmdError)error ); };
//	// ------------------------------------
//	// Display Methods
//	// ------------------------------------
//
//	/** Size and position that the window needs to be on the VR display. */
//	void SteamVR_GetWindowBounds( int32* X, int32* Y, uint32* Width, uint32* Height ){HMD->GetWindowBounds(X,Y,Width,Height);};
//
//	/** Suggested size for the intermediate render target that the distortion pulls from. */
//	void SteamVR_GetRecommendedRenderTargetSize( uint32 *Width, uint32 *Height ){return HMD->GetRecommendedRenderTargetSize(Width,Height);};
//
//	/** Gets the viewport in the frame buffer to draw the output of the distortion into */
//	void SteamVR_GetEyeOutputViewport( Hmd_Eye Eye, uint32 *X, uint32 *Y, uint32 *Width, uint32 *Height ){return HMD->GetEyeOutputViewport(Eye, X, Y, Width, Height);};
//
//	/** The projection matrix for the specified eye */
//	HmdMatrix44_t SteamVR_GetProjectionMatrix( Hmd_Eye Eye, float NearZ, float FarZ, GraphicsAPIConvention ProjType ){return HMD->GetProjectionMatrix(Eye, NearZ, FarZ, ProjType);};
//
//	/** The components necessary to build your own projection matrix in case your
//	* application is doing something fancy like infinite Z */
//	void SteamVR_GetProjectionRaw( Hmd_Eye Eye, float *Left, float *Right, float *Top, float *Bottom ){HMD->GetProjectionRaw(Eye, Left, Right, Top, Bottom );};
//
//	/** Returns the result of the distortion function for the specified eye and input UVs. UVs go from 0,0 in 
//	* the upper left of that eye's viewport and 1,1 in the lower right of that eye's viewport. */
//	DistortionCoordinates_t SteamVR_ComputeDistortion( Hmd_Eye Eye, float U, float V ){return HMD->ComputeDistortion(Eye, U, V);};
//
//	/** Returns the transform from eye space to the head space. Eye space is the per-eye flavor of head
//	* space that provides stereo disparity. Instead of Model * View * Projection the sequence is Model * View * Eye^-1 * Projection. 
//	* Normally View and Eye^-1 will be multiplied together and treated as View in your application. 
//	*/
//	HmdMatrix34_t SteamVR_GetHeadFromEyePose( Hmd_Eye Eye ){return HMD->GetHeadFromEyePose(Eye);};
//
//	/** For use in simple VR apps, this method returns the concatenation of the 
//	* tracking pose and the eye matrix to get a full view matrix for each eye.
//	* This is ( GetEyeMatrix() ) * (GetWorldFromHeadPose() ^ -1 )  */
//	bool SteamVR_GetViewMatrix( float SecondsFromNow, HmdMatrix44_t *MatLeftView, HmdMatrix44_t *MatRightView, HmdTrackingResult *Result ){return HMD->GetViewMatrix(SecondsFromNow, MatLeftView, MatRightView, Result);};
//
//	/** [D3D9 Only]
//	* Returns the adapter index that the user should pass into CreateDevice to set up D3D9 in such
//	* a way that it can go full screen exclusive on the HMD. Returns -1 if there was an error.
//	*/
//	uint32 SteamVR_GetD3D9AdapterIndex(){return HMD->GetD3D9AdapterIndex();};
//
//	/** [D3D10/11 Only]
//	* Returns the adapter index and output index that the user should pass into EnumAdapters adn EnumOutputs 
//	* to create the device and swap chain in DX10 and DX11. If an error occurs both indices will be set to -1.
//	*/
//	void SteamVR_GetDXGIOutputInfo( int32 *AdapterIndex, int32 *AdapterOutputIndex ){ HMD->GetDXGIOutputInfo(AdapterIndex,AdapterOutputIndex);};
//
//	/** [Windows Only]
//	* Notifies the system that the VR output will appear in a particular window.
//	*/
//	void SteamVR_AttachToWindow( void *hWnd ){ HMD->AttachToWindow(hWnd);};
//
//	// ------------------------------------
//	// Tracking Methods
//	// ------------------------------------
//
//	/** The pose that the tracker thinks that the HMD will be in at the specified
//	* number of seconds into the future. Pass 0 to get the current state. 
//	*
//	* This is roughly analogous to the inverse of the view matrix in most applications, though 
//	* many games will need to do some additional rotation or translation on top of the rotation
//	* and translation provided by the head pose.
//	*
//	* If this function returns true the pose has been populated with a pose that can be used by the application.
//	* Check peResult for details about the pose, including messages that should be displayed to the user.
//	*/
//	bool SteamVR_GetTrackerFromHeadPose( float PredictedSecondsFromNow, HmdMatrix34_t *Pose, HmdTrackingResult *Result ){return HMD->GetTrackerFromHeadPose(PredictedSecondsFromNow,Pose,Result);};
//
//	/** Passes back the pose matrix from the last successful call to GetWorldFromHeadPose(). Returns true if that matrix is 
//	* valid (because there has been a previous successful pose.) */
//	bool SteamVR_GetLastTrackerFromHeadPose( HmdMatrix34_t *Pose ){return HMD->GetLastTrackerFromHeadPose(Pose);};
//
//	/** Returns true if the tracker for this HMD will drift the Yaw component of its pose over time regardless of
//	* actual head motion. This is true for gyro-based trackers with no ground truth. */
//	bool SteamVR_WillDriftInYaw(){return HMD->WillDriftInYaw();};
//
//	/** Sets the zero pose for the tracker coordinate system. After this call all WorldFromHead poses will be relative 
//	* to the pose whenever this was called. The new zero coordinate system will not change the fact that the Y axis is
//	* up in the real world, so the next pose returned from GetWorldFromHeadPose after a call to ZeroTracker may not be
//	* exactly an identity matrix. */
//	void SteamVR_ZeroTracker(){ HMD->ZeroTracker();};
//
//	/** Returns the zero pose for the tracker coordinate system. If the tracker has never had a valid pose, this
//	* will be an identity matrix. */
//	HmdMatrix34_t SteamVR_GetTrackerZeroPose(){return HMD->GetTrackerZeroPose();};
//
//	// ------------------------------------
//	// Administrative methods
//	// ------------------------------------
//
//	/** The ID of the driver this HMD uses as a UTF-8 string. Returns the length of the ID in bytes. If 
//	* the buffer is not large enough to fit the ID an empty string will be returned. In general, 128 bytes
//	* will be enough to fit any ID. */
//	uint32 SteamVR_GetDriverId( char *Buffer, uint32 BufferLen ){return HMD->GetDriverId(Buffer,BufferLen);};
//
//	/** The ID of this display within its driver this HMD uses as a UTF-8 string. Returns the length of the ID in bytes. If 
//	* the buffer is not large enough to fit the ID an empty string will be returned. In general, 128 bytes
//	* will be enough to fit any ID. */
//	uint32 SteamVR_GetDisplayId( char *Buffer, uint32 BufferLen ){return HMD->GetDisplayId(Buffer,BufferLen);};
}