/*
 * A3Source.c
 *
 *   gcc -shared -fPIC -o A3Source.so A3Source.c
 */

#include <string.h>     // strcmp, strncpy
#include <sys/socket.h>  //socket
#include <arpa/inet.h>   //inet_addr

static char version[] = "0.1";

int sockfd, n;
struct sockaddr_in server;

char buffer[256];

void RVExtension(char *output, int outputSize, const char *function)
{
  if (!strcmp(function, "version"))
  {
    strncpy(output, version, outputSize);
  }
  else if (!strcmp(function, "connect")){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 5000 );
    if (connect(sockfd , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //Connect failed
        strncpy(output, "fail", outputSize);
        return;
    }
    strncpy(output, "OK", outputSize);
  }
  else
  {
    //echo content back to arma
    strncpy(output, function, outputSize);
  }
  output[outputSize-1]='\0';

  return;
}
