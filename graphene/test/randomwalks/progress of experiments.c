progress of experiments:

2018.4.20 : new randomwalks 
	 problem ： as for the memmap:can not allocate memory problem:
	 solution :     sudo su 
	            	echo 10240 > /proc/sys/vm/nr_hugepages

	problem : ‘MAP_HUGE_2MB’ was not declared in this scope
	solution : Add `#define MAP_HUGE_2MB (21 << MAP_HUGE_SHIFT)` into /usr/include/x86_64-linux-gnu/asm/mman.h
	1. sudo vim /usr/include/x86_64-linux-gnu/asm/mman.h
	2. add the `#define MAP_HUGE_2MB (21 << MAP_HUGE_SHIFT)`, follow the `#define MAP_32BIT`

	--> endless loop for selective load_key(level) (line-275),
	      fine for load_kv_vert_full(level)(line 276)
	      analysis : in load_key function {
	      						get_chunk();
	      						load_chunk(); //获取空闲的chunk,提交到IO请求，占用circ_free_chunk()
	      						get_chunk(); //获取提交的IO请求，添加到circ_load_chunk()
	      						load_chunk();
	      					}


2018.5.28 - 2018.5.31 : gdb调试graphene
1、终端命令 (跑N×1*6的random walks)：
     -> cd  ** /Graphene-master/graphene/test/randomwalks
     -> gdb ./aio_randomwalks.bin
     -> set args 1 1 2 '/home/wang/Documents/graph processing system/Graphene-master/converter/LJ' '/home/wang/Documents/graph processing system/Graphene-master/converter/LJ' soc-LiveJournal1.txt-split_beg soc-LiveJournal1.txt-split_csr 8 20971520 4 32 16 128 1 2

2、输入参数
	-- /path/to/exe = ./aio_randomwalks.bin
	-- #row_partitions = 1
	-- #col_partitions = 1
	-- thread_count = 2
	-- /path/to/beg_pos_dir = '/home/wang/Documents/graph processing system/Graphene-master/converter/LJ'
	-- /path/to/csr_dir = '/home/wang/Documents/graph processing system/Graphene-master/converter/LJ'
	-- beg_header = soc-LiveJournal1.txt-split_beg
	-- csr_header = soc-LiveJournal1.txt-split_csr
	-- num_chunks = 8
	-- chunk_sz (#bytes) = 20971520    (20M)
	-- concurr_IO_ctx = 4 = io_limit
	-- max_continuous_useless_blk = 32 = MAX_USELESS
	-- ring_vert_count = 16
	-- num_buffs = 32
	-- num_walks = 1
	-- num_steps = 6

3、跟踪程序
	-- randomwalks.cpp
	-- main(line 63)
	--{
		-- sa_t *sa_curr=NULL; //当前iteration节点的值（walks数量） --> mmap 2MB大页
		-- sa_t *sa_next=NULL;  //下一轮iteration节点的值（walks数量）  --> mmap 2MB大页
		-- vertex_t **front_queue_ptr;
			-- front_queue_ptr = new vertex_t*[num_rows * num_cols];
		-- index_t *front_count_ptr;
			-- front_count_ptr = new index_t[num_rows * num_cols];
		-- vertex_t *col_ranger_ptr;  // 行列划分子图到各SSD的节点编号
			-- col_ranger_ptr = new vertex_t[(num_cols + 1) * num_rows];
		-- index_t *comm = new index_t[NUM_THDS]; // 当前SSD的子图的节点个数
		-- const index_t vert_count = 4847571 //总节点数
		-- const index_t vert_per_chunk = chunk_sz / sizeof(vertex_t); = 5242880

		-- // IO管理（每个SSD一个，并行处理）
		-- IO_smart_iterator **it_comm = new IO_smart_iterator*[NUM_THDS];
		-- #pragma omp parallel  num_threads (NUM_THDS) \     //开始多线程并行处理
		--shared(sa_next,sa_curr,comm)
		--{
                   -- sa_t level = 0; //iteration数
			-- int tid = omp_get_thread_num(); //进程号
			-- int comp_tid = tid >> 1; //计算进程号--> SSD子图号
			-- comp_t *neighbors;
			-- vertex_t *sources;
			-- vertex_t dest, source;
			-- index_t *beg_pos=NULL;

			-- index_t beg_1d = tid * step_1d;        //tid = 0 : [0,2423785)
			-- index_t end_1d = beg_1d + step_1d;     //tid = 1 : [2423785,4847571)

		
			-- if((tid&1) == 0) 
			-- {
	            		//Base Constructor(IO_smart_iterator.cpp::line190)
	            		-- IO_smart_iterator::IO_smart_iterator(...)
	            		--{
					-- VERT_PER_BLK=BLK_SZ/sizeof(vertex_t); = 128
					-- beg_pos //记录各节点i的前i个节点的度数和 --> mmap 2MB大页
					-- io_conserve = false;
					-- csr //记录各节点的出边邻居
					-- total_blks = beg_pos_ptr[row_ranger_end-row_ranger_beg]/VERT_PER_BLK; //总block数 = 539014
					-- reqt_blk_bitmap --> mmap: ((total_blks>>3)+8) * sizeof(bit_t) 2MB大页
					-- blk_beg_vert //记录各block开始的节点的编号 --> mmap 2MB大页
					-- 赋值: if(beg_pos_ptr[j+1-row_ranger_beg]>i*VERT_PER_BLK) blk_beg_vert[i] = j; 
						-- (IO_smart_iterator.cpp::line30)
						-- IO_smart_iterator::IO_smart_iterator(...)
					-- reqt_list --> mmap: sizeof(index_t) * total_blks * 10   2MB大页
					-- buff_max_vert = ring_vert_count; = 16

					-- buff_src_vert = new vertex_t*[num_buffs];
					-- buff_dest = new vertex_t*[num_buffs];
					-- buff_edge_count = new index_t[num_buffs];
					-- front_queue = front_queue_ptr;
						-- front_queue[comp_tid] = new vertex_t[col_ranger_end - col_ranger_beg];
					-- //allocate cache driver cd = new cache_driver(...)
					-- "cd init"
				      -- //bitmap only implementation(cache_driver.cpp::line46)
				            -- fetch_sz=0;
				            -- io_submit_time = 0;
				            -- io_poll_time = 0; // IO轮询时间
				            -- VERT_PER_BLK=BLK_SZ/sizeof(vertex_t); = 128
				            -- load_blk_off = 0;
				            -- coarse_grain_off = 0; //粗粒度
				            -- vert_per_chunk = chunk_sz / sizeof(vertex_t); = 5242880
				            -- blk_per_chunk = vert_per_chunk/VERT_PER_BLK; = 40960
				            -- time_out = new struct timespec; //time out spec
				            -- //using a big buffer for all chunks
				            -- buff --> mmap: chunk_sz*num_chunks  2MB大页
				            -- cache = new struct chunk*[num_chunks]; //num_chunks=8
							-- cache[i]->buff = &(buff[i*vert_per_chunk]);
				            -- io_list = new struct io_req*[io_limit]; //io_limit=4
				            -- piocb = new struct iocb*[MAX_EVENTS]; //MAX_EVENTS=(unsigned int)64
							-- io_list[i]->chunk_id = new index_t[MAX_EVENTS];
				            -- events = new struct io_event[MAX_EVENTS];
				            -- circ_free_chunk = new circle(num_chunks);
				            -- circ_load_chunk = new circle(num_chunks);
				            -- circ_free_ctx = new circle(io_limit);
				            -- circ_submitted_ctx = new circle(io_limit);
						-- for(index_t i = 0; i < num_chunks; i++)
						       circ_free_chunk->en_circle(i);
						-- for(index_t i = 0; i < io_limit; i++)
						       circ_free_ctx->en_circle(i);
						-- (cache_driver.cpp::line23)
							-- this->reqt_list = reqt_list;
				--}// end of new IO_smart_iterator(...)
					-- it_comm[tid]->is_bsp_done = false;
			--} // end of if(tid==0)
			-- IO_smart_iterator *it = it_comm[(tid>>1)<<1];
			

			///////////////////////////////////////////////////////////////////////////////////////////
			//开始执行过程,
         		-- "Start random walks ... "
        		-- while(true) （randomwalks.cpp::line 167）
            		--{
             		-- std::cout<<"Start running level " << level << std::endl;
             		-- if((tid & 1) == 0){...进行一些初始化...}
		             -- if((tid & 1) == 0) // tid = 0
		             --{ 
					-- it->req_translator(0);
					--{
						-- (IO_smart_iterator.cpp::367)
						-- ... reqt_blk_bitmap[j>>3] |= (1<<(j&7)); //将相应的位置为1
						-- reqt_blk_count++ ...// 统计需要加载的block的数目
						-- io_conserve = true;
					--}
		                 -- it->is_bsp_done = false; 
		             --}
		             -- else   // tid = 1
		                 -- { it->is_io_done = false; }

		             -- #pragma omp barrier // 同步一下

		             //IO和计算用两个线程并行处理
		             -- if((tid & 1) == 0) // tid = 0  --> 用于计算
		             {
		                 -- //不断去找已加载的chunk   randomwalks.cpp::204
		                 -- while(true){ 
		                     -- int chunk_id = -1;
		                     -- while((chunk_id = it->cd->circ_load_chunk->de_circle()) == -1){
		                         -- if(it->is_bsp_done){
		                             -- chunk_id = it->cd->circ_load_chunk->de_circle();
		                             -- break; }}
		                     -- std::cout << "tid=" << tid << ...  << std::endl;
		                     -- if(chunk_id == -1) break;
		                     -- //找到一个已加载的chunk randomwalks.cpp::227
		                     -- struct chunk *pinst = it->cd->cache[chunk_id]; 
		                     -- index_t blk_beg_off = pinst->blk_beg_off;
		                     -- index_t num_verts = pinst->load_sz;
		                     -- vertex_t vert_id = pinst->beg_vert;
		                     -- //开始处理一个chunk randomwalks.cpp::233
		                     -- 
		                     -- 
		                 -- }  //while(true)的结束
				--} // end of tid = 0, 计算部分

		             -- else // tid = 1    --> 用于IO
		             --{
					-- //开始加载图数据 randomwalks.cpp::275
					-- //一次it->load_key(level)的调用只加载num_chunk chunk(<64 -> 一次IO)，最多同时加载16次IO，每次IO最多min(64,num_chunk)个chunk，每个chunk最多包含2096个连续的block。
		             	-- while(it->is_bsp_done == false)
		             	--{
						-- it->load_key(level); //->IO_smart_iterator.cpp::683
						--{
						       -- //加载chunk数据 IO_smart_iterator.cpp::689
						       -- cd->get_chunk();
						       --{
								-- //第一遍尝试get一个chunk cache_driver.cpp::600
								-- while(1)
									-- { index_t io_id = circ_submitted_ctx->de_circle();
									-- if(io_id==-1) break;}
			               		--}
						       -- cd->load_chunk()
						       --{
						       	-- //第一遍尝试load一个chunk cache_driver.cpp::192
								-- load_blk_off = 0; // 要加载的block的id
								-- *io_conserve = false;
								-- circ_free_chunk->reset_circle();
								-- circ_load_chunk->reset_circle();
								-- req->num_ios = 0;

								//如果没有遍历完所有的block并且还有剩余的请求的block，继续进入循环
								-- while((load_blk_off<total_blks) && (*reqt_blk_count != 0)
								--{ 
									//如果当前编号为load_blk_off的block是需要加载的，以此为起点新建一个chunk
						                   -- if(reqt_blk_bitmap[load_blk_off>>3] & (1<<(load_blk_off&7)))
						                   --{
						                   		-- if(circ_free_chunk->get_sz() == 0)  break;  //一次IO最多加载num_chunk个chunk，当chunk满了就跳出循环，然后提交当前IO
										-- //新建一个chunk
										--  reqt_blk_bitmap[load_blk_off>>3] &= (~(1<<(load_blk_off&7))); //相应block的bitmap复位为0
										--  //更新该chunk的元数据信息
										--  ... blk_beg_off=VERT_PER_BLK * beg_blk_id; //总度数和的offset
										--  ...//生成一个chunk,最大包含4096个block
										--  // 最多生成MAX_EVENTS=64个chunk
										-- if(req->num_ios==MAX_EVENTS)
										--{
											-- circ_submitted_ctx->en_circle(io_id);
											-- //提交一个IO请求，每个IO请求最多min(64,num_chunk)个chunk，每个chunk是一段连续的IO，最多包含4096个block, 最多同时提交16个IO请求
											-- submit_io_req(io_id);
											-- //创建一个新的io_ctx，去填满num_chunk
											-- if(circ_free_ctx->get_sz()==0) return;
											-- io_id = circ_free_ctx->de_circle();
											-- req = io_list[io_id];
											-- req->num_ios=0;
										--} //end of if(req->num_ios==MAX_EVENTS)
						             	--} //end of if(当前block[load_blk_off]需要加载)
						             	--else { ++load_blk_off; }
						             --} // end of while (load_blk_off<total_blk&& (*reqt_blk_count != 0) 
						             -- finishpoint:
						             --{
						             	-- if(io_list[io_id]->num_ios != 0)
						             	--{
							             	-- circ_submitted_ctx->en_circle(io_id);
										-- //提交一个IO请求，每个IO请求最多num_chunk个chunk，每个chunk是一段连续的IO，最多包含4096个block, 最多同时提交16个IO请求
										-- submit_io_req(io_id);
										-- {//提交一个IO请求,（cache_driver.cpp::139）
											-- for(index_t i=0;i<io_list[io_id]->num_ios;i++){
												-- io_prep_pread(...) //初始化IO控制块
												-- fetch_sz += cache[chunk_id]->load_sz * sizeof(vertex_t);}
											-- if(ret=io_submit(...)!=io_list[io_id]->num_ios) --> error //提交一个包含64个chunk的IO请求
										--} // end of submit_io_req(io_id);
									--}//end of  if(io_list[io_id]->num_ios != 0)
								--} // end of finishpoint : submit_io_req
						       --} // end of cd->load_chunk();
						       -- cd->get_chunk();
						       --{
						       	-- //第二遍尝试get一个chunk cache_driver.cpp::600
						       	-- //将之前提交的IO请求转化为加载的IO ctx，返回得到的IO ctx
								-- while(true)
								-- { 
									-- index_t io_id = circ_submitted_ctx->de_circle();
									-- if(io_id==-1) break; //此时有提交的io_ctx，逐个处理每个io_ctx
									-- struct io_req *req=io_list[io_id];
									-- ret=n=io_getevents(req->ctx,req->num_ios,MAX_EVENTS,events,NULL);
									//获取当前IO请求，逐个加入等待加载
									-- for(int i=0;i<req->num_ios;i++)
									--{
										--//std::cout<<"Get-a-chunk\n";
										--index_t chunk_id = req->chunk_id[i];
										--cache[chunk_id]->status = LOADED;
										--circ_load_chunk->en_circle(chunk_id);
									--}
									--//在空闲的ctx队列中释放当前空闲的位置
									--circ_free_ctx->en_circle(io_id);
								--} //end of while(true)
								-- ... 
								-- return circ_load_chunk;  //
						       --} // end of 第二次 get_chunk()
						       -- cd->load_chunk(); //第二次load_chunk（）和第一次一样，再次提交一个IO请求

						--} // end of it->load_key(level);
					--} // end of while(it->is_bsp_done == false)
		             --} //end of tid = 1, IO部分

		--}//end of shared
	--}//end of main






























///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
