exe = aio_randomwalks.bin

cc = "$(shell which g++)" 
# cc = "$(shell which g++ -std=c1x)" 
cucc= "$(shell which nvcc)"


#cuflags= -gencode=arch=compute_35,code=\"sm_35,compute_35\"  -Xptxas -v -Xcudafe -\# -Xptxas -abi=no -m64 -I"/usr/local/cuda/bin/../include" -I. -I../../../ -I../../../b40c -O3 -D_FORCE_INLINES
# flags = -I../../lib/ -I. -laio -fopenmp -O3 -g
flags = -I../../lib/ -I. -laio -fopenmp -O0 -g -w

flags+=-DKV_BOTH_SORTING -DBLK_SZ=512 
ifeq ($(time), 1)
  cuflags+= -DTIMING
	flags += -DTIMING
endif

ifeq ($(profile),1)
	cuflags+=-DPROFILE
	flags+=-DPROFILE
endif

objs = $(patsubst %.cpp,%.o,$(wildcard ../../lib/*.cpp)) \
		$(patsubst %.cu,%.o,$(wildcard ../../lib/*.cu)) \
		$(patsubst %.cpp,%.o,$(wildcard $@.cpp))

deps =	$(wildcard ../../lib/*.h) \
				$(wildcard ../../lib/*.cuh) \
				$(wildcard *.h) \
				$(wildcard *.cuh) \
				Makefile

#flags+=-L$(shell dirname $(cucc))/../lib64 -lcuda -lcudart
apps: apps/rwdomination apps/graphlet apps/personalizedpagerank apps/simrank apps/rawrandomwalks 

apps/% : apps/%.o $(objs) 
	@mkdir -p bin/$(@D)
	$(cc) $(objs) -o bin/$@ $(flags)

%.o:%.cpp $(deps)
	$(cc) -c $< -o $@ $(flags)

# %.o:%.cpp $(deps)
# 	$(cc) -c $< -o $@ $(flags)

# %.o:%.cu $(deps)
# 	$(cucc) -c $< -o $@ $(cuflags)

# $(exe):$(objs)
# 	$(cc) $(objs) -o $(exe) $(flags)

testp:apps/pagerank
	./aio_randomwalks.bin 1 1 2 ../../../converter/LJ ../../../converter/LJ soc-LiveJournal1.txt-split_beg soc-LiveJournal1.txt-split_csr 8 20971520 4 32 16 128 1 2

clean:
	@rm -rf bin/*

