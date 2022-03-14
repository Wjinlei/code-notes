// 模式是 Rust 中特殊的语法，它用来匹配类型中的结构，无论类型是简单还是复杂。
// 结合使用模式和 match 表达式以及其他结构可以提供更多对程序控制流的支配权。
//
// 模式由如下一些内容组合而成：
//     字面值
//     解构的数组、枚举、结构体或者元组
//     变量
//     通配符
//     占位符
//
// 模式这个东西怎么说呢，你匹配一个东西的规则都可以叫模式
//
// 模式这个东西基本上是理论的东西
// 建议多读几遍 https://kaisery.github.io/trpl-zh-cn/ch18-00-patterns.html
//
// 你在日常使用Rust中，不可避免的都会用到模式，只是你没有感觉而已

fn main() {
    // 模式例子1
    let x = 1;
    match x {
        1 => println!("one"),
        2 => println!("two"),
        3 => println!("three"),
        _ => println!("anything"),
    }

    // 模式例子2
    let mut stack = Vec::new();
    stack.push(1);
    stack.push(2);
    stack.push(3);
    while let Some(top) = stack.pop() {
        println!("{}", top);
    }

    // 模式例子3
    let v = vec!['a', 'b', 'c'];
    for (index, value) in v.iter().enumerate() {
        println!("{} is at index {}", value, index);
    }

    // ...等等还有很多很多
}
