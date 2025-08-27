
#!/bin/bash
# run.sh - open Konsole in Bin/ and run the app with args

cd "$(dirname "$0")/Bin" || exit 1

if [ -z "$1" ]; then
    echo "Usage: $0 <executable> [args...]"
    exit 1
fi

APP="$1"
shift

konsole -e "./$APP" "$@"
