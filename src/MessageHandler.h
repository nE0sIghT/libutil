// Copyright (c) 2005 - 2015 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Return To The Roots.
//
// Return To The Roots is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Return To The Roots is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Return To The Roots. If not, see <http://www.gnu.org/licenses/>.

#ifndef MessageHandler_h__
#define MessageHandler_h__

class Message;
class Socket;

typedef Message* (*CreateMsgFunction)(unsigned short);

class MessageHandler
{
    CreateMsgFunction createMsg;

public:
    MessageHandler(CreateMsgFunction createMsg): createMsg(createMsg) {}

    /// Sends that message. Returns number of bytes submitted (-1 for failure)
    static int send(Socket& sock, const Message& msg);
    /// Receives a message. Returns NULL on error, or if nothing is available
    /// Sets error if NULL returned: -1 = Fatal Error, 0 = socket busy, 1 = No msg available, 2 = incomplete, 3 = Header-Error, 4 = data incomplete
    /// If wait is true, this blocks until a message is received or timeout is reached
    Message* recv(Socket& sock, int& error, bool wait);
};


#endif // MessageHandler_h__