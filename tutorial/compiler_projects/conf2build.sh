#!/bin/sh
exec "$(cd "$(dirname "$0")/../../tools/project_generation" && pwd)/conf2build.sh" "$@"
