package com.github.wjinlei.springbootblog.dao;

import com.github.wjinlei.springbootblog.entity.Blog;
import org.apache.ibatis.session.SqlSession;
import org.springframework.stereotype.Service;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Service
public class BlogMapper {
    private final String NAMESPACE = "blog.mapper";
    private final SqlSession sqlSession;

    public BlogMapper(SqlSession sqlSession) {
        this.sqlSession = sqlSession;
    }

    public int insert(Blog blog) {
        return sqlSession.insert(NAMESPACE + ".insert", blog);
    }

    public int delete(Integer id) {
        return sqlSession.delete(NAMESPACE + ".delete", id);
    }

    public int update(Blog blog) {
        return sqlSession.update(NAMESPACE + ".update", blog);
    }

    public List<Blog> selectAll(Integer pageNumber, Integer pageSize, Integer userId, Boolean atIndex) {
        Map<String, Object> param = new HashMap<>();
        param.put("offset", (pageNumber - 1) * pageSize);
        param.put("limit", pageSize);
        param.put("atIndex", atIndex);
        param.put("user_id", userId);
        return sqlSession.selectList(NAMESPACE + ".select", param);
    }

    public Blog selectById(Integer id) {
        return sqlSession.selectOne(NAMESPACE + ".selectWhereId", id);
    }
}
