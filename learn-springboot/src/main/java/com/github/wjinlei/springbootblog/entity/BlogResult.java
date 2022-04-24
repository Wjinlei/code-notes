package com.github.wjinlei.springbootblog.entity;

public class BlogResult extends Result<Object> {
    public static BlogResult fail(String msg) {
        return new BlogResult("fail", msg, null);
    }

    public static BlogResult fail() {
        return new BlogResult("fail", "系统异常", null);
    }

    public static BlogResult ok(Object data) {
        return new BlogResult("ok", "获取成功", data);
    }

    public static BlogResult ok(String msg, Object data) {
        return new BlogResult("ok", msg, data);
    }

    private BlogResult(String status, String msg, Object data) {
        super(status, msg, data);
    }
}
