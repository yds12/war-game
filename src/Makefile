# Makefile
# Author: Yuri David Santos
# Since: 28/08/2011
# Modified: 21/12/2011
# Version: 0.9

# Variables
Codes=game.cpp match.cpp warmap.cpp terrain.cpp mmatch.cpp smatch.cpp res.cpp options.cpp unitmodel.cpp unit.cpp natureobject.cpp team.cpp playercontroller.cpp humancontroller.cpp aicontroller.cpp
Objs=game.o match.o warmap.o terrain.o mmatch.o smatch.o res.o options.o unitmodel.o unit.o natureobject.o team.o playercontroller.o humancontroller.o aicontroller.o
Headers=match.h warmap.h terrain.h mmatch.h smatch.h res.h options.h unitmodel.h unit.h support.h natureobject.h team.h playercontroller.h humancontroller.h aicontroller.h
Libs=-lagl -lagl-graphics -lagl-motion -lagl-mapping -lagl-net

# Build the application
game: $(Objs) $(Headers)
	g++ -o game $(Objs) $(Libs)

# Build the objects
game.o: game.cpp
	g++ -c game.cpp

match.o: match.cpp match.h
	g++ -c match.cpp

warmap.o: warmap.cpp warmap.h
	g++ -c warmap.cpp

terrain.o: terrain.cpp terrain.h
	g++ -c terrain.cpp

mmatch.o: mmatch.cpp mmatch.h
	g++ -c mmatch.cpp

smatch.o: smatch.cpp smatch.h
	g++ -c smatch.cpp

res.o: res.cpp res.h
	g++ -c res.cpp

options.o: options.cpp options.h
	g++ -c options.cpp

unitmodel.o: unitmodel.cpp unitmodel.h
	g++ -c unitmodel.cpp

unit.o: unit.cpp unit.h
	g++ -c unit.cpp

natureobject.o: natureobject.cpp natureobject.h
	g++ -c natureobject.cpp

team.o: team.cpp team.h
	g++ -c team.cpp

playercontroller.o: playercontroller.cpp playercontroller.h
	g++ -c playercontroller.cpp

humancontroller.o: humancontroller.cpp humancontroller.h
	g++ -c humancontroller.cpp

aicontroller.o: aicontroller.cpp aicontroller.h
	g++ -c aicontroller.cpp

# Cleans the directories, removing executables and objects
clean:
	rm $(Objs) game
