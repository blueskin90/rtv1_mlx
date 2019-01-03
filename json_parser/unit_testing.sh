#!/bin/bash
for filename in ../json_tests/*.json; do
	echo $filename
	#echo "../json_test/"$filename".json"
	#./json_parser "../json_test/"$filename".json"
	./json_parser $filename
done
