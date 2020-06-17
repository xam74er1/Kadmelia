#!/bin/bash
ls $1/*.c | sed -e "s/^/$1\//g" | sed -e "s/.c/.o/g" |  tr '\n' ' '
echo ""