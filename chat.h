#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUF_SIZE 256
#define QUEUE_SIZE 1024

char path[BUF_SIZE]; //임시 파일 경로
char spath[BUF_SIZE]; //임시 파일 경로2
int msgid;   //msg queue id using receive
int sndmsgid;   //msg queue id using send
struct mymsgbuf{
        long mtype;
        char mtext[QUEUE_SIZE];
};


int makepath(char* buf,const char*id);
int makefile(char* buf,const char* id);
int getMSG(int* _msgid,char* path,int flag);
int receiveMSG(char**buf,int msgid);
int sendMSG(char* buf, int sndmsgid);
void exitHandler();
