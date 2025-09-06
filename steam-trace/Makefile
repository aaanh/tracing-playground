default: build run trace

build:
	gcc main.c -lm -finstrument-functions -g -o prime-sieve

trace:
	chmod +x ./trace.sh
	./trace.sh

# manually copy traces to current folder
# when OUTDIR is not set in trace.sh
copy:
	mkdir -p lttng-traces
	rsync -avPh ~/repos/tracing-playground/prime-sieve/traces/ ./lttng-traces

run:
	./prime-sieve