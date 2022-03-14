// 让我们看看在Rust中如何解决继承的问题
//
// 在这个例子中，我们将创建一个图形用户接口（Graphical User Interface， GUI）工具的例子
// 它通过遍历列表并调用每一个项目的 draw 方法来将其绘制到屏幕上 —— 此乃一个 GUI 工具的常见技术。
// 我们将要创建一个叫做 gui 的库 crate，它含一个 GUI 库的结构。
// 这个 GUI 库包含一些可供开发者使用的类型，比如 Button 或 TextField。
// 在此之上，gui 的用户希望创建自定义的可以绘制于屏幕上的类型：
//     比如，一个程序员可能会增加 Image，另一个可能会增加 SelectBox。

// 这个例子中并不会实现一个功能完善的 GUI 库，不过会展示其中各个部分是如何结合在一起的。
// 编写库的时候，我们不可能知晓并定义所有其他程序员希望创建的类型。
// 我们所知晓的是 gui 需要记录一系列不同类型的值，并需要能够对其中每一个值调用 draw 方法。
// 这里无需知道调用 draw 方法时具体会发生什么，只要该值会有那个方法可供我们调用。

// 在拥有继承的语言中，可以定义一个名为 Component 的类，该类上有一个 draw 方法。
// 其他的类比如 Button、Image 和 SelectBox 会从 Component 派生并因此继承 draw 方法。
// 它们各自都可以覆盖 draw 方法来定义自己的行为，但是框架会把所有这些类型当作是 Component 的实例，并在其上调用 draw。
// 不过 Rust 并没有继承，我们得另寻出路。

// 为了实现 gui 所期望的行为，让我们定义一个 Draw trait，其中包含名为 draw 的方法。
// 接着可以定义一个存放 trait 对象（trait object） 的 vector。
// trait 对象指向一个实现了我们指定 trait 的类型的实例，以及一个用于在运行时查找该类型的trait方法的表。
// 我们通过指定某种指针来创建 trait 对象，我们可以使用 trait 对象代替泛型或具体类型。
// 任何使用 trait 对象的位置，Rust 的类型系统会在编译时确保任何在此上下文中使用的值会实现其 trait 对象的 trait。
// 如此便无需在编译时就知晓所有可能的类型。

// 定义一个带有 draw 方法的 trait Draw
pub trait Draw {
    fn draw(&self);
}

// 定义了一个存放了名叫 components 的 vector 的结构体 Screen。
// 这个 vector 的类型是 Box<dyn Draw>，此为一个 trait 对象：它是 Box 中任何实现了 Draw trait 的类型的替身。
pub struct Screen {
    pub components: Vec<Box<dyn Draw>>,
}

// 在 Screen 结构体上，我们将定义一个 run 方法，该方法会对其 components 上的每一个组件调用 draw 方法
impl Screen {
    pub fn run(&self) {
        for component in self.components.iter() {
            component.draw();
        }
    }
}

// 你可能会问，为什么不用泛型？
// 泛型类型参数一次只能替代一个具体类型，而 trait 对象则允许在运行时替代多种具体类型。
// 下面是使用泛型的例子
pub struct Screen2<T: Draw> {
    pub components: Vec<T>,
}

impl<T> Screen2<T>
where
    T: Draw,
{
    pub fn run(&self) {
        for component in self.components.iter() {
            component.draw();
        }
    }
}
