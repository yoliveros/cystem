#!/bin/bash

exec="cm"

if [[ $1 == "dist" ]]; then
  make dist
else
  make
  ./dev/$exec $1 $2
fi
