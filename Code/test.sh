#!/bin/bash
echo "begin test---"
for file in ../Test/*.cmm ;do
        echo ""
	echo "================= start  test ${file} ====================="
	./parser ${file}
	echo "================= finish test ${file} ====================="
	echo ""
done
echo "finish all the test!"  
