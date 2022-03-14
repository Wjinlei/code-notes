fn main() {
    // 可以使用一个由中括号中的 [starting_index..ending_index] 指定的 range 创建一个 slice，
    // 其中 starting_index 是 slice 的第一个位置，ending_index 则是 slice 最后一个位置的后一个值。
    // 在其内部，slice 的数据结构存储了 slice 的开始位置和长度，长度对应于 ending_index 减去 starting_index 的值。
    // 所以对于 let world = &s[6..11]; 的情况，world 将是一个包含指向 s 第 7 个字节（从 1 开始）的指针和长度值 5 的 slice。
    let s = String::from("hello world");
    let hello = &s[0..5];
    let world = &s[6..11];
    println!("{}", hello);
    println!("{}", world);

    // 对于 Rust 的 .. range 语法，如果想要从第一个索引（0）开始，可以不写两个点号之前的值。换句话说，如下两个语句是相同的：
    let slice1 = &s[0..2];
    let slice2 = &s[..2];
    println!("{}", slice1);
    println!("{}", slice2);

    // 依此类推，如果 slice 包含 String 的最后一个字节，也可以舍弃尾部的数字。这意味着如下也是相同的：
    let len = s.len();
    let slice3 = &s[3..len];
    let slice4 = &s[3..];
    println!("{}", slice3);
    println!("{}", slice4);

    // 也可以同时舍弃这两个值来获取整个字符串的 slice。所以如下亦是相同的：
    let len = s.len();
    let slice5 = &s[0..len];
    let slice6 = &s[..];
    println!("{}", slice5);
    println!("{}", slice6);

    // 小练习
    let word1 = first_word(&s);
    println!("{}", word1);

    // 字符串字面值就是 slice
    // 还记得我们讲到过字符串字面值被储存在二进制文件中吗？现在知道 slice 了，我们就可以正确地理解字符串字面值了：
    let ns = "Hello, world!";
    println!("{}", ns);
    // 这里 ns 的类型是 &str：它是一个指向二进制程序特定位置的 slice。这也就是为什么字符串字面值是不可变的；&str 是一个不可变引用。

    let word2 = first_word2(&s[..]);
    println!("{}", word2);

    let word3 = first_word2(&ns[..]);
    println!("{}", word3);
}

// 练习:
// 该函数接收一个字符串，并返回在该字符串中找到的第一个单词。
// 如果函数在该字符串中并未找到空格，则整个字符串就是一个单词，所以应该返回整个字符串。
fn first_word(s: &String) -> &str {
    let bytes = s.as_bytes(); // 因为需要逐个元素的检查 String 中的值是否为空格，需要用 as_bytes 方法将 String 转化为字节数组：

    // 接下来，使用 iter 方法在字节数组上创建一个迭代器：
    // 现在，只需知道 iter 方法返回集合中的每一个元素，而 enumerate 包装了 iter 的结果，将这些元素作为元组的一部分来返回。
    // enumerate 返回的元组中，第一个元素是索引，第二个元素是集合中元素的引用。
    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[0..i];
        }
    }
    &s[..]
}

// 改进版first_word，
// 它使得可以对 String 值和 &str 值使用相同的函数：
fn first_word2(s: &str) -> &str {
    let bytes = s.as_bytes();
    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[0..i];
        }
    }
    &s[..]
}
