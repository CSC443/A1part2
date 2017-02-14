#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "record.h"
#include "merge.h"

int merge_sort(int buffer_num, int mem, int block_size);
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

	// find file size
    fseek(fp_read, 0L, SEEK_END);
	int file_size = ftell(fp_read);
	printf("file size %d\n", file_size);

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
    
    while (run < chunk_num+1){
    	FILE *fp_write;
    	char k[2];
		sprintf(k,"%d",run);
		char * filename = (char *) calloc(20,sizeof(char));
		printf("%s\n",filename );
		strcat(filename,"sorted");
		strcat(filename,k);
		strcat(filename,".dat");
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

		free(buffer);
		
	   }
	   free(filename);
	   fclose(fp_write);

	   run++; 

   }
   fclose(fp_read);
   merge_sort(chunk_num + 1, mem, block_size);
   return 0;
   
 }

 int merge_sort(int buffer_num, int mem, int block_size){
 	MergeManager * manager = (MergeManager *)calloc(1, sizeof(MergeManager));

 	int records_per_block  = block_size/sizeof(Record);
 	int records_per_mem = mem/sizeof(Record);
 	int records_per_buffer = records_per_mem / buffer_num + 1;


 	manager->heap_capacity = buffer_num;
 	manager->heap = (HeapElement *)calloc(buffer_num, sizeof(HeapElement));
 	strcpy(manager->output_file_name , "sorted_merge.dat");
 	strcpy(manager->input_prefix, "sorted");
 	manager->output_buffer_capacity = records_per_buffer;
 	manager->input_buffer_capacity = records_per_buffer;
 	
 	int input_file_numbers[buffer_num];
 	int current_input_file_positions[buffer_num];
 	int current_input_buffer_positions[buffer_num];
 	int total_input_buffer_elements[buffer_num];
 	Record** input_buffers = malloc(buffer_num * sizeof(Record *));
 	for(int i = 0; i < buffer_num; i++){
 		input_file_numbers[i] = i;
 		current_input_file_positions[i] = 0;
 		current_input_buffer_positions[i] = 0;
 		total_input_buffer_elements[i] = 0;
 		input_buffers[i] = (Record *)calloc(records_per_buffer, sizeof(Record));
 	}	
 	manager->input_file_numbers = input_file_numbers;
 	manager->output_buffer = (Record *)calloc(records_per_buffer, sizeof(Record));
 	manager->current_output_buffer_position = 0;
 	manager->input_buffers = input_buffers;
 	manager->current_input_file_positions = current_input_file_positions;
 	manager->current_input_buffer_positions = current_input_buffer_positions;
 	manager->total_input_buffer_elements = total_input_buffer_elements;
 	merge_runs(manager);
 	return 0;
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
