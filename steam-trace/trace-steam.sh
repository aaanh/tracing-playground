#!/bin/bash

# trace-steam.sh
# Run Steam under LTTng with kernel + UST tracing, libc wrapper, and filters

SESSION_NAME="steam-$(date +%Y%m%d-%H%M%S)"
APP_PATH="$HOME/.local/share/Steam/steam.sh"   # adjust path if needed

# Paths to LTTng UST wrappers (verify with ldconfig -p | grep lttng)
export LD_PRELOAD="liblttng-ust-cyg-profile.so"

# Create session
sudo lttng create "$SESSION_NAME"

# Enable UST events, filter to Steam processes
sudo lttng enable-event -u -a --filter 'procname == "steam" || procname == "steamwebhelper"'

# Enable kernel syscalls, filter to Steam processes
sudo lttng enable-event -k -a --filter 'procname == "steam" || procname == "steamwebhelper"'

# Add useful contexts
sudo lttng add-context -u -t vtid -t vpid -t procname -t ip
sudo lttng add-context -k -t pid -t tid -t procname -t prio

# Start tracing
sudo lttng start

# Run Steam with wrappers preloaded
"$APP_PATH" &

# Wait for Steam to exit
wait $!

# Stop and destroy session
sudo lttng stop
sudo lttng destroy
