lab->MIT6.828 study os. important boot load, paging, lock, mulpty task, file system, network
疑问：
在pmap.h中page2pa强转类型。48转32为啥是shr 0x3 %eax。不是直接舍弃，而是位移3bit.