comp:	main.o tablafrecuencia.o treeelement.o treenode.o
	g++ main.o tablafrecuencia.o treeelement.o treenode.o -o comp
main.o:	main.cpp tablafrecuencia.h treeelement.h treenode.h
	g++ -c main.cpp
tablafrecuencia.o:	tablafrecuencia.cpp
	g++ -c tablafrecuencia.cpp
treeelement.o:	treeelement.cpp
	g++ -c treeelement.cpp
treenode.o:	treenode.cpp treeelement.h
	g++ -c treenode.cpp
