#!/bin/sh

s='one_two_three_four_five'
A="$(cut -d'_' -f2 <<<"$s")"
echo "$A"
