#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "record.h"

/**
* Compares two records a and b 
* with respect to the value of the integer field f.
* Returns an integer which indicates relative order: 
* positive: record a > record b
* negative: record a < record b
* zero: equal records
*/
int compare (const void *a, const void *b) {
 int a_uid2 = ((const struct record*)a)->uid2;
 int b_uid2= ((const struct record*)b)->uid2;
 return (a_uid2 - b_uid2);
}

int main(int argc, char *atgv[]){
 	printf("start disk_sort\n");
 	//FILE *fp_write;
 	FILE *fp_read;
    int block_size = atoi(atgv[3]);
    int mem = atoi(atgv[2]);
    
    int block_num= (mem/block_size);
    printf("%d,%d\n", mem,block_size);
    printf("This is block_num %d\n",block_num);
    printf("this is b num:%d\n",1024*1024*200/1024 );
    int num_records = mem / sizeof(Record);
	if (!(fp_read = fopen (atgv[1] , "rb" ))){
		return -1;
	}

	//fp_write = fopen("sorted.dat", "wb");
	// if(fp_write == NULL){
	// 	perror("Error opening file");
	// 	return -1;
	// }	

	// find file size
    fseek(fp_read, 0L, SEEK_END);
	int file_size = ftell(fp_read);

	int total_records = file_size/sizeof(Record);
    int records_per_block = block_size/sizeof(Record);
 
	int chunk_num = file_size/(block_num*block_size); 
    
    int last_chunk_size = file_size - chunk_num*(block_num*block_size);
    int records_per_chunk = records_per_block*block_num;
    int records_last_chunk = last_chunk_size/sizeof(Record);
	//set pointe to the begining of the file
	fseek(fp_read, 0L, SEEK_SET);
    int run = 0;
    printf("chunk num is %d,block num per chunk  is %d, last_chunk_size is %d\n",chunk_num,block_num,last_chunk_size);

    //fp_write = fopen("sroted_chunks.dat", "wb");
    //FILE *fp_write;
    while (run < chunk_num+1){
    	printf("1 \n");
    	FILE *fp_write;
    	printf("2 \n");
    	char k[2];
    	printf("3 \n");
		sprintf(k,"%d",run);
		printf("4 \n");
		char * filename = (char *) calloc(20,sizeof(char));
		printf("%s\n",filename );
		printf("5 \n");
		strcat(filename,"sorted");
		printf("6 \n");
		strcat(filename,k);
		printf("7 \n");
		strcat(filename,".dat");
		printf("8 \n");
		printf("%s\n",filename );
		//printf("%s\n",strcat(strcat("sorted",k), ".dat") );
		fp_write = fopen( filename, "wb");
		if(fp_write == NULL){
	 	perror("Error opening file");
	 	return -1;
	    }	
        if (run == chunk_num) {
        	if (last_chunk_size== 0){
                   break;

        	}else{
        		Record * buffer = (Record *) calloc (records_last_chunk, sizeof (Record));
        		fread (buffer, sizeof(Record), records_last_chunk, fp_read);
				qsort (buffer, records_last_chunk, sizeof(Record), compare);
				fwrite(buffer, sizeof(Record), records_last_chunk, fp_write);
				fflush (fp_write);
                free (buffer);
        	}            
        }
        else{
		Record * buffer = (Record *) calloc (records_per_chunk, sizeof (Record));
		printf("run 1 is %d\n", run );
		fread (buffer, sizeof(Record), records_per_chunk, fp_read);
		
		qsort (buffer, records_per_chunk, sizeof(Record), compare);
		fwrite(buffer, sizeof(Record), records_per_chunk, fp_write);
		fflush (fp_write);

		//printf("run is %d\n",run)
		free(buffer);
		
	   }
	   free(filename);
	   fclose(fp_write);
	   //free (buffer);
	   //free(buffer);
	   run++; 
	//	int pointer = 0;
	// while(pointer < num_records){
	// 		printf("%d , %d\n" , buffer[pointer].uid1,buffer[pointer].uid2);
	// 		pointer++;
	// 	}
	//fwrite(buffer, sizeof(Record), num_records, stdout);
   }
   fclose(fp_read);
   
 }

 int mm_sorting(char *filename,int size) {
      int num_records = size / sizeof(Record) ; 
      FILE *fp_read;
      if (!(fp_read = fopen ( filename, "rb" ))){
		return -1;
	}

	Record * buffer = (Record *) calloc (num_records, sizeof (Record));
	fread (buffer, sizeof(Record), num_records, fp_read);
	qsort (buffer, num_records, sizeof(Record), compare);
	int pointer = 0;
	while(pointer < num_records){
			printf("%d , %d\n" , buffer[pointer].uid1,buffer[pointer].uid2);
			pointer++;
		}
	//fwrite(buffer, sizeof(Record), num_records, stdout);

	fclose (fp_read);
	free (buffer);
    return 0 ;
 }
