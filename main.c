#include "chat.h"
int main(int argc,char* argv[]){
        atexit(exitHandler);


        char * rm = NULL;

        if(argc==2){
                if(makefile(path,argv[1])){
                  perror("can't not make id file.");
                  exit(1);
                }
                if(getMSG(&msgid,path,IPC_CREAT|0644)){
                  perror("can't not get msg queue.");
                  exit(1);
                }
                printf("%s열림\n",path);

                if(receiveMSG(&rm,msgid)){ //here s problem.
                  perror("cannot receive msg.");
                  exit(1);
                };
                printf("%s받음\n",rm );//receive queue를 여는 부분.
                strcpy(spath,rm);
                if(getMSG(&sndmsgid,spath,0)){
                    perror("can't not get send msg queue.");
                    exit(1);
                }
        }else if(argc == 3){
                makefile(path,argv[1]);
                getMSG(&msgid,path,IPC_CREAT|0644);
                printf("%s열림\n",path);

                makepath(spath,argv[2]);

                if(getMSG(&sndmsgid,spath,0)){
                  perror("can't get send msg queue.");
                  exit(1);
                };
                printf("%s열림\n",spath);

                if(sendMSG(path,sndmsgid)){
                  perror("can't not send path msg.");
                  exit(1);
                } // 내 path를 상대에게 보내줌.

        }else{
                printf("put args atleast 1\n");
                exit(1);
        }


        sleep(3);
        return 0;
}
