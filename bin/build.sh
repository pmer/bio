#!/bin/bash
mkdir -p build
cd $_
cmake .. -G Ninja && ninja
