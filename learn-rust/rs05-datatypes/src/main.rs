fn main() {
    // 在 Rust 中，每一个值都属于某一个 数据类型（data type），这告诉 Rust 它被指定为何种数据，以便明确数据处理方式。
    // 记住，Rust 是 静态类型（statically typed）语言，也就是说在编译时就必须知道所有变量的类型。
    //
    // 标量（scalar）类型代表一个单独的值。Rust 有四种基本的标量类型：整型、浮点型、布尔类型和字符类型。
    //
    // 整型
    // 长度     有符号    无符号
    // 8-bit    i8        u8
    // 16-bit   i16       u16
    // 32-bit   i32       u32
    // 64-bit   i64       u64
    // 128-bit  i128      u128
    // arch     isize     usize
    // isize 和 usize 类型依赖运行程序的计算机架构：64 位架构上它们是 64 位的， 32 位架构上它们是 32 位的。
    //
    // 浮点数
    // 32-bit   f32
    // 64-bit   f64
    let x = 2.0; // f64
    let y: f32 = 3.0; // f32
    println!("This value of x is: {}", x);
    println!("This value of y is: {}", y);

    // 布尔类型
    // bool
    //
    let t = true;
    let f: bool = false; // 显式指定类型注解
    println!("This value of t is: {}", t);
    println!("This value of f is: {}", f);

    // 字符类型
    // char
    let c = 'z';
    let z = 'ℤ';
    let heart_eyed_cat = '😻';
    println!("This value of c is: {}", c);
    println!("This value of z is: {}", z);
    println!("This value of heart_eyed_cat is: {}", heart_eyed_cat);

    // 复合类型
    // 元祖类型
    let tup: (i32, f64, u8) = (500, 6.4, 1);
    println!("This value of tup is: {},{},{}", tup.0, tup.1, tup.2);

    // 数组类型
    // 数组非常有用。但是数组并不如 vector 类型灵活。
    // vector 类型是标准库提供的一个 允许 增长和缩小长度的类似数组的集合类型。
    // 当不确定是应该使用数组还是 vector 的时候，你可能应该使用 vector。
    let arr1 = [1, 2, 3, 4, 5];
    let arr2: [i32; 5] = [1, 2, 3, 4, 5];
    let arr3 = [3; 5]; // 变量名为 a 的数组将包含 5 个元素，这些元素的值最初都将被设置为 3。
                       // 这种写法与 let a = [3, 3, 3, 3, 3]; 效果相同，但更简洁。
    println!("This value of arr1[0] is: {}", arr1[0]);
    println!("This value of arr2[1] is: {}", arr2[1]);
    println!("This value of arr3[2] is: {}", arr3[2]);
}
