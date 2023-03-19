#!/bin/bash
echo "begin test---"
if [ $1 = '-tree' ];
then 
  for file in ../Test/*tree.cmm ;do
  echo ""
	echo "================= start  test ${file} ====================="
	./parser ${file}
	echo "================= finish test ${file} ====================="
	echo ""
  done
else 
  for file in ../Test/*.cmm ;do
   if [ $file = "*tree.cmm" ]; then echo "tree"
   else
   echo ""
	 echo "================= start  test ${file} ====================="
	 #./parser ${file}
	 echo "================= finish test ${file} ====================="
	 echo ""
   fi
  done
fi
echo "finish all the test!"  
