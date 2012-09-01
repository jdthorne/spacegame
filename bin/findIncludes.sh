#!/bin/bash

find ../src -type d | sed -E 's/^(.*)$/-I\1/g'
