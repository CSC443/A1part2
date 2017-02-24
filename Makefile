CC = gcc
CFLAGS = -O3 -Wall 
CFLAGS += -D_LARGEFILE_SOURCE
CFLAGS += -fno-exceptions
CFLAGS += -funroll-loops
CFLAGS += -D_FILE_OFFSET_BITS=64

# Source files
MERGE_EXTERNAL = record.c merge_external.c
DISK_SORT = merge_external.c record.c disk_sort.c
DISTRIBUTION = distribution.c record.c
# Binaries
all: disk_sort merge_external distribution

#sequential writing in blocks
disk_sort: ${DISK_SORT}
	$(CC) $(CFLAGS) $^ -o disk_sort
merge_external: ${DISK_SORT}
	$(CC) $(CFLAGS) $^ -o merge_external
distribution: ${DISTRIBUTION}
	$(CC) $(CFLAGS) $^ -o distribution


clean:  
	rm disk_sort merge_external distribution
