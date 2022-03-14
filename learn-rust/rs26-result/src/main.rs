// 大部分错误并没有严重到需要程序完全停止执行。
// 有时，一个函数会因为一个容易理解并做出反应的原因失败。
// 例如，如果因为打开一个并不存在的文件而失败，此时我们可能想要创建这个文件，而不是终止进程。

use std::fs;
use std::fs::File;
use std::io;
use std::io::ErrorKind;
use std::io::Read;

fn main() {
    // Result 枚举，它定义有如下两个成员，Ok 和 Err：
    // T 和 E 是泛型类型参数；第十章会详细介绍泛型。
    // 现在你需要知道的就是 T 代表成功时返回的 Ok 成员中的数据的类型。
    // 而 E 代表失败时返回的 Err 成员中的错误的类型。
    /*

    enum Result<T, E> {
        Ok(T),
        Err(E),
    }

    */

    // File::open 返回一个Result<T, E>类型
    // 当 File::open 成功的情况下，变量 f 的值将会是一个包含文件句柄的 Ok 实例。
    // 在失败的情况下，f 的值会是一个包含更多关于出现了何种错误信息的 Err 实例。
    // 我们可以通过match来匹配模式处理它,下面是一个例子
    // 例子1
    match File::open("text.txt") {
        Ok(file) => file,
        Err(err) => {
            panic!("[ERROR] Open file: {}", err);
        }
    };

    // 然而通常我们不希望程序停止运行,而是对特定的错误进行处理
    // 例子2
    match File::open("text.txt") {
        Ok(file) => file,
        Err(e) => match e.kind() {
            // 如果错误是文件未找到,则创建该文件
            ErrorKind::NotFound => match File::create("text.txt") {
                Ok(fc) => fc,
                Err(e) => panic!("[ERROR] Create file {}", e),
            },
            // 由于rust match是穷尽的,因此其他错误也要处理
            other_error => panic!("[ERROR] Open file {:?}", other_error),
        },
    };

    // Result<T, E> 有很多接受闭包的方法，并采用 match 表达式实现。
    // 通过 unwrap_or_else 方法处理,可以避免写多个match 嵌套
    // 暂时先不管这个,了解下即可
    // 例子3
    File::open("hello.txt").unwrap_or_else(|error| {
        if error.kind() == ErrorKind::NotFound {
            File::create("hello.txt").unwrap_or_else(|error| {
                panic!("Problem creating the file: {:?}", error);
            })
        } else {
            panic!("Problem opening the file: {:?}", error);
        }
    });
    // 感觉还不如上面的

    // match 能够胜任它的工作，不过它可能有点冗长并且不总是能很好的表明其意图。
    // Result<T, E> 类型定义了很多辅助方法来处理各种情况。
    // 其中之一叫做 unwrap，如果 Result 值是成员 Ok，unwrap 会返回 Ok 中的值。
    // 如果 Result 是成员 Err，unwrap 会为我们调用 panic!。
    // 那么例子1就可以简写成下面的格式
    File::open("text.txt").unwrap();
    // 还有另一个类似于 unwrap 的方法它还允许我们选择 panic! 的错误信息：
    File::open("text.txt").expect("[ERROR] Failed to open file");

    match read_username_from_file() {
        Ok(username) => println!("{}", username),
        Err(e) => panic!("[ERROR] Read username {:?}", e),
    };

    match read_username_from_file2() {
        Ok(username) => println!("{}", username),
        Err(e) => panic!("[ERROR] Read username {:?}", e),
    };

    match read_username_from_file3() {
        Ok(username) => println!("{}", username),
        Err(e) => panic!("[ERROR] Read username {:?}", e),
    };

    // rust 提供一个更简单的api
    match fs::read_to_string("hello.txt") {
        Ok(username) => println!("{}", username),
        Err(e) => panic!("[ERROR] Read username {:?}", e),
    };
}

// 返回错误
fn read_username_from_file() -> Result<String, io::Error> {
    // Result<String, io::Error>。
    // 这意味着函数返回一个 Result<T, E> 类型的值，
    // 其中泛型参数 T 的具体类型是 String，而 E 的具体类型是 io::Error。
    // 如果这个函数没有出任何错误成功返回，函数的调用者会收到一个包含 String 的 Ok 值,函数从文件中读取到的用户名。
    // 如果函数遇到任何错误，函数的调用者会收到一个 Err 值，它储存了一个包含更多这个问题相关信息的 io::Error 实例。
    let f = File::open("hello.txt");

    let mut f = match f {
        Ok(file) => file,
        Err(e) => return Err(e), // 可以通过return 提前返回
    };

    let mut s = String::new();
    match f.read_to_string(&mut s) {
        Ok(_) => Ok(s),
        Err(e) => Err(e),
    }
}

// ? 运算符
// 如果 Result 的值是 Ok，这个表达式将会返回 Ok 中的值而程序将继续执行。
// 如果值是 Err，Err 中的值将作为整个函数的返回值。
// 就好像使用了 return 关键字一样，这样错误值就被传播给了调用者。
// ? 运算符消除了大量样板代码并使得函数的实现更简单。
fn read_username_from_file2() -> Result<String, io::Error> {
    let mut f = File::open("hello.txt")?;
    // File::open 调用结尾的 ? 将会把 Ok 中的值返回给变量 f。
    // 如果出现了错误，? 运算符会提早返回整个函数并将一些 Err 值传播给调用者。
    // 同理也适用于 read_to_string 调用结尾的 ?。
    let mut s = String::new();
    f.read_to_string(&mut s)?;
    Ok(s)
}

// 我们甚至可以在 ? 之后直接使用链式方法调用来进一步缩短代码
// ? 运算符只能在返回Result的函数中使用
fn read_username_from_file3() -> Result<String, io::Error> {
    let mut s = String::new();
    File::open("hello.txt")?.read_to_string(&mut s)?;
    Ok(s)
}
