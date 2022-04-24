package com.github.wjinlei.dao;

import java.io.File;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class CrawlerJdbcDao implements CrawlerDao {
    private static Connection connection;

    public CrawlerJdbcDao() {
        File projectDir = new File(System.getProperty("basedir", System.getProperty("user.dir")));
        String jdbcUrl = "jdbc:h2:file:" + new File(projectDir, "news").getAbsolutePath();
        try {
            connection = DriverManager.getConnection(jdbcUrl, "root", "toor");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Delete link from LINKS_UN_HANDLED
     *
     * @param link http or https link
     * @throws SQLException SQLException
     */
    @Override
    public void deleteLinksUnHandled(String link) throws SQLException {
        updateLink("DELETE FROM LINKS_UN_HANDLED WHERE link = ?", link);
    }

    /**
     * Insert into link to LINKS_UN_HANDLED
     *
     * @param link http or https link
     * @throws SQLException SQLException
     */
    @Override
    public void updateLinksUnHandled(String link) throws SQLException {
        updateLink("INSERT INTO LINKS_UN_HANDLED(link) VALUES ( ? )", link);
    }

    /**
     * Insert into link to LINKS_IN_HANDLED
     *
     * @param link http or https link
     * @throws SQLException SQLException
     */
    @Override
    public void updateLinksInHandled(String link) throws SQLException {
        updateLink("INSERT INTO LINKS_IN_HANDLED(link) VALUES ( ? )", link);
    }

    /**
     * Insert into news
     *
     * @param title   news title
     * @param content news content
     * @param url     news url
     * @throws SQLException SQLException
     */
    @Override
    public void updateNews(String title, String content, String url) throws SQLException {
        try (PreparedStatement preparedStatement
                     = connection.prepareStatement("INSERT INTO NEWS(title, content, url) VALUES ( ?, ?, ? )")) {
            preparedStatement.setString(1, title);
            preparedStatement.setString(2, content);
            preparedStatement.setString(3, url);
            preparedStatement.executeUpdate();
        }
    }

    /**
     * Get link from LINKS_IN_HANDLED
     *
     * @param url http or https link
     * @return ResultSet
     * @throws SQLException SQLException
     */
    @Override
    public boolean selectLinksInHandled(String url) throws SQLException {
        try (ResultSet resultSet = queryLink("SELECT link FROM LINKS_IN_HANDLED WHERE link = ?", url)) {
            return resultSet.next();
        }
    }

    /**
     * Get a link from LINKS_UN_HANDLED
     *
     * @return ResutSet
     * @throws SQLException SQLException
     */
    @Override
    public synchronized String removeLinksUnHandled() throws SQLException {
        try (ResultSet resultSet = query("SELECT link FROM LINKS_UN_HANDLED LIMIT 1")) {
            if (resultSet.next()) {
                String link = resultSet.getString(1);
                if (link != null) {
                    deleteLinksUnHandled(link);
                    return link;
                }
            }
        }
        return null;
    }

    /**
     * Execute query
     *
     * @param sql sql
     * @return ResultSet
     * @throws SQLException SQLException
     */
    private ResultSet query(String sql) throws SQLException {
        return connection.prepareStatement(sql).executeQuery();
    }

    /**
     * Execute query for link
     *
     * @param sql  sql
     * @param link http or https link
     * @return ResultSet
     * @throws SQLException SQLException
     */
    private ResultSet queryLink(String sql, String link) throws SQLException {
        PreparedStatement preparedStatement = connection.prepareStatement(sql);
        preparedStatement.setString(1, link);
        return preparedStatement.executeQuery();
    }

    /**
     * Update link
     *
     * @param sql  sql
     * @param link http or https link
     * @throws SQLException SQLException
     */
    private void updateLink(String sql, String link) throws SQLException {
        try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, link);
            preparedStatement.executeUpdate();
        }
    }
}
