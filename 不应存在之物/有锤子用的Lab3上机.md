# 有锤子用的Lab3上机

## lab3-1

### exam-2021

#### PART1

`u_int fork(struct Env *e);`

在今天的实验里我们要求你实现一个简易的`fork`函数（并不包括实际load代码段），通过给定的原始进程块(输入参数`struct Env *e`)生成一个新的进程控制块，并返回新进程控制块的`env_id`。同学们需要在`lib/env.c`和`include/env.h`中分别定义和声明`fork`函数，要求如下：

1. 从`env_free_list`中从头申请一个新的进程控制块
2. 新进程控制块的 `env_status`、`env_pgdir`、`env_cr3`、`env_pri`和原进程控制块保持一致。
3. 为新进程控制块生成对应的`env_id`
4. env_parent_id 的值为原进程控制块的`env_id`
5. 返回值为新进程的`env_id`

#### PART2

`void lab3_output(u_int env_id);`

本部分要求修改`struct Env`，在进程控制块中增加字段（具体增加哪些内容请自行组织）组织起进程间的父子、兄弟关系，并按照要求在`lib/env.c`和`include/env.h`中分别定义和声明`lab3_output`函数输出相关内容，详情如下： 

函数`lab3_output`的定义如下：`void lab3_output(u_int env_id);`

要求输出的内容有：其父进程的`env_id`、其第一个子进程的`env_id`、其前一个兄弟进程的`env_id`以及其后一个兄弟进程的`env_id `所有的子进程都由fork创建，两个进程如果是兄弟，它们的父进程一定相同。 以某进程第一个子进程是指，由该进程作为父进程使用 fork 创建的第一个子进程。兄弟进程间的顺序即为这些进程被创建的顺序，前一个兄弟进程为较早被创建的进程

需要在 PART1 的 fork 函数中进行对添加字段的修改

输出格式为：`printf("%08x %08x %08x %08x\n", a, b, c, d);`其中 a, b, c, d分别为父进程的 env_id、第一个子进程的 env_id、前一个兄弟进程的 env_id以及后一个兄弟进程的 env_id 如果 a, b, c, d 中有不存在的参数，则输出0

#### PART3

`int lab3_get_sum(u_int env_id);`

在PART2的基础上，在`lib/env.c`和` include/env.h`中分别定义和声明`lab3_get_sum`函数，函数的功能为：给定一个进程的`env_id`，返回以该进程为根节点的子进程树中进程的数目（包括它本身）： 

#### 解答

比较简单，但是小坑不断。有的人第一题没有用`env_alloc()`结果忘记给`free_env_list` remove 掉分配的`env`

```C
struct Env {
    struct Trapframe env_tf; // Saved registers
    LIST_ENTRY(Env)
    env_link;            // Free list
    u_int env_id;        // Unique environment identifier
    u_int env_parent_id; // env_id of this env's parent
    u_int env_status;    // Status of the environment
    Pde *env_pgdir;      // Kernel virtual address of page dir
    u_int env_cr3;
    LIST_ENTRY(Env)
    env_sched_link;
    u_int env_pri;
    // Lab 4 IPC
    u_int env_ipc_value;   // data value sent to us
    u_int env_ipc_from;    // envid of the sender
    u_int env_ipc_recving; // env is blocked receiving
    u_int env_ipc_dstva;   // va at which to map received page
    u_int env_ipc_perm;    // perm of page mapping received

    // Lab 4 fault handling
    u_int env_pgfault_handler; // page fault state
    u_int env_xstacktop;       // top of exception stack

    // Lab 6 scheduler counts
    u_int env_runs; // number of times been env_run'ed
    u_int env_nop;  // align to avoid mul instruction

    int son_num;            // add on exam
    u_int son_id_arr[1024]; // add on exam
};

u_int fork(struct Env *e) {
    struct Env *e_son;
    env_alloc(&e_son, e->env_id);
    e_son->env_status = e->env_status;
    e_son->env_pgdir = e->env_pgdir;
    e_son->env_cr3 = e->env_cr3;
    e_son->env_pri = e->env_pri;

    // ---- father ----
    e->son_id_arr[e->son_num++] = e_son->env_id;

    return e_son->env_id;
}

void lab3_output(u_int env_id) {
    struct Env *e_now;
    u_int fa_id = 0;
    u_int first_son_id = 0;
    u_int bro_bf_id = 0; // "bf" means "before"
    u_int bro_af_id = 0; // "af" means "after"

    envid2env(env_id, &e_now, 0);
    // son part
    first_son_id = e_now->son_id_arr[0];

    // parent part
    fa_id = e_now->env_parent_id;
    if (fa_id) { // have a parent
        struct Env *e_fa;
        envid2env(fa_id, &e_fa, 0);
        int index = 0;
        for (index = 0; index < 1024; index++) {
            if (e_fa->son_id_arr[index] == env_id) {
                break;
            }
        }
        // index is the env of father now
        if (index > 0) { // have bro bf
            bro_bf_id = e_fa->son_id_arr[index - 1];
        }

        // have a bro_af
        if (e_fa->son_num > index + 1) {
            bro_af_id = e_fa->son_id_arr[index + 1];
        }
    }
    // fa_id, fist_son_id, bro_bf, bro_af
    printf("%08x %08x %08x %08x\n", fa_id, first_son_id, bro_bf_id, bro_af_id);
}

int lab3_get_sum(u_int env_id) {
    struct Env *e_now;
    envid2env(env_id, &e_now, 0);
    // if e_now has no son
    if (e_now->son_num == 0) {
        return 1;
    }
    // have many sons, recuring
    int ans = 1;
    int i = 0;
    for (i = 0; i < e_now->son_num; i++) {
        struct Env *e_son;
        u_int son_id = e_now->son_id_arr[i];
        envid2env(son_id, &e_son, 0); // now got a son
        ans += lab3_get_sum(son_id);
    }
    return ans;
}
```

### exam-2019

增加了 3 个函数，看上去和 env_pri 直接相关（重新设置了进程 id，并通过进程 id 得到 pri）：

`u_int newmkenvid(struct Env *e, int pri);`

`void output_env_info(int envid);`

`void init_envid();`

```C
u_int newmkenvid(struct Env *e, int pri) {
    u_int idx = e - envs;
    return (pri << (1 + LOG2NENV)) | idx;
}

void output_env_info(int envid) {
    static int cnt_times = 0;
    cnt_times++;
    int pri = envid >> (1 + LOG2NENV);
    printf("no=%d,env_index=%d,env_pri=%d\n", cnt_times, ENVX(envid), pri);
}

void init_envid() {
    int i;
    struct Env *e;
    for (i = 0; i < NENV; i++) {
        e = &envs[i];
        if (e->env_status == ENV_RUNNABLE) {
            e->env_id = newmkenvid(e, e->env_pri);
        }
    }
}
```

### Extra-2021

#### 题目

`void lab3_kill(u_int env_id);`

lib/env.c 和 include/env.h 中分别定义和声明 lab3_kill 函数，功能为：杀死一个进程。

进程树的根节点代表的进程收养（接管）他的孤儿进程。这些孤儿进程将依次排列在根进程的子进程的尾部。测试中保证不会杀死根节点代表的进程。函数接口如下：`void lab3_kill(u_int env_id);`在完成一次删除后，基础测试 PART2 lab3_output，输出的结果在新的树结构下仍应正确。一颗进程树的根节点代表的进程由 env_alloc 创建，其余节点代表的进程皆由 PART1 fork 创建。 本部分中“杀死进程”的要**清空进程控制块相关字段**（可以参考`free_env()`，但是不能调用`free_env()`）以及其他相关处部分测试较强，请务必考虑完善。

#### 解答

```C
void lab3_kill(u_int env_id) {
    // get e_now and e_root
    struct Env *e_now;
    struct Env *e_root;
    envid2env(env_id, &e_now, 0);

    u_int root_id = e_now->env_parent_id;
    envid2env(root_id, &e_root, 0);

    // while this "root" have a father
    while (e_root->env_parent_id != 0) {
        root_id = e_root->env_parent_id;
        envid2env(root_id, &e_root, 0);
    }

    // now we get the root
    int now_son_num = e_now->son_num;
    int root_son_num = e_root->son_num;

    int i = 0;

    // remove from father, careful!: root == father
    struct Env *e_fa;
    u_int fa_id = e_now->env_parent_id;
    envid2env(fa_id, &e_fa, 0);
    // get the index
    for (i = 0; i < e_fa->son_num; i++) {
        if (e_fa->son_id_arr[i] == env_id) {
            break;
        }
    }

    // cover
    for (; i < e_fa->son_num - 1; i++) {
        e_fa->son_id_arr[i] = e_fa->son_id_arr[i + 1];
    }
    e_fa->son_id_arr[i] = 0;
    e_fa->son_num--;

    // attach all sons to root
    for (i = 0; i < now_son_num; i++) {
        u_int now_son_id = e_now->son_id_arr[i];
        e_root->son_id_arr[e_root->son_num] = now_son_id;
        e_root->son_num += 1;
    }

    // free the env
    e_now->son_num = 0;
    for (i = 0; i < e_now->son_num; i++) {
        e_now->son_id_arr[i] = 0;
    }
    e_now->env_status = ENV_FREE;
    e_now->env_cr3 = 0;
    e_now->env_pgdir = 0;

    // maybe i should add, then i can pass
    LIST_INSERT_HEAD(&env_free_list, e, env_link);
}
```

### Extra-2019

```c
int check_same_root(u_int envid1, u_int envid2) {
    struct Env *now1, *now2;
    envid2env(envid1, &now1, 0);
    envid2env(envid2, &now2, 0);
    if (now1->env_status == ENV_NOT_RUNNABLE ||
        now2->env_status == ENV_NOT_RUNNABLE) {
        return -1;
    }
    while (now1->env_parent_id != 0) {
        envid2env(now1->env_parent_id, &now1, 0);
    }
    while (now2->env_parent_id != 0) {
        envid2env(now2->env_parent_id, &now2, 0);
    }
    if (now1 == now2) {
        return 1;
    } else {
        return 0;
    }
}

int fa[NENV];

int findfa(int i) {
    return fa[i] == i ? i : (fa[i] = findfa(fa[i]));
}

void kill_all(u_int envid) {
    int i, par;
    int now;
    struct Env *e;
    int r;
    now = ENVX(envid);
    for (i = 0; i < NENV; i++) {
        fa[i] = i;
    }
    for (i = 0; i < NENV; i++) {
        e = envs + i;
        if (e->env_status != ENV_FREE) {
            if (e->env_parent_id) {
                par = ENVX(e->env_parent_id);
                findfa(par);
                findfa(i);
                if (fa[i] != fa[par]) {
                    fa[fa[i]] = fa[par];
                }
            }
        }
    }
    int has = 0;
    for (i = 0; i < NENV; i++) {
        findfa(i);
        findfa(now);
        if (fa[now] == fa[i]) {
            e = envs + i;
            if (e->env_status == ENV_NOT_RUNNABLE) {
                has = 1;
                break;
            }
        }
    }
    if (has) {
        printf("something is wrong!\n");
    } else {
        for (i = 0; i < NENV; i++) {
            findfa(i);
            findfa(now);
            if (fa[now] == fa[i]) {
                e = envs + i;
                e->env_status = ENV_NOT_RUNNABLE;
            }
        }
    }
}
```

## lab3-2

题目要求：在本次课上测试中，我们对 env_pri 的含义进行如下约定：

1. env_pri的第0-7位仍然表示进程的优先级（PRI）
2. env_pri的第8-15位为功能字段1（FUNC_1）
3. env_pri的第16-23位为功能字段2（FUNC_2）
4. env_pri的第24-31位为功能字段3（FUNC_3）
5. FUNC_1, FUNC_2, FUNC_3 均为无符号数

```c
#define PRI(X) (((X)->env_pri) & 0xff)
#define FUNC_1(X) ((((X)->env_pri) >> 8) & 0xff)
#define FUNC_2(X) ((((X)->env_pri) >> 16) & 0xff)
#define FUNC_3(X) ((((X)->env_pri) >> 24) & 0xff)
```

### exam-2021

#### PART1

在这次的课上测试中，我们需要你实现一个新的调度算法，具体要求如下：

1. 修改 sched_yield 函数，使得在进程调度时高优先级（用 PRI 表示）的进程永远比低优先级（用 PRI 表示）的进程先调度。
2. 为了简化问题，不需要考虑两个进程优先级相同的情况。例如：如果有两个进程 A 和 B，优先级分别为 1 和 2，且 env_status 都为 ENV_RUNNABLE，则只有 B 会得到执行；当 B 的状态不为 ENV_RUNNABLE 时，A 才会得到执行。

#### PART2

在 PART1 中的 sched_yield 上继续修改，要求如下：在当前进程（记为进程 X）被时钟中断暂停执行时，进行如下操作：

1. 根据 FUNC_1 的值更新进程 X 的优先级：若 FUNC_1 的值为 0，则不修改进程 X 的优先级 若 FUNC_1 的值为正，则将进程 X 的优先级减少 FUNC_1 的值（如果减少之后优先级小于 0 则优先级置零）
2. 完成 PART1 中的进程调度

#### 解答

有一些坑：

1. `(x << 24) >> 24`可能导致结果为负数，所以最好`x & 0xff`
2. 没有时间片的概念，所以不存在一个进程的时间片用完这种说法，所以不用在两个 list 之间倒腾来倒腾去
3. 本地测试时，永远输出一个数字，不存在进程切换

```c
#define MAX(a, b) (a) > (b) ? (a) : (b)

void sched_yield(void) {
    static int count = 0; // remaining time slices of current env
    static int point = 0; // current env_sched_list index

    static struct Env *e = NULL;

    struct Env *tempe;
    int maxpri = 0;

    while (!LIST_EMPTY(&env_sched_list[1])) { // abandon list[1]
        tempe = LIST_FIRST(&env_sched_list[1]);
        LIST_REMOVE(tempe, env_sched_link);
        LIST_INSERT_HEAD(&env_sched_list[0], tempe, env_sched_link);
    }
    if (e != NULL) {
        if (FUNC_1(e) > 0) {
            e->env_pri = MAX(e->env_pri - FUNC_1(e), 0);
        }
    }
    maxpri = 0;
    LIST_FOREACH(tempe, &env_sched_list[0], env_sched_link)
    {
        if (PRI(tempe) > maxpri && tempe->env_status == ENV_RUNNABLE) {
            e = tempe;
            maxpri = PRI(tempe);
        }
    }

    env_run(e);
}
```

或者：

```c
struct Env *e = NULL;

void sched_yield(void) {
    static int count = 0; // remaining time slices of current env
    static int point = 0; // current env_sched_list index

    count--;
    if (curenv != NULL) {
        if (FUNC1(curenv) != 0) {
            int a = PRI(curenv);
            a = ((a - FUNC1(curenv)) < 0) ? 0 : (a - FUNC1(curenv));
            curenv->env_pri = ((curenv->env_pri) & 0xffffff00) | a;
        }
    }
    if (count <= 0 || curenv == NULL) {
        if (curenv != NULL) {
            LIST_INSERT_TAIL(&env_sched_list[0], curenv, env_sched_link);
        }
        int pri = 0;
        struct Env *max;
        LIST_FOREACH(e, &env_sched_list[0], env_sched_link)
        {
            if (PRI(e) > pri) {
                pri = PRI(e);
                max = e;
            }
        }
        if (LIST_EMPTY(&env_sched_list[0])) {
            panic("^^^^No env is RUNNABLE!^^^^\n");
        }
        LIST_REMOVE(max, env_sched_link);
        count = pri;
        env_run(max);
    }
    env_run(curenv);
    panic("^^^^sched_yield func reach end!^^^^\n");
}
```

### exam-2019

```c
#include <env.h>
#include <pmap.h>
#include <printf.h>

extern struct Env_list env_sched_list[];
extern struct Env *curenv;

void sched_yield(void) {
    static u_int cur_lasttime = 1;
    static int cur_head_index = 0;
    struct Env *next_env;
    cur_lasttime--;
    if (cur_lasttime == 0 || curenv == NULL) {
        if (curenv != NULL) {
            LIST_INSERT_HEAD(&env_sched_list[!cur_head_index],
                             curenv, env_sched_link);
        }
        if (LIST_EMPTY(&env_sched_list[cur_head_index])) {
            cur_head_index = !cur_head_index;
        }
        if (LIST_EMPTY(&env_sched_list[cur_head_index])) {
            panic("^^^^^^No env is RUNNABLE!^^^^^^");
        }
        next_env = LIST_FIRST(&env_sched_list[cur_head_index]);
        LIST_REMOVE(next_env, env_sched_link);
        cur_lasttime = next_env->env_pri;
        env_run(next_env);
    }
    env_run(curenv);
    panic("^^^^^^sched yield reached end^^^^^^");
}
```

### Extra-2021

#### 题目要求

Extra 部分要求在 exam 部分的基础上继续修改 sched_yield：

在当前进程（记为进程 X）被时钟中断暂停执行时，进行如下操作：

1. 如果当前的时钟中断是第 FUNC_2 个（从 1 开始计数）时钟中断，那么在接下来的 FUNC_3 个时间片里，将进程 X 的 env_status 改为 ENV_NOT_RUNNABLE，不进行调度，FUNC_3 个时间片之后（无论这时是哪一个进程被中断），将进程 X 的 env_status 改为 ENV_RUNNABLE，参与调度。
2. 否则，不进行处理（注意，为了简化问题，我们保证这一部分测试数据中 FUNC_1 始终为0）
3. 按照 PART1 中的策略进行调度

```c
#define MAX(a, b) (a) > (b) ? (a) : (b)

void sched_yield(void) {
    static int count = 0; // times of interrupted
    static int point = 0; // current env_sched_list index
    static struct Env *e = NULL;
    struct Env *tempe;
    int maxpri = 0;

    count++;

    while (!LIST_EMPTY(&env_sched_list[1])) { // abandon list[1]
        tempe = LIST_FIRST(&env_sched_list[1]);
        LIST_REMOVE(tempe, env_sched_link);
        LIST_INSERT_HEAD(&env_sched_list[0], tempe, env_sched_link);
    }
    if (e != NULL) {
        if (FUNC_1(e) > 0) {
            e->env_pri = MAX(e->env_pri - FUNC_1(e), 0);
        }
        if (FUNC_2(e) == count) {
            e->env_status = ENV_NOT_RUNNABLE;
        }
    }
    maxpri = 0;
    LIST_FOREACH(tempe, &env_sched_list[0], env_sched_link)
    {
        if (tempe->env_status == ENV_NOT_RUNNABLE && count ==
                                                     (FUNC_2(tempe) + FUNC_3(tempe))) {
            tempe->env_status = ENV_RUNNABLE;
        }
        if (PRI(tempe) > maxpri && tempe->env_status == ENV_RUNNABLE) {
            e = tempe;
            maxpri = PRI(tempe);
        }
    }

    env_run(e);
}
```

或者：

```c
struct Env *e = NULL;

void sched_yield(void) {
    static int count = 0; // remaining time slices of current env
    static int point = 0; // current env_sched_list index
    static int int_cnt = 0;

    count--;
    int_cnt++;
    if (curenv != NULL) {
        if (FUNC1(curenv) != 0) {
            int a = PRI(curenv);
            a = ((a - FUNC1(curenv)) < 0) ? 0 : (a - FUNC1(curenv));
            curenv->env_pri = ((curenv->env_pri) & 0xffffff00) | a;
        }
        if (FUNC2(curenv) == int_cnt) {
            LIST_REMOVE(curenv, env_sched_link);
            curenv->reset = FUNC3(curenv) + 1;
            curenv->env_status = ENV_NOT_RUNNABLE;
            LIST_INSERT_HEAD(&env_sched_list[1], curenv, env_sched_link);

            curenv = NULL;
        }
    }
    LIST_FOREACH(e, &env_sched_list[1], env_sched_link)
    {
        if (e == NULL)
            break;
        if (e->reset > 0) {
            e->reset--;
        }
        if (e->reset == 0) {
            e->env_status = ENV_RUNNABLE;
            LIST_REMOVE(e, env_sched_link);
            LIST_INSERT_TAIL(&env_sched_list[0], e, env_sched_link);
        }
    }
    if (count <= 0 || curenv == NULL) {
        if (curenv != NULL) {
            LIST_INSERT_TAIL(&env_sched_list[0], curenv, env_sched_link);
        }
        int pri = 0;
        struct Env *max;
        LIST_FOREACH(e, &env_sched_list[0], env_sched_link)
        {
            if (PRI(e) > pri) {
                pri = PRI(e);
                max = e;
            }
        }
        if (LIST_EMPTY(&env_sched_list[0])) {
            panic("^^^^No env is RUNNABLE!^^^^\n");
        }
        LIST_REMOVE(max, env_sched_link);
        count = pri;
        env_run(max);
    }
    env_run(curenv);
    panic("^^^^sched_yield func reach end!^^^^\n");
}
```

#### 解答

题干中虽然提到了“时间片”的概念，其实一个时间片就是一次中断。

测试样例很弱，挺多人过 Extra 的，所以不能保证自己的程序是否正确。

我觉得简单的做法应该是修改 env.h 里的 env 结构体，置一个 time_to_run，每个中断更新下，更新到 0 的话就置为 RUNNABLE。然后遍历 list 取 RUNNABLE 里 pri 最大的就行。

一个 list 就够了。

### Extra-2019

handle_ov.c:

```c
#include<printf.h>
#include<trap.h>

extern char *KERNEL_SP;

void ov_do(char *sp) {
    struct Trapframe *tf;
    int i;
    tf = (struct Trapframp *) sp;// - sizeof(struct Trapframe));
    u_int *instr_p = tf->cp0_epc;
    u_int instr = *instr_p;
    printf("Instr: 0x%x\n", instr);
    printf("reg %d and reg %d\n",
           (instr >> 21) & (0x1f), (instr >> 16) & (0x1f));
    for (i = 8; i <= 15; i++) {
        tf->regs[i] = 0;
    }
    return;
}
```

handle_ov_asm.S:

```assembly
#include <asm/regdef.h>
#include <asm/cp0regdef.h>
#include <asm/asm.h>
#include <stackframe.h>
#include <trap.h>

.extern ov_do

LEAF(handle_ov)
	.set noat
	nop
	SAVE_ALL
	CLI
	move a0, sp
	jal ov_do
	nop
	jal ov_check
	nop
	j ret_from_exception
	nop
END(handle_ov)
```

