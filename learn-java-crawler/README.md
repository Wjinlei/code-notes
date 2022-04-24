## Crawler project

此项目仅供学习交流，严禁用于商业用途

- 这是一个`JAVA`多线程爬虫,用于爬取[新浪](https://sina.cn)新闻
- 底层使用了`Elasticsearch`实现,你可以很方便的更换数据库
- [项目笔记](https://wjinlei.github.io/posts/exp-java-day13/)

## QuickStart

1. Clone project`git clone https://github.com/Wjinlei/project-test-crawler.git`
2. Start`Elasticsearch`,port:`9200`
3. Run`Main`

## Migrate to MySQL

1. 添加MySQL JDBC驱动

```xml
<!-- https://mvnrepository.com/artifact/mysql/mysql-connector-java -->
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.27</version>
</dependency>
```

2. 修改flyway连接配置

```xml
<url>jdbc:mysql://localhost:3306/news?characterEncoding=utf-8</url>
<user>root</user>
<password>toor</password>
```

3. 修改Mybatis的驱动和连接配置

- 值得注意的是新版的jdbc驱动class是`com.mysql.cj.jdbc.Driver`

```xml
<dataSource>
    <property name="driver" value="com.mysql.jdbc.Driver"/>
    <property name="url" value="jdbc:mysql://localhost:3306/news?characterEncoding=utf-8"/>
    <property name="username" value="root"/>
    <property name="password" value="toor"/>
</dataSource>
```

4. 在MySQL中创建`news`数据库,并指定`utf8mb4`编码
    - 注意MySQL帐号是`root`密码是`toor`

5. `mvn initialize`

## Migrate to H2

1. 添加H2 JDBC驱动

```xml
<!-- https://mvnrepository.com/artifact/com.h2database/h2 -->
<dependency>
   <groupId>com.h2database</groupId>
   <artifactId>h2</artifactId>
   <version>1.4.200</version>
</dependency>
```

2. 修改Flyway连接配置

```xml
<url>jdbc:h2:file:./news</url>
<user>root</user>
<password>toor</password>
```

3. 修改Mybatis的驱动和连接配置

```xml
<dataSource type="POOLED">
    <property name="driver" value="org.h2.Driver"/>
    <property name="url" value="jdbc:h2:file:./news"/>
    <property name="username" value="root"/>
    <property name="password" value="toor"/>
</dataSource>
```

4. `mvn initialize`