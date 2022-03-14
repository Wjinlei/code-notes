// 结构体和元组类似，结构体的每一部分可以是不同类型。
// 但不同于元组，结构体需要命名各部分数据以便能清楚的表明其值的意义。
// 由于有了这些名字，结构体比元组更灵活：不需要依赖顺序来指定或访问实例中的值。
//
// 定义结构体，需要使用 struct 关键字并为整个结构体提供一个名字。
// 结构体的名字需要描述它所组合的数据的意义。
// 接着，在大括号中，定义每一部分数据的名字和类型，我们称为 字段（field）。

// 一个存储用户账号信息的结构体
struct User {
    username: String,
    email: String,
    sign_in_count: u64,
    active: bool,
}
// User 结构体的定义中，我们使用了自身拥有所有权的 String 类型而不是 &str 字符串 slice 类型。
// 这是一个有意而为之的选择，因为我们想要这个结构体拥有它所有的数据，为此只要整个结构体是有效的话其数据也是有效的。
// 可以使结构体存储被其他对象拥有的数据的引用，不过这么做的话需要用上 生命周期（lifetimes）
// 生命周期确保结构体引用的数据有效性跟结构体本身保持一致。
// 这个问题以后再说,这里只是提一嘴。

fn main() {
    // 不可变的
    let user = User {
        username: String::from("wjl"),
        email: String::from("wjl@localhost.com"),
        sign_in_count: 1,
        active: true,
    };
    println!("username: {}", user.username);
    println!("email: {}", user.email);
    println!("sign_in_count: {}", user.sign_in_count);
    println!("active: {}", user.active);

    // 可变的
    let mut user = User {
        username: String::from("wjl"),
        email: String::from("wjl@localhost.com"),
        sign_in_count: 1,
        active: true,
    };
    user.username = String::from("lxf");
    // 注意整个实例必须是可变的；Rust 并不允许只将某个字段标记为可变。
    println!("username: {}", user.username);

    // 调用函数返回实例
    let user1 = build_user(String::from("user1@localhost.com"), String::from("user1"));
    let user2 = build_user2(String::from("user2@localhost.com"), String::from("user2"));
    println!("user1 username is: {}", user1.username);
    println!("user1 email is: {}", user1.email);
    println!("user2 username is: {}", user2.username);
    println!("user1 email is: {}", user2.email);

    // 使用旧实例的大部分值但改变其部分值来创建一个新的结构体实例通常是很有帮助的。
    // 这可以通过 结构体更新语法（struct update syntax）实现。
    // 下面展示不通过结构体更新语法,创建新的实例
    let user3 = User {
        email: String::from("user3@localhost.com"),
        username: String::from("user3"),
        active: user2.active,
        sign_in_count: user2.sign_in_count,
    };
    println!("user3 username is: {}", user3.username);
    println!("user3 email is: {}", user3.email);

    // 下面是通过结构体更新语法创建的新实例
    let user4 = User {
        email: String::from("user4@localhost.com"),
        username: String::from("user4"),
        ..user2
    };
    println!("user4 username is: {}", user4.username);
    println!("user4 email is: {}", user4.email);

    // 也可以定义与元组类似的结构体，称为 元组结构体（tuple structs）。
    // 元组结构体有着结构体名称提供的含义，但没有具体的字段名，只有字段的类型。
    // 当你想给整个元组取一个名字，并使元组成为与其他元组不同的类型时，元组结构体是很有用的
    // 这时像常规结构体那样为每个字段命名就显得多余和形式化了。
    // 下面定了了两个元祖结构体,Color和Point
    struct Color(i32, i32, i32);
    struct Point(i32, i32, i32);
    let black = Color(0, 0, 0);
    let origin = Point(0, 0, 0);
    println!("{}, {}, {}", black.0, black.1, black.2);
    println!("{}, {}, {}", origin.0, origin.1, origin.2);

    // 我们也可以定义一个没有任何字段的结构体！
    // 它们被称为 类单元结构体（unit-like structs）因为它们类似于 ()，即 unit 类型。
    // 类单元结构体常常在你想要在某个类型上实现 trait 但不需要在类型中存储数据的时候发挥作用。
}

// 另外需要注意同其他任何表达式一样，我们可以在函数体的最后一个表达式中构造一个结构体的新实例，来隐式地返回这个实例。
fn build_user(email: String, username: String) -> User {
    User {
        email: email,
        username: username,
        active: true,
        sign_in_count: 1,
    }
    // 为函数参数起与结构体字段相同的名字是可以理解的，但是不得不重复 email 和 username 字段名称与变量有些啰嗦。
    // 如果结构体有更多字段，重复每个名称就更加烦人了。幸运的是，有一个方便的简写语法！
}

fn build_user2(email: String, username: String) -> User {
    User {
        email,    // 简写写法,当变量名称和结构体成员名称相同时
        username, // 简写写法,当变量名称和结构体成员名称相同时
        active: true,
        sign_in_count: 1,
    }
    // 为函数参数起与结构体字段相同的名字是可以理解的，但是不得不重复 email 和 username 字段名称与变量有些啰嗦。
    // 如果结构体有更多字段，重复每个名称就更加烦人了。幸运的是，有一个方便的简写语法！
}
