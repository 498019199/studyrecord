FROM python:3.7

 # 设置pip源为国内源
 COPY pip.conf /root/.pip/pip.conf

# 在容器内/var/www/html/下创建 mysite1文件夹
RUN mkdir -p /var/www/html/mysite1
# 设置容器内工作目录
WORKDIR /var/www/html/mysite1
# 将当前目录文件加入到容器工作目录中（. 表示当前宿主机目录）
ADD . /var/www/html/mysite1


 # 利用 pip 安装依赖
 RUN pip install -r requirements.txt

 # https://zhuanlan.zhihu.com/p/141976805