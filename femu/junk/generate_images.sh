#! /usr/bin/env bash
for i in $(ls *.dot); do
    neato -Tsvg <$i >$i.svg
done
