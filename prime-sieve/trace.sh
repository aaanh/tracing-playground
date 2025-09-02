#!/usr/bin/env bash
set -euo pipefail

# --- By default, use the LTTng libs assuming
# they've already been correctly added to PATH
LIBC_WRAPPER="liblttng-ust-libc-wrapper.so"
CYG_PROFILE="liblttng-ust-cyg-profile.so"
FORK_WRAP="liblttng-ust-fork.so"

## --- UNCOMMENT AND USE THESE ABSOLUTE PATHS IF NEEDED ---
## if there are errors complaining unable to load the shared objects 
# LIBC_WRAPPER="/usr/local/lib/liblttng-ust-libc-wrapper.so"
# CYG_PROFILE="/usr/local/lib/liblttng-ust-cyg-profile.so"
# FORK_WRAP="/usr/local/lib/liblttng-ust-fork.so"


SESSION="prime-sieve-$(date +%Y%m%d-%H%M%S)"
OUTDIR="${PWD}/traces/${SESSION}"

# Ensure per-user session daemon is running
lttng-sessiond --daemonize 2>/dev/null || true

# Create a UST session that writes locally
lttng create "${SESSION}" --output="${OUTDIR}"

# Enable all UST events and add useful context
lttng enable-event -u -a
lttng add-context -u -t vtid -t procname -t vpid -t ip

lttng start

# Preload UST helper libs for richer symbols/hooks
export LD_PRELOAD="${CYG_PROFILE}:${FORK_WRAP}:${LIBC_WRAPPER}"

# (Optional) avoid long waits if no session present
export LTTNG_UST_REGISTER_TIMEOUT=0

./prime-sieve

lttng stop
lttng destroy

echo "Trace written to: ${OUTDIR}"
