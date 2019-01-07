#!/bin/bash
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' 
echo -e "\n\nWELL FORMATTED JSONS : \n"
for filename in json_tests/good_examples/*.json; do
	#echo "../json_test/"$filename".json"
	#./json_parser "../json_test/"$filename".json"
	echo -e "$filename"
	output=$(./json_parser $filename)
	if [ "$output" = "NO ERRORS" ]
	then
		echo -e "${GREEN}$output${NC}"
	else 
		echo -e "${RED}$output${NC}"
	fi
done
echo -e "\n\n\nBAD FORMATTED JSONS : \n"
for filename in json_tests/bad_examples/*.json; do
	#echo "../json_test/"$filename".json"
	#./json_parser "../json_test/"$filename".json"
	echo -e "$filename"
	output=$(./json_parser $filename)
	if [ "$output" = "NO ERRORS" ]
	then
		echo -e "${GREEN}$output${NC}"
	else 
		echo -e "${RED}$output${NC}"
	fi
done
