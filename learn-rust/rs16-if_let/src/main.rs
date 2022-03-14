// if let 语法让我们以一种不那么冗长的方式结合 if 和 let，来处理只匹配一个模式的值而忽略其他模式的情况。
// 考虑示例 6-6 中的程序，它匹配一个 Option<u8> 值并只希望当值为 3 时执行代码：
fn main() {
    // 我们想要对 Some(3) 匹配进行操作但是不想处理任何其他 Some<u8> 值或 None 值。
    // 为了满足 match 表达式（穷尽性）的要求，必须在处理完这唯一的成员后加上 _ => ()，这样也要增加很多样板代码。
    let some_u8_value = Some(0u8);
    match some_u8_value {
        Some(3) => println!("three"),
        _ => (),
    }
    // 不过我们可以使用 if let 这种更短的方式编写。如下代码与示例 6-6 中的 match 行为一致：
    if let Some(3) = some_u8_value {
        println!("three");
    }

    // 可以在 if let 中包含一个 else。
    // else 块中的代码与 match 表达式中的 _ 分支块中的代码相同，这样的 match 表达式就等同于 if let 和 else。
    if let Some(3) = some_u8_value {
        println!("three");
    } else {
        println!("no three");
    }
    // 它等于下面的写法
    match some_u8_value {
        Some(3) => println!("three"),
        _ => println!("no three"),
    }
}
