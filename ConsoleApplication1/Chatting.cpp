#include "Chatting.h"

void Chatting::ChatLoop(TCPManager& ClientSide)
{
	m_ServerLocal = &ClientSide;
	m_SendingThread = std::thread(&Chatting::Send, this);
	m_ListeningThread = std::thread(&Chatting::Receive, this);
	m_SendingThread.detach();
	m_ListeningThread.join();
}

void Chatting::Receive()
{
	while (m_RecievedMessage != "end")
	{

		if (m_ServerLocal->Receive(m_RecievedMessage) && m_RecievedMessage != "")
		{

			if (!m_ServerLocal->Send(m_RecievedMessage))
			{
				m_Tools->Debug("Can't relay the message", RED);
			}
			//else 
			//{
			//	m_Tools->LogNoPause("Received client Message");
			//}
			//std::cout << std::endl << "Received: " << m_RecievedMessage << std::endl;
		}
		else { m_Tools->Debug("Can't recieve message", RED); }
	}
}

void Chatting::Send()
{
	while (m_RecievedMessage != "end")
	{
		if (m_RecievedMessage != "")
		{
			if (!m_ServerLocal->Send(m_RecievedMessage))
			{
				m_Tools->Debug("Can't send message", RED);
			}
			if (m_RecievedMessage != "end") { m_RecievedMessage.clear(); }
		}
	}
}

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