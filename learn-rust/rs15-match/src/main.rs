// Rust 有一个叫做 match 的极为强大的控制流运算符
// 它允许我们将一个值与一系列的模式相比较，并根据相匹配的模式执行相应代码。
// 模式可由字面值、变量、通配符和许多其他内容构成。
//
// 可以把 match 表达式想象成某种硬币分类器：硬币滑入有着不同大小孔洞的轨道，每一个硬币都会掉入符合它大小的孔洞。
// 同样地，值也会通过 match 的每一个模式，并且在遇到第一个 “符合” 的模式时，值会进入相关联的代码块并在执行中被使用。

// 因为刚刚提到了硬币，让我们用它们来作为一个使用 match 的例子！
// 我们可以编写一个函数来获取一个未知的硬币，并以一种类似验钞机的方式，确定它是何种硬币并返回它的美分值
enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter,
}

fn value_in_cents(coin: Coin) -> u8 {
    match coin {
        Coin::Penny => {
            // 如果想要在分支中运行多行代码，可以使用大括号。
            println!("Lucky penny");
            1
        }
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter => 25,
    }
}

// 绑定值的模式
#[derive(Debug)] // 这样可以立刻看到州的名称
enum UsState {
    Alaska,
}

enum Coin2 {
    Quarter(UsState),
}

// 如果调用 value_in_cents2(Coin2::Quarter(UsState::Alaska))，coin 将是 Coin2::Quarter(UsState::Alaska)。
// 当将值与每个分支相比较时，没有分支会匹配，直到遇到 Coin::Quarter(state)。
// 这时，state 绑定的将会是值 UsState::Alaska。
// 接着就可以在 println! 表达式中使用这个绑定了，像这样就可以获取 Coin 枚举的 Quarter 成员中内部的州的值。
fn value_in_cents2(coin: Coin2) -> u8 {
    match coin {
        Coin2::Quarter(state) => {
            println!("State quarter from {:?}!", state);
            25
        }
    }
}

fn main() {
    let coin1 = Coin::Penny;
    let penny = value_in_cents(coin1);
    println!("This value of penny is: {}", penny);

    let coin2 = Coin::Nickel;
    let nickel = value_in_cents(coin2);
    println!("This value of nickel is: {}", nickel);

    let coin3 = Coin::Dime;
    let dime = value_in_cents(coin3);
    println!("This value os dime is: {}", dime);

    let coin4 = Coin::Quarter;
    let quarter = value_in_cents(coin4);
    println!("This value of quarter is: {}", quarter);

    // 匹配分支的另一个有用的功能是可以绑定匹配的模式的部分值。这也就是如何从枚举成员中提取值的。
    let coin5 = Coin2::Quarter(UsState::Alaska);
    let quarter2 = value_in_cents2(coin5);
    println!("This value of quarter2 is: {}", quarter2);

    // 匹配 Option<T>
    let five = Some(5);
    let six = plus_one(five);
    let none = plus_one(None);
    println!("six: {:?}", six);
    println!("none: {:?}", none);

    // _ 通配符
    // Rust 也提供了一个模式用于不想列举出所有可能值的场景。
    // 例如，u8 可以拥有 0 到 255 的有效的值，如果我们只关心 1、3、5 和 7 这几个值，
    // 就并不想必须列出 0、2、4、6、8、9 一直到 255 的值。
    // 所幸我们不必这么做：可以使用特殊的模式 _ 替代：
    let some_u8_value = 0u8;
    match some_u8_value {
        1 => println!("one"),
        3 => println!("three"),
        5 => println!("five"),
        7 => println!("seven"),
        _ => (),
    }
}

// 比如我们想要编写一个函数，它获取一个 Option<i32> ，
// 如果其中含有一个值，将其加一。如果其中没有值，函数应该返回 None 值，而不尝试执行任何操作。
fn plus_one(x: Option<i32>) -> Option<i32> {
    match x {
        None => None,
        Some(i) => Some(i + 1),
    }
}
