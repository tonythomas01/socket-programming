#!/usr/bin/python3
import socket, sys, threading
# Copied from https://gist.githubusercontent.com/owainlewis/3217710/raw/2bda03005314ab32961f59b5439b9ce95547bace/socket_chat.py
# Simple chat client that allows multiple connections via threads

PORT = 9876 # the port number to run our server on

__version__ = "0.0.1"

class ChatServer(threading.Thread):
    
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
        storeddata = ""
        while True:
            data = conn.recv(1024).lower()
            if data.startswith('put '):
                print("PUT")
                datatobestored = data.split(" ")[1]
                storeddata = datatobestored
                conn.sendall("!PUT: %s"%storeddata)
            elif data.startswith('get'):
                print("GET")
                if storeddata:
                    conn.sendall("!GET: %s"%storeddata)
                    storeddata= ""
            elif data.startswith('look'):
                print("LOOK")
                if storeddata:
                    conn.sendall("!LOOK: %s"%storeddata)
            elif data.startswith('drop '):
                print("DROP")
                if storeddata:
                    storeddata= ""
            elif data.startswith('help '):
                print("HELP")
            elif data.startswith('quit '):
                print("QUIT")
                break
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