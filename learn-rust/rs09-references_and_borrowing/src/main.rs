// 在每一个函数中都获取所有权并接着返回所有权有些啰嗦。
// 如果我们想要函数使用一个值但不获取所有权该怎么办呢？
// 如果我们还要接着使用它的话，每次都传进去再返回来就有点烦人了
// 除此之外，我们也可能想返回函数体中产生的一些数据。
fn main() {
    let s1 = String::from("hello");
    let (s2, len) = calculate_length(s1);
    println!("The length of '{}' is {}.", s2, len);

    let s3 = String::from("hello");
    let len = calculate_length2(&s3); // 注意我们传递 &s1 给 calculate_length，同时在函数定义中，我们获取 &String 而不是 String。
    println!("The length of '{}' is {}.", s3, len);

    // 引用默认是不可变的,但你可以通过mut来创建一个可变引用
    let mut s = String::from("hello");
    change(&mut s);
    println!("This value of s is: {}", s);

    // 不过可变引用有一个很大的限制：在特定作用域中的特定数据只能有一个可变引用。
    //let r1 = &mut s;
    //let r2 = &mut s;
    //println!("{}, {}", r1, r2);

    // 注意一个引用的作用域从声明的地方开始一直持续到最后一次使用为止。
    let r1 = &s; // 没问题
    let r2 = &s; // 没问题
    println!("{} and {}", r1, r2);
    // 此位置之后 r1 和 r2 不再使用

    let r3 = &mut s; // 没问题
    println!("{}", r3);

    let reference_to_nothing = no_dangle();
    println!("{}", reference_to_nothing)
}

// 我们可以使用元组来返回多个值
// 但是这未免有些形式主义，而且这种场景应该很常见。
fn calculate_length(s: String) -> (String, usize) {
    let length = s.len(); // len() 返回字符串的长度

    (s, length)
}

// 幸运的是，Rust 对此提供了一个功能，叫做 引用（references）
// 下面是如何定义并使用一个（新的）calculate_length 函数，它以一个对象的引用作为参数而不是获取值的所有权：
fn calculate_length2(s: &String) -> usize {
    // s 是对 String 的引用
    s.len()
} // 这里，s 离开了作用域。但因为它并不拥有引用值的所有权，
  // 所以什么也不会发生

// 引用默认是不可变的,但你可以通过mut来创建一个可变引用
fn change(some_string: &mut String) {
    some_string.push_str(", world");
}

// 悬垂引用
// 在具有指针的语言中，很容易通过释放内存时保留指向它的指针而错误地生成一个 悬垂指针（dangling pointer）
// 所谓悬垂指针是其指向的内存可能已经被分配给其它持有者。
//fn dangle() -> &String {
//// dangle 返回一个字符串的引用
//let s = String::from("hello"); // s 是一个新字符串
//&s // 返回字符串 s 的引用
//} // 这里 s 离开作用域并被丢弃。其内存被释放。
//// 危险！

// 解决办法是直接返回String
fn no_dangle() -> String {
    let s = String::from("hello");
    s
}
