#include "Chatting.h"

void Chatting::ChatLoop(TCPManager& ClientSide, std::string UserName)
{
	//m_UserName = UserName;
	m_ClientLocal = &ClientSide;
	m_SendingThread = std::thread(&Chatting::Send, this);
	m_ListeningThread = std::thread(&Chatting::Receive, this);
	m_SendingThread.detach();
	m_ListeningThread.join();
}

void Chatting::Receive()
{
	while (m_RecievedMessage != "end")
	{
		if (m_ClientLocal->Receive(m_RecievedMessage))
		{
			std::cout << std::endl << m_RecievedMessage << std::endl;
			//system("pause");
		}
		else { m_Tools->Debug("Can't recieve message", RED); }
	}
}

void Chatting::Send()
{
	while (m_SentMessage != "end")
	{
		std::cout << "> ";
		std::getline(std::cin, m_SentMessage);
		//m_SentMessage = m_UserName + ":" + m_SentMessage;
		if (!m_ClientLocal->Send(m_SentMessage))
		{
			m_Tools->Debug("Can't send message", RED);
		}
		if (m_SentMessage != "end") { m_SentMessage.clear(); }
	}
}

Chatting::Chatting()
{
	m_Tools = new TTools;
	m_ClientLocal = nullptr;
}

void Chatting::CloseChat()
{
	delete m_Tools;
	m_ClientLocal = nullptr;
}