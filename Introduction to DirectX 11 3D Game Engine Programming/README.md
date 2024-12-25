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

xnamath.h(2716,52): warning C4838: 从“unsigned int”转换到“INT”需要收缩转换
warning C4005: “DXGI_ERROR_REMOTE_CLIENT_DISCONNECTED”: DXGI_ERROR_NOT_CURRENTLY_AVAILABLE 宏重定义 
winerror.h  dxgitype.h
临时用屏蔽警告
```
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4061")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4005")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4820")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5246")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4838")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4668")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4365")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5219")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5029")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5267")
```

