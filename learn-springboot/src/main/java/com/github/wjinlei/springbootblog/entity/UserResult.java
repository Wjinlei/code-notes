package com.github.wjinlei.springbootblog.entity;

public class UserResult extends Result<User> {
    private boolean login;

    private UserResult(String status, String msg, User data) {
        super(status, msg, data);
    }

    private UserResult(String status, String msg, User data, boolean login) {
        super(status, msg, data);
        this.login = login;
    }

    public static UserResult ok(String msg) {
        return new UserResult("ok", msg, null);
    }

    public static UserResult ok(String msg, User data, boolean login) {
        return new UserResult("ok", msg, data, login);
    }

    public static UserResult fail(String msg) {
        return new UserResult("fail", msg, null);
    }

    public boolean isLogin() {
        return login;
    }
}
