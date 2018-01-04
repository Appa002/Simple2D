#!/usr/bin/env bash

echo "## Updating ##"

if [ -f ../Simple2DEngine/testObj/external.so ]; then
    rm ../Simple2DEngine/testObj/external.so
fi

mv ./external.so ../Simple2DEngine/testObj/


echo "## Updated ##"