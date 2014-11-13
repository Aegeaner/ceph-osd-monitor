all: pool_mon rbd_demo

pool_mon:
	gcc pool_mon.c -lrados -o pool_mon --std=c99

helper.o:
	g++ -c helper.cc -lrados -lrbd -o helper.o

rbd_demo.o: 
	g++ -c rbd_demo.cc -o rbd_demo.o

rbd_demo: rbd_demo.o helper.o
	g++ rbd_demo.o helper.o -lrados -lrbd -o rbd_demo

clean:
	rm -rf *.o pool_mon rbd_demo
