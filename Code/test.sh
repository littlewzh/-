#!/bin/bash
echo "begin test---"
for file in ../Test/*.cmm ;do
	echo "================= start  test ${file} ====================="
	./parser ${file}
	echo "================= finish test ${file} ====================="
done
echo "finish all the test!"  
