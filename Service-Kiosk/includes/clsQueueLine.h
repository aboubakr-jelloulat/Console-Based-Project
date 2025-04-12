#pragma once

#include <iostream>
#include <queue>
#include "stack"
#include "SystemDate.h"
#include "SystemDate.h"
using namespace std;

class clsQueueLine
{

private:
	short _TotalTickets = 0;
	short _AverageServeTime = 0; // Waiting	Time
	string _Prefix = "";

	class _clsTicket // Subclass
	{
	private:
		short _Number = 0;
		string _Prefix;
		string _TicketTime;
		short _WaitingClients = 0;
		short _AverageServeTime = 0;

	public:
		_clsTicket(string Prefix, short Number, short WaitingClients, short AverageServeTime)
		{
			_Number = Number; // number of this ticket
			_TicketTime = clsSystemDate::GetSystemDateTimeString();
			_Prefix = Prefix;
			_WaitingClients = WaitingClients;
			_AverageServeTime = AverageServeTime;
		}
		string Prefix()
		{
			return _Prefix;
		}
		short Number()
		{
			return _Number;
		}

		string FullNumber()
		{
			return _Prefix + to_string(_Number);
		}

		string TicketTime()
		{
			return _TicketTime;
		}

		short WaitingClients()
		{
			return _WaitingClients;
		}

		short ExpectedServeTime()
		{
			return _AverageServeTime * _WaitingClients;
		}

		void Print()
		{
			cout << "\n\t\t\t  _______________________\n";
			cout << "\n\t\t\t\t    " << FullNumber();
			cout << "\n\n\t\t\t    " << _TicketTime;
			cout << "\n\t\t\t    Wating Clients = " << _WaitingClients;
			cout << "\n\t\t\t      Serve Time In";
			cout << "\n\t\t\t       " << ExpectedServeTime() << " Minutes.";
			cout << "\n\t\t\t  _______________________\n";
		}
	};

public:
	queue<_clsTicket> QueueLine;

	clsQueueLine(string Prefix, short AverageServeTime)
	{
		_Prefix = Prefix;
		_TotalTickets = 0;
		_AverageServeTime = AverageServeTime;
	}

	void IssueTicket()
	{
		_TotalTickets++;
		_clsTicket Ticket(_Prefix, _TotalTickets, WaitingClients(), _AverageServeTime);
		QueueLine.push(Ticket);
	}

	int WaitingClients()
	{
		return QueueLine.size();
	}

	string WhoIsNext()
	{
		if (QueueLine.empty())
			return "No Clients Left.";
		else
			return QueueLine.front().FullNumber();
	}

	bool ServeNextClient()
	{
		if (QueueLine.empty())
			return false;
		return QueueLine.pop(), true;
	}

	short ServedClients()
	{
		return _TotalTickets - WaitingClients();
	}

	void PrintInfo()
	{
		cout << "\n\t\t\t _________________________\n";
		cout << "\n\t\t\t\tQueue Info";
		cout << "\n\t\t\t _________________________\n";
		cout << "\n\t\t\t    Prefix   = " << _Prefix;
		cout << "\n\t\t\t    Total Tickets   = " << _TotalTickets;
		cout << "\n\t\t\t    Served Clients  = " << ServedClients();
		cout << "\n\t\t\t    Wating Clients  = " << WaitingClients();
		;
		cout << "\n\t\t\t _________________________\n";
		cout << "\n";
	}

	void PrintTicketsLineRTL() // Right to left
	{

		if (QueueLine.empty())
			cout << "\n\t\tTickets: No Tickets.";
		else
			cout << "\n\t\tTickets: ";

		// we copy the queue in order not to lose the original
		queue<_clsTicket> TempQueueLine = QueueLine;

		while (!TempQueueLine.empty())
		{
			_clsTicket Ticket = TempQueueLine.front(); // copy the front

			cout << " " << Ticket.FullNumber() << " <-- ";

			TempQueueLine.pop();
		}
		cout << endl;
	}

	void PrintTicketsLineLTR() // Left to Right
	{
		if (QueueLine.empty())
			cout << "\n\t\tTickets: No Tickets.";
		else
			cout << "\n\t\tTickets: ";

		// we copy the queue in order not to lose the original
		queue<_clsTicket> TempQueueLine = QueueLine;
		stack<_clsTicket> TempStackLine;

		while (!TempQueueLine.empty())
		{
			TempStackLine.push(TempQueueLine.front());
			TempQueueLine.pop();
		} // copy the Queue element to stack

		while (!TempStackLine.empty())
		{
			_clsTicket Ticket = TempStackLine.top();

			cout << " " << Ticket.FullNumber() << " --> ";

			TempStackLine.pop();
		}
		cout << "\n";
	}

	void PrintAllTickets()
	{

		cout << "\n\n\t\t\t       ---Tickets---";

		if (QueueLine.empty())
			cout << "\n\n\t\t\t     ---No Tickets---\n";

		for (queue<_clsTicket> TempQueueLine = QueueLine; !TempQueueLine.empty(); TempQueueLine.front().Print(), TempQueueLine.pop())
			;
	}
};
