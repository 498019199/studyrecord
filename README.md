lab->MIT6.828 study os. important boot load, paging, lock, mulpty task, file system, network
疑问：
1.在pmap.h中page2pa强转类型。48转32为啥是shr 0x3 %eax。不是直接舍弃，而是位移3bit.
2.pgdir[PDX(va)] |= perm;// 子页表项权限改变上一级也改变？？？ assert(kern_pgdir[0] & PTE_U);
