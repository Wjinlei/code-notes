use rust_inherit::{Draw, Screen};

// 定义一个组件Button
pub struct Button {
    pub width: u32,
    pub height: u32,
    pub label: String,
}

// 为Button实现Draw trait
impl Draw for Button {
    fn draw(&self) {
        println!(
            "Button[{}],Width:{},Height:{}",
            self.label, self.width, self.height
        );
    }
}

// 实现一个SelectBox
struct SelectBox {
    width: u32,
    height: u32,
    options: Vec<String>,
}

// 为SelectBox实现Draw trait
impl Draw for SelectBox {
    fn draw(&self) {
        println!(
            "SelectBox[options:{:?}],Width:{},Height:{}",
            self.options, self.width, self.height
        );
    }
}

// 库使用者现在可以在他们的 main 函数中创建一个 Screen 实例。
// 至此可以通过将 SelectBox 和 Button 放入 Box<T> 转变为 trait 对象来增加组件。
// 接着可以调用 Screen 的 run 方法，它会调用每个组件的 draw 方法。
fn main() {
    let screen = Screen {
        components: vec![
            Box::new(Button {
                width: 25,
                height: 30,
                label: String::from("button1"),
            }),
            Box::new(SelectBox {
                width: 30,
                height: 15,
                options: vec![
                    String::from("Yes"),
                    String::from("Maybe"),
                    String::from("No"),
                ],
            }),
        ],
    };
    screen.run()
}
// 当编写库的时候，我们不知道何人会在何时增加 SelectBox 类型
// 不过 Screen 的实现能够操作并绘制这个新类型，因为 SelectBox 实现了 Draw trait，这意味着它实现了 draw 方法。

// 这个概念 —— 只关心值所反映的信息而不是其具体类型 —— 类似于动态类型语言中称为 鸭子类型（duck typing）的概念：
//     如果它走起来像一只鸭子，叫起来像一只鸭子，那么它就是一只鸭子！
//     在示例中 Screen 上的 run 实现中，run 并不需要知道各个组件的具体类型是什么。
//     它并不检查组件是 Button 或者 SelectBox 的实例。
// 通过指定 Box<dyn Draw> 作为 components vector 中值的类型，我们就定义了 Screen 为需要可以在其上调用 draw 方法的值。

// 使用 trait 对象和 Rust 类型系统来进行类似鸭子类型操作的优势是：
//     无需在运行时检查一个值是否实现了特定方法或者担心在调用时因为值没有实现方法而产生错误。
//     如果值没有实现 trait 对象所需的 trait 则 Rust 不会编译这些代码。
