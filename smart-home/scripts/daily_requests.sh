#!/usr/bin/bash

todaydate=$(date +%F)

numrequests=$(grep -c -w "$todaydate" 'request.txt')

echo "There were $numrequests request(s) today! ($todaydate)"

echo "There were $numrequests request(s) today! ($todaydate)" > 'num_matches.txt'