
echo $(gcc -Wall -c helpers/src/init.c && gcc -Wall -c helpers/src/ll_operations.c && gcc -Wall -c serial_linked_list.c && gcc -o out helpers/src/init.c helpers/src/ll_operations.c serial_linked_list.c -lm && ./out)
    
echo $(gcc -Wall -c helpers/src/init.c && gcc -Wall -c helpers/src/ll_operations.c && gcc -Wall -c one_mutex_linked_list.c && gcc -o out helpers/src/init.c helpers/src/ll_operations.c one_mutex_linked_list.c -lm -lpthread && ./out)

echo $(gcc -Wall -c helpers/src/init.c && gcc -Wall -c helpers/src/ll_operations.c && gcc -Wall -c rw_lock_linked_list.c && gcc -o out helpers/src/init.c helpers/src/ll_operations.c rw_lock_linked_list.c -lm -lpthread && ./out)