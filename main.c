#include "chat.h"
int main(int argc,char* argv[]){
        atexit(exitHandler);

        char path[BUF_SIZE]; //임시 파일 경로
        char spath[BUF_SIZE]; //임시 파일 경로2
        int msgid;   //msg queue id using receive
        int sndmsgid;   //msg queue id using send
        char rm[QUEUE_SIZE];

        if(argc==2){
                if(makefile(path,argv[1])){
                  printf("can't not make id file.");
                  exit(1);
                }
                if(getMSG(&msgid,path,IPC_CREAT|0644)){
                  printf("can't not get msg queue.");
                  exit(1);
                }
                printf("%s Opened.\n",path);

                if(receiveMSG(rm,msgid)){ //here s problem.
                  printf("cannot receive msg.");
                  exit(1);
                };
                printf("%s Connected.\n",rm );//receive queue를 여는 부분.
                strcpy(spath,rm);
                if(getMSG(&sndmsgid,spath,0)){
                    printf("can't not get send msg queue.");
                    exit(1);
                }
        }else if(argc == 3){
                if(makefile(path,argv[1])){
                    printf("can't not make id file.");
                    exit(1);
                }
                getMSG(&msgid,path,IPC_CREAT|0644);
                printf("%s Opened\n",path);

                makepath(spath,argv[2]);

                getMSG(&sndmsgid,spath,0);
                printf("%s Connected\n",spath);

                sendMSG(path,sndmsgid);

        }else{
                printf("Useage ID friendID\n");
                exit(1);
        }


        pid_t pid;
        if((pid = fork()) == -1){
          printf("can't fork, erro\n");
          exit(1);
        }
        else if(pid == 0){ //child
          printf("put message!\n");
          char input[QUEUE_SIZE];

          // fputs("you:",stdout);
          while(fgets(input,QUEUE_SIZE,stdin)){
            if(sendMSG(input,sndmsgid)){
              printf("can't not send msg.");
              exit(1);
            }
            //printf("%s sended\n",input);
            // fputs("you:",stdout);
          }

        }else{             // parent

          char rcv[QUEUE_SIZE];
          while(!receiveMSG(rcv,msgid)){

            printf("receive:");
            fputs(rcv,stdout);//stdout.
          }

        }

        return 0;
}
