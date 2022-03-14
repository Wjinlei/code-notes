use std::sync::Arc;
use std::{sync::Mutex, thread};
//use std::rc::Rc;

// 在某种程度上，任何编程语言中的通道都类似于单所有权，因为一旦将一个值传送到通道中，将无法再使用这个值。
// 共享内存类似于多所有权：多个线程可以同时访问相同的内存位置。
// 如果你非要通过共享内存的方式来通讯 那么你就必须要以某种方式管理这些不同的所有者。
//
// 互斥器（mutex）是 mutual exclusion 的缩写，也就是说，任意时刻，其只允许一个线程访问某些数据。
// 为了访问互斥器中的数据，线程首先需要通过获取互斥器的 锁（lock）来表明其希望访问数据。
// 锁是一个作为互斥器一部分的数据结构，它记录谁有数据的排他访问权。
// 因此，我们描述互斥器为通过锁系统 保护（guarding）其数据。
// 互斥器以难以使用著称，因为你不得不记住：
//     在使用数据之前尝试获取锁。
//     处理完被互斥器所保护的数据之后，必须解锁数据，这样其他线程才能够获取锁。

fn main() {
    // 我们使用关联函数 new 来创建一个 Mutex<T>。
    let m = Mutex::new(0);
    {
        // 这个调用会阻塞当前线程，直到我们拥有锁为止。
        let mut num = m.lock().unwrap(); //使用 lock 方法获取锁，以访问互斥器中的数据。
        *num = 6;
    }
    println!("m = {:?}", m);

    mutex_example3();
}

// 现在让我们尝试使用 Mutex<T> 在多个线程间共享值。
// 我们将启动十个线程，并在各个线程中对同一个计数器值加一，这样计数器将从 0 变为 10。
// 示例中的例子会出现编译错误，而我们将通过这些错误来学习如何使用 Mutex<T>
/*
fn mutex_example1() {
    let counter = Mutex::new(0);
    let mut handles = vec![];
    for _ in 0..10 {
        // counter 值在上一次循环中被移动了。
        // 所以 Rust 告诉我们不能将 counter 锁的所有权移动到多个线程中。
        let handle = thread::spawn(move || {
            let mut num = counter.lock().unwrap();
            *num += 1;
        });
        handles.push(handle);
    }
    for handle in handles {
        handle.join().unwrap();
    }
    println!("Result: {}", *counter.lock().unwrap());
}
*/

// 让我们通过之前学习的只能指针Rc<T>来解决这个问题
// 下面的代码仍然会报错
// Rc<T> 并不能安全的在线程间共享。
// 当 Rc<T> 管理引用计数时，它必须在每一个 clone 调用时增加计数，并在每一个克隆被丢弃时减少计数。
// Rc<T> 并没有使用任何并发原语，来确保改变计数的操作不会被其他线程打断。
// 在计数出错时可能会导致诡异的 bug，比如可能会造成内存泄漏，或在使用结束之前就丢弃一个值。
// 我们所需要的是一个完全类似 Rc<T>，又以一种线程安全的方式改变引用计数的类型。
/*
fn mutex_example2() {
    let counter = Rc::new(Mutex::new(0));
    let mut handles = vec![];

    for _ in 0..10 {
        let counter = Rc::clone(&counter);
        let handle = thread::spawn(move || {
            let mut num = counter.lock().unwrap();

            *num += 1;
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }
    println!("Result: {}", *counter.lock().unwrap());
}
*/

// 原子引用计数 Arc<T>
// 所幸 Arc<T> 正是 这么一个类似 Rc<T> 并可以安全的用于并发环境的类型。
// 字母 “a” 代表 原子性（atomic），所以这是一个原子引用计数（atomically reference counted）类型。
// 原子性是另一类这里还未涉及到的并发原语：请查看标准库中 std::sync::atomic 的文档来获取更多细节。
// 其中的要点就是：原子性类型工作起来类似原始类型，不过可以安全的在线程间共享。
fn mutex_example3() {
    let counter = Arc::new(Mutex::new(0));
    let mut handles = vec![];

    for _ in 0..10 {
        let counter = Arc::clone(&counter);
        let handle = thread::spawn(move || {
            let mut num = counter.lock().unwrap();

            *num += 1;
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }
    println!("Result: {}", *counter.lock().unwrap());
}
