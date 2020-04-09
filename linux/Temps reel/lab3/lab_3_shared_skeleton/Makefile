GCC=gcc
GNAT=gnatmake


shared: shared_2.adb shared_3.adb
	$(GCC) -c *.c
	$(GNAT) shared_2.adb  -lcap -largs lock.o jobs.o prefault.o
	$(GNAT) shared_3.adb  -lcap -largs lock.o jobs.o prefault.o
	/sbin/setcap cap_sys_nice=ep shared_2
	/sbin/setcap cap_sys_nice=ep shared_3

clean:
	/bin/rm -f *~ *.o *.ali shared_2 shared_3
