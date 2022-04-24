package com.github.wjinlei.springbootblog;

import com.github.wjinlei.springbootblog.entity.User;
import com.github.wjinlei.springbootblog.entity.UserResult;
import com.github.wjinlei.springbootblog.service.UserService;
import org.springframework.dao.DuplicateKeyException;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.BadCredentialsException;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

@RestController
public class UserController {
    private final UserService userService;
    private final AuthenticationManager authenticationManager;

    public UserController(UserService userService, AuthenticationManager authenticationManager) {
        this.userService = userService;
        this.authenticationManager = authenticationManager;
    }

    @GetMapping("/auth")
    public UserResult auth() {
        /* Check user is login */
        Authentication session = SecurityContextHolder.getContext().getAuthentication();
        User user = userService.selectUserByUsername(session == null ? null : session.getName());
        if (user == null) return UserResult.fail("请先登录!");

        return UserResult.ok("用户已登录", user, true);
    }

    @PostMapping("/auth/register")
    @ResponseBody
    public UserResult register(@RequestBody Map<String, String> body) {
        String username = body.get("username");
        String password = body.get("password");
        if (username.length() < 1 || username.length() > 15) return UserResult.fail("用户名,长度1到15个字符!");
        if (password.length() < 6 || password.length() > 16) return UserResult.fail("密码,长度6到16个任意字符!");

        try {
            userService.registerUser(username, password);
            return UserResult.ok("注册成功", userService.selectUserByUsername(username), false);
        } catch (DuplicateKeyException e) {
            return UserResult.fail("注册失败,用户已存在!");
        } catch (Exception e) {
            return UserResult.fail("注册失败");
        }
    }

    @PostMapping("/auth/login")
    public UserResult login(@RequestBody Map<String, String> body) {
        UserDetails userDetails;
        try {
            userDetails = userService.loadUserByUsername(body.get("username"));
        } catch (UsernameNotFoundException e) {
            return UserResult.fail("用户不存在!");
        }

        UsernamePasswordAuthenticationToken token = new UsernamePasswordAuthenticationToken(userDetails, body.get("password"), userDetails.getAuthorities());

        try {
            authenticationManager.authenticate(token);
            SecurityContextHolder.getContext().setAuthentication(token);
            return UserResult.ok("登录成功", userService.selectUserByUsername(token.getName()), true);
        } catch (BadCredentialsException e) {
            return UserResult.fail("密码错误");
        }
    }

    @GetMapping("/auth/logout")
    public UserResult logout() {
        if (SecurityContextHolder.getContext().getAuthentication() == null) return UserResult.fail("你已经登出!");
        SecurityContextHolder.clearContext();
        return UserResult.ok("注销成功");
    }
}
