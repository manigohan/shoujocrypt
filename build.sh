#!/bin/bash
set -e

# This is to be ran after building the ShoujoCrypt payload and OverlayService
export PROJECT_ROOT="$PWD"
export build="$PROJECT_ROOT/build"

if [ -e "$PROJECT_ROOT/out" ]; then
  rm -rf $PROJECT_ROOT/out
  mkdir $PROJECT_ROOT/out
else
  mkdir $PROJECT_ROOT/out
fi
echo -e "Made output directory at $PROJECT_ROOT/out"

bash $build/image.sh
bash $build/zipitup.sh

echo -e "Done!"