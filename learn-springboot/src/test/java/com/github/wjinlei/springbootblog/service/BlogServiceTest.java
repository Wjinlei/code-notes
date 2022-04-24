package com.github.wjinlei.springbootblog.service;

import com.github.wjinlei.springbootblog.dao.BlogMapper;
import com.github.wjinlei.springbootblog.entity.Blog;
import com.github.wjinlei.springbootblog.entity.BlogResult;
import com.github.wjinlei.springbootblog.entity.User;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import java.time.Instant;
import java.util.ArrayList;

import static org.mockito.Mockito.any;
import static org.mockito.Mockito.anyInt;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

@ExtendWith(MockitoExtension.class)
public class BlogServiceTest {
    @Mock
    BlogMapper mockBlogMapper;

    @InjectMocks
    BlogService blogService;

    @Test
    public void testSelectAllOk() {
        when(mockBlogMapper.selectAll(anyInt(), anyInt(), any(), any()))
                .thenReturn(new ArrayList<>());
        BlogResult blogResult = blogService.select(1, 20, 1, true);
        verify(mockBlogMapper).selectAll(anyInt(), anyInt(), anyInt(), any());
        Assertions.assertEquals("ok", blogResult.getStatus());
        Assertions.assertEquals("获取成功", blogResult.getMsg());
    }

    @Test
    public void testSelectAllFail() {
        when(mockBlogMapper.selectAll(anyInt(), anyInt(), any(), any()))
                .thenThrow(new RuntimeException());
        BlogResult blogResult = blogService.select(1, 20, 1, true);
        verify(mockBlogMapper).selectAll(anyInt(), anyInt(), anyInt(), any());
        Assertions.assertEquals("fail", blogResult.getStatus());
        Assertions.assertEquals("系统异常", blogResult.getMsg());
    }

    @Test
    public void testSelectByIdOk() {
        when(mockBlogMapper.selectById(anyInt())).thenReturn(new Blog());
        BlogResult blogResult = blogService.selectById(1);
        verify(mockBlogMapper).selectById(anyInt());
        Assertions.assertEquals("ok", blogResult.getStatus());
        Assertions.assertEquals("获取成功", blogResult.getMsg());
    }

    @Test
    public void testSelectByIdFail() {
        when(mockBlogMapper.selectById(anyInt())).thenThrow(new RuntimeException());
        BlogResult blogResult = blogService.selectById(1);
        verify(mockBlogMapper).selectById(anyInt());
        Assertions.assertEquals("fail", blogResult.getStatus());
        Assertions.assertEquals("系统异常", blogResult.getMsg());
    }

    @Test
    public void testInsertOk() {
        BlogResult insert = blogService.insert(
                1,
                "测试文章",
                "测试文章",
                "这是一篇测试文章",
                true);
        verify(mockBlogMapper).insert(any());
        Assertions.assertEquals("ok", insert.getStatus());
        Assertions.assertEquals("创建成功", insert.getMsg());

    }

    @Test
    public void testInsertFail() {
        when(mockBlogMapper.insert(any())).thenThrow(new RuntimeException());
        BlogResult blogResult = blogService.insert(
                1,
                "测试文章",
                "测试文章",
                "这是一篇测试文章",
                true);
        Assertions.assertEquals("fail", blogResult.getStatus());
        Assertions.assertEquals("系统异常", blogResult.getMsg());
    }

    @Test
    public void testUpdateOk() {
        BlogResult update = blogService.update(newBlog());
        verify(mockBlogMapper).update(any());
        Assertions.assertEquals("ok", update.getStatus());
        Assertions.assertEquals("修改成功", update.getMsg());
    }

    @Test
    public void testUpdateFail() {
        when(mockBlogMapper.update(any())).thenThrow(new RuntimeException());
        BlogResult blogResult = blogService.update(newBlog());
        Assertions.assertEquals("fail", blogResult.getStatus());
        Assertions.assertEquals("系统异常", blogResult.getMsg());
    }

    @Test
    public void testDeleteOk() {
        BlogResult delete = blogService.delete(1);
        verify(mockBlogMapper).delete(anyInt());
        Assertions.assertEquals("ok", delete.getStatus());
        Assertions.assertEquals("删除成功", delete.getMsg());
    }

    @Test
    public void testDeleteFail() {
        when(mockBlogMapper.delete(anyInt())).thenThrow(new RuntimeException());
        BlogResult delete = blogService.delete(1);
        Assertions.assertEquals("fail", delete.getStatus());
        Assertions.assertEquals("系统异常", delete.getMsg());
    }

    private Blog newBlog() {
        User user = new User(
                1,
                "admin",
                "admin123",
                "https://avatars.dicebear.com/api/human/rin1234.svg?mood[]=happy",
                Instant.now(),
                Instant.now());

        return new Blog(
                1,
                "测试文章",
                "测试文章",
                "这是一篇测试文章",
                true,
                1,
                user,
                Instant.now(),
                Instant.now());
    }
}
