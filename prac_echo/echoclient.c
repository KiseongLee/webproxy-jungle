#include "csapp.h"

int main(int argc, char **argv)
{
    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }
    host = argv[1];
    port = argv[2];

    clientfd = open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    while (fgets(buf, MAXLINE, stdin) != NULL) {
        Rio_writen(clientfd, buf, strlen(buf));
        Rio_readlineb(&rio, buf, MAXLINE);
        fputs(buf, stdout);
    }
    // 서버와의 연결을 수립한 이후
    // 클라이언트는 표준 입력에서 텍스트 줄을 반복해서 읽는 루프에 진입
    // 서버에 텍스트 줄을 전송하고, 
    // 서버에서 echo 줄을 읽어서 그 결과를 표준 출력으로 인쇄
    // 루프는 fgets가 EOF 표준 입력을 만나면 종료
    Close(clientfd);
    exit(0);
}