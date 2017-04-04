import socket

def Main():
    host = "127.0.0.1"
    port = 5000

    mySocket = socket.socket()
    mySocket.bind((host,port))

    mySocket.listen(1)
    conn, addr = mySocket.accept()
    print ("Connection from: " + str(addr))
    while True:
            data = conn.recv(1024).decode().replace("\n","")
            if not data:
                    break
            print ("from connected  user: " + str(data))

            if str(data) == "STATUS":
                conn.send(b"OK")

    conn.close()

if __name__ == '__main__':
    Main()
