use std::{
    fs,
    io::{Read, Write},
    net::{TcpListener, TcpStream},
};

fn main() {
    let listener = TcpListener::bind("127.0.0.1:6588").unwrap();

    // TcpListener 的 incoming 方法返回一个迭代器，它提供TcpStream 类型的流。
    // 流（stream）代表一个客户端和服务端之间打开的连接。
    for stream in listener.incoming() {
        // TcpStream 允许我们读取它来查看客户端发送了什么，并可以编写响应。
        // 总体来说，这个 for 循环会依次处理每个连接并产生一系列的流供我们处理。
        // 目前为止，处理流的过程包含 unwrap 调用，如果出现任何错误会终止程序，如果没有任何错误，则打印出信息。
        let stream = stream.unwrap();
        //handle_connection(stream)
        //handle_connection2(stream)
        handle_connection3(stream)
    }
}

fn handle_connection(mut stream: TcpStream) {
    // 缓冲区
    let mut buffer = [0; 1024];

    // stream 参数是可变的。
    // 这是因为 TcpStream 实例在内部记录了所返回的数据。
    // 它可能读取了多于我们请求的数据并保存它们以备下一次请求数据。
    // 因此它需要是 mut 的因为其内部状态可能会改变；通常我们认为 “读取” 不需要可变性，不过在这个例子中则需要 mut 关键字。
    stream.read(&mut buffer).unwrap();

    // 将缓冲区中的字节转换为字符串并打印出来。
    // String::from_utf8_lossy 函数获取一个 &[u8] 并产生一个 String。
    // 函数名的 “lossy” 部分来源于当其遇到无效的 UTF-8 序列时的行为
    // 它使用 �，U+FFFD REPLACEMENT CHARACTER，来代替无效序列。
    // 你可能会在缓冲区的剩余部分看到这些替代字符，因为他们没有被请求数据填满。
    println!("Request: {}", String::from_utf8_lossy(&buffer[..]));

    // 响应请求
    // 定义了变量 response 来存放将要返回的成功响应的数据。
    // 接着，在 response 上调用 as_bytes，因为 stream 的 write 方法获取一个 &[u8] 并直接将这些字节发送给连接。
    let response = "HTTP/1.1 200 OK\r\n\r\n";
    stream.write(response.as_bytes()).unwrap();
    stream.flush().unwrap();

    // 响应真实的文件内容
    let contents = fs::read_to_string("hello.html").unwrap();
    let response = format!(
        "HTTP/1.1 200 OK\r\nContent-Length: {}\r\n\r\n{}",
        contents.len(),
        contents
    );
    stream.write(response.as_bytes()).unwrap();
    stream.flush().unwrap();
}

fn handle_connection2(mut stream: TcpStream) {
    // 现在让我们改造一下上面的函数
    // 当请求路径是 / 时，才响应html，否则响应404代码
    let mut buffer = [0; 1024];
    stream.read(&mut buffer).unwrap();

    // 因为我们将原始字节读取进了缓冲区，所以在 get 的数据开头增加 b"" 字节字符串语法将其转换为字节字符串。
    let get = b"GET / HTTP/1.1\r\n"; // 对应的请求路径

    // 接着检查 buffer 是否以 get 中的字节开头。
    // 如果是，这就是一个格式良好的 / 请求，也就是 if 块中期望处理的成功情况，并会返回 HTML 文件内容的代码。
    // starts_with 以什么什么开头
    if buffer.starts_with(get) {
        let contents = fs::read_to_string("hello.html").unwrap();
        let response = format!(
            "HTTP/1.1 200 OK\r\nContent-Length: {}\r\n\r\n{}",
            contents.len(),
            contents
        );
        stream.write(response.as_bytes()).unwrap();
        stream.flush().unwrap();
    } else {
        let status_line = "HTTP/1.1 404 NOT FOUND\r\n\r\n";
        let contents = fs::read_to_string("404.html").unwrap();
        let response = format!("{}{}", status_line, contents);
        stream.write(response.as_bytes()).unwrap();
        stream.flush().unwrap();
    }
}

fn handle_connection3(mut stream: TcpStream) {
    // 优化代码
    let mut buffer = [0; 1024];
    stream.read(&mut buffer).unwrap();

    let get = b"GET / HTTP/1.1\r\n";

    // if 和 else 块所做的唯一的事就是在一个元组中返回合适的状态行和文件名的值
    // 接着使用 let 语句通过解构元组的两部分为 filename 和 header 赋值。
    let (status_line, filename) = if buffer.starts_with(get) {
        ("HTTP/1.1 200 OK\r\n\r\n", "hello.html")
    } else {
        ("HTTP/1.1 400 NOT FOUND\r\n\r\n", "404.html")
    };

    let contents = fs::read_to_string(filename).unwrap();
    let response = format!("{}{}", status_line, contents);
    stream.write(response.as_bytes()).unwrap();
    stream.flush().unwrap();
}
