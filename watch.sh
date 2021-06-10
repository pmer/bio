#!/bin/sh
ls answers/* input/* src/* | entr sh -c 'tput reset; (cd build; ninja) && bin/test.sh'
