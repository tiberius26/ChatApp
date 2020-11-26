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
	
	//m_SendingThread.detach(); //both needed even in multiclients
	//m_ListeningThread.join();
}

void Chatting::Receive(std::string Client)
{
	while (m_RecievedMessage != "end")
	{

		//std::cout << "hit" << std::endl;
		if (m_ServerLocal->Receive(m_RecievedMessage, Client))
		{
			m_SendMessage = m_RecievedMessage;
			m_RecievedMessage.clear();
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
}

//void Chatting::test()
//{
//	while (m_RecievedMessage != "end") { m_ServerLocal->Receive(m_RecievedMessage); std::cout << "me!"; }
//}

Chatting::Chatting()
{
	m_Tools = new TTools;
	m_ServerLocal = nullptr;
}

void Chatting::CloseChat()
{
	delete m_Tools;
	m_ServerLocal = nullptr;
}