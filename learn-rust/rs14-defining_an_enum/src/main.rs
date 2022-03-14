// 让我们看看一个需要诉诸于代码的场景，来考虑为何此时使用枚举更为合适且实用。
// 假设我们要处理 IP 地址。目前被广泛使用的两个主要 IP 标准：IPv4（version four）和 IPv6（version six）。
// 这是我们的程序可能会遇到的所有可能的 IP 地址类型：所以可以 枚举 出所有可能的值，这也正是此枚举名字的由来。
//
// 任何一个 IP 地址要么是 IPv4 的要么是 IPv6 的，而且不能两者都是。
// IP 地址的这个特性使得枚举数据结构非常适合这个场景，因为枚举值只可能是其中一个成员。
// IPv4 和 IPv6 从根本上讲仍是 IP 地址，所以当代码在处理适用于任何类型的 IP 地址的场景时应该把它们当作相同的类型。
//
// 下面的实例定义了一个枚举类型
#[derive(Debug)]
enum IpAddrKind {
    V4,
    V6,
}

#[derive(Debug)]
struct IpAddr {
    kind: IpAddrKind,
    address: String,
}

#[derive(Debug)]
enum IpAddr2 {
    V4(String),
    V6(String),
}

#[derive(Debug)]
enum IpAddr3 {
    V4(u8, u8, u8, u8),
    V6(String),
}

// 枚举上也可以定义方法
impl IpAddr3 {
    fn print(&self) {
        println!("{:?}", self)
    }
}

fn main() {
    // 可以像这样创建 IpAddrKind 两个不同成员的实例：
    //let four = IpAddrKind::V4;
    //let six = IpAddrKind::V6;
    // 注意枚举的成员位于其标识符的命名空间中，并使用两个冒号分开。
    // 这么设计的益处是现在 IpAddrKind::V4 和 IpAddrKind::V6 都是 IpAddrKind 类型的。

    // 我们将枚举和String类型关联
    // 这里我们定义了一个有两个字段的结构体 IpAddr：
    // IpAddrKind（之前定义的枚举）类型的 kind 字段
    // String 类型 address 字段。
    // 我们有这个结构体的两个实例。第一个，home，它的 kind 的值是 IpAddrKind::V4 与之相关联的地址数据是 127.0.0.1。
    // 第二个实例，loopback，kind 的值是 IpAddrKind 的另一个成员，V6，关联的地址是 ::1。
    // 我们使用了一个结构体来将 kind 和 address 打包在一起，现在枚举成员就与值相关联了。
    let home = IpAddr {
        kind: IpAddrKind::V4,
        address: String::from("127.0.0.1"),
    };
    println!("{:?}", home);

    let loopback = IpAddr {
        kind: IpAddrKind::V6,
        address: String::from("::1"),
    };
    println!("{:?}", loopback);

    // 我们可以使用一种更简洁的方式来表达相同的概念，
    // 仅仅使用枚举并将数据直接放进每一个枚举成员而不是将枚举作为结构体的一部分。
    // IpAddr2 枚举的新定义表明了 V4 和 V6 成员都关联了 String 值：
    let home2 = IpAddr2::V4(String::from("127.0.0.1"));
    let loopback2 = IpAddr2::V6(String::from("::1"));
    println!("{:?}", home2);
    println!("{:?}", loopback2);

    // 用枚举替代结构体还有另一个优势：每个成员可以处理不同类型和数量的数据。
    // IPv4 版本的 IP 地址总是含有四个值在 0 和 255 之间的数字部分。
    // 如果我们想要将 V4 地址存储为四个 u8 值而 V6 地址仍然表现为一个 String，
    // 这就不能使用结构体了。枚举则可以轻易的处理这个情况：
    let home3 = IpAddr3::V4(127, 0, 0, 1);
    let loopback3 = IpAddr3::V6(String::from("::1"));
    println!("{:?}", home3);
    println!("{:?}", loopback3);

    // 标准库提供了一个开箱即用的定义！
    // https://doc.rust-lang.org/std/net/enum.IpAddr.html

    // 枚举上也可以定义方法
    home3.print()

    // Option 枚举,这个没咋看懂,后面再回来研究
    // https://kaisery.github.io/trpl-zh-cn/ch06-01-defining-an-enum.html?search=#option-%E6%9E%9A%E4%B8%BE%E5%92%8C%E5%85%B6%E7%9B%B8%E5%AF%B9%E4%BA%8E%E7%A9%BA%E5%80%BC%E7%9A%84%E4%BC%98%E5%8A%BF
}
