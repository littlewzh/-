#!/bin/bash
echo "---begin test---"
  for file in ../Test/Tests/inputs/*.cmm ;do
   echo ""
	 echo "================= start  test ${file} ====================="
	 ./parser ${file}
	 echo "================= finish test ${file} ====================="
	 echo ""
  done
echo "Finish all the test!"  
