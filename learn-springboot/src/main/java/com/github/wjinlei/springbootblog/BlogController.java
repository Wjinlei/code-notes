package com.github.wjinlei.springbootblog;

import com.github.wjinlei.springbootblog.entity.Blog;
import com.github.wjinlei.springbootblog.entity.BlogResult;
import com.github.wjinlei.springbootblog.entity.User;
import com.github.wjinlei.springbootblog.service.BlogService;
import com.github.wjinlei.springbootblog.service.UserService;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PatchMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

@RestController
public class BlogController {
    private final BlogService blogService;
    private final UserService userService;

    public BlogController(BlogService blogService, UserService userService) {
        this.blogService = blogService;
        this.userService = userService;
    }

    @PostMapping("/blog")
    @ResponseBody
    public BlogResult postBlog(@RequestBody Map<String, Object> params) {
        /* Check user is login */
        User user = sessionGetUser();
        if (user == null) return BlogResult.fail("登录后才能操作");

        return blogService.insert(user.getId(), (String) params.get("title"), (String) params.get("description"), (String) params.get("content"), (Boolean) params.get("atIndex"));
    }

    @DeleteMapping("/blog/{blogId}")
    @ResponseBody
    public BlogResult deleteBlog(@PathVariable("blogId") Integer id) {
        /* Check user is login */
        User user = sessionGetUser();
        if (user == null) return BlogResult.fail("登录后才能操作");

        /* Check blog */
        Blog blog = (Blog) blogService.selectById(id).getData();
        if (blog == null) return BlogResult.fail("博客不存在");
        if (!blog.getUserId().equals(user.getId())) return BlogResult.fail("无法删除别人的博客");

        return blogService.delete(id);
    }

    @PatchMapping("/blog/{blogId}")
    @ResponseBody
    public BlogResult patchBlog(@PathVariable("blogId") Integer id, @RequestBody Map<String, Object> params) {
        /* Check user is login */
        User user = sessionGetUser();
        if (user == null) return BlogResult.fail("登录后才能操作");

        /* Check blog */
        Blog blog = (Blog) blogService.selectById(id).getData();
        if (blog == null) return BlogResult.fail("博客不存在");
        if (!blog.getUserId().equals(user.getId())) return BlogResult.fail("无法修改别人的博客");

        blog.setId(id);
        blog.setDescription((String) params.get("description"));
        blog.setTitle((String) params.get("title"));
        blog.setContent((String) params.get("content"));
        blog.setUserId(user.getId());
        blog.setAtIndex((Boolean) params.get("atIndex"));
        return blogService.update(blog);
    }

    @GetMapping("/blog/{blogId}")
    @ResponseBody
    public BlogResult getBlogById(@PathVariable(value = "blogId") Integer id) {
        return blogService.selectById(id);
    }

    @GetMapping("/blog")
    @ResponseBody
    public BlogResult getBlog(@RequestParam("page") Integer page,
                              @RequestParam(value = "userId", required = false) Integer userId,
                              @RequestParam(value = "atIndex", required = false) Boolean atIndex) {
        if (page == null || page < 0) page = 1;
        return blogService.select(page, 20, userId, atIndex);
    }

    private User sessionGetUser() {
        Authentication session = SecurityContextHolder.getContext().getAuthentication();
        return userService.selectUserByUsername(session == null ? null : session.getName());
    }
}
