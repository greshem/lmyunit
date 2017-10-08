//--------------------------------------------------------------------------------------------------------------------------------
#include "msocket.h"
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MSocket,MObject)

END_LMYUNIT
//................................................................................................................................
MSocket::MSocket(void)
{

}
//................................................................................................................................
MSocket::~MSocket()
{

}
//................................................................................................................................
int  MSocket::InstanceCommCondition(void)
{
#ifdef WINDOWSCODE
	WORD						Version;
	WSADATA						WsaData;

	Version = MAKEWORD(1,1);
	if ( ::WSAStartup(Version,&WsaData) != 0 )
	{
		return(ERROR_SYSTEM(::WSAGetLastError()));
	}

	return(1);
#else
	return(1);
#endif
}
//................................................................................................................................
void MSocket::ReleaseCommCondition(void)
{
#ifdef WINDOWSCODE
	::WSACleanup();
#else
#endif
}
//................................................................................................................................
int  MSocket::SetSocketSync(SOCKET InSocket)
{
#ifdef WINDOWSCODE

	register unsigned long						errorcode = 0;

	if ( ::ioctlsocket(InSocket,FIONBIO,&errorcode) == SOCKET_ERROR )
	{
		return(ERROR_SYSTEM(::WSAGetLastError()));
	}
	else
	{
		return(1);
	}

#else
	fcntl( InSocket, F_SETFL, O_SYNC);
	return(1);
#endif
}
//................................................................................................................................
int  MSocket::SetSocketAsync(SOCKET InSocket)
{

#ifdef WINDOWSCODE

	register unsigned long						errorcode = 1;

	if ( ::ioctlsocket(InSocket,FIONBIO,&errorcode) == SOCKET_ERROR )
	{
		return(ERROR_SYSTEM(::WSAGetLastError()));
	}
	else
	{
		return(1);
	}

#else
	fcntl( InSocket, F_SETFL, O_NONBLOCK);
	return(1);
#endif
}
//--------------------------------------------------------------------------------------------------------------------------------
