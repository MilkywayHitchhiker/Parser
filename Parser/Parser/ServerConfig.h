#pragma once
#include <Windows.h>
#include "Parser.h"
class CServerConfig
{
private :
	CServerConfig (void)
	{
		SetConfig ();
	}

	~CServerConfig ()
	{

	}


	void SetConfig (void);


	static CServerConfig *Config;
	Parser parser;
public :

	static void Initialize (void)
	{
		if ( Config == NULL )
		{
			Config = new CServerConfig ();
		}
		return;
	}

	char SERVER_NAME[11];

	char BIND_IP[11];
	int BIND_PORT;

	char LOGIN_SERVER_IP[11];
	int LOGIN_SERVER_PORT;

	char MONITORING_SERVER_IP[11];
	int MONITORING_SERVER_PORT;


	int WORKER_THREAD_NUM;

	int CLIENT_MAX;
	char PACKET_CODE;
	char PACKET_KEY1;
	char PACKET_KEY2;
};