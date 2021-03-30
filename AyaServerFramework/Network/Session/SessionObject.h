#pragma once

#include "../Socket/AyaSocket.h"
#include "../Socket/AyaUdpSocket.h"
#include "../../Core/Overlapped/OverlappedIOManager.h"
#include <queue>

namespace AYA
{
	class Accepter;

	// ����, Overlapped Data�� ������ ����.  
	// ���� LPOverlapped ���ڿ� �̰� ����. 
	// ������ �־�� �ϴ� �� : Accpet Async Handler, Send Aysnc Handler, Recv Async Handler;
	class SessionObject
	{
	public:
		SessionObject(int session_index);
		virtual ~SessionObject();

	public:
		virtual void OnConnect(const HANDLE& connection_thread_handle);
		virtual void OnDisConnect();
		virtual void OnRecieve();
		virtual void OnRecieveFrom();
		virtual void OnSendComplete();

		bool Send(Buffer& buffer);
		bool SendTo(Buffer& buffer);
	public:
		inline OverlappedData* GetAcceptOverlappedData() { return m_acceept_overlapped_data.get(); }
		inline const int GetSessionIndex() const { return m_session_index; }
		inline Socket& GetSocket () { return m_socket; }
		inline UdpSocket& GetUdpSocket() { return m_udp_socket; }

		inline bool IsConnected() { return m_is_connected; }
	private:
		void InitOverlappedIOData();
		void ReleaseOverlappedIOData();
		bool SendIo();
		
	private:
		// overlapped io data
		OverlappedDataPointer m_acceept_overlapped_data;
		OverlappedDataPointer m_recieve_overlapped_data;
		std::queue<OverlappedDataPointer> m_send_queue;
		std::mutex m_send_queue_lock;

	private:
		// udp io data 
		OverlappedDataPointer m_udp_recieve_overlapped_data;
	private:
		bool m_is_connected;
		int m_session_index;
		Socket m_socket;
		UdpSocket m_udp_socket;
	};
}
