// 在集合章节中讨论字符串的原因是，字符串就是作为字节的集合外加一些方法实现的。

fn main() {
    // 创建 =============================================
    // 创建,新建一个空的 String
    let s1 = String::new();
    println!("{}", s1);

    // 第二种方式
    let data = "s2 Helllo World";
    let s2 = data.to_string();
    println!("{}", s2);

    // 该方法也可直接用于字符串字面值：
    let s3 = "s3 Hello World".to_string();
    println!("{}", s3);

    // 也可以使用 String::from 函数来从字符串字面值创建 String。
    // 使用 String::from 函数从字符串字面值创建 String
    // 等同于使用 to_string。
    // String::from 和 .to_string 最终做了完全相同的工作，所以如何选择就是风格问题了。
    // 我选from
    let s4 = String::from("s4 Hello World");
    println!("{}", s4);

    // 更新 ==============================================
    // 可以通过 push_str 方法来附加字符串 slice
    let mut s5 = String::from("foo");
    s5.push_str("bar");
    println!("{}", s5);

    // push 方法被定义为获取一个单独的字符作为参数，并附加到 String 中。
    s5.push('l');
    println!("{}", s5);

    // 还有一种方便的方式,可以方便的使用 + 运算符或 format! 宏来拼接 String 值。
    let s6 = String::from("Hello, ");
    let s7 = String::from("world!");
    let s8 = s6 + &s7; // 注意 s6 被移动了，不能继续使用
    println!("{}", s8);
    // s6不再有效的原因是:
    // + 号实际上被rust解释为: fn add(self, s: &str) -> String {}
    // 可以发现签名中 add 获取了 self 的所有权，因为 self 没有 使用 &。
    // 这意味着示例中 s6 的所有权将被移动到 add 调用中，之后就不再有效。
    //
    // 之所以能够在 add 调用中使用 &s2 是因为 &String 可以被 强转（coerced）成 &str。这个以后再说
    let s9 = String::from("tic");
    let s10 = String::from("tac");
    let s11 = String::from("toe");
    let s12 = s9 + "-" + &s10 + "-" + &s11; // 如果想要级联多个字符串，+ 的行为就显得笨重了：
    println!("{}", s12);
    // 更好的办法是使用 format! 宏：
    let s13 = String::from("tic");
    let s14 = String::from("tac");
    let s15 = String::from("toe");
    let s16 = format!("{}-{}-{}", s13, s14, s15);
    println!("{}", s16);
    // format! 与 println! 的工作原理相同，不过不同于将输出打印到屏幕上，它返回一个带有结果内容的 String。

    // rust 不支持索引字符串,下面的代码会报错
    // let s1 = String::from("hello");
    // let h = s1[0];
    // 原因: https://kaisery.github.io/trpl-zh-cn/ch08-02-strings.html#%E7%B4%A2%E5%BC%95%E5%AD%97%E7%AC%A6%E4%B8%B2

    // 遍历字符串方式
    // 如果你需要操作单独的 Unicode 标量值，最好的选择是使用 chars 方法。
    for c in "नमस्ते".chars() {
        println!("{}", c);
    }

    // bytes 方法返回每一个原始字节
    for b in "नमस्ते".bytes() {
        println!("{}", b);
    }

    // 什么是字节、标量值和字形簇？
    // 字符串的3中表现形式
    // 字节:[224, 164, 168, 224, 164, 174, 224, 164, 184, 224, 165, 141, 224, 164, 164, 224, 165, 135]
    // 标量值: ['न', 'म', 'स', '्', 'त', 'े']
    // 字型簇: ["न", "म", "स्", "ते"]
    // 从字符串中获取字形簇是很复杂的，所以标准库并没有提供这个功能。crates.io 上有些提供这样功能的 crate。
}
