#ifndef __MANDELBROTSET_H__
#define __MANDELBROTSET_H__

#include"defs.h"
#include<math.h>
#include<stdio.h>

int get_mbs_iter(double x, double y , double tavan)
{   
    // zn+1=zn*zn+c   z0 = 0 >>zx=0 , zy=0 , zn= x+iy zn*zn = x*x - y*y + 2xyi
    double zx = 0 , zy = 0 ;
    int max_iter = 1000;
    int i ; 
    for ( i =0  ; i<max_iter ; i++){

        double r = sqrt(zx*zx+zy*zy);
        double theta = atan2(zy,zx);
        double new_zx = pow(r,tavan) * cos(tavan*theta);
        double new_zy = pow(r,tavan) * sin(tavan*theta);
        zx = new_zx + x;
        zy = new_zy + y;

        if (zx*zx + zy*zy >=4){
            break;
        }
    // double zx2 = zx1*zx1 - zy1*zy1 + x;
    // double zy2 = 2*zx1*zy1 + y ;
    // zx1 = zx2;
    // zy1 = zy2;

    // if (zx2*zx2 + zy2*zy2 > pow(10,12)){
    //     break;
    // }
    }
    
    return i ;
}

// void hsv_to_rgb(int hue, int min, int max, COLORINDEX* p) {
    
    // int color[12][3]={
    //     {255,0,0},
    //     {255,127,0},
    //     {255,255,0},
    //     {127,255,0},
    //     {0,255,0},
    //     {0,255,127},
    //     {0,255,255},
    //     {0,127,255},
    //     {0,0,255},
    //     {127,0,255},
    //     {225,0,225},
    //     {225,0,127}
    // };
    // int size = (hue*12)/360;
    // if(size<12 )
    // {   
    //     p->r=color[size][0];
    //     p->g=color[size][1];
    //     p->b=color[size][2];
    // }

//     double h = hue/360.0; 
//     double s = max/100.0;                
//     double v = min/100.0;               
//     int i = (int)(h*6);
//     double f = h*6-i;
//     double x = v*(1-s);
//     double q = v*(1-f*s);
//     double t = v*(1-(1-f)*s);
                  

//     double r, g, b;

//     if (i%6==0) { r = v; g = t; b = x; }
//     else if (i%6==1) { r = q; g = v; b = x; }            
//     else if (i%6==2) { r = x; g = v; b = t; }         
//     else if (i%6==3) { r = x; g = q; b = v; }            
//     else if (i%6==4) { r = t; g = x; b = v; }             
//     else if (i%6==5) { r = v; g = x; b = q; }             
//     // else { r = 0; g = 0; b = 0; }
    
//     p->r = (unsigned char)(r  * 255);
//     p->g = (unsigned char)(g  * 255);
//     p->b = (unsigned char)(b * 255);
// }




void UpdateImageData(ImageState* state)
{   
    
    for (int i = 0; i < 256; i++) {
        if (i==0){
        state->bmFileData.bmHeader.colorIdx[0].r = 0;
        state->bmFileData.bmHeader.colorIdx[0].g = 0;
        state->bmFileData.bmHeader.colorIdx[0].b = 0;

        }
        else {
            state->bmFileData.bmHeader.colorIdx[i].r=0;
            state->bmFileData.bmHeader.colorIdx[i].g=0;
            state->bmFileData.bmHeader.colorIdx[i].b=(i%128)*2;
        }
        
    }
    double lenx = state->maxx - state->minx;
    double leny = state->maxy - state->miny;
    for(int x=0; x<state->width; x++){

        for(int y=0; y<state->height; y++)
        {   
           {   
            double dx = state->cx - lenx/2 +(lenx*x/state->width);
            double dy =state->cy - leny/2 +(leny*y/state->height);

            double rx = dx * cos(state->angle*(M_PI/180.0)) - dy * sin(state->angle*(M_PI/180.0));
            double ry = dx * sin(state->angle*(M_PI/180.0)) + dy * cos(state->angle*(M_PI/180.0)); 

            int iter = get_mbs_iter(rx,ry,state->tavan);
            if (iter == 1000) {
                state->bmFileData.bmData[y * state->width + x] = 0; 
            } else {
                state->bmFileData.bmData[y * state->width + x] = iter%256;       
                    }
        
            }

            
        }
    
    }
}


void ChangeCenter(ImageState* state, double newcx, double newcy, int steps)
{   
    double cx_step = (newcx-state->cx)/steps;
    double cy_step = (newcy-state->cy)/steps;
    for(int i=0;i<steps; i++)
    {   
        state->cx+=cx_step;
        state->cy+=cy_step;
        // printf("%f , %f" , state->cx , state->cy);
        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, & state->bmFileData);
    }
}

void ChangeZoom(ImageState* state, double zoom, int steps)
{   
    double zoom_factor=pow(zoom,1.0/steps);
    for(int i=0; i<steps; i++)
    {   
        double center_x = (state->maxx + state->minx) / 2;
        double center_y = (state->maxy + state->miny) / 2;
        double new_width = (state->maxx - state->minx) / zoom_factor;
        double new_height = (state->maxy - state->miny) / zoom_factor;
        state->minx = center_x - (new_width / 2);
        state->maxx = center_x + (new_width / 2);
        state->miny = center_y - (new_height / 2);
        state->maxy = center_y + (new_height / 2);
        
        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, & state->bmFileData);
    }
}

void ChangeRotation(ImageState* state, double angle, int steps)
{

    double angle_step = angle / steps;
    for(int i=0; i<steps; i++)
    {
        state->angle += angle_step;

        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, &state->bmFileData);
    }
}


void Hold(ImageState* state, int steps)
{
    if (steps<=0){
        printf("I can not hold");
        return;
    }
    for(int i=0; i<steps; i++)
    {   
        WriteBitmapFile(state->image_count++, & state->bmFileData);
    }
}

void tavan(ImageState* state ,double tavan, int steps){
    double tavan_step = (state->tavan-tavan)/steps;
    for (int i=0 ; i<steps ;i++){
        state->tavan-=tavan_step;
        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, &state->bmFileData);

    if (state->tavan<2){

        break;;   
    }
    }
}
#endif