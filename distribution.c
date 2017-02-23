#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h"

int main(int argc, char *atgv[]){
	
	char* read_filename = atgv[1];
	int block_size = atoi(atgv[2]);
	char* col_id = atgv[3];
	int max_deg = atoi(atgv[4]);
	int results[max_deg + 1];
	int j;
	for(j = 0; j <= max_deg; j ++){
		results[j] = 0;
	}

	int records_per_block = block_size / sizeof(Record);
	FILE *fp_read;
	FILE *fp_write;
	/* allocate buffer for 1 block */
	Record * buffer = (Record *) calloc (records_per_block, sizeof (Record)) ;
	
	if (!(fp_read = fopen (read_filename , "rb" ))){
		return -1;
	}
	if(strcmp(col_id, "UID1") == 0){
		if (!(fp_write = fopen ("megered.txt" , "wb" ))){
			return -1;
		}
	}else if(strcmp(col_id, "UID2") == 0){
		if (!(fp_write = fopen ("megered2.txt" , "wb" ))){
			return -1;
		}
	}
	

	int result = 0;
	
	int current_id = -1;
	int count = 0;
	while((result = fread (buffer, sizeof(Record), records_per_block, fp_read)) > 0){
		int pointer = 0;
		records_per_block = block_size/sizeof(Record);
		//Check if the total number of records read from file is less than one block 
		if (result!=records_per_block){
			records_per_block = result;
		}

		while(pointer < records_per_block){
			//printf("uid1:%d,uid2:%d\n", buffer[pointer].uid1 , buffer[pointer].uid2);
			if(strcmp(col_id, "UID1") == 0){
				if(current_id == -1){
					current_id = buffer[pointer].uid1;
				}
				if(current_id != buffer[pointer].uid1){
					results[count]++;
					count = 0;
					current_id = buffer[pointer].uid1;	
				}
			}else if(strcmp(col_id, "UID2") == 0){
				if(current_id == -1){
					current_id = buffer[pointer].uid2;
				}
				if(current_id != buffer[pointer].uid2){
					results[count]++;
					count = 0;
					current_id = buffer[pointer].uid2;	
				}
				
			}
			count++;	
			pointer++;
		
		}
			
	}
	results[count]++;
	int k = 0;
	for(k = 0; k <= max_deg; k++){
		if(results[k] != 0){
			fprintf(fp_write, "%d, %d\n", k, results[k]);
		}
	}	
	fclose(fp_read);
	fclose(fp_write);
	free(buffer);
	return 0;
}

