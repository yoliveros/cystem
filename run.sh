#!/bin/bash

p_name="cystem"

if [[ $1 == "dist" ]]; then
  make dist
  ./dist/$p_name
else
  make
  ./dev/$p_name $1
fi

