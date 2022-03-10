#!/bin/bash

command < $2 1>$3
sed -n '8p' $2
sed -n '32p' $2
sed -n '128p' $2
sed -n '512p' $2
sed -n '1024p' $2

