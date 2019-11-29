#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<conio.h>

int main(){
 
float E1[200];
float E2[200];
float E3[200];
float E4[200];
float t[3][200];

	
	
    float  w1[5][5];
    float nw1[5][5];
    float vw1[5][5];
    
    float  w2[5][5];
    float nw2[5][5];
    float vw2[5][5];
    
    float I[5][5];
    float O[5][5];
    float d1[5];
    float d2[5];
    float erro;
    int i=0,j,l;
    int cs;
    int n;
    
    //------------------LER-----------------------------
   FILE *in;

   if ((in =fopen("data_bv.txt", "rt"))== NULL)
   {
	  printf("Cannot open input file.\n");
	  return 1;
   }

   while(!feof(in)){
	  fscanf(in,"%f%f%f%f%f%f",&E1[i],&E2[i],&E3[i],&E4[i],&t[0][i],&t[1][i]);

	  i++;
					  }

	for(j=0;j<(i-1);j++){
	printf("%d %f %f %f %f %f %f \n",j,E1[j],E2[j],E3[j],E4[j],t[0][j],t[1][j]);
			}

   fclose(in);
getch();
//-----------------------------------------------------
    
for(j=0;j<3;j++){
for(i=0;i<5;i++){
	vw1[i][j]=0.0;
 	 w1[i][j]=(rand()/32767.0)*4.0-2.0;
}
}
 
for(l=0;l<3;l++){
for(j=0;j<4;j++){
	vw2[j][l]=0.0;
	 w2[j][l]=(rand()/32767.0)*4.0-2.0;
}
}   
    
do{
    
erro=0.0;
for(n=0;n<601;n++){
	
	
	//-----propagation----------------------------
	cs=rand()%150;    			//numero de casos
    
	I[0][0] = E1[cs];
    I[0][1] = E2[cs];
    I[0][2] = E3[cs];
    I[0][3] = E4[cs];
    I[0][4] = 1.0;
    
    O[0][0] = I[0][0];
    O[0][1] = I[0][1];
    O[0][2] = I[0][2];
    O[0][3] = I[0][3];
    O[0][4] = I[0][4];
    
    
    for(j = 0; j < 3; j++){
    	I[1][j]=0.0;
    	for(i = 0; i< 5; i++){
    		I[1][j] +=  w1[i][j]*O[0][i];
		}
		O[1][j]=1.0 / (1.0 + exp(-I[1][j]));
	}
	
    I[1][3]=1.0;
    O[1][3]=I[1][3];

   for(l = 0; l < 3; l++){
    	I[2][l]=0.0;
    	for(j = 0; j< 4; j++){
    			I[2][l] +=  w2[j][l]*O[1][j];
		}
		O[2][l]=1.0 / (1.0 + exp(-I[2][l]));
	}
	//-----backpropagation----------------------
	
	for(l = 0; l < 3; l++){
		d2[l]=(t[l][cs]-O[2][l])*O[2][l]*(1.0-O[2][l]);
	}
	
	for(j = 0; j < 3; j++){
		d1[j]=0.0;
		for(l = 0; l < 3; l++){
		d1[j]+=d2[l]*w2[j][l];
	}
		d1[j]=O[1][j]*(1.0-O[1][j])*d1[j];
	}
	
	
	//d1[0]=O[1][0]*(1.0-O[1][0])*(d2[0]*w2[0][0]+d2[1]*w2[0][1]+d2[2]*w2[0][2]);
	//d1[1]=O[1][1]*(1.0-O[1][1])*(d2[0]*w2[1][0]+d2[1]*w2[1][1]+d2[2]*w2[1][2]);
	//d1[2]=O[1][2]*(1.0-O[1][2])*(d2[0]*w2[2][0]+d2[1]*w2[2][1]+d2[2]*w2[2][2]);

	
//-------------------------------------------------	
for(l=0;l<3;l++){
for(j=0;j<4;j++){
nw2[j][l]= w2[j][l]+0.5*d2[l]*O[1][j]+0.5*vw2[j][l];
vw2[j][l]=nw2[j][l]-w2[j][l];
 w2[j][l]=nw2[j][l];
}
}

//-------------------------------------------------
for(j=0;j<3;j++){
for(i=0;i<5;i++){
nw1[i][j]= w1[i][j]+0.5*d1[j]*O[0][i]+0.5*vw1[i][j];
vw1[i][j]=nw1[i][j]-w1[i][j];
 w1[i][j]=nw1[i][j];
}
}
	
	//------------------------------------------
    for(l=0;l<3;l++){
		erro+=(t[l][cs]-O[2][l])*(t[l][cs]-O[2][l]);
	}
}//close for n

	erro=erro/600.0;
    printf("%f \n",erro );

    }while(erro>0.0001);
    
    	for(j = 0; j < 3; j++){
    		for(i = 0; i< 5; i++){
    			printf("w1[%d][%d]=%f; \n",i,j,w1[i][j]);
			}
		}
    	for(l = 0; l < 3; l++){
    		for(j = 0; j< 4; j++){
    			printf("w2[%d][%d]=%f; \n",j,l,w2[j][l]);
			}
		}
		
	
	
return 0;	
}
