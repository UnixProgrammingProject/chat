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
int getMSG(int* _msgid,char* path,int flag){
        key_t key;
        key = ftok(path,1);
        *_msgid = msgget(key,flag);
        //printf("%s:%d\n",path,*_msgid);

        if(*_msgid == -1){
                printf("msgget error\n");
                return 1;
        }
        return 0;
}
int receiveMSG(char*buf,int msgid){
        struct mymsgbuf rcvmesg;  //receive 메시지 버퍼
        int len;
        len = msgrcv(msgid, &rcvmesg, QUEUE_SIZE,0,0);
        //printf("receive msg:%s, Len=%d\n",rcvmesg.mtext,len);
        if(len == -1){
          printf("cannot receive msg\n");
          return 1;
        }
        len++;

        // if(buf ==NULL){
        //   printf("malloc error\n");
        //   return 1;
        // }
        strcpy(buf,rcvmesg.mtext);
        //buf[len-1]='0';
        printf("receive msg:%s\n",buf);
        //buf=rcvmesg.mtext;
        return 0;
}
int sendMSG(char* buf, int sndmsgid){
        struct mymsgbuf sndmesg;  //send 메시지 버퍼
        sndmesg.mtype = 1;
        strcpy(sndmesg.mtext, buf);
        int len = strlen(buf);
        if(msgsnd(sndmsgid, (void*)&sndmesg,len+1 , IPC_NOWAIT) == -1){
                printf("msgsnd error\n");
                return 1;
        }
        return 0;
}
void exitHandler(){
        msgctl(msgid,IPC_RMID,(struct msqid_ds *)NULL); // 메시지 큐 제거
        unlink(path);
        printf("program terminated!\n");
}
