CXXFLAGS += -std=c++17
objects = BitConverter.o ByteBuffer.o PtMessagePackage.o NetStruct.o Message.o
objects += GamePlayerSvo.o GameRoomSvo.o GameServerData.o Event.o #thread_pool.o
objects += ServerListener.o Server.o #BitFloat.o #time.o
cppversion = -std=c++17
a.out:Source.o $(objects)
	g++ -o a.out Source.o $(objects) -lenet -lpthread
Source.o: Source.cpp
	g++ -c $(cppversion) Source.cpp
BitConverter.o:BitConverter.cpp BitConverter.h
	g++ -c $(cppversion) BitConverter.cpp
ByteBuffer.o:ByteBuffer.cpp ByteBuffer.h BitConverter.h
	g++ -c $(cppversion) ByteBuffer.cpp
PtMessagePackage.o:PtMessagePackage.cpp PtMessagePackage.h ByteBuffer.h
	g++ -c $(cppversion) PtMessagePackage.cpp
NetStruct.o:NetStruct.cpp NetStruct.h
	g++ -c $(cppversion) NetStruct.cpp
GamePlayerSvo.o:GamePlayerSvo.cpp GamePlayerSvo.h
	g++ -c $(cppversion) GamePlayerSvo.cpp
GameRoomSvo.o:GameRoomSvo.cpp GameRoomSvo.h
	g++ -c $(cppversion) GameRoomSvo.cpp
GameServerData.o:GameServerData.cpp GameServerData.h
	g++ -c $(cppversion) GameServerData.cpp
Message.o:Message.cpp Message.h
	g++ -c $(cppversion) Message.cpp
Event.o:Event.cpp Event.h
	g++ -c $(cppversion) Event.cpp
#thread_pool:thread_pool.cpp thread_pool.h
#	g++ -c $(cppversion) thread.cpp
#timer.o:timer.cpp timer.h
#	g++ -c $(cppversion) timer.cpp
#BitFloat.o:BitFloat.cpp BitFloat.h
#	g++ -c $(cppversion) BitFloat.cpp
ServerListener.o:ServerListener.cpp ServerListener.h
	g++ -c $(cppversion) ServerListener.cpp
Server.o:Server.cpp Server.h
	g++ -c $(cppversion) Server.cpp
.PHONY:clean
clean:
	-rm a.out Source.o $(objects)
