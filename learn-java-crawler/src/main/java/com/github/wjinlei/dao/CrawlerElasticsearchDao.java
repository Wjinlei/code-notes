package com.github.wjinlei.dao;

import org.apache.http.HttpHost;
import org.elasticsearch.action.delete.DeleteRequest;
import org.elasticsearch.action.get.GetRequest;
import org.elasticsearch.action.get.GetResponse;
import org.elasticsearch.action.index.IndexRequest;
import org.elasticsearch.action.search.SearchRequest;
import org.elasticsearch.action.search.SearchResponse;
import org.elasticsearch.client.RequestOptions;
import org.elasticsearch.client.RestClient;
import org.elasticsearch.client.RestHighLevelClient;
import org.elasticsearch.client.indices.CreateIndexRequest;
import org.elasticsearch.client.indices.GetIndexRequest;
import org.elasticsearch.search.builder.SearchSourceBuilder;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class CrawlerElasticsearchDao implements CrawlerDao {
    private static final String unHandled = "links_un_handled";
    private static final String inHandled = "links_in_handled";
    private static final String news = "news";

    public CrawlerElasticsearchDao() {
        createIndex(unHandled);
        createIndex(inHandled);
        createIndex(news);
        updateLink("https://sina.cn", unHandled);

        try {
            Thread.sleep(3000); // Waiting for initialization
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private RestHighLevelClient newClient() {
        return new RestHighLevelClient(RestClient.builder(
                new HttpHost("127.0.0.1", 9200, "http")));
    }

    @Override
    public void deleteLinksUnHandled(String link) {
        try (RestHighLevelClient client = newClient()) {
            client.delete(new DeleteRequest(unHandled, link), RequestOptions.DEFAULT);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void updateLinksUnHandled(String link) {
        updateLink(link, unHandled);
    }

    @Override
    public void updateLinksInHandled(String link) {
        updateLink(link, inHandled);
    }

    private void updateLink(String link, String index) {
        Map<String, Object> document = new HashMap<>();
        document.put("link", link);
        try (RestHighLevelClient client = newClient()) {
            client.index(new IndexRequest(index).source(document).id(link), RequestOptions.DEFAULT);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void updateNews(String title, String content, String url) {
        Map<String, Object> document = new HashMap<>();
        document.put("title", title);
        document.put("content", content);
        document.put("url", url);
        try (RestHighLevelClient client = newClient()) {
            client.index(new IndexRequest(news).source(document).id(url), RequestOptions.DEFAULT);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public boolean selectLinksInHandled(String link) {
        try (RestHighLevelClient client = newClient()) {
            GetResponse response = client.get(new GetRequest(inHandled, link), RequestOptions.DEFAULT);
            return response.isExists();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public synchronized String removeLinksUnHandled() {
        try (RestHighLevelClient client = newClient()) {
            SearchRequest request = new SearchRequest(unHandled).source(new SearchSourceBuilder().size(1));
            SearchResponse response = client.search(request, RequestOptions.DEFAULT);
            if (response.getHits().getTotalHits().value < 1) return null;
            String link = (String) response.getHits().getAt(0).getSourceAsMap().get("link");
            if (link == null) return null;
            deleteLinksUnHandled(link);
            return link;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private void createIndex(String index) {
        try (RestHighLevelClient client = newClient()) {
            if (!client.indices().exists(new GetIndexRequest(index), RequestOptions.DEFAULT)) {
                CreateIndexRequest request = new CreateIndexRequest(index);
                client.indices().create(request, RequestOptions.DEFAULT);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
