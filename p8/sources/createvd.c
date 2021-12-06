#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <vdisk.h>

#define NSECS HEADS*SECTORS*CYLINDERS

int main(int argc,char **argv)
{
    int fp;
    int i;
    char nombre[20];
    char buffer[512];
    if(argc!=2)
    {
        fprintf(stderr,"Debe indicar el número de disco virtual a crear\n\n");
        exit(2);
    }
    if(argv[1][0]<'0' || argv[1][0]>'3')
    {
        fprintf(stderr,"Los números válidos para la creación del disco son entre 0 y 3\n\n");
        exit(2);
    }
    sprintf(nombre,"../drives/disco%c.vd",argv[1][0]);
    fp=open(nombre,0);
    if(fp!=-1)
    {
        fprintf(stderr,"Este disco virtual ya existe, para volver a crearlo es necesario borrarlo\n\n");
        exit(2);
    }
    fp=creat(nombre,0644);
    memset(buffer,0,512);
    for(i=0;i<NSECS;i++)
        write(fp,buffer,512);
    close(fp);
}
