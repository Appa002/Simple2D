#!/usr/bin/env bash

echo "## Updating ##"

if [ -f ../Simple2DEngine/TestObj/external.so ]; then
    rm ../Simple2DEngine/TestObj/external.so
fi

mv ./external.so ../../Simple2DEngine/TestObj/

echo "## Updated ##"