## Lab2

1. 课程 > 内存管理 > MIPS (R3000) 访存流程概览 > 虚拟地址到物理地址映射

   ![截屏2022-04-01 13.21.58](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ucmznb8j22800ksmzc.jpg)

   ![截屏2022-04-01 13.22.11](https://tva1.sinaimg.cn/large/e6c9d24ely1h13uclmfmaj22800ksgny.jpg)

2. 课程 > 内存管理 > 物理内存管理 > 内存控制块

   Thinking 2.3

   请阅读 `include/queue.h` 以及 `include/pmap.h`, 将 `Page_list` 的结构梳理清楚，选择正确的展开结构。

   ```c
   A:
   struct Page_list{
       struct {
           struct {
               struct Page *le_next;
               struct Page **le_prev;
           }* pp_link;
           u_short pp_ref;
       }* lh_first;
   }
   
   ```

   ```c
   B:
   struct Page_list{
       struct {
           struct {
               struct Page *le_next;
               struct Page **le_prev;
           } pp_link;
           u_short pp_ref;
       } lh_first;
   }
   ```

   ```c
   C:
   struct Page_list{
       struct {
           struct {
               struct Page *le_next;
               struct Page **le_prev;
           } pp_link;
           u_short pp_ref;
       }* lh_first;
   }
   ```

   ![截屏2022-04-01 13.35.52](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ucq967jj22800hm40h.jpg)

3. 课程 > 内存管理 > 虚拟内存管理 > 两级页表结构

   ![截屏2022-04-01 13.43.01](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ucs387dj22800eomyh.jpg)

   ![截屏2022-04-01 13.43.22](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ucrkyb4j22800kegnl.jpg)

4. 课程 > 内存管理 > 虚拟内存管理 > 系统启动相关函数

   ![截屏2022-04-01 13.44.35](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ucmi7ghj21oo0u0q5q.jpg)

5. 课程 > 内存管理 > 虚拟内存管理 > 进程运行相关函数

   ![截屏2022-04-01 13.45.38](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ucow92ij22800eymyk.jpg)

6. 课程 > 内存管理 > 访存与 TLB 重填 > 用户进程访存流程

   ![截屏2022-04-01 13.49.47](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ucnwwc2j22800ju0ua.jpg)

7. 课程 > 内存管理 > 访存与 TLB 重填 > TLB重填流程

   ![截屏2022-04-01 13.50.51](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ucqsu4rj22800hqmyw.jpg)

8. 课程 > 内存管理 > 多级页表与页目录自映射 > 多级页表与页目录自映射

   ![截屏2022-04-01 13.52.01](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ucpp0p8j22800deabl.jpg)