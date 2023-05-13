#!/bin/bash
curl --silent https://api.thecatapi.com/v1/images/search | jq .[].url | sed 's/"//g' | xargs wget --quiet -O tmpimg
img2txt tmpimg
curl --silent http://api.icndb.com/jokes/random | jq '.value.joke'
rm tmpimg
