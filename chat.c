#include "chat.h"
int makepath(char* buf,const char*id)
{
        strcpy( buf , "/tmp/");
        strcat( buf ,id ); // making path.
}
int makefile(char* buf,const char* id)
{
        makepath(buf,id);
        int fd = open(buf,O_CREAT|O_EXCL,0644);
        if(fd == -1){
                printf("open error\n");
                return 1;
        }
        close(fd);
        return 0;
}
int get(int* _msgid,char* path,int flag){
        key_t key;
        key = ftok(path,1);
        *_msgid = msgget(key,flag);
        printf("%s:%d\n",path,*_msgid);

        if(*_msgid == -1){
                printf("msgget error\n");
                return 1;
        }
        return 0;
}
int receive(char*buf,int msgid){
        struct mymsgbuf rcvmesg;  //receive 메시지 버퍼
        int len;
        len = msgrcv(msgid, &rcvmesg, QUEUE_SIZE,0,0)+1;
        buf= (char*)malloc(sizeof(char)*len);
        strcpy(buf,rcvmesg.mtext);
        //buf=rcvmesg.mtext;
        return 0;
}
int send(char* buf, int sndmsgid){
        struct mymsgbuf sndmesg;  //send 메시지 버퍼
        sndmesg.mtype = 1;
        strcpy(sndmesg.mtext, buf);
        int len = strlen(buf);
        if(msgsnd(sndmsgid, (void*)&sndmesg,len , IPC_NOWAIT) == -1){
                printf("msgsnd error\n");
                return 1;
        }
        return 0;
}
void exitHandler(){
        msgctl(msgid,IPC_RMID,(struct msqid_ds *)NULL); // 메시지 큐 제거
        unlink(path);
        printf("program terminated\n");
}
