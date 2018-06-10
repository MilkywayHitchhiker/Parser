#include"stdafx.h"
#include"ServerConfig.h"
CServerConfig *CServerConfig::Config;


void CServerConfig::SetConfig (void)
{
	int Length = 11;

	parser.LoadFile ("_ChatServer.cnf");

	parser.SetArea ("NETWORK");
	/*
	parser.GetValue ("SERVER_NAME", SERVER_NAME, &Length);

	parser.GetValue ("BIND_IP", BIND_IP, &Length);
	parser.GetValue ("BIND_PORT", &BIND_PORT);

	parser.GetValue ("LOGIN_SERVER_IP", LOGIN_SERVER_IP, &Length);
	parser.GetValue ("LOGIN_SERVER_PORT", &LOGIN_SERVER_PORT);

	parser.GetValue ("MONITORING_SERVER_IP", MONITORING_SERVER_IP, &Length);
	parser.GetValue ("MONITORING_SERVER_PORT", &MONITORING_SERVER_PORT);


	parser.GetValue ("WORKER_THREAD", &WORKER_THREAD_NUM);


	parser.SetArea ("SYSTEM");
	parser.GetValue ("CLIENT_MAX", &CLIENT_MAX);

	parser.GetValue ("PACKET_CODE", (int *)&PACKET_CODE);
	parser.GetValue ("PACKET_KEY1", (int *)&PACKET_KEY1);
	parser.GetValue ("PACKET_KEY2", ( int * )&PACKET_KEY2);
	*/
}



/*
char SERVER_NAME[10];

char BIND_IP[19];
int BIND_PORT;

char LOGIN_SERVER_IP[19];
int LOGIN_SERVER_PORT;

char MONITOR_SERVER_IP[19];
int MONITOR_SERVER_PORT;


int WORKER_THREAD_NUM;

int CLIENT_MAX;
char PACKET_CODE;
char PACKET_KEY1;
char PACKET_KEY2;
*/