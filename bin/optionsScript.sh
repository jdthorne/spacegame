#!/bin/bash

find `pwd`/../src -type d | sed -E 's/^(.*)$/-I\1/g'
