use std::env;
use std::process;
use rs31_minigrep::Config;

fn main() {
    // nwrap_or_else，它定义于标准库的 Result<T, E> 上。
    // 使用 unwrap_or_else 可以进行一些自定义的非 panic! 的错误处理。
    // 当 Result 是 Ok 时，这个方法的行为类似于 unwrap：它返回 Ok 内部封装的值。
    // 然而，当其值是 Err 时，该方法会调用一个 闭包（closure）
    // 也就是一个我们定义的作为参数传递给 unwrap_or_else 的匿名函数。
    // 后面会更详细的介绍闭包。
    // 现在你需要理解的是 unwrap_or_else 会将 Err 的内部值，传递给闭包中位于两道竖线间的参数 err。
    // 闭包中的代码在其运行时可以使用这个 err 值。

    //let args: Vec<String> = env::args().collect();

    //let config = Config::new(&args).unwrap_or_else(|err| {
        //eprintln!("Problem parsing arguments: {}", err); // eprintln!将错误信息打印到标准错误流中
        //process::exit(1);
    //});

    // 使用33学习的迭代器知识优化new函数
    let config = Config::new2(env::args()).unwrap_or_else(|err| {
        eprintln!("Problem parsing arguments: {}", err); // eprintln!将错误信息打印到标准错误流中
        process::exit(1);
    });

    if let Err(e) = rs31_minigrep::run(config) {
        eprintln!("Application error: {}", e);
        process::exit(1);
    }
}

