#!/usr/bin/python3
import socket, sys, threading
# Copied from https://gist.githubusercontent.com/owainlewis/3217710/raw/2bda03005314ab32961f59b5439b9ce95547bace/socket_chat.py
# Simple chat client that allows multiple connections via threads

PORT = 1337 # the port number to run our server on

__version__ = "0.0.1"

class ChatServer(threading.Thread):
    
    storeddata = ""
    
    helpmessage = """!help: A cubby hole is a small hiding place where one can hide things.
!help: We now define the cubby hole protocol that allows users to store
!help: one line messages on a server. 
!help: As the hole is really small, the server will only store one
!help: message at a time, but keeps and shares it across different
!help: connections. If a new message is put in the cubby hole, the
!help: old message is lost.
!help:
!help: The following commands should be supported:
!help:
!help: PUT <msg> Places a new message in the cubby hole. 
!help: GET       Takes the message out of the cubby hole and displays it.
!help: LOOK      Displays message without taking it out of the cubby hole.
!help: DROP      Takes the message out of the cubby hole without displaying it.
!help: HELP      Displays some help message.
!help: QUIT      Terminates the connection.
!help:
!help: Have Fun and play around!\n""" 

    
    def __init__(self, port, host='localhost'):
        threading.Thread.__init__(self)
        self.port = port
        self.host = host
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.users = {} # current connections
        
        try:
            self.server.bind((self.host, self.port))
        except socket.error:
            print('Bind failed %s' % (socket.error))
            sys.exit()

        self.server.listen(10)
        
    # Not currently used. Ensure sockets are closed on disconnect
    def exit(self):
        self.server.close()

    def run_thread(self, conn, addr):
        print('Client connected with ' + addr[0] + ':' + str(addr[1]))
        conn.sendall("!hello: welcome aboard\n")
        while True:
            data = conn.recv(1024).lower()
            if data.startswith('put '):
                datatobestored = data.split(" ")[1]
                self.storeddata = datatobestored
                conn.sendall("!PUT: %s"%self.storeddata)
            elif data.startswith('get'):
                if self.storeddata:
                    conn.sendall("!GET: %s"%self.storeddata)
                    self.storeddata= ""
            elif data.startswith('look'):
                if self.storeddata:
                    conn.sendall("!LOOK: %s"%self.storeddata)
            elif data.startswith('drop '):
                if self.storeddata:
                    self.storeddata= ""
            elif data.startswith('help'):
                conn.sendall(self.helpmessage)
            elif data.startswith('quit'):
                break
            elif data: 
                conn.sendall("ERROR: Invalid command. Please type help for HELP\n")
            elif not data: 
                break
            
        conn.close() # Close

    def run(self):
        print('Waiting for connections on port %s' % (self.port))
        # We need to run a loop and create a new thread for each connection
        while True:
            conn, addr = self.server.accept()
            threading.Thread(target=self.run_thread, args=(conn, addr)).start()

if __name__ == '__main__':
    server = ChatServer(PORT)
    # Run the chat server listening on PORT
    server.run()