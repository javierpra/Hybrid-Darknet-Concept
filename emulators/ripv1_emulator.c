#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <err.h>

int handle_datagram(char buffer[], int count){
    if (strstr(buffer,"\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x10")!=NULL){
        //printf("Message received!\n");
        return 1;
    }
    else{
        return -1;
    }
}

int main(){
    //Create child(deamon) process
    pid_t process_id = fork();
    if (process_id<0){
        printf("Fork failure!\n");
        exit(1);
    }
    else if (process_id>0){
        //printf("Deamon process initialized!\n");
        //printf("Terminating parent process...\n");
        exit(0);
    }
    
    //IP address and port converted from string to struct sockaddr_in
    const char* hostname="0.0.0.0"; /* wildcard */
    const char* portname="520";
   	struct addrinfo hints;
    
    //Content to reflect back
   	char content[]={0xea,0xd7,0x2f,0xdd,0x2c,0xf3,0xad,0x8c,0xa1,0x96,0x39,0x62,0xdc,0x7e,0x9b,0x3c,0x73,0x5a,0x73,0x08,0xa1,0x3c,0x3b,0x13,0x9d,0xbb,0xfe,0x10,0xb8,0xeb,0xda,0xe7,0x39,0xfe,0x36,0x43,0xf9,0xb7,0xc4,0xda,0xbd,0x92,0x36,0x7b,0x56,0xb5,0xbf,0xd9,0x7a,0x94,0x50,0x19,0x61,0x67,0x8f,0x1d,0x1f,0x4d,0x97,0x8e,0xc4,0x3d,0x73,0xac,0x35,0xb1,0x57,0xd5,0xc9,0x11,0xa4,0xd6,0xa3,0xe0,0x9a,0xf5,0xd2,0xa8,0xda,0xbb,0x2a,0xa6,0xa3,0x82,0xe0,0x36,0xc9,0xc1,0xe7,0xfd,0x74,0x1a,0x0e,0xd8,0x9e,0x20,0xd6,0x88,0x4a,0xea,0x14,0x1a,0x85,0x59,0x4b,0x17,0x1e,0x28,0xc7,0x70,0x25,0xb8,0x79,0x28,0x24,0x99,0x96,0xbf,0x20,0xd8,0xee,0x62,0x4e,0x0b,0x0d,0xd4,0x95,0x1d,0x13,0x1a,0xc7,0xda,0x53,0xe9,0x9f,0x39,0xae,0xd0,0x7a,0x6d,0xae,0x25,0xd6,0xaa,0x62,0xb1,0x8b,0xb8,0xfc,0x1b,0xcb,0x39,0x2b,0x15,0xdb,0xb9,0x39,0x48,0x8e,0x7a,0xe4,0x00,0x86,0xfd,0xfe,0x97,0x2a,0x50,0xc3,0xa3,0x66,0x1b,0xfe,0xdf,0x26,0x68,0xda,0xda,0x90,0x35,0x89,0x61,0x03,0xbb,0x97,0xad,0xd4,0x7c,0x0b,0x4d,0xc3,0x0f,0x42,0xd2,0x3f,0xab,0x8c,0x3c,0x5e,0x75,0x83,0x27,0x9a,0x8a,0x2f,0xb5,0x4d,0xca,0xdb,0x3a,0xea,0x6a,0xb5,0xab,0x01,0x38,0x28,0xc4,0xf1,0xad,0xfa,0xfb,0x6a,0xb5,0x25,0x27,0xaa,0x3d,0x75,0xf0,0x73,0x80,0xe5,0xf5,0xce,0x12,0xba,0xc0,0x82,0xa9,0x5d,0x6b,0x53,0xae,0xf9,0x0e,0xfb,0x88,0xd9,0xf0,0xea,0xa3,0x7f,0x69,0xbc,0x42,0x83,0x98,0x7e,0x0a,0x32,0xca,0xa1,0x4a,0xe2,0xa5,0xba,0x0b,0x16,0x18,0xff,0xdc,0x57,0x03,0x82,0x5a,0xcd,0xa5,0x2b,0x81,0xa0,0xc9,0x76,0xb6,0x11,0xb0,0xf2,0x90,0x56,0xbd,0x75,0x6a,0x3a,0xe3,0x20,0xa9,0x71,0xcf,0x16,0xcd,0xbc,0xd4,0xfb,0x3a,0xc1,0x9a,0x2e,0xc4,0xa8,0x86,0xc7,0xfd,0x75,0xe8,0x4f,0x3e,0x28,0xe8,0x42,0x76,0x96,0x2d,0x45,0xb5,0x05,0x52,0x27,0x77,0x8a,0x0a,0x99,0xb1,0x23,0x0d,0xae,0x9d,0x94,0xca,0x11,0x46,0x02,0xca,0x08,0xd3,0x51,0xe5,0x2c,0x93,0x3d,0x28,0xe5,0xcc,0x3a,0x82,0xa8,0x43,0x0c,0x31,0xf0,0x8b,0x26,0xef,0xfd,0x0e,0xc4,0xdb,0x4f,0xdd,0xc7,0x29,0xe1,0x37,0x54,0x89,0x26,0xdb,0x2b,0x58,0xc4,0x0d,0xc7,0x89,0x13,0x6a,0x3b,0x51,0x54,0x6d,0xc7,0x96,0xb1,0xbd,0x3d,0x15,0xf9,0x3c,0x16,0x55,0x18,0xd0,0x53,0x4f,0x57,0xef,0x15,0xda,0x59,0xed,0xfb,0xd8,0xd1,0x05,0x3f,0x23,0x04,0x29,0x90,0x35,0x02,0x89,0xad,0x99,0xa4,0xe5,0xc6,0x15,0x44,0x93,0x92,0x94,0x3f,0x4f,0x2f,0xd6,0x2c,0xc6,0xbe,0xd6,0xd9,0xe1,0xba,0xfe,0x0a,0xd2,0x1c,0x0d,0xf0,0xdf,0x31,0xc4,0x6b,0xf1,0x36,0x54,0xff,0xdc,0xb9,0x87,0x98,0x6c,0xaf,0xb0,0xfe,0x33,0x54,0x54,0x16,0x15,0xc6,0x95,0xde,0x90,0x60,0x62,0x26,0xcc,0xd7,0x60,0x0f,0x66,0x17,0x97,0x45,0xfc,0xdb,0xdd,0xfc,0x78,0x0e,0x03,0xab,0x1d,0xe5,0xc1,0x8b,0x53,0xb9,0x61,0xce,0x32,0xa5,0x2e,0xa0,0xd0,0xe4,0x9c,0xde,0x4b,0xe7,0x34,0x99,0x95,0x39,0x46,0x49,0x02,0x13,0x4d,0xd1,0x93,0xbf,0x20,0x37,0x00,0xad,0xde,0x1f,0x87,0x56,0x97,0x0c,0x77,0xd4,0xba,0x56,0x7b,0x3e,0x43,0xeb,0xa7,0xc5,0xa1,0xc6,0x44,0x90,0x68,0x2f,0x5c,0x57,0xbb,0xb7,0x04,0xc1,0x77,0xf2,0x6c,0x7e,0x20,0xf2,0xa8,0x24,0x8c,0x88,0x3b,0xcb,0x51,0x3a,0x68,0x67,0xf0,0x03,0x39,0xe8,0xbe,0xcd,0x4c,0x13,0x96,0xaf,0x61,0x1e,0x40,0xe6,0xa3,0x0e,0xa0,0x95,0xb9,0xd1,0x9e,0x3d,0x8c,0x1a,0xd9,0xfa,0xd7,0x00,0x0b,0x83,0x70,0x56,0x3a,0xdf,0x58,0xc8,0xa4,0xe8,0x83,0xba,0x68,0x81,0x68,0xe1,0xf4,0x97,0x49,0x9d,0x32,0xd8,0x40,0x1d,0x71,0x36,0x0d,0x31,0x15,0x1a,0xa1,0xee,0xff,0x68,0x69,0x04,0xba,0x37,0x5c,0xde,0x6a,0x4d,0xc3,0x7e,0x75,0x5d,0xcb,0x17,0xee,0x00,0xcc,0x67,0xc6,0x73,0x57,0xdb,0xb1,0x16,0x02,0x60,0xda,0xa0,0xf3,0x0a,0x46,0x23,0x2d,0x68,0x08,0xc3,0x9d,0xa1,0x2a,0x36,0xe3,0x57,0x56,0xfb,0xe2,0x38,0x48,0x5a,0x06,0x64,0xf4,0x1e,0x58,0x82,0x76,0x15,0x43,0xa0,0xbd,0x44,0x23,0xce,0xf7,0xea,0x93,0x7a,0xbc,0x3b,0x73,0x8a,0xfa,0xd9,0xbb,0x3c,0xa3,0x12,0x03,0xbd,0x17,0xdd,0xce,0x8a,0x53,0x91,0x9a,0x8a,0xd7,0x6b,0xa8,0xe8,0x59,0xbe,0x8b,0xb2,0x2b,0xf7,0x73,0x33,0x6d,0x57,0x37,0x10,0xf2,0x70,0x24,0x25,0xf3,0x5c,0x87,0x1d,0x76,0xc0,0xfc,0xd3,0x7c,0x84,0x75,0x6c,0xed,0x50,0x09,0x31,0x44,0xc5,0x82,0x2d,0xfa,0x80,0xa5,0x8a,0xb4,0xcf,0x3f,0xac,0x2c,0x31,0xf4,0x0b,0xdf,0x90,0xc7,0xd1,0x7b,0x3d,0x68,0x37,0x07,0xaf,0x41,0x9f,0xd0,0xfb,0x3f,0x72,0x17,0x13,0x61,0xb7,0x7c,0xbe,0x01,0x78,0x28,0x5b,0xe5,0xd5,0xbe,0x55,0x05,0xe5,0xff,0x65,0x1a,0x50,0x3f,0x8b,0xeb,0xad,0x8b,0xca,0x57,0x9c,0x97,0xa6,0x21,0xa3,0x6a,0x5e,0x7e,0xc9,0xc8,0xea,0x60,0xf5,0x63,0xb3,0x80,0x04,0xc0,0x15,0x2e,0xab,0xea,0x95,0xd8,0x13,0xda,0xe2,0x5c,0x2e,0xa1,0x8d,0x0d,0xda,0x5b,0x88,0x87,0xbd,0xd4,0x60,0x33,0xdb,0xf7,0x3a,0x99,0xf7,0xfb,0x8f,0x69,0xb0,0x4c,0xa7,0x47,0x56,0x3a,0xd6,0x5a,0x91,0x63,0x79,0x93,0xb0,0xe1,0xaf,0xbd,0xd2,0x34,0xd8,0x49,0xb7,0xee,0xcf,0xd7,0x63,0x21,0xe7,0x84,0x78,0x88,0xa6,0xf6,0x51,0x78,0x44,0x28,0xde,0x84,0xe2,0xf6,0x42,0xf3,0x8a,0x68,0x2e,0xe3,0xea,0xbe,0xfb,0x39,0xd0,0x40,0x8a,0x50,0x65,0xc2,0xdc,0x5d,0x29,0xf9,0x70,0xa4,0xb2,0x81,0x60,0x5c,0x24,0xaa,0x3a,0x63,0x6f,0x06,0x9f,0xa2,0x4b,0xb3,0x9e,0x3e,0xf5,0x68,0xce,0x84,0xa6,0x42,0x2d,0x91,0xd8,0x4c,0xbb,0xc4,0x38,0xd0,0xd6,0xe5,0x69,0x61,0x54,0x12,0x7f,0xa3,0x62,0x6d,0x36,0xe1,0x1f,0x87,0xf6,0x4c,0xf8,0x8b,0x87,0x14,0xc2,0x2a,0x94,0x29,0x99,0x4a,0xe1,0xce,0x7a,0x6e,0x4c,0xe2,0xa2,0xe3,0x85,0xee,0xa6,0xb0,0x8d,0xed,0x4f,0x3b,0xef,0xdf,0x3b,0xbb,0xc1,0x0c,0x35,0x61,0x5a,0x19,0x4f,0x46,0xd0,0xcc,0xc5,0x13,0x38,0x9e,0x91,0x72,0x9d,0x06,0xcd,0x38,0xbc,0x80,0xcd,0x4f,0x85,0x5f,0xf8,0x65,0x52,0x58,0x6a,0x56,0xe5,0xca,0x4c,0x5a,0x24,0xce,0xee,0xee,0x93,0x03,0xa9,0x83,0x95,0x16,0x77,0xe9,0x62,0x14,0x4f,0x7a,0xc8};
    while(1){
        memset(&hints,0,sizeof(hints));
        hints.ai_family=AF_INET;
        hints.ai_socktype=SOCK_DGRAM;
        hints.ai_protocol=0;
        hints.ai_flags=AI_PASSIVE|AI_ADDRCONFIG;
        
        struct addrinfo* res=0;
        int err = getaddrinfo(hostname,portname,&hints,&res);
        if (err!=0) {
            printf("ERROR");
        }
        //Create socket
        int fd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
        if (fd==-1) {
            printf("ERROR: socket");
        }
        //Bind socket
        if (bind(fd,res->ai_addr,res->ai_addrlen)==-1) {
            printf("ERROR: bind");
        }
        //Receive and handle datagrams
        char buffer[1549];
        struct sockaddr_in src_addr;
        socklen_t src_addr_len;
        ssize_t count;
        
        count = recvfrom(fd,buffer,sizeof(buffer),0,(struct sockaddr*)&src_addr,&src_addr_len);
        if (count==-1) {
            printf("ERROR: count=-1");
        }
        else if (count==sizeof(buffer)) {
            warn("datagram too large for buffer: truncated");
        }
        else {//Sending response
            if (handle_datagram(buffer,count)==1){
                sendto(fd,content,sizeof(content),0,(struct sockaddr*)&src_addr,src_addr_len);
            }
        }
        memset(&buffer[0],0,sizeof(buffer));
        close(fd);
    }
    return 0;
}

