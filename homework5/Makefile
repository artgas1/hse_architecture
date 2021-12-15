all: start argsn args argsall

start: build
	echo "\nтест с аргументами по умолчанию"
	./war 
argsn: build
	echo "\nтест с неверным количеством  аргументов"
	./war -bsn 
args: build
	echo "\nтест с неверными аргументами"
	./war -bsn no -asn 32
argsall: build
	echo "\nтест с аргументами"
	./war -asn 444 -bsn 33 -asl 66 -bsl 25 -apn 2 -apl 5 -bpn 1
build:
	g++ -pthread -std=gnu++11 -o war war.cpp
