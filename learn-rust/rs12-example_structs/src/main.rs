// 为了理解何时会需要使用结构体，让我们编写一个计算长方形面积的程序。
// 我们会从单独的变量开始，接着重构程序直到使用结构体替代他们为止。

fn main() {
    let width = 30;
    let height = 50;
    println!(
        "The area of the rectangle is {} square pixels.",
        area1(width, height)
    );

    let rect1 = (30, 50);
    println!(
        "The area of the rectangle is {} square pixels.",
        area2(rect1)
    );

    let rect2 = Rectangle {
        width: 30,
        height: 50,
    };
    println!(
        "The area of the rectangle is {} square pixels.",
        area3(&rect2)
    );
    // 在 {} 中加入 :? 指示符告诉 println! 我们想要使用叫做 Debug 的输出格式。
    // Debug 是一个 trait，它允许我们以一种对开发者有帮助的方式打印结构体，以便当我们调试代码时能看到它的值。
    println!("{:?}", rect2); //
}

// 最基础的方法
fn area1(widht: i32, height: i32) -> i32 {
    widht * height
}

// area 函数时传入每个维度来计算出长方形的面积，不过我们可以做的更好。
// 宽度和高度是相关联的，因为他们在一起才能定义一个长方形。
// area 本应该计算一个长方形的面积，不过函数却有两个参数。
// 这两个参数是相关联的，不过程序本身却没有表现出这一点。
// 将长度和宽度组合在一起将更易懂也更易处理。
// 使用元组重构
fn area2(dimensions: (u32, u32)) -> u32 {
    dimensions.0 * dimensions.1
}

// 在某种程度上说，这个程序更好一点了。
// 元组帮助我们增加了一些结构性，并且现在只需传一个参数。
// 不过在另一方面，这个版本却有一点不明确了：元组并没有给出元素的名称，
// 所以计算变得更费解了，因为不得不使用索引来获取元组的每一部分：
// 在计算面积时将宽和高弄混倒无关紧要，不过当在屏幕上绘制长方形时就有问题了！
// 我们必须牢记 width 的元组索引是 0，height 的元组索引是 1。
// 如果其他人要使用这些代码，他们必须要搞清楚这一点，并也要牢记于心。
// 很容易忘记或者混淆这些值而造成错误，因为我们没有在代码中传达数据的意图。
// 使用结构体重构：赋予更多意义
#[derive(Debug)] // Debug trait
struct Rectangle {
    width: u32,
    height: u32,
}
fn area3(rectangle: &Rectangle) -> u32 {
    rectangle.width * rectangle.height
}
