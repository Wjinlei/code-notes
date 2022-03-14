// 泛型就是用来解决重复问题的,这个学过java的都懂。

use std::cmp::PartialOrd;

fn main() {
    let number_list = vec![1, 30, 2, 23, 44];
    println!("{}", largest1(&number_list));

    let char_list = vec!['a', 'c', 'b', 'e'];
    println!("{}", largest2(&char_list));

    // 调用泛型函数
    println!("{}", largest3(&number_list));
    println!("{}", largest3(&char_list));

    let integer = Point1 { x: 5, y: 10 };
    let integer2 = Point1 { x: 5.0, y: 1.0 };
    let float = Point2 { x: 1, y: 4.0 };
    println!("x = {}, y = {}", integer.x(), integer.y);
    println!("x = {}, y = {}", integer2.distance_from_origin(), integer.y);
    println!("x = {}, y = {}", float.x, float.y);

    let float2 = Point2 { x: 2, y: 3.0 };
    let float3 = float.mixup(float2);
    println!("x = {}, y = {}", float3.x, float3.y);
}

// 在函数定一种使用泛型
// 考虑一下这个寻找列表中最大值的小程序
// 这个函数的问题是只能接受i32类型的slice
// 我们想要处理其他类型的怎么办
fn largest1(list: &[i32]) -> i32 {
    // 取slice的第一个元素放到变量largest中
    let mut largest = list[0];

    // 遍历list
    for &item in list.iter() {
        if item > largest {
            // 如果元素比第一个元素大,则把它的值重新赋值给largest
            largest = item;
        }
    }
    largest
}

// 可以再定义一个
fn largest2(list: &[char]) -> char {
    let mut largest = list[0];

    for &item in list.iter() {
        if item > largest {
            largest = item;
        }
    }
    largest
}

// 但都不好,因为你写了两个函数体一样的函数,只是参数类型不一样
// 我们来看看利用泛型该怎么优化这个问题
// 可以这样理解这个定义：
// 函数 largest3 有泛型类型 T。
// 它有个参数 list，其类型是元素为 T 的 slice。
// largest3 函数的返回值类型也是 T。
fn largest3<T: PartialOrd + Copy>(list: &[T]) -> T {
    let mut largest = list[0];

    for &item in list.iter() {
        if item > largest {
            largest = item;
        }
    }
    largest
}
// 至于<T: PartialOrd + Copy>现在不必深究,后面会学习它

// 结构体中定义泛型
// 定义一个可以存放任何类型的 x 和 y 坐标值的结构体 Point1
struct Point1<T> {
    x: T,
    y: T,
}
// 定义一个可以存放两种任何类型的 x 和 y 坐标值的结构体 Point2
struct Point2<T, U> {
    x: T,
    y: U,
}

// 枚举中定义泛型同理我们已经见过Option<T>,和Result<T, E>枚举

// 方法中定义泛型
// 这里在 Point<T> 上定义了一个叫做 x 的方法来返回字段 x 中数据的引用
// 注意必须在 impl 后面声明 T，这样就可以在 Point<T> 上实现的方法中使用它了。
// 在 impl 之后声明泛型 T ，这样 Rust 就知道 Point 的尖括号中的类型是泛型而不是具体类型。
impl<T> Point1<T> {
    fn x(&self) -> &T {
        &self.x
    }
}
// 例如，可以选择为 Point<f32> 实例实现方法，而不是为泛型 Point 实例。
// 这段代码意味着 Point<f32> 类型会有一个方法 distance_from_origin
// 而其他 T 不是 f32 类型的 Point<T> 实例则没有定义此方法。
impl Point1<f32> {
    fn distance_from_origin(&self) -> f32 {
        (self.x.powi(2) + self.y.powi(2)).sqrt()
    }
}

// 结构体定义中的泛型类型参数并不总是与结构体方法签名中使用的泛型是同一类型。
// 这个方法获取另一个 Point2 作为参数，而它可能与调用 mixup 的 self 是不同的 Point2 类型。
// 这个方法用 self 的 Point2 类型的 x 值（类型 T）和参数的 Point2 类型的 y 值（类型 W）来创建一个新 Point2 类型的实例
impl<T, U> Point2<T, U> {
    fn mixup<V, W>(self, other: Point2<V, W>) -> Point2<T, W> {
        Point2 {
            x: self.x,
            y: other.y,
        }
    }
}
