lab->MIT6.828 study os. important boot load, paging, lock, mulpty task, file system, network

疑问：


解决：
1.在pmap.h中page2pa强转类型。48转32为啥是shr 0x3 %eax。不是直接舍弃，而是位移3bit.
因为在x86 32位系统。寄存器eax...都是32位的，如果是48位结构体应该分别存储2个寄存器中.
```asm
lea eax, [MyStruct] ; 计算结构体的地址
mov edx, [eax + 4]  ; 加载结构体的高 32 位字节到 edx 中
mov eax, [eax]      ; 加载结构体的低 32 位字节到 eax 中
shl edx, 32         ; 将高 32 位字节移动到寄存器的高位
or eax, edx         ; 将低 32 位字节移动到寄存器的低位
mov eax, eax        ; 将高 32 位字节清零，转换为 32 位无符号整数
```
我查询的值`%eax`物理地址的有效位小于32位。猜测移除了高位的有效位===有时间在看看。

2.pgdir[PDX(va)] |= perm;// 子页表项权限改变上一级也改变？？？ assert(kern_pgdir[0] & PTE_U);
chatGPT:虽然修改一个子页表项的访问权限不会影响到其父页表项的访问权限，但是如果修改了父页表项的访问权限，会影响到所有映射到该物理页面的虚拟地址空间的访问权限。

3.check_kern_pgdir()的assert(check_va2pa(pgdir, UPAGES + i) == PADDR(pages) + i);调试好久不知道为啥错误
1>主要是boot_map_region函数错误导致。
    last没有计算对，for循环没有展开。
    pgdir_walk中传入va参数错误。