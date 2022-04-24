package com.github.wjinlei.springbootblog;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.core.env.Environment;
import org.springframework.test.context.TestPropertySource;
import org.springframework.test.context.junit.jupiter.SpringExtension;

import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

@ExtendWith(SpringExtension.class)
/* 指定要测试SpringbootBlogApplication, 并指定一个随机端口,因为你不能占用正常的端口 */
@SpringBootTest(classes = SpringbootBlogApplication.class, webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
/* 指定一个测试的配置文件,因为真实的项目配置文件连接的数据库是3306,而我们测试数据库是3307 */
/* 我们可以在test包中新建一个resources/test.properties配置文件并修改端口为3307 */
@TestPropertySource(locations = "classpath:test.properties")
public class AppIntegrationTest {
    @Autowired
    Environment environment;

    /**
     * 测试首页能够访问
     */
    @Test
    void testAuthByDefault() throws IOException, InterruptedException {
        /* 获得随机启动的端口号 */
        String port = environment.getProperty("local.server.port");
        /* 使用Java 11 自带的httpclient库发送请求 */
        HttpClient client = HttpClient.newHttpClient();
        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create("http://localhost:" + port + "/auth"))
                .build();
        HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
        Assertions.assertEquals(200, response.statusCode());
        Assertions.assertTrue(response.body().contains("请先登录"));
    }
}
