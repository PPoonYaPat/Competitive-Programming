#!/bin/bash

problem=vision

g++ -std=gnu++14 -O2 -Wall -pipe -static -o "${problem}" "grader.cpp" "${problem}.cpp"
