#!/bin/bash
# Geometry Engine Pipeline

set -e

INPUT_JSON=$1

echo "=== Geometry Engine Pipeline ==="
echo "Input geometry file: $INPUT_JSON"
echo

# DEBUG
echo "Step 1"
# DEBUG
echo "[Scheme] Generating geometry JSON..."
scheme --load scheme/src/geometry.scm --eval "(export-geometry \"INPUT_JSON\")"
echo "Geometry JSON written to $INPUT_JSON"
echo

# DEBUG
echo "Step 2"
# DEBUG
echo "[c++] Computing distances, areas, and invarients..."
./cpp/build/geometry_engine "$INPUT_JSON" > results.txt
cat results.txt
echo

# DEBUG
echo "Step 3"
# DEBUG
echo "[Prolog] Checking geometric relations..."
swipl -s prolog/relations.pl -g "check_geometry('$INPUT_JSON'), halt."
echo

echo "=== Pipeline Complete ==="