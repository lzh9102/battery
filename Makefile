battery: battery.c config.h
	gcc -o battery -O3 -Wall battery.c
	strip battery

config.h: config.sh Makefile
	sh config.sh > config-tmp.h
	mv config-tmp.h config.h

clean:
	rm -f battery
	rm -f config.h
	rm -f config-tmp.h
