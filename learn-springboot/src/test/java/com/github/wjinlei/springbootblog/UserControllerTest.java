package com.github.wjinlei.springbootblog;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.github.wjinlei.springbootblog.service.UserService;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.mockito.junit.jupiter.MockitoExtension;
import org.springframework.http.MediaType;
import org.springframework.mock.web.MockHttpSession;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.test.context.junit.jupiter.SpringExtension;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.MvcResult;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;
import org.springframework.test.web.servlet.setup.MockMvcBuilders;

import javax.servlet.http.HttpSession;
import java.nio.charset.StandardCharsets;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

@ExtendWith(MockitoExtension.class)
@ExtendWith(SpringExtension.class)
class UserControllerTest {
    private MockMvc mockMvc; /* 测试Controller必须的,模拟各种请求 */

    @Mock
    private UserService userService;
    @Mock
    private AuthenticationManager authenticationManager;

    private final BCryptPasswordEncoder bCryptPasswordEncoder = new BCryptPasswordEncoder();

    /* 每次调用测试方法之前,都会执行 */
    @BeforeEach
    void setUp() {
        mockMvc = MockMvcBuilders.standaloneSetup(new UserController(userService, authenticationManager)).build();
    }

    @Test
    void testAuthByDefault() throws Exception {
        privateTestGet("/auth", "请先登录");
    }

    @Test
    void testAuthByLogin() throws Exception {
        privateTestGet("/auth", "请先登录");
        privateTestAuthWithLogin("username", "password", "用户已登录");
    }

    @Test
    void testLogin() throws Exception {
        privateTestAuthWithLogin("username", "password", "用户已登录");
    }


    @Test
    void testRegister() throws Exception {
        privateTestPostUsernameAndPassword("/auth/register", "username_jerry1996", "test123", "用户名,长度1到15个字符");

        privateTestPostUsernameAndPassword("/auth/register", "", "test123", "用户名,长度1到15个字符");

        privateTestPostUsernameAndPassword("/auth/register", "username", "test", "密码,长度6到16个任意字符");

        privateTestPostUsernameAndPassword("/auth/register", "username", "password_jerry1996", "密码,长度6到16个任意字符");

        privateTestPostUsernameAndPassword("/auth/register", "username", "password", "注册成功");
    }

    @Test
    void testLogout() throws Exception {
        privateTestAuthWithLogin("username", "password", "用户已登录");
        privateTestGet("/auth/logout", "注销成功");
        privateTestGet("/auth", "请先登录");
    }

    private void privateTestAuthWithLogin(String username, String password, String content) throws Exception {
        Mockito.when(userService.loadUserByUsername(username))
                .thenReturn(new User(username, bCryptPasswordEncoder.encode(password), Collections.emptyList()));
        Mockito.when(userService.selectUserByUsername(username))
                .thenReturn(new com.github.wjinlei.springbootblog.entity.User(username, password));
        MvcResult mvcResult = privateTestPostUsernameAndPassword("/auth/login", username, password, "登录成功");
        HttpSession session = mvcResult.getRequest().getSession(); /* 从请求中获取session */
        /* 再次发起GET /auth 请求,并断言结果中包含"用户已登录" */
        mockMvc.perform(MockMvcRequestBuilders.get("/auth").session((MockHttpSession) session))
                .andExpect(MockMvcResultMatchers.status().isOk())
                .andExpect(result -> Assertions.assertTrue(result.getResponse().getContentAsString(StandardCharsets.UTF_8).contains(content)));
    }

    private MvcResult privateTestPostUsernameAndPassword(String url, String username, String password, String content) throws Exception {
        Map<String, String> params1 = new HashMap<>();
        params1.put("username", username);
        params1.put("password", password);
        return mockMvc.perform(MockMvcRequestBuilders.post(url)
                        .contentType(MediaType.APPLICATION_JSON)
                        .content(new ObjectMapper().writeValueAsString(params1)))
                .andExpect(MockMvcResultMatchers.status().isOk())
                .andExpect(result -> Assertions.assertTrue(result.getResponse().getContentAsString(StandardCharsets.UTF_8).contains(content)))
                .andReturn();
    }

    private void privateTestGet(String url, String content) throws Exception {
        /* 执行一个Get请求,请求auth接口,并预期的返回的状态码是 200,并且响应中包含"用户尚未登录" */
        mockMvc.perform(MockMvcRequestBuilders.get(url))
                .andExpect(MockMvcResultMatchers.status().isOk())
                .andExpect(result -> Assertions.assertTrue(result.getResponse().getContentAsString(StandardCharsets.UTF_8).contains(content)));
    }
}
