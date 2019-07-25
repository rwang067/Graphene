# # !/bin/bash

sudo su
echo 102400 > /proc/sys/vm/nr_hugepages

    # 2019.7.12
    echo "2019.7.12 compare with Graphene SSD 64GB R730" >> Graphene_runtimes.statistics 

## Friendster   
    echo "app = RandomWalkDomination, dataset = Friendster from echo" >> Graphene_runtimes.statistics 
    echo "R = 1×N, L = 6, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        free -m
        sync; echo 1 > /proc/sys/vm/drop_caches
        free -m
        ./bin/apps/rwdomination 1 1 2 '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' out.friendster-reorder-split_beg out.friendster-reorder-split_csr 512 33554432 4 32 16 128 1 6
   done

    echo "app = Graphlet, dataset = Friendster from echo" >> Graphene_runtimes.statistics 
    echo "R = 100000, L = 4, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        free -m
        sync; echo 1 > /proc/sys/vm/drop_caches
        free -m
        ./bin/apps/graphlet 1 1 2 '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' out.friendster-reorder-split_beg out.friendster-reorder-split_csr 512 33554432 4 32 16 128 100000 4
   done

    echo "app = PersonalizedPageRank, dataset = Friendster from echo" >> Graphene_runtimes.statistics 
    echo "R = 1000, L = 10, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        free -m
        sync; echo 1 > /proc/sys/vm/drop_caches
        free -m
        ./bin/apps/personalizedpagerank 1 1 2 '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' out.friendster-reorder-split_beg out.friendster-reorder-split_csr 512 33554432 4 32 16 128 13 2000 10
   done

    echo "app = SimRank, dataset = Friendster from echo" >> Graphene_runtimes.statistics 
    echo "R = 2000, L = 11, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        free -m
        sync; echo 1 > /proc/sys/vm/drop_caches
        free -m
        ./bin/apps/simrank 1 1 2 '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' out.friendster-reorder-split_beg out.friendster-reorder-split_csr 512 33554432 4 32 16 128 12 13 1000 11
    done

    ## Yahoo ####################################################################################################################################################################################################  
    echo "app = RandomWalkDomination, dataset = Yahoo from echo" >> Graphene_runtimes.statistics 
    echo "R = 1×N, L = 6, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        free -m
        sync; echo 1 > /proc/sys/vm/drop_caches
        free -m
        ./bin/apps/rwdomination 1 1 2 '/home/wang/raid0_defghij/Yahoo/yahoo-webmap.txt_Graphene/' '/home/wang/raid0_defghij/Yahoo/yahoo-webmap.txt_Graphene/' yahoo-webmap.txt-split_beg yahoo-webmap.txt-split_csr 512 33554432 4 32 16 128 1 6
   done

    echo "app = Graphlet, dataset = Yahoo from echo" >> Graphene_runtimes.statistics 
    echo "R = 100000, L = 4, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        free -m
        sync; echo 1 > /proc/sys/vm/drop_caches
        free -m
        ./bin/apps/graphlet 1 1 2 '/home/wang/raid0_defghij/Yahoo/yahoo-webmap.txt_Graphene/' '/home/wang/raid0_defghij/Yahoo/yahoo-webmap.txt_Graphene/' yahoo-webmap.txt-split_beg yahoo-webmap.txt-split_csr 512 33554432 4 32 16 128 100000 4
   done

    echo "app = PersonalizedPageRank, dataset = Yahoo from echo" >> Graphene_runtimes.statistics 
    echo "R = 1000, L = 10, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        free -m
        sync; echo 1 > /proc/sys/vm/drop_caches
        free -m
        ./bin/apps/personalizedpagerank 1 1 2 '/home/wang/raid0_defghij/Yahoo/yahoo-webmap.txt_Graphene/' '/home/wang/raid0_defghij/Yahoo/yahoo-webmap.txt_Graphene/' yahoo-webmap.txt-split_beg yahoo-webmap.txt-split_csr 512 33554432 4 32 16 128 9 2000 10
   done

    echo "app = SimRank, dataset = Yahoo from echo" >> Graphene_runtimes.statistics 
    echo "R = 2000, L = 11, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        free -m
        sync; echo 1 > /proc/sys/vm/drop_caches
        free -m
        ./bin/apps/simrank 1 1 2 '/home/wang/raid0_defghij/Yahoo/yahoo-webmap.txt_Graphene/' '/home/wang/raid0_defghij/Yahoo/yahoo-webmap.txt_Graphene/' yahoo-webmap.txt-split_beg yahoo-webmap.txt-split_csr 512 33554432 4 32 16 128 4 9 1000 11
    done

echo 102400 > /proc/sys/vm/nr_hugepages

./bin/apps/rawrandomwalks 1 1 2 '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' out.friendster-reorder-split_beg out.friendster-reorder-split_csr 512 33554432 4 32 16 128 100000 4

echo 0 > /proc/sys/vm/nr_hugepages

cat /proc/sys/vm/nr_hugepages
