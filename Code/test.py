#!/usr/bin/env python3
import os,subprocess
import atexit

testpath = '../Test/Tests/inputs/'
outpath = '../Test/Tests/expects/'
def run(file1:str):
    cmd = f"./parser {file1}"
    p = subprocess.Popen(cmd,shell=True,stdin=subprocess.PIPE,stdout=subprocess.PIPE)
    outs, _ = p.communicate()
    return outs.decode()

def compare(s1,s2):
    t1,t2 = s1.strip().split("\n"),s2.strip().split("\n")
    for line1,line2 in zip(t1,t2):
        if line1.strip()!=line2.strip():
            return False
    return True

if __name__ == "__main__":
    testlist = sorted(os.listdir(testpath))
    for t in testlist:
        print(f'begin test:{t}')
        out = run(f'{testpath}{t}')
        file = t.split('.')[0]
        if os.path.exists(f'{outpath}{file}.exp'):
            with open(f'{outpath}{file}.exp') as f: exp = f.read()
            assert compare(out,exp),f"Wrong answer {t},input/output files dumped"
            print('right syntax tree')
        else:
            print(out)
        print(f'finish test:{t}\n')
