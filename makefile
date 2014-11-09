end: assign2 assign1 clean
assign2:test_assign2_2.o dberror.o storage_mgr.o buffer_mgr.o linked_list.o buffer_mgr_stat.o
	gcc test_assign2_2.o dberror.o storage_mgr.o buffer_mgr.o linked_list.o buffer_mgr_stat.o -o assign2 -pthread
assign1:test_assign2_1.o dberror.o storage_mgr.o buffer_mgr.o linked_list.o buffer_mgr_stat.o
	gcc test_assign2_1.o dberror.o storage_mgr.o buffer_mgr.o linked_list.o buffer_mgr_stat.o -o assign1
test_assign2_2.o :test_assign2_2.c test_helper.h dberror.h storage_mgr.h buffer_mgr.h linked_list.h buffer_mgr_stat.h
		gcc -c test_assign2_2.c 
test_assign2_1.o :test_assign2_1.c test_helper.h dberror.h storage_mgr.h buffer_mgr.h linked_list.h buffer_mgr_stat.h
		gcc -c test_assign2_1.c 
dberror.o:dberror.c dberror.h
	gcc -c dberror.c
storage_mgr.o:storage_mgr.c storage_mgr.h dberror.h
	gcc -c storage_mgr.c
buffer_mgr.o:buffer_mgr.c buffer_mgr.h
	gcc -c buffer_mgr.c
linked_list.o:linked_list.c linked_list.h
	gcc -c linked_list.c
buffer_mgr_stat.o:buffer_mgr_stat.c buffer_mgr_stat.h
	gcc -c buffer_mgr_stat.c
clean:
	-rm -rf *.o 
