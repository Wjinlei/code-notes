use multi_thread_webserver::ThreadPool;
use std::{
    fs,
    io::{Read, Write},
    net::{TcpListener, TcpStream},
    thread,
    time::Duration,
};

fn main() {
    let listener = TcpListener::bind("127.0.0.1:6588").unwrap();
    // 这里使用 ThreadPool::new 来创建一个新的线程池，它有一个可配置的线程数的参数。
    let pool = ThreadPool::new(4);

    for stream in listener.incoming() {
        let stream = stream.unwrap();
        //thread::spawn(|| handle_connection(stream)); // 简单采用多线程来处理
        // 简单采用多线程来处理是有问题的，这最终会使系统崩溃因为我们无限制的创建新线程。
        //
        // 我们打算实现一个线程池
        // 线程池（thread pool）是一组预先分配的等待或准备处理任务的线程。
        // 当程序收到一个新任务，线程池中的一个线程会被分配任务，这个线程会离开并处理任务。
        // 其余的线程则可用于处理在第一个线程处理任务的同时处理其他接收到的任务。
        // 当第一个线程处理完任务时，它会返回空闲线程池中等待处理新任务。
        // 线程池允许我们并发处理连接，增加 server 的吞吐量。
        //
        // pool.execute 有着类似 thread::spawn 的接口，它获取一个线程池运行于每一个流的闭包。
        // pool.execute 需要实现为获取闭包并传递给池中的线程运行。
        pool.execute(|| {
            handle_connection(stream);
        });
    }
}

fn handle_connection(mut stream: TcpStream) {
    let mut buffer = [0; 1024];
    stream.read(&mut buffer).unwrap();

    let get = b"GET / HTTP/1.1\r\n";
    let sleep = b"GET /sleep HTTP/1.1\r\n";

    let (status_line, filename) = if buffer.starts_with(get) {
        ("HTTP/1.1 200 OK\r\n\r\n", "hello.html")
    } else if buffer.starts_with(sleep) {
        // 模拟慢请求，访问/sleep，会等待5秒
        // 此时再访问 /，会等待/sleep处理结束后才会继续处理
        thread::sleep(Duration::from_secs(5));
        ("HTTP/1.1 200 OK\r\n\r\n", "hello.html")
    } else {
        ("HTTP/1.1 400 NOT FOUND\r\n\r\n", "404.html")
    };

    let contents = fs::read_to_string(filename).unwrap();
    let response = format!("{}{}", status_line, contents);
    stream.write(response.as_bytes()).unwrap();
    stream.flush().unwrap();
}
