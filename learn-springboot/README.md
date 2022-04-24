## Springboot-blog project

![index](/index.png)

## 快速开始

克隆项目

```shell
git clone https://github.com/Wjinlei/springboot-blog.git
```

- [x] 你需要一个`Mysql`,并且创建一个名为`blog`的数据库,我建议使用`Docker`

```shell
sudo docker run --name mysql -p 3306:3306 -e MYSQL_ROOT_PASSWORD=root -e MYSQL_DATABASE=blog -d mysql:8.0.27
```

- [x] 你需要迁移数据库,项目使用了`flyway`,你可以通过如下命令建立初始表

```shell
mvn flyway:migrate
```

## 构建镜像

如果你有兴趣,你还可以构建`Docker镜像`,项目提供了`Dockerfile`,  
但在构建镜像前,你需要修改项目的数据库连接地址为你的数据库服务器地址

- 你可以通过如下命令构建一个镜像

```shell
sudo docker build . -t springboot-blog
```

- 启动镜像

```shell
sudo docker run --name springboot-blog -p 8080:8080 springboot-blog
```