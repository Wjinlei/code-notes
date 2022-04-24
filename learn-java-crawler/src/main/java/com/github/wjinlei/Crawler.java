package com.github.wjinlei;

import com.github.wjinlei.dao.CrawlerDao;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.io.IOException;
import java.sql.SQLException;
import java.util.stream.Collectors;

public class Crawler extends Thread {
    private final CrawlerDao dao;

    public Crawler(CrawlerDao dao) {
        this.dao = dao;
    }

    @Override
    public void run() {
        String link;
        try {
            while ((link = dao.removeLinksUnHandled()) != null) {
                if (dao.selectLinksInHandled(link)) continue;
                if (isWantTo(link)) {
                    Document jsoup = parseHtmlToHrefAndInsertIntoLinksUnHandled(link);
                    jsoupCssSelectAirtcleAndParseToInsertIntoNews(jsoup, link);
                    dao.updateLinksInHandled(link);
                }
            }
        } catch (IOException | SQLException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Parse html to a tag, and insert into links_un_handled
     *
     * @param url http or https link
     * @return Jsoup Document
     * @throws SQLException SQLException
     * @throws IOException  IOException
     */
    private Document parseHtmlToHrefAndInsertIntoLinksUnHandled(String url) throws SQLException, IOException {
        Document jsoup = Jsoup.parse(httpGetHTML(url));
        for (Element a : jsoup.select("a")) {
            String href = a.attr("href");
            if (href.toLowerCase().startsWith("http")) {
                if (isWantTo(href)) {
                    dao.updateLinksUnHandled(href);
                }
            }
        }
        return jsoup;
    }

    /**
     * Get HTML content
     *
     * @param link http or https link
     * @return html body
     * @throws IOException IOException
     */
    private static String httpGetHTML(String link) throws IOException {
        if (link.startsWith("//")) {
            link = "https:" + link;
        }
        CloseableHttpClient document = HttpClients.createDefault();
        HttpGet request = new HttpGet(link);
        request.setHeader("User-Agent",
                "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/95.0.4638.69 Safari/537.36");
        try (CloseableHttpResponse response = document.execute(request)) {
            return EntityUtils.toString(response.getEntity());
        }
    }

    /**
     * Save news to database
     *
     * @param jsoup Jsoup parse
     */
    private void jsoupCssSelectAirtcleAndParseToInsertIntoNews(Document jsoup, String url) throws SQLException {
        Elements articles = jsoup.select("article");
        if (!articles.isEmpty()) {
            for (Element article : articles) {
                String title = article.select("h1.art_tit_h1")
                        .stream().map(Element::text).collect(Collectors.joining(","));
                String content = article.select("p.art_p")
                        .stream().map(Element::text).collect(Collectors.joining("\n"));
                dao.updateNews(title, content, url);
                System.out.println(url);
                System.out.println(title);
            }
        }
    }

    /**
     * Determine whether it is the desired link
     *
     * @param link http or https link
     * @return true or false
     */
    private static boolean isWantTo(String link) {
        return isNotLogin(link) && (isIndex(link) || isNews(link));
    }

    /**
     * Determine whether it is the home page
     *
     * @param link http or https link
     * @return true or false
     */
    private static boolean isIndex(String link) {
        return "https://sina.cn".equals(link);
    }

    /**
     * Determine whether it is a login page
     *
     * @param link http or https link
     * @return true or false
     */
    private static boolean isNotLogin(String link) {
        return !link.contains("passport.sina.cn");
    }

    /**
     * Determine whether it is a news page
     *
     * @param link http or https link
     * @return true or false
     */
    private static boolean isNews(String link) {
        return link.contains("news.sina.cn");
    }
}
