#include"optimizer.h"
int main(int argc, char** argv){
    if (argc < 3) return 1;
    //分三个模块执行：读入、优化、打印
    readinput(argv[1]);
    optimize();
    printoutput(argv[2]);
    return 0;
}