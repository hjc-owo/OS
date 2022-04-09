# Lab0实验报告

## 实验思考题

### Thinking 0.1

status 不一样。

add 之前的 status 表示没有跟踪某个文件的变化，使用`git add`之后才对文件进行跟踪。

修改 add 过之后的文件的 status 表示修改了某个文件，但还没有加入到暂存区中。

### Thinking 0.2

- add the file 对应 `git add`
- stage the file 对应 `git add`
- commit 对应 `git commit`

### Thinking 0.3

- 使用

  ```shell
  git checkout printf.c
  ```

- 依次使用

  ```shell
  git reset HEAD printf.c
  git checkout printf.c
  ```

- 使用

  ```shell
  git rm --cached Tucao.txt
  ```

### Thinking 0.4

`git reset --hard`指令可以用来恢复文件的版本，既可以往回恢复，也可以往后“恢复”。



但是，--hard 是 reset 命令唯一的危险用法，它也是 git 会真正地销毁数据的几个操作之一。其他任何形式的 reset 调用都可以轻松撤消，但是 --hard 选项不能，因为它强制覆盖了工作目录中的文件。若该文件还未提交，git 会覆盖它从而导致无法恢复。使用时要小心谨慎。

### Thinking 0.5

1. 正确。克隆 gitHub 用户 SunzeY 的 BUAA_OS_2021 仓库，使用`git branch -a`命令查看，可以看到所有分支。但是只有HEAD指向的分支被检出。

2. 正确。在我们做作业时要提交到远程。若不使用`git push`，则所有访问都是在本地库中进行，不会访问到远程库。

3. 错误。由问题1可知，克隆时所有分支均被克隆。

4. 错误。如图所示。分支名字只是个代号。问题1中，clone 下来后，默认分支是 lab6-challenge 分支，但是分支中存在 master 分支。默认分支可以设置，与设置的 default 分支相同。

   ![截屏2022-03-16 22.49.07](https://tva1.sinaimg.cn/large/e6c9d24ely1h13u4xsecvj211w0qugql.jpg)


### Thinking 0.6

如图所示

1. 执行 `echo first` 和`echo second > output.txt`

   ![截屏2022-03-16 23.05.08](https://tva1.sinaimg.cn/large/e6c9d24ely1h13u53c5jgj20vo0j2taa.jpg)

2. 执行`echo third > output.txt`

   ![截屏2022-03-16 23.05.08](https://tva1.sinaimg.cn/large/e6c9d24ely1h13u50m9l8j20vo0j2taa.jpg)

3. 执行`echo forth >> output.txt`

   ![截屏2022-03-16 23.06.05](https://tva1.sinaimg.cn/large/e6c9d24ely1h13u52gtd5j20vi0io0uq.jpg)

### Thinking 0.7

Command.sh 文件如下：

```shell
#!/usr/bin/env bash 

echo 'echo Shell Start...' > test.sh
echo 'echo set a = 1' >> test.sh
echo 'a=1' >> test.sh
echo 'echo set b = 2' >> test.sh
echo 'b=2' >> test.sh
echo 'echo set c = a+b' >> test.sh
echo 'c=$[$a+$b]' >> test.sh
echo 'echo save c to ./file1' >> test.sh
echo 'echo $c>file1' >> test.sh
echo 'echo save b to ./file2' >> test.sh
echo 'echo $b>file2' >> test.sh
echo 'echo save a to ./file3' >> test.sh
echo 'echo $a>file3' >> test.sh
echo 'echo save file1 file2 file3 to file4' >> test.sh
echo 'cat file1>file4' >> test.sh
echo 'cat file2>>file4' >> test.sh
echo 'cat file3>>file4' >> test.sh
echo 'echo save file4 to ./result' >> test.sh
echo 'cat file4>>result' >> test.sh
```

result 文件如下：

```
3
2
1
```

![截屏2022-03-16 23.38.48](https://tva1.sinaimg.cn/large/e6c9d24ely1h13u4zu1jcj21c00u0q81.jpg)



`echo echo Shell Start` 与 `echo 'echo Shell Start'`效果完全一样：

![截屏2022-03-16 23.23.09](https://tva1.sinaimg.cn/large/e6c9d24ely1h13u51jigpj214m0qu40p.jpg)

`echo echo \$c>file1` 与 `echo 'echo \$c>file1'`效果不一样。

前者新建了 file1 文件，内容为`echo \$c`，后者直接在终端显示`echo \$c>file1`。如图所示。

![截屏2022-03-16 23.26.37](https://tva1.sinaimg.cn/large/e6c9d24ely1h13u4ymhu6j20xy0iu3zz.jpg)

## 实验难点

本次实验需要掌握并熟悉较多的命令操作。主要为熟悉 Linux 的`bash`基本命令，还有使用 vim 编辑文本，gcc 命令行，编写 Shell 脚本、make 文件。本次实验的主要难度在于编写 Shell 脚本和 make 文件，主要原因是第一次接触。遇到的困难就是 make 文件的复合调用以及链接库文件，也就是这次 Exercise 0.4 的部分。

一开始我觉得不需要编写 code 文件夹中的 Makefile 文件也可以完成，但是考虑到题目的要求，应该是外层 Makefile 调用内层 Makefile 完成需求。于是通过查阅资料以及看课程指导书下方的讨论区，从而了解到如何通过外层 Makefile 调用内层 Makefile，以及如何连接到不是本文件夹下的库文件，从而写出下方的两个 Makefile。

/csc 目录下的 Makefile：

```makefile
all:
	cd ./code && make fibo

clean:
	rm ./code/*.o
```

/csc/code 目录下的 Makefile：

```makefile
fibo:
	gcc -c fibo.c
	gcc -c main.c -I../include
	gcc fibo.o main.o -o ../fibo
```



`Shell`脚本以及`Makefile`文件中的赋值语句中，参数与等于号之间不应有空格，若有空格系统会判定空格为分隔符，从而语句非法。

## 体会与感想

本实验并不涉及操作系统课程的主体部分，仅仅是一个对 shell 指令的练习。还是由于命令行使用的不熟练，界面不适应等原因，在学习这些指令，尤其是在 shell 脚本与 makefile 的使用中，以及完成作业上仍然还是花了较多的时间。在后期进行真正的操作系统架构的设计时，仍然需要多次调用这些指令，因此掌握它们尤为重要，在接下来的时间中，我仍应该多对这些指令进行联系，从而让自己接下来的操作系统实验进行得更加顺利。

## 指导书反馈

条目或许分的太细了，导致经常找不到想要查阅的地方。同时 Thinking 部分与指导书内的选择题要是能单独拿出来，食用起来或许更方便？