#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
  srand48(time(NULL));
  double b_b=0.2497;
  double b_d=5.16;
  double a_d=0.3105;
  double a_h=64.3;
  FILE* datos;
  FILE* escritura;
  datos=fopen("RadialVelocities.dat","r");
  escritura=fopen("CurvaRotacion.txt","w");
  int linea;
  float num;
  float num2;
  int dim=300;
  double  * pos = (double *)malloc(dim*sizeof(double));
  double  * vel = (double *)malloc(dim*sizeof(double));

  int n=-1;
  double media=0;
   do{
     
     if(n!=-1)
     {

        linea=fscanf(datos,"%f %f\n", &num,&num2);
        pos[n]=num;
        vel[n]=num2;
        media+=num2/300.0;
        // printf("%f %f\n",pos[n],vel[n]);
     }
     else
       {
         fscanf(datos, "%*[^\n]\n", NULL);
       }
      
   
   n+=1;
   }while(linea!=EOF);
   int l;
   float var;
   // for(l=0;l<300;l++)
   // {
   //   var+=pow(vel[l]-media,2.0)/300.0;
   //  }
    float x[1000];
  float y[1000];
  //float modelo[2000];
  float likelihood[2000];
  float likelihoodprima[2000];
  float b1[2000];
  float b2[2000];
  float b3[2000];
  float yini[300];
  float yprima[300];
  int i=0;
  int j=0;
  for(i=0;i<1000;i++)
    {
     
      x[i]=(float)(rand()%100);
    }
  for(j=0;j<1000;j++)
	{
          y[j]=(float)(rand()%100);
	}
  b1[0]=drand48();
  b2[0]=drand48();
  b3[0]=drand48();
  float a1[300];
  float a2[300];
  float a3[300];
  float vari[300];
   for(i=0;i<300;i++)
     {
       a1[i]=1.0/(pow(pow(pos[i],2.0)+pow(b_b,2.0),0.75));
       a2[i]=1.0/(pow(pow(pos[i],2.0)+pow(b_d+a_d,2.0),0.75));
       a3[i]=1.0/(pow(pow(pos[i],2.0)+pow(a_h*1.0,2.0),0.25));
	  yini[i]=pos[i]*(b1[0]*a1[i]+b2[0]*a2[i])+b3[0]*a3[i];
	  // printf("%f %f\n",yini[i],vel[i]);
	  // vari[i]=(y
     }
  
   for(i=0;i<300;i++)
     {
       likelihood[0]+=pow(vel[i]-yini[i],2.0);
     }
   // printf("%f",likelihood[0]);
   // printf("%f\n",exp(-likelihood[0]/var));
   likelihood[0]=exp(-likelihood[0]/10000.0);
   //printf("%f %f %f\n",b1[0],b2[0],b3[0]);
   float b1prima;
   float b2prima;
   float b3prima;
   float lmax=likelihood[0];

   //srand48(time(NULL));
   //printf("%f\n",lmax);
   int argmax=0;
    for(j=0;j<2000;j++)
     { 
       if(j<1999)
	 {
	   b1prima=sqrt(-log(1-drand48())*2*0.1)*cos(drand48())+b1[j];
	   b2prima=sqrt(-log(1-drand48())*2*0.1)*cos(drand48())+b2[j];
           b3prima=sqrt(-log(1-drand48())*2*0.1)*cos(drand48())+b3[j];
           //printf("%f %f %f\n",b1prima,b2prima,b3prima);
        for(i=0;i<300;i++)
        {
           yini[i]=pos[i]*(b1[j]*a1[i]+b2[j]*a2[i])+b3[j]*a3[i];
           yprima[i]=pos[i]*(b1prima*a1[i]+b2prima*a2[i])+b3prima*a3[i];
           likelihood[j]+=pow(vel[i]-yini[i],2.0)/10000.0;
           likelihoodprima[j]+=pow(vel[i]-yprima[i],2.0)/10000.0;
        }
        likelihood[j]=exp(-likelihood[j]);
        //printf("%f\n",likelihoodprima[j]);
        likelihoodprima[j]=exp(-likelihoodprima[j]);
        float alpha=likelihoodprima[j]/likelihood[j];
        //printf("%f",likelihood[j]);
        if(alpha>1.0)
	  {
            likelihood[j+1]=likelihoodprima[j];
            b1[j+1]=b1prima;
            b2[j+1]=b2prima;
            b3[j+1]=b3prima;
          }
        else
	  {
	    double beta=drand48();
	      if(beta<=alpha)
		{
		  likelihood[j+1]=likelihoodprima[j];
                  b1[j+1]=b1prima;
                  b2[j+1]=b2prima;
                  b3[j+1]=b3prima;
		}
              else
		{
                  likelihood[j+1]=likelihood[j];
                  b1[j+1]=b1[j];
                  b2[j+1]=b2[j];
                  b3[j+1]=b3[j];
		}
	  }
	 }
	if(lmax<likelihood[j])
	  {
	    lmax=likelihood[j];
            argmax=j;
	  }
	 
     }
    printf("%f %f %f\n",pow(b1[argmax],2.0),pow(b2[argmax],2.0),pow(b3[argmax],2.0));
    fprintf(escritura,"%f %f %f\n",pow(b1[argmax],2.0),pow(b2[argmax],2.0),pow(b3[argmax],2.0));
    //printf("%d\n",argmax);
    // for(i=0;i<300;i++)
    // {
    //	printf("%f %f\n",pos[i]*(b1[argmax]*a1[i]+b2[argmax]*a2[i])+b3[argmax]*a3[i],vel[i]);
    //    printf("%d\n",argmax);
    //  }
    
}
