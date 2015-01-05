//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
#include "libMain.h"

////////////////////////////////////////////////////////////////////////////////////////////
// Session-less connection functions
//    automatically establishes NAT-traversing or Relay server connections

// Sends a P2P packet to the specified user
// UDP-like, unreliable and a max packet size of 1200 bytes
// the first packet send may be delayed as the NAT-traversal code runs
// if we can't get through to the user, an error will be posted via the callback P2PSessionConnectFail
// see EP2PSend enum above for the descriptions of the different ways of sending packets
//
// Channel is a routing number you can use to help route message to different systems 	- you'll have to call ReadP2PPacket() 
// with the same channel number in order to retrieve the data on the other end
// using different channels to talk to the same user will still use the same underlying p2p connection, saving on resources
bool SteamNetworking_SendP2PPacket( CSteamID steamIDRemote, const void *Data, uint32 cData, EP2PSend SendType, int Channel){return SteamNetworking()->SendP2PPacket(steamIDRemote,Data,cData,SendType,Channel);};

// returns true if any data is available for read, and the amount of data that will need to be read
bool SteamNetworking_IsP2PPacketAvailable( uint32 *MsgSize, int Channel){return SteamNetworking()->IsP2PPacketAvailable(MsgSize,Channel);};

// reads in a packet that has been sent from another user via SendP2PPacket()
// returns the size of the message and the steamID of the user who sent it in the last two parameters
// if the buffer passed in is too small, the message will be truncated
// this call is not blocking, and will return false if no data is available
bool SteamNetworking_ReadP2PPacket( void *Dest, uint32 cDest, uint32 *MsgSize, CSteamID *steamIDRemote, int Channel){return SteamNetworking()->ReadP2PPacket(Dest,cDest,MsgSize,steamIDRemote,Channel);};

// AcceptP2PSessionWithUser() should only be called in response to a P2PSessionRequest callback
// P2PSessionRequest_t will be posted if another user tries to send you a packet that you haven't talked to yet
// if you don't want to talk to the user, just ignore the request
// if the user continues to send you packets, another P2PSessionRequest will be posted periodically
// this may be called multiple times for a single user
// (if you've called SendP2PPacket() on the other user, this implicitly accepts the session request)
bool SteamNetworking_AcceptP2PSessionWithUser( CSteamID steamIDRemote ){return SteamNetworking()->AcceptP2PSessionWithUser(steamIDRemote);};

// call CloseP2PSessionWithUser() when you're done talking to a user, will free up resources under-the-hood
// if the remote user tries to send data to you again, another P2PSessionRequest_t callback will be posted
bool SteamNetworking_CloseP2PSessionWithUser( CSteamID steamIDRemote ){return SteamNetworking()->CloseP2PSessionWithUser(steamIDRemote);};

// call CloseP2PChannelWithUser() when you're done talking to a user on a specific channel. Once all channels
// open channels to a user have been closed, the open session to the user will be closed and new data from this
// user will trigger a P2PSessionRequest_t callback
bool SteamNetworking_CloseP2PChannelWithUser( CSteamID steamIDRemote, int Channel ){return SteamNetworking()->CloseP2PChannelWithUser(steamIDRemote,Channel);};

// fills out P2PSessionState_t structure with details about the underlying connection to the user
// should only needed for debugging purposes
// returns false if no connection exists to the specified user
bool SteamNetworking_GetP2PSessionState( CSteamID steamIDRemote, P2PSessionState_t *ConnectionState ){return SteamNetworking()->GetP2PSessionState(steamIDRemote,ConnectionState);};

// Allow P2P connections to fall back to being relayed through the Steam servers if a direct connection
// or NAT-traversal cannot be established. Only applies to connections created after setting this value,
// or to existing connections that need to automatically reconnect after this value is set.
//
// P2P packet relay is allowed by default
bool SteamNetworking_AllowP2PPacketRelay( bool Allow ){return SteamNetworking()->AllowP2PPacketRelay(Allow);};


////////////////////////////////////////////////////////////////////////////////////////////
// LISTEN / CONNECT style interface functions
//
// This is an older set of functions designed around the Berkeley TCP sockets model
// it's preferential that you use the above P2P functions, they're more robust
// and these older functions will be removed eventually
//
////////////////////////////////////////////////////////////////////////////////////////////


// creates a socket and listens others to connect
// will trigger a SocketStatusCallback_t callback on another client connecting
// VirtualP2PPort is the unique ID that the client will connect to, in case you have multiple ports
//		this can usually just be 0 unless you want multiple sets of connections
// IP is the local IP address to bind to
//		pass in 0 if you just want the default local IP
// Port is the port to use
//		pass in 0 if you don't want users to be able to connect via IP/Port, but expect to be always peer-to-peer connections only
SNetListenSocket_t SteamNetworking_CreateListenSocket( int VirtualP2PPort, uint32 IP, uint16 Port, bool AllowUseOfPacketRelay ){return SteamNetworking()->CreateListenSocket(VirtualP2PPort,IP,Port,AllowUseOfPacketRelay);};

// creates a socket and begin connection to a remote destination
// can connect via a known steamID (client or game server), or directly to an IP
// on success will trigger a SocketStatusCallback callback
// on failure or timeout will trigger a SocketStatusCallback callback with a failure code in SNetSocketState
SNetSocket_t SteamNetworking_CreateP2PConnectionSocket( CSteamID steamIDTarget, int VirtualPort, int TimeoutSec, bool AllowUseOfPacketRelay ){return SteamNetworking()->CreateP2PConnectionSocket(steamIDTarget,VirtualPort,TimeoutSec,AllowUseOfPacketRelay);};
SNetSocket_t SteamNetworking_CreateConnectionSocket( uint32 IP, uint16 Port, int TimeoutSec ){return SteamNetworking()->CreateConnectionSocket(IP,Port,TimeoutSec);};

// disconnects the connection to the socket, if any, and invalidates the handle
// any unread data on the socket will be thrown away
// if NotifyRemoteEnd is set, socket will not be completely destroyed until the remote end acknowledges the disconnect
bool SteamNetworking_DestroySocket( SNetSocket_t Socket, bool NotifyRemoteEnd ){return SteamNetworking()->DestroySocket(Socket,NotifyRemoteEnd);};
// destroying a listen socket will automatically kill all the regular sockets generated from it
bool SteamNetworking_DestroyListenSocket( SNetListenSocket_t Socket, bool NotifyRemoteEnd ){return SteamNetworking()->DestroyListenSocket(Socket,NotifyRemoteEnd);};

// sending data
// must be a handle to a connected socket
// data is all sent via UDP, and thus send sizes are limited to 1200 bytes; after this, many routers will start dropping packets
// use the reliable flag with caution; although the resend rate is pretty aggressive,
// it can still cause stalls in receiving data (like TCP)
bool SteamNetworking_SendDataOnSocket( SNetSocket_t Socket, void *Data, uint32 cData, bool Reliable ){return SteamNetworking()->SendDataOnSocket(Socket,Data,cData,Reliable);};

// receiving data
// returns false if there is no data remaining
// fills out *MsgSize with the size of the next message, in bytes
bool SteamNetworking_IsDataAvailableOnSocket( SNetSocket_t Socket, uint32 *MsgSize ){return SteamNetworking()->IsDataAvailableOnSocket(Socket,MsgSize);}; 

// fills in pubDest with the contents of the message
// messages are always complete, of the same size as was sent (i.e. packetized, not streaming)
// if *MsgSize < cDest, only partial data is written
// returns false if no data is available
bool SteamNetworking_RetrieveDataFromSocket( SNetSocket_t Socket, void *Dest, uint32 cDest, uint32 *MsgSize ){return SteamNetworking()->RetrieveDataFromSocket(Socket,Dest,cDest,MsgSize);}; 

// checks for data from any socket that has been connected off this listen socket
// returns false if there is no data remaining
// fills out *MsgSize with the size of the next message, in bytes
// fills out *Socket with the socket that data is available on
bool SteamNetworking_IsDataAvailable( SNetListenSocket_t ListenSocket, uint32 *MsgSize, SNetSocket_t *Socket ){return SteamNetworking()->IsDataAvailable(ListenSocket,MsgSize,Socket);};

// retrieves data from any socket that has been connected off this listen socket
// fills in Dest with the contents of the message
// messages are always complete, of the same size as was sent (i.e. packetized, not streaming)
// if *MsgSize < cDest, only partial data is written
// returns false if no data is available
// fills out *Socket with the socket that data is available on
bool SteamNetworking_RetrieveData( SNetListenSocket_t ListenSocket, void *Dest, uint32 cDest, uint32 *MsgSize, SNetSocket_t *Socket ){return SteamNetworking()->RetrieveData(ListenSocket,Dest,cDest,MsgSize,Socket);};

// returns information about the specified socket, filling out the contents of the pointers
bool SteamNetworking_GetSocketInfo( SNetSocket_t Socket, CSteamID *SteamIDRemote, int *SocketStatus, uint32 *IPRemote, uint16 *PortRemote ){return SteamNetworking()->GetSocketInfo(Socket,SteamIDRemote,SocketStatus,IPRemote,PortRemote);};

// returns which local port the listen socket is bound to
// *IP and *Port will be 0 if the socket is set to listen for P2P connections only
bool SteamNetworking_GetListenSocketInfo( SNetListenSocket_t ListenSocket, uint32 *IP, uint16 *Port ){return SteamNetworking()->GetListenSocketInfo(ListenSocket,IP,Port);};

// returns true to describe how the socket ended up connecting
ESNetSocketConnectionType SteamNetworking_GetSocketConnectionType( SNetSocket_t Socket ){return SteamNetworking()->GetSocketConnectionType(Socket);};

// max packet size, in bytes
int SteamNetworking_GetMaxPacketSize( SNetSocket_t Socket ){return SteamNetworking()->GetMaxPacketSize(Socket);};