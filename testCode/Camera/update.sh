#!/usr/bin/env bash

echo "## Updating ##"

if [ -f ../Simple2DEngine/Camera/external.so ]; then
    rm ../Simple2DEngine/Camera/external.so
fi

mv ./external.so ../../Simple2DEngine/Camera/

echo "## Updated ##"