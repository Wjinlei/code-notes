CREATE TABLE user
(
    id         BIGINT PRIMARY KEY AUTO_INCREMENT,
    username   VARCHAR(100) NOT NULL,
    password   VARCHAR(100) NOT NULL,
    avatar     VARCHAR(500)          DEFAULT 'https://avatars.dicebear.com/api/human/rin1234.svg?mood[]=happy',
    created_at TIMESTAMP    NOT NULL DEFAULT NOW(),
    updated_at TIMESTAMP    NOT NULL DEFAULT NOW()
);

CREATE TABLE blog
(
    id          BIGINT PRIMARY KEY AUTO_INCREMENT,
    title       VARCHAR(100) NOT NULL,
    description VARCHAR(200),
    content     TEXT,
    atIndex     BOOL         NOT NULL DEFAULT 0,
    user_id     BIGINT       NOT NULL,
    created_at  TIMESTAMP    NOT NULL DEFAULT NOW(),
    updated_at  TIMESTAMP    NOT NULL DEFAULT NOW()
);

CREATE UNIQUE INDEX USER_USERNAME_UINDEX ON user (username);
CREATE UNIQUE INDEX BLOG_TITLE_UINDEX ON blog (title);
