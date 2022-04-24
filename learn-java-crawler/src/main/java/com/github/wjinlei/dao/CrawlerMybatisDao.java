package com.github.wjinlei.dao;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;

public class CrawlerMybatisDao implements CrawlerDao {
    private final SqlSessionFactory sqlSessionFactory;
    private final String NAMESPACE = "com.github.wjinlei.mybatis";

    public CrawlerMybatisDao() {
        String resource = "db/mybatis/mybatis-config.xml";
        try (InputStream inputStream = Resources.getResourceAsStream(resource)) {
            sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void deleteLinksUnHandled(String link) {
        try (SqlSession sqlSession = sqlSessionFactory.openSession(true)) {
            sqlSession.delete(NAMESPACE + ".deleteFromLinksUnHandledWhereLinkIs", link);
        }
    }

    @Override
    public void updateLinksUnHandled(String link) {
        updateLink(link, "LINKS_UN_HANDLED");
    }

    @Override
    public void updateLinksInHandled(String link) {
        updateLink(link, "LINKS_IN_HANDLED");
    }


    @Override
    public void updateNews(String title, String content, String url) {
        try (SqlSession sqlSession = sqlSessionFactory.openSession(true)) {
            HashMap<String, Object> hashMap = new HashMap<>();
            hashMap.put("title", title);
            hashMap.put("content", content);
            hashMap.put("url", url);
            sqlSession.update(NAMESPACE + ".updateNews", hashMap);
        }
    }

    @Override
    public boolean selectLinksInHandled(String url) {
        try (SqlSession sqlSession = sqlSessionFactory.openSession()) {
            Object result = sqlSession.selectOne(NAMESPACE + ".selectLinkFromLinksInHandledWhereLinkIs", url);
            if (result != null) {
                return (boolean) result;
            }
            return false;
        }
    }

    @Override
    public synchronized String removeLinksUnHandled() {
        try (SqlSession sqlSession = sqlSessionFactory.openSession()) {
            String link = sqlSession.selectOne(NAMESPACE + ".selectLinkFromLinksUnHandledLimit1");
            if (link != null) {
                deleteLinksUnHandled(link);
                return link;
            }
        }
        return null;
    }

    private void updateLink(String link, String links_un_handled) {
        try (SqlSession sqlSession = sqlSessionFactory.openSession(true)) {
            HashMap<String, Object> hashMap = new HashMap<>();
            hashMap.put("table_name", links_un_handled);
            hashMap.put("link", link);
            sqlSession.update(NAMESPACE + ".updateLinksUnHandled", hashMap);
        }
    }
}
