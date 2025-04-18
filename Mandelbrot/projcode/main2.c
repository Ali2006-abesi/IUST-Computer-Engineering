#include<stdio.h>





int get_mbs_iter(double x, double y)
{   
    // zn+1=zn*zn+c   z0 = 0 >>zx=0 , zy=0 , zn= x+iy zn*zn = x*x - y*y + 2xyi
    double zx1 = 0 , zy1 = 0 ;
    int max_iter = 1000 ;
    int i ; 
    for ( i =0  ; i<max_iter ; i++){

    double zx2 = zx1*zx1 - zy1*zy1 + x;
    double zy2 = 2*zx1*zy1 + y ;
    zx1 = zx2;
    zy1 = zy2;

    if (zx1*zx1 + zy1*zy1 > 4){
        break;
    }
    }
    // TODO
    return i ;
}

void main(){
    for(int x=0; x<40; x++){

        for(int y=0; y<50; y++)
        {   
            double real = (x - 40 / 2.0) * 4.0 / 40;
            double imag = (y - 50/ 2.0) * 2.0 /50;
            int iter = get_mbs_iter(real , imag);
            if (iter==1000){
                printf("*");
            }
            else{
                printf(" ");
            }
            
        }
        printf("\n");
        }
}