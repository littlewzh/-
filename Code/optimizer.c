#include"optimizer.h"
#define OPTIMIZER
#ifdef OPTIMIZER
#define odebug(...) printf(__VA_ARGS__)
#else
#define odebug(...) assert(1)
#endif

void readinput(char* filename){
//输入模块读取输入文件信息到数据结构
    odebug("-----Read Input Begin-----\n");
    FILE *f = fopen(filename, "r");
    if (!f){
        printf("cannot open file : %s\n",filename);
        return;
    }
    char buf[500];//读取一行
    int linenum = 0;//记录行数
    while(fgets(buf,256,f)!=NULL){
        linenum++;
        odebug("Line %d : ",linenum);
        int len = strlen(buf);//长度
        if(buf[0]=='\n'){//空行
            odebug("null\n");
            continue;
        }
        else if (buf[0]=='F'){//新函数
            odebug("new function");
        }
        else if (buf[0]=='L'){//新标签=>新基本块
            odebug("new label");
        }
        else if (buf[0]=='G'){//GOTO
            odebug("GOTO");
        }
        else if (buf[0]=='I'){//IF_GOTO
            odebug("IF_GOTO");
        }
        else if (buf[0]=='R'&&buf[2]=='T'){//RETUR
            odebug("RETURN");
        }
        else if (buf[0]=='D'){//DEC
            odebug("DEC");
        }
        else if (buf[0]=='A'){//ARG
            odebug("ARG");
        }
        else if (buf[0]=='C'){//CALL
            odebug("CALL");
        }
        else if (buf[0]=='P'){//PARAM
            odebug("PARAM");
        }
        else if (buf[0]=='R'&&buf[2]=='A'){//READ
            odebug("READ");
        }
        else if (buf[0]=='W'){//WRITE
            odebug("WRITE");
        }
        else if (buf[0]=='v'||buf[0]=='t'||buf[0]=='*'||buf[0]=='&'){//
            odebug("ASSIGN...");
        }
        else{
            odebug("wrong line type");
            assert(0);
        }
    }
    odebug("-----Read Input Finished!-----\n");
}
void optimize(){
//优化模块主函数
    odebug("-----Optimize Begin-----\n");
    odebug("-----Optimize Finished!-----\n");
}
void printoutput(char *filename){
//输出模块打印优化后中间代码
    odebug("-----Print output Begin-----\n");
    FILE *f = fopen(filename, "w");
        if (!f){
            printf("cannot open file : %s\n",filename);
            return;
        }
    odebug("-----Print output Finished!-----\n");
}
