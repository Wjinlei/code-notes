package com.github.wjinlei.dao;

import java.sql.SQLException;

public interface CrawlerDao {

    void deleteLinksUnHandled(String link) throws SQLException;

    void updateLinksUnHandled(String link) throws SQLException;

    void updateLinksInHandled(String link) throws SQLException;

    void updateNews(String title, String content, String url) throws SQLException;

    boolean selectLinksInHandled(String link) throws SQLException;

    String removeLinksUnHandled() throws SQLException;
}
