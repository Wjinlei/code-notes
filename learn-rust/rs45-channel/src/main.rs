use std::{sync::mpsc, thread, time::Duration};

// Rust 中线程间通信类似Go语言，它使用channel(通道)来进行线程间通讯

fn main() {
    // 这里使用 mpsc::channel 函数创建一个新的通道
    // mpsc 是 多个生产者，单个消费者（multiple producer, single consumer）的缩写。
    // 简而言之，Rust 标准库实现的通道可以有多个产生值的发送（sending）端，但只能有一个消费这些值的 接收（receiving）端。
    //
    // mpsc::channel 函数返回一个元组：第一个元素是发送端，而第二个元素是接收端。
    // 由于历史原因，tx 和 rx 通常作为 发送者（transmitter）和 接收者（receiver）的缩写
    // 所以这就是我们将用来绑定这两端变量的名字。这里使用了一个 let 语句和模式来解构了此元组
    //
    // 创建一个通道，并将其两端赋值给 tx 和 rx
    let (tx, rx) = mpsc::channel();

    // 发送端
    // 这里再次使用 thread::spawn 来创建一个新线程并使用 move 将 tx 移动到闭包中这样新建线程就拥有 tx 了。
    // 新建线程需要拥有通道的发送端以便能向通道发送消息。
    thread::spawn(move || {
        let val = String::from("hi");
        // 通道的发送端有一个 send 方法用来获取需要放入通道的值。
        // send 方法返回一个 Result<T, E> 类型，所以如果接收端已经被丢弃了，将没有发送值的目标，所以发送操作会返回错误。
        // 在这个例子中，出错的时候调用 unwrap 产生 panic。不过对于一个真实程序，需要合理地处理它
        tx.send(val).unwrap();

        //println!("val is {}", val); // 这里会报错，Rust不允许这么做
        // 允许这么做是一个坏主意：一旦将值发送到另一个线程后，那个线程可能会在我们再次使用它之前就将其修改或者丢弃。
        // 其他线程对值可能的修改会由于不一致或不存在的数据而导致错误或意外的结果。
    });

    // 接收端
    //
    // 通道的接收端有两个有用的方法：recv 和 try_recv。
    // 这里，我们使用了 recv，它是 receive 的缩写。
    //
    // recv 方法会阻塞主线程执行直到从通道中接收一个值。
    // 一旦发送了一个值，recv 会在一个 Result<T, E> 中返回它。
    // 当通道发送端关闭，recv 会返回一个错误表明不会再有新的值到来了。
    //
    // try_recv 不会阻塞，相反它立刻返回一个 Result<T, E>：Ok 值包含可用的信息，而 Err 值代表此时没有任何消息。
    // 如果线程在等待消息过程中还有其他工作时使用 try_recv 很有用
    // 可以编写一个循环来频繁调用 try_recv，在有可用消息时进行处理，其余时候则处理一会其他工作直到再次检查。
    let received = rx.recv().unwrap();
    println!("Got: {}", received);


    // 示例3：通过克隆发送者来创建多个生产者
    let (tx2, rx2) = mpsc::channel();

    let tx3 = tx2.clone(); // 克隆一个发送者

    thread::spawn(move || {
        let vals = vec![
            String::from("hi"),
            String::from("from"),
            String::from("the"),
            String::from("thread"),
        ];
        // 新建线程现在会发送多个消息并在每个消息之间暂停一秒钟。
        for val in vals {
            tx3.send(val).unwrap();
            thread::sleep(Duration::from_secs(1));
        }
    });

    thread::spawn(move || {
        let vals = vec![
            String::from("hi"),
            String::from("from"),
            String::from("the"),
            String::from("thread"),
        ];
        // 新建线程现在会发送多个消息并在每个消息之间暂停一秒钟。
        for val in vals {
            tx2.send(val).unwrap();
            thread::sleep(Duration::from_secs(1));
        }
    });

    // 示例2：等待接收值
    // 在主线程中，不再显式调用 recv 函数：而是将 rx 当作一个迭代器。
    // 对于每一个接收到的值，我们将其打印出来。当通道被关闭时，迭代器也将结束。
    // 因为主线程中的 for 循环里并没有任何暂停或等待的代码，所以可以说主线程是在等待从新建线程中接收值。
    for received in rx2 {
        println!("Got: {}", received);
    }
}
