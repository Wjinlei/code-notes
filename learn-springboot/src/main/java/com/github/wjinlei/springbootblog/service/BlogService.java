package com.github.wjinlei.springbootblog.service;

import com.github.wjinlei.springbootblog.dao.BlogMapper;
import com.github.wjinlei.springbootblog.entity.Blog;
import com.github.wjinlei.springbootblog.entity.BlogBuilder;
import com.github.wjinlei.springbootblog.entity.BlogResult;
import org.springframework.stereotype.Service;

@Service
public class BlogService {
    private final BlogMapper blogMapper;

    public BlogService(BlogMapper blogMapper, UserService userService) {
        this.blogMapper = blogMapper;
    }

    public BlogResult insert(Integer userId,
                             String title,
                             String description,
                             String content,
                             Boolean atIndex) {
        Blog blog = BlogBuilder.aBlog()
                .withTitle(title)
                .withDescription(description.isEmpty() ? content : description)
                .withContent(content)
                .withUserId(userId)
                .withAtIndex(atIndex).build();
        try {
            blogMapper.insert(blog);
        } catch (Exception e) {
            return BlogResult.fail();
        }
        return BlogResult.ok("创建成功", blogMapper.selectById(blog.getId()));
    }

    public BlogResult update(Blog blog) {
        try {
            blogMapper.update(blog);
        } catch (Exception e) {
            return BlogResult.fail();
        }
        return BlogResult.ok("修改成功", blogMapper.selectById(blog.getId()));
    }

    public BlogResult selectById(Integer id) {
        try {
            return BlogResult.ok(blogMapper.selectById(id));
        } catch (Exception e) {
            return BlogResult.fail();
        }
    }

    public BlogResult select(Integer pageNumber, Integer pageSize, Integer userId, Boolean atIndex) {
        try {
            return BlogResult.ok(blogMapper.selectAll(pageNumber, pageSize, userId, atIndex));
        } catch (Exception e) {
            return BlogResult.fail();
        }
    }

    public BlogResult delete(Integer id) {
        try {
            blogMapper.delete(id);
        } catch (Exception e) {
            return BlogResult.fail();
        }
        return BlogResult.ok("删除成功", null);
    }
}
