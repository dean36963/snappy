#!/bin/bash

PID=$(ps x -A | grep snappy | grep -v grep | cut -d" " -f2)

top -p $PID
