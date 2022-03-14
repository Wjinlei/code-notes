// vector 允许我们在一个单独的数据结构中储存多于一个的值，它在内存中彼此相邻地排列所有的值。
// vector 只能储存相同类型的值。vector 可以理解为一个动态数组

fn main() {
    // 注意这里我们增加了一个类型注解。
    // 因为没有向这个 vector 中插入任何值，Rust 并不知道我们想要储存什么类型的元素。
    // 这是一个非常重要的点。vector 是用泛型实现的
    // 所有你需要知道的就是 Vec 是一个由标准库提供的类型，它可以存放任何类型。
    // 而当 Vec 存放某个特定类型时，那个类型位于尖括号中。
    // 在更实际的代码中，一旦插入值 Rust 就可以推断出想要存放的类型，所以你很少会需要这些类型注解。
    let v1: Vec<i32> = Vec::new();
    println!("{:?}", v1);

    // 更常见的做法是使用初始值来创建一个 Vec，而且为了方便 Rust 提供了 vec! 宏。
    // 这个宏会根据我们提供的值来创建一个新的 Vec。
    let v2 = vec![1, 2, 3];
    println!("{:?}", v2);
    // 因为我们提供了 i32 类型的初始值，Rust 可以推断出 v 的类型是 Vec<i32>，因此类型注解就不是必须的。

    // 更新
    // 对于新建一个 vector 并向其增加元素，可以使用 push 方法。
    let mut v3: Vec<i32> = Vec::new();
    v3.push(1);
    v3.push(2);
    v3.push(3);
    v3.push(4);
    println!("{:?}", v3);

    // 读取
    // 索引语法,这种方法当你引用一个不存在的索引会引发panic异常
    let v4 = vec![1, 2, 3, 4, 5];
    let third: &i32 = &v4[2];
    println!("The third element is {}", third);
    // get 方法,这种方法当你引用一个不存在的索引会返回None
    match v4.get(2) {
        Some(third) => println!("The third element is {}", third),
        None => println!("There is no third element."),
    }
    // Rust 有两个引用元素的方法的原因是程序可以选择如何处理当索引值在 vector 中没有对应值的情况。

    // 遍历
    // for
    for i in v4 {
        println!("{}", i);
    }

    // 遍历其可变引用并修改它
    let mut v5 = vec![1, 2, 3, 4, 5];
    for i in &mut v5 {
        *i += 50; // 为了修改可变引用所指向的值，在使用 += 运算符之前必须使用解引用运算符（*）获取 i 中的值。
        println!("{}", i);
    }

    // 在本章的开始，我们提到 vector 只能储存相同类型的值。
    // 这是很不方便的；绝对会有需要储存一系列不同类型的值的用例。
    // 幸运的是，枚举的成员都被定义为相同的枚举类型，所以当需要在 vector 中储存不同类型值时，我们可以定义并使用一个枚举！
    // 例如，假如我们想要从电子表格的一行中获取值，而这一行的有些列包含数字，有些包含浮点值，还有些是字符串。
    // 我们可以定义一个枚举，其成员会存放这些不同类型的值，同时所有这些枚举成员都会被当作相同类型，那个枚举的类型。
    // 接着可以创建一个储存枚举值的 vector，这样最终就能够储存不同类型的值了。

    let row = vec![
        SpreadsheetCell::Int(3),
        SpreadsheetCell::Text(String::from("blue")),
        SpreadsheetCell::Float(10.12),
    ];
    for i in row {
        println!("{:?}", i);
    }
}

#[derive(Debug)]
enum SpreadsheetCell {
    Int(i32),
    Float(f64),
    Text(String),
}
