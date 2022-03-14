// 当使用Box<T>时，又同时操作了共享数据时使用Rc<T>
// Rc<T> 的类型。其名称为 引用计数（reference counting）的缩写。
// 引用计数意味着记录一个值引用的数量来知晓这个值是否仍在被使用。
// 如果某个值有零个引用，就代表没有任何有效引用并可以被清理。
// 注意 Rc<T> 只能用于单线程场景，克隆 Rc<T> 会增加引用计数

use std::rc::Rc;

#[derive(Debug)]
enum List1 {
    Cons(i32, Box<List1>),
    Nil,
}

#[derive(Debug)]
enum List2 {
    Cons(i32, Rc<List2>),
    Nil,
}

fn main() {
    let a = List1::Cons(5, Box::new(List1::Cons(10, Box::new(List1::Nil))));
    println!("a = {:?}", a);
    let b = List1::Cons(3, Box::new(a));
    println!("b = {:?}", b);
    //let c = List1::Cons(4, Box::new(a)); // 这会报错,因为a被移动到了b中

    let c = Rc::new(List2::Cons(
        5,
        Rc::new(List2::Cons(10, Rc::new(List2::Nil))),
    ));
    // Rc::clone 的实现并不像大部分类型的 clone 实现那样对所有数据进行深拷贝。
    // Rc::clone 只会增加引用计数，这并不会花费多少时间。
    // 深拷贝可能会花费很长时间。
    // 通过使用 Rc::clone 进行引用计数，可以明显的区别深拷贝类的克隆和增加引用计数类的克隆。
    // 当查找代码中的性能问题时，只需考虑深拷贝类的克隆而无需考虑 Rc::clone 调用。
    println!("c = {:?}", c);
    let d = List2::Cons(3, Rc::clone(&c));
    println!("d = {:?}", d);
    let e = List2::Cons(4, Rc::clone(&c));
    println!("e = {:?}", e);
}
