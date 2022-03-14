// 方法 与函数类似：它们使用 fn 关键字和名称声明，可以拥有参数和返回值，同时包含在某处调用该方法时会执行的代码。
// 不过方法与函数是不同的，因为它们在结构体的上下文中被定义（或者是枚举或 trait 对象的上下文，）
// 并且它们第一个参数总是 self，它代表调用该方法的结构体实例。
// 和其他语言类似，没什么好说的，只是表现形式不同

// 让我们重写rs12中 area3 函数，改写成一个定义于 Rectangle 结构体上的 area 方法
#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    // impl 块的另一个有用的功能是：允许在 impl 块中定义 不 以 self 作为参数的函数。
    // 这被称为 关联函数（associated functions），因为它们与结构体相关联。
    // 它们仍是函数而不是方法，因为它们并不作用于一个结构体的实例。
    // 你已经使用过 String::from 关联函数了。
    // 关联函数经常被用作返回一个结构体新实例的构造函数。
    fn from(size: u32) -> Rectangle {
        // 这是个函数，不是方法，关联函数
        Rectangle {
            width: size,
            height: size,
        }
    }

    fn area3(&self) -> u32 {
        self.width * self.height
    }

    // 方法2,多个参数,如果 self 能完全包含第二个长方形则返回 true；否则返回 false。
    fn can_hold(&self, other: &Rectangle) -> bool {
        self.width > other.width && self.height > other.height
    }
}

fn main() {
    let rect1 = Rectangle {
        width: 30,
        height: 50,
    };
    let rect2 = Rectangle {
        width: 10,
        height: 40,
    };
    let rect3 = Rectangle {
        width: 60,
        height: 45,
    };

    println!("{:?}", rect1);
    println!(
        "The area of the rectangle is {} square pixels.",
        rect1.area3() // 调用方法
    );

    println!("Can rect1 hold rect2? {}", rect1.can_hold(&rect2));
    println!("Can rect1 hold rect3? {}", rect1.can_hold(&rect3));

    let rect4 = Rectangle::from(3);
    println!("{:?}", rect4);
}
