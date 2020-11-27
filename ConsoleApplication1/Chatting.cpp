#include "Chatting.h"

void Chatting::ChatLoop(TCPManager& ClientSide)
{
	m_ServerLocal = &ClientSide;
	for (int i = 0; i < ClientSide.GetUserCount(); i++)
	{

		std::string User = "User" + std::to_string(i);
		if (m_SendingThreads.find(User) == m_SendingThreads.end() && m_ListeningThreads.find(User) == m_ListeningThreads.end()) 
		{
			m_SendingThreads[User] = std::thread(&Chatting::Send, this, User);
			m_ListeningThreads[User] = std::thread(&Chatting::Receive, this, User);
			m_SendingThreads[User].detach();
			m_ListeningThreads[User].detach();
		}
	}

	//std::string test;
	//m_SendingThread.detach(); //both needed even in multiclients
	//m_ListeningThread.join();
}

void Chatting::Receive(std::string Client)
{
	while (m_SendMessage != "end")
	{

		//std::cout << "hit" << std::endl;
		if (m_ServerLocal->Receive(m_RecievedMessage, Client))
		{
			m_SendMessage = m_RecievedMessage;
			m_RecievedMessage.clear();

			m_ChatLog += m_SendMessage + "\n";
			//if (!m_ServerLocal->Send(m_RecievedMessage))
			//{
			//	m_Tools->Debug("Can't relay the message", RED);
			//}
			//else 
			//{
			//m_Tools->LogNoPause("Received client Message");
			//}
			//std::cout << std::endl << "Received: " << m_RecievedMessage << std::endl;
		}
		//else { m_Tools->Debug("Can't recieve message", RED);}
	}
	m_IsChatOver = true;
	m_ChatLog += "################### \n";
	m_ChatLog += "End Of Conversation";
	//m_ServerLocal->TurnListeningOff();
}

void Chatting::Send(std::string Client)
{
	while (m_SendMessage != "end")
	{
		if (m_SendMessage != "")
		{
			if (!m_ServerLocal->Send(m_SendMessage, Client))
			{
				m_Tools->Debug("Can't relay message", RED);
			}
			//m_Tools->LogNoPause("Message Sent");
			if (m_RecievedMessage != "end") { m_SendMessage.clear(); }
		}
	}
	//std::string test;
	m_ServerLocal->Send(m_SendMessage, Client);
	//m_ServerLocal->TurnListeningOff();
}

//void Chatting::test()
//{
//	while (m_RecievedMessage != "end") { m_ServerLocal->Receive(m_RecievedMessage); std::cout << "me!"; }
//}

Chatting::Chatting()
{
	m_Tools = new TTools;
	m_ServerLocal = nullptr;
	m_IsChatOver = false;
}

void Chatting::CloseChat()
{
	delete m_Tools;
}
void Chatting::SaveLog(int LogCount)
{
	int LogCountLocal = LogCount;
	char SaveLocation[50];
	sprintf_s(SaveLocation, "Data/Logs/Log%d.ini", LogCountLocal);
	bool NoDublicateLog = false;
	while (NoDublicateLog == false)
	{
		std::fstream CheckFile(SaveLocation);
		if (!CheckFile)
		{
			NoDublicateLog = true;
		}
		else
		{
			LogCountLocal++;//makes sure that the save is unique
			sprintf_s(SaveLocation, "Data/Logs/Log%d.ini", LogCountLocal);
		}

	}
	std::ofstream Log(SaveLocation);//saves player stats:
	Log << m_ChatLog;
	Log.close();

	std::string OprionsPath = "Data/ServerOptions.ini";
	std::ofstream Options(OprionsPath);//saves player stats:
	Options << "Port=1234" << std::endl;
	Options << "LogCount=" << LogCountLocal << std::endl;
	Options.close();
}