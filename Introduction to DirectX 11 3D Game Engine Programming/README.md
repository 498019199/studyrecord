2024年11月17日 23点58分
4.4 框架设计 Adapt 适配器，windowApp 窗口和消息循环，RenderDevice Device和context，GameTick 计时器从

# debug 记录
## 1.error LNK2019: 无法解析的外部符号 D3D11CreateDevice，函数XXX. fatal error LNK1120: 1 个无法解析的外部命令
- a. 怀疑文件名空格影响，` `替换`_` 。不行
- b. D3D11CreateDevice 跟dx11库名冲突，换类名。不行
- c. 搞错了，**是无法链接dx11的** “error LNK2019: 无法解析的外部符号 D3D11CreateDevice”，不是自己的库文件中的函数。
---
解决方案：
**dx11用书中的方法链接**, 下载官方库，重新连接，没有报错。
