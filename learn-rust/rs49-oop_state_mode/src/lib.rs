// State trait 定义了所有不同状态的博文所共享的行为
trait State {
    // 审核博文方法
    fn request_review(self: Box<Self>) -> Box<dyn State>;

    // 发布博文方法
    fn approve(self: Box<Self>) -> Box<dyn State>;

    // content 方法的默认实现来返回一个空字符串 slice。
    // 这意味着无需为 Draft 和 PendingReview 结构体实现 content 了。
    // 这两个状态调用content时都会返回空
    fn content<'a>(&self, _post: &'a Post) -> &'a str {
        ""
    }
}

struct Draft {}
// Draft 状态实现了State，它代表博文(初始)状态
impl State for Draft {
    fn request_review(self: Box<Self>) -> Box<dyn State> {
        Box::new(PendingReview {}) // 审核后将状态改变为PendingPeview状态
    }
    fn approve(self: Box<Self>) -> Box<dyn State> {
        self
    }
}

struct PendingReview {}
// PendingReview状态实现了State，它代表博文(审核)状态
impl State for PendingReview {
    fn request_review(self: Box<Self>) -> Box<dyn State> {
        self
    }
    fn approve(self: Box<Self>) -> Box<dyn State> {
        Box::new(Published {}) // 发布后将状态改变为Published状态
    }
}

struct Published {}
// Published状态实现了State，它代表博文(发布)状态
impl State for Published {
    fn request_review(self: Box<Self>) -> Box<dyn State> {
        self
    }
    fn approve(self: Box<Self>) -> Box<dyn State> {
        self
    }

    // Published 结构体会覆盖 content 方法并会返回 post.content 的值。
    fn content<'a>(&self, post: &'a Post) -> &'a str {
        &post.content
    }
}

pub struct Post {
    state: Option<Box<dyn State>>,
    content: String,
}

impl Post {
    pub fn new() -> Post {
        // 当创建新的 Post 时，我们将其 state 字段设置为一个存放了 Box 的 Some 值。
        // 这个 Box 指向一个 Draft 结构体新实例。这确保了无论何时新建一个 Post 实例，它都会从草案开始。
        // 因为 Post 的 state 字段是私有的，也就无法创建任何其他状态的 Post 了！。
        // Post::new 函数中将 content 设置为新建的空 String。
        Post {
            state: Some(Box::new(Draft {})),
            content: String::new(),
        }
    }

    // 添加博文内容
    pub fn add_text(&mut self, text: &str) {
        self.content.push_str(text);
    }

    // 审核博文内容
    pub fn request_review(&mut self) {
        if let Some(s) = self.state.take() {
            self.state = Some(s.request_review())
        }
    }

    // 发布博文内容
    pub fn approve(&mut self) {
        // take 方法会取出 Some 而留下 None。
        if let Some(s) = self.state.take() {
            self.state = Some(s.approve())
        }
    }

    // 返回博文内容
    pub fn content(&self) -> &str {
        // 因为目标是将所有像这样的规则保持在实现了 State 的结构体中
        // 我们将调用 state 中的值的 content 方法并传递博文实例（也就是 self）作为参数。
        // 接着返回 state 值的 content 方法的返回值。

        // 这里调用 Option 的 as_ref 方法是因为需要 Option 中值的引用而不是获取其所有权。
        // 因为 state 是一个 Option<Box<State>>，调用 as_ref 会返回一个 Option<&Box<State>>。
        // 如果不调用 as_ref，将会得到一个错误，因为不能将 state 移动出借用的 &self 函数参数。

        // 接着调用 unwrap 方法，这里我们知道它永远也不会 panic
        // 因为 Post 的所有方法都确保在他们返回时 state 会有一个 Some 值。
        // 这就是"当我们比编译器知道更多的情况"部分讨论过的我们知道 None 是不可能的而编译器却不能理解的情况。
        self.state.as_ref().unwrap().content(self)
    }
}
