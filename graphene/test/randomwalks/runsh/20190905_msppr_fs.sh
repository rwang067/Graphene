# !/bin/bash
    
    echo 10240 > /proc/sys/vm/nr_hugepages

    echo "\n\n########################################################" >> Graphene_runtimes.statistics 
    echo "2019.9.5 compare with Graphene/GraFSoft by msppr in Friendster in SSD 64GB R730" >> Graphene_runtimes.statistics
    echo "MSPPR from echo, 2000*10 walks for each source, numsources from 10^0 to 10^7"  >> Graphene_runtimes.statistics
    ## Graphlet
    echo "app = MSPPR, dataset = Friendster from echo" >> Graphene_runtimes.statistics
    for(( numsources = 1; numsources <= 10000000; numsources*=10))
    do
        echo "numsources = " $numsources ", fixed 2000*10 walks for each soource from echo" >> Graphene_runtimes.statistics
        for(( times = 0; times < 5; times++))
        do
            echo "times = " $times " from echo"
            free -m
            sync; echo 1 > /proc/sys/vm/drop_caches
            free -m
            ./bin/apps/personalizedpagerank 1 1 2 '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' out.friendster-reorder-split_beg out.friendster-reorder-split_csr 64 33554432 4 32 16 128 4 $numsources
        done
    done

    echo 0 > /proc/sys/vm/nr_hugepages

    # echo 102400 > /proc/sys/vm/nr_hugepages

    # ./bin/apps/rawrandomwalks 1 1 2 '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' out.friendster-reorder-split_beg out.friendster-reorder-split_csr 64 33554432 4 32 16 128 100000 4

    # cat /proc/sys/vm/nr_hugepages
