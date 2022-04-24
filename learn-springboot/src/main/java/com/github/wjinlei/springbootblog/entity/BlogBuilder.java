package com.github.wjinlei.springbootblog.entity;

import java.time.Instant;

public final class BlogBuilder {
    private Integer id;
    private String title;
    private String description;
    private String content;
    private Boolean atIndex;
    private Integer userId;
    private User user;
    private Instant createdAt;
    private Instant updatedAt;

    private BlogBuilder() {
    }

    public static BlogBuilder aBlog() {
        return new BlogBuilder();
    }

    public BlogBuilder withId(Integer id) {
        this.id = id;
        return this;
    }

    public BlogBuilder withTitle(String title) {
        this.title = title;
        return this;
    }

    public BlogBuilder withDescription(String description) {
        this.description = description;
        return this;
    }

    public BlogBuilder withContent(String content) {
        this.content = content;
        return this;
    }

    public BlogBuilder withAtIndex(Boolean atIndex) {
        this.atIndex = atIndex;
        return this;
    }

    public BlogBuilder withUserId(Integer userId) {
        this.userId = userId;
        return this;
    }

    public BlogBuilder withUser(User user) {
        this.user = user;
        return this;
    }

    public BlogBuilder withCreatedAt(Instant createdAt) {
        this.createdAt = createdAt;
        return this;
    }

    public BlogBuilder withUpdatedAt(Instant updatedAt) {
        this.updatedAt = updatedAt;
        return this;
    }

    public Blog build() {
        Blog blog = new Blog();
        blog.setId(id);
        blog.setTitle(title);
        blog.setDescription(description);
        blog.setContent(content);
        blog.setAtIndex(atIndex);
        blog.setUserId(userId);
        blog.setUser(user);
        blog.setCreatedAt(createdAt);
        blog.setUpdatedAt(updatedAt);
        return blog;
    }
}
