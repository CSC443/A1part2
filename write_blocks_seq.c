#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "record.h"

 int main(int argc, char *atgv[]){
 	printf("start\n");
 	csv_to_record(atgv[1], atgv[2]);
 	return 0;
 }
