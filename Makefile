CC = gcc
CFLAGS = -O3 -Wall 
CFLAGS += -D_LARGEFILE_SOURCE
CFLAGS += -fno-exceptions
CFLAGS += -funroll-loops
CFLAGS += -D_FILE_OFFSET_BITS=64

# Source files
WRITE_BLOCKS_SRC=record.c write_blocks_seq.c 
READ_BLOCKS_SRC= record.c read_blocks_seq.c
WRITE_LINES = record.c write_lines.c
READ_RAM_SRC = record.c read_ram_seq.c
READ_BLOCKS_RAND= record.c read_blocks_rand.c
READ_RAM_RAND= record.c read_ram_rand.c
WRITE_BLOCKS_RAND= record.c write_blocks_rand.c
WRITE_RAM_RAND= record.c write_ram_rand.c
MERGE_EXTERNAL = record.c merge_external.c
DISK_SORT = merge_external.c record.c disk_sort.c
DISTRIBUTION = distribution.c record.c
# Binaries
all:write_blocks_seq read_blocks_seq disk_sort merge_external distribution

#sequential writing in blocks
write_blocks_seq: $(WRITE_BLOCKS_SRC)
	$(CC) $(CFLAGS) $^ -o write_blocks_seq
read_blocks_seq: $(READ_BLOCKS_SRC)
	$(CC) $(CFLAGS) $^ -o read_blocks_seq
disk_sort: ${DISK_SORT}
	$(CC) $(CFLAGS) $^ -o disk_sort
merge_external: ${DISK_SORT}
	$(CC) $(CFLAGS) $^ -o merge_external
distribution: ${DISTRIBUTION}
	$(CC) $(CFLAGS) $^ -o distribution


clean:  
	rm write_blocks_seq disk_sort read_blocks_seq merge_external distribution
