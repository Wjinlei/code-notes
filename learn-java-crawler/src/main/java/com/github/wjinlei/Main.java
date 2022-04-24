package com.github.wjinlei;

import com.github.wjinlei.dao.CrawlerElasticsearchDao;

public class Main {
    public static void main(String[] args) {
        CrawlerElasticsearchDao crawlerElasticsearchDao = new CrawlerElasticsearchDao();
        for (int i = 0; i < 16; i++) {
            new Crawler(crawlerElasticsearchDao).start();
        }
    }
}
