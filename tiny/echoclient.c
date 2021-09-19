#include "csapp.h"

int main(int argc, char **argv) {   // 배열 길이, filename, port ?
    int clientfd;
    char *host, *port, buf[MAXLINE];
    /*
     * Rio Package: 짧은 카운트에서 발생할 수 있는 네트워크 프로그램 같은 응용에서 편리하고,
       안정적이고 효율적인 I/O 제공
    */
    rio_t rio;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }

    host = argv[1];
    port = argv[2];

    printf("Open_clientfd...\n");
    clientfd = Open_clientfd(host, port);
    printf("Connected!\n");

    /*
     * rio_readinitb - Associate a descriptor with a read buffer and reset buffer
       open한 식별자마다 한 번 호출. 함수는 식별자 clientfd를 주소 rio에 위치한 rio_t타입의 읽기 버퍼와 연결한다.
    */
    Rio_readinitb(&rio, clientfd);

    while (Fgets(buf, MAXLINE, stdin) != NULL) {
        Rio_writen(clientfd, buf, strlen(buf));     // buf에서 식별자 clientfd로 strlen(buf)바이트를 전송
        Rio_readlineb(&rio, buf, MAXLINE);          // 다음 텍스트 줄을 파일 rio(종료 새 줄 문자를 포함)에서 읽고, 이것을 메모리 buf로 복사하고, 텍스트 라인을 NULL(0)문자로 종료시킴
        Fputs(buf, stdout);
    }

    Close(clientfd);
    exit(0);
}