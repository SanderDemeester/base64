#include <stdio.h>
static char *base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
void base64_encode(const unsigned char *input,int len, unsigned char *output){
  do{
    *output++ = base64[(input[0] & 0xFC ) >> 2];
    if(len==1){
      *output++ = base64[((input[0] & 0x03) << 4 ) ];
      *output++ = '=';
      *output++ = '=';
      break;
    }
    *output++ = base64[ 
		       ((input[0] & 0x03 ) << 4) | ((input[1] & 0xF0) >> 4)];
    if(len==2){
      *output++ = base64[((input[1] & 0x0F) << 2)];
      *output++ = '=';
      break;
    }
    *output++ = base64[
		       ((input[1] & 0x0F) << 2) | ((input[2] & 0xC0) >> 6)];
    *output++ = base64[(input[2] & 0x3F)];
    input +=3;
  }while(len -=3);
  *output = '\0';
  *output = '\n';
}
		       
int main(int argc, char *argv[]){
  char buffer[(3/4)*sizeof(argv[1])];
  if(argc == 2){
  base64_encode(argv[1],sizeof(argv[1]),&buffer[0]);
  printf(buffer);
  }
  return 0;
}
		       
