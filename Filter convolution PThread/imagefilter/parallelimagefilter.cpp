#include<iostream>
#include<stdio.h>
#include<pthread.h>
#include<cstdlib>
#include <sys/time.h>
using namespace std;
int flag_file=1;
int no_of_thread;
int * * image2D;
int  mask2D[3][3];
int rows_to_store_in ;
int **  newimage;
int imagedimension[2];
FILE * storeImg;
double GetWallTime() {
struct timeval tp;
int rtn = gettimeofday(&tp, NULL);
return ((double) tp.tv_sec + (1.e-6)*tp.tv_usec);
}
void * applyFilter(void * rank)
{
    
    int myrank = *((int *) rank)-1;
    cout<<"my rank is = " <<myrank;
     int start_at ;
     int end_at;
    if((rows_to_store_in%no_of_thread)==0)
    {
         start_at = myrank * (rows_to_store_in/no_of_thread);
          end_at = start_at+ (rows_to_store_in/no_of_thread);
    }else
    {
        if(myrank<no_of_thread-1)
        {
            start_at = myrank * ((rows_to_store_in-(rows_to_store_in%no_of_thread))/(no_of_thread));
            end_at = start_at+ (rows_to_store_in-(rows_to_store_in%no_of_thread))/(no_of_thread);
        }
        else if(myrank==no_of_thread-1)
        {
             start_at =  myrank * ((rows_to_store_in-(rows_to_store_in%no_of_thread))/(no_of_thread));
            end_at = start_at+ (rows_to_store_in-(rows_to_store_in%no_of_thread))/(no_of_thread) + ((rows_to_store_in%no_of_thread));
        }
    }
    cout<<" my start = "<<start_at<<" my end = "<<end_at<<endl; 
    int summation =0;
    int row,col;
    for(int i=start_at;i<end_at&& (i+2)<imagedimension[0];)
        {
             row =i;
            for(int j=0;j<imagedimension[1]&&(j+2)<imagedimension[1];row=row-3)
            {
               col=j;
                for(int maskr = 0 ;maskr<3;maskr++,row++,col=col-3)
                {
                    for(int maskc = 0; maskc<3;maskc++,col++)
                    {
                        
                        summation += image2D[row][col] * mask2D[maskr][maskc] ;

                    }
                }
                if(flag_file==0)
                summation = summation/16;
                newimage[i+1][j+1]=summation;
                summation=0;
                j++;
            }
            i++;
        }
     
   
    return NULL;
}
int main(int argc,char ** argv)
{
      if(argc>=3){
    double start = GetWallTime();
    char * image = argv[1];
    char * mask = argv[2];
    char * newImg = argv[3];
    
    FILE * readImg = fopen(image,"r+");
    FILE * readMask = fopen(mask,"r+");
    storeImg = fopen(newImg,"w+");
    cout<<1<<endl;
    fscanf(readImg,"%d %d",&imagedimension[0],&imagedimension[1]);
    cout<<2<<endl;
   	image2D = new int *[imagedimension[0]];
		newimage = new  int *[imagedimension[0]];
		cout << imagedimension[0] << " " << imagedimension[1] << endl;
		for (int i = 0; i < imagedimension[0]; i++) {
			image2D[i] = new int[imagedimension[1]];
			newimage[i] = new int[imagedimension[1]];
		}
    cout<< " dimension is = "<<imagedimension[0] << "  "<<imagedimension[1]<<endl;
   for (int i = 0; i < imagedimension[0]; i++) {
			for (int j = 0; j < imagedimension[1]; j++) {
				fscanf(readImg, "%d", &image2D[i][j]);
				newimage[i][j] = image2D[i][j];
			}
		}
    int maskrow = 0 , maskcol = 0;
    while(!feof(readMask))
    {
        if(maskcol<3 && maskrow<3){
            fscanf(readMask,"%d",&mask2D[maskrow][maskcol]);
            maskcol++;
            }
            else if(maskrow>3)
                break;
                else
                {
                    maskrow++;
                    maskcol=0;
                }
                
    }
    rows_to_store_in = imagedimension[0];
    
    if(rows_to_store_in<4)
    {
        no_of_thread=rows_to_store_in;
    }
    else
    {
        no_of_thread = 4;
    }
    
    pthread_t * threads;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    threads = new pthread_t[no_of_thread] ;
    int rc , thread_no;
    for (thread_no = 0; thread_no < no_of_thread; thread_no++)
    {
        cout<< " main() creating thread, "<<thread_no<<endl;
        rc = pthread_create(&threads[thread_no], &attr, applyFilter, (void *)&thread_no);
            if(rc)
            {
                cout<< " unable to create thread "<<rc<<endl;
                exit(-1);
            }
    }
    
    for(int j=0;j<no_of_thread;j++)
        pthread_join(threads[j],NULL);

           for(int i=0;i<imagedimension[0];i++)
        {
            for(int j=0;j<imagedimension[1];j++)
                fprintf(storeImg,"%d %c",newimage[i][j],' ');
                fprintf(storeImg,"%c",'\n');
        }
    
          fclose(readImg);
            double finish = GetWallTime();
		    cout << "Elapsed time = "<< finish - start << endl;
    }
   
   }
