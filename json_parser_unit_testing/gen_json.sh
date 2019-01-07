#!/bin/sh

MAX_OBJ=0
TEST_FILE="test.json"

/bin/echo  '[' > $TEST_FILE
	/bin/echo  '{' >> $TEST_FILE
	
	/bin/echo "\"name\" : \"salutasdl;fjhasdkjskdfjsdf\"," >> $TEST_FILE

field_gen() {
	/bin/echo -n '"' >> $TEST_FILE
	cat /dev/urandom | head -c 10 | LC_LOCAL='C' base64  | tr '\n' 'A'  >> $TEST_FILE
	/bin/echo -n '" : ' >> $TEST_FILE

	/bin/echo -n '"' >> $TEST_FILE
	cat /dev/urandom | head -c 10 | LC_LOCAL='C' base64 | tr '\n' 'A'  >> $TEST_FILE
	if [ $1 -eq 1 ] 
	then
		/bin/echo '",' >> $TEST_FILE
	else
		/bin/echo '"' >> $TEST_FILE
	fi

}

obj_gen() {
	if ! [[ -z $3 ]]
	then
		/bin/echo -n '"' >> $TEST_FILE
		/bin/echo -n "$3" >> $TEST_FILE
		/bin/echo -n '" : ' >> $TEST_FILE
		
	else
		/bin/echo -n '"' >> $TEST_FILE
		cat /dev/urandom | head -c 10| LC_LOCAL='C' base64 | tr '\n' 'A' >> $TEST_FILE
		/bin/echo -n '" : ' >> $TEST_FILE
	fi

	/bin/echo  '{' >> $TEST_FILE
	if [ $2 -eq 1 ] 
	then
		field_gen 1
		field_gen 1
		field_gen 0
	else
		i=0
		obj_gen 1 1 "sphere"
		while [ $i -lt $MAX_OBJ ]
		do
			
			obj_gen 1 1 "sphere-$i"
			i=$((i+=1))
			
		done
		obj_gen 0 1 ""

	fi	
	if [ $1 -eq 1 ] 
	then
		/bin/echo '},' >> $TEST_FILE
	else
		/bin/echo '}' >> $TEST_FILE
	fi
}


obj_gen 0 0 "objects"  "sphere"

/bin/echo '}' >> $TEST_FILE

/bin/echo ']' >> $TEST_FILE