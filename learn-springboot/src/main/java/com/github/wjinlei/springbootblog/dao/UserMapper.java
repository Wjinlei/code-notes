package com.github.wjinlei.springbootblog.dao;

import com.github.wjinlei.springbootblog.entity.User;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

@Mapper
public interface UserMapper {
    @Insert("INSERT INTO user (username, password) VALUES ( #{username}, #{password})")
    void registerUser(@Param("username") String username, @Param("password") String password);

    @Select("SELECT * FROM user WHERE username=#{username}")
    User selectUserByUsername(@Param("username") String username);
}
