#!/bin/bash
echo "---begin test---"
  for file in $1/*.cmm ;do
   echo ""
	 echo "================= start  test ${file} ====================="
	 ./parser ${file}
	 echo "================= finish test ${file} ====================="
	 echo ""
  done
echo "Finish all the test!"  
