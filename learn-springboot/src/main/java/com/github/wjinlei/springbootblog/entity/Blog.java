package com.github.wjinlei.springbootblog.entity;

import com.fasterxml.jackson.annotation.JsonIgnore;

import java.time.Instant;

public class Blog {
    private Integer id;
    private String title;
    private String description;
    private String content;
    private Boolean atIndex;
    @JsonIgnore
    private Integer userId;
    private User user;
    private Instant createdAt;
    private Instant updatedAt;

    public Blog() {
    }

    public Blog(Integer id, String title, String description, String content, Boolean atIndex, Integer userId, User user, Instant createdAt, Instant updatedAt) {
        this.id = id;
        this.title = title;
        this.description = description;
        this.content = content;
        this.atIndex = atIndex;
        this.userId = userId;
        this.user = user;
        this.createdAt = createdAt;
        this.updatedAt = updatedAt;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public Boolean getAtIndex() {
        return atIndex;
    }

    public void setAtIndex(Boolean atIndex) {
        this.atIndex = atIndex;
    }

    public Integer getUserId() {
        return userId;
    }

    public void setUserId(Integer userId) {
        this.userId = userId;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public Instant getCreatedAt() {
        return createdAt;
    }

    public void setCreatedAt(Instant createdAt) {
        this.createdAt = createdAt;
    }

    public Instant getUpdatedAt() {
        return updatedAt;
    }

    public void setUpdatedAt(Instant updatedAt) {
        this.updatedAt = updatedAt;
    }
}
