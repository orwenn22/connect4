enginedirs = Engine/*.cpp \
		  	 Engine/States/*.cpp

all: server client Makefile
	
server: src_server/*.cpp src_common/*.cpp Makefile
	g++ -Ienet/include -Isrc_common \
		src_server/*.cpp src_common/*.cpp ./enet/build/libenet.a -o ./server

client: src_client/*.cpp src_common/*.cpp Makefile ${enginedirs}
	g++ -Ienet/include -Iraylib/src -Isrc_common -I. \
		src_client/*.cpp src_common/*.cpp ${enginedirs} ./enet/build/libenet.a ./raylib/src/libraylib.a -o ./client


clear:
	rm server
	rm client