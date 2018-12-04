#include "chat.h"
int main(int argc,char* argv[]){
        atexit(exitHandler);



        if(argc==2){
                makefile(path,argv[1]);
                get(&msgid,path,IPC_CREAT|0644);
                printf("%s열림\n",path);

                char * rm = NULL;
                receive(rm,msgid);
                printf("%s받음\n",rm );//receive queue를 여는 부분.
                strcpy(spath,rm);
                get(&sndmsgid,spath,0);
        }else if(argc == 3){
                makefile(path,argv[1]);
                get(&msgid,path,IPC_CREAT|0644);
                printf("%s열림\n",path);

                makepath(spath,argv[2]);
                printf("%s열림\n",spath);
                get(&sndmsgid,spath,0);
                send(path,sndmsgid); // 내 path를 상대에게 보내줌.
        }else{
                printf("put args atleast 1\n");
                exit(1);
        }


        sleep(3);
        return 0;
}
