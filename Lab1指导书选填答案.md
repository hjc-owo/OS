## Lab1

1. 课程 > 内核、Boot 和 printf > 操作系统的启动 > 内核在哪里？

   ![截屏2022-03-21 18.56.30](https://tva1.sinaimg.cn/large/e6c9d24ely1h13uaws8s1j22800nignv.jpg)

   ![截屏2022-03-21 18.56.40](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub728ilj22800ncgp2.jpg)

2. 课程 > 内核、Boot 和 printf > 操作系统的启动 > Bootloader

   ![截屏2022-03-21 18.59.00](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub381rsj22800nedis.jpg)

3. 课程  内核、Boot 和 printf  Let's hack the kernel!  Makefile——内核代码的地图

   ![截屏2022-03-21 19.02.06](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub4oefqj22800hywft.jpg)

4. 课程 > 内核、Boot 和 printf > Let's hack the kernel! > ELF——深入探究编译与链接

   ![截屏2022-03-21 21.47.27](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub9rnumj22800nwtbc.jpg)

   ![截屏2022-03-21 21.47.34](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub5qay2j22800o240v.jpg)

   ![截屏2022-03-21 21.47.44](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub7iqy1j22800potan.jpg)

   ![截屏2022-03-21 21.47.53](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub2unqyj22800no76g.jpg)

   ![截屏2022-03-21 21.48.00](https://tva1.sinaimg.cn/large/e6c9d24ely1h13uba7yvvj22800nudht.jpg)

   ![截屏2022-03-21 21.48.10](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub565epj22800o0q4s.jpg)

5. 课程 > 内核、Boot 和 printf > Let's hack the kernel! > MIPS内存布局——寻找内核的正确位置

   ![截屏2022-03-21 21.49.58](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub1e8d8j22800om76e.jpg)

6. 课程 > 内核、Boot 和 printf > Let's hack the kernel! > Linker Script——控制加载地址

   ![截屏2022-03-21 21.50.52](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub7wywaj22800no769.jpg)

   ![截屏2022-03-21 21.50.59](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub20mqvj22800ragoo.jpg)

   ![截屏2022-03-21 21.51.08](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ubaosu9j22800fk762.jpg)

7. 课程 > 内核、Boot 和 printf > MIPS汇编与C语言 > 循环与判断

   ![截屏2022-03-21 21.53.11](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub98g4mj228007074l.jpg)

   ```assembly
   ...
   ...
   func:
   sw $fp, 0($sp)
   addi $fp, $sp, 4
   sw $ra, -8($fp)
   add $t1, $zero, $a0
   add $t2, $zero, $a1
   bgez $t1, if_else_0
   li $t8, 0
   sub $t0, $t8, $t1
   add $t0, $t0, 0
   add $v0, $t2, $t0
   move $sp, $fp
   lw $fp, -4($sp)
   lw $ra, -8($sp)
   jr $ra
   if_else_0:
   if_end_0:
   add $t0, $t1, -0
   add $v0, $t2, $t0
   move $sp, $fp
   lw $fp, -4($sp)
   lw $ra, -8($sp)
   jr $ra
   ...
   ...
   ```

   ![截屏2022-03-21 21.54.13](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub625ulj22800b8mxz.jpg)

8. 课程 > 内核、Boot 和 printf > MIPS汇编与C语言 > 函数调用

   ![截屏2022-03-21 21.55.29](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub8wwbzj22800nctay.jpg)

   ![截屏2022-03-21 21.55.36](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub3nu7xj22800ne76h.jpg)

9. 课程 > 内核、Boot 和 printf > MIPS汇编与C语言 > 通用寄存器使用约定

   ![截屏2022-03-21 21.56.08](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub4887pj22800n476t.jpg)

   ![截屏2022-03-21 21.56.15](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub8cki5j22800n4acs.jpg)

10. 课程 > 内核、Boot 和 printf > 实战printf > 实战printf

    ![截屏2022-03-21 21.57.12](https://tva1.sinaimg.cn/large/e6c9d24ely1h13ub6hx3ij22800fk40l.jpg)