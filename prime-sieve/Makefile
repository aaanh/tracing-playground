default: build run trace copy

build:
	gcc main.c -lm -finstrument-functions -g -o prime-sieve

trace:
	chmod +x ./trace.sh
	./trace.sh

copy:
	mkdir -p lttng-traces
	sudo chmod 777 -R /root/lttng-traces
	sudo rsync -avPh /root/lttng-traces/ ./lttng-traces

run:
	./prime-sieve