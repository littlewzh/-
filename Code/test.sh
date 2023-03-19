#!/bin/bash
echo "---begin test---"
#实现一个专门针对树的测试
if [ "$1" = '-tree' ];
then 
  for file in ../Test/*tree.cmm ;do
  echo ""
	echo "================= start  test ${file} ====================="
	./parser ${file}
	echo "================= finish test ${file} ====================="
	echo ""
  done
#实现指定cmm的测试
elif [ -n "$1" ];
then 
  for file in ../Test/"$1".cmm;do
  echo ""
	echo "================= start  test ${file} ====================="
	./parser ${file}
	echo "================= finish test ${file} ====================="
	echo ""
  done
else 
#不加参数的正常测试
  for file in ../Test/*.cmm ;do
   if [[ "$file" =~ "test_oj_tree.cmm" ]]; then echo "nomal test : skip oj_tree_test"
   else
   echo ""
	 echo "================= start  test ${file} ====================="
	 ./parser ${file}
	 echo "================= finish test ${file} ====================="
	 echo ""
   fi
  done
fi
echo "Finish all the test!"  
