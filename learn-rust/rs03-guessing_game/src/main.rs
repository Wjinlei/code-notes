use rand::Rng; // use rand::Rng。Rng 是一个 trait，它定义了随机数生成器应实现的方法，现在先不必深究这是什么
use std::cmp::Ordering; // 从标准库引入了一个叫做 std::cmp::Ordering 的类型。
                        // 同 Result 一样， Ordering 也是一个枚举，不过它的成员是 Less、Greater 和 Equal。这是比较两个值时可能出现的三种结果。
use std::io; // 为了获取用户输入并打印结果作为输出，我们需要将 io（输入/输出）库引入当前作用域
fn main() {
    println!("Guess the number!");

    // rand::thread_rng 函数提供实际使用的随机数生成器：它位于当前执行线程的本地环境中，并从操作系统获取 seed。
    // 接下来，调用随机数生成器的 gen_range 方法。这个方法由刚才引入到作用域的 Rng trait 定义。
    // gen_range 方法获取两个数字作为参数，并生成一个范围在两者之间的随机数。
    // 它包含下限但不包含上限，所以需要指定 1 和 101 来请求一个 1 和 100 之间的数。
    let secret_number = rand::thread_rng().gen_range(1..101);

    // println!("The secret number is: {}", secret_number); // 正式发布中,要删掉,别问为什么

    // loop 关键字创建了一个无限循环。将其加入后，用户可以反复猜测：
    loop {
        println!("Please input your guess.");

        // 在rust中,变量默认是不可变的,可以通过mut关键字来使一个变量可变
        // String 是一个标准库提供的字符串类型，它是 UTF-8 编码的可增长文本块。
        // ::new 那一行的 :: 语法表明 new 是 String 类型的一个 关联函数（associated function）。
        // new 函数创建了一个新的空字符串
        let mut guess = String::new(); //总结一下，这一行创建了一个可变变量guess，当前它绑定到一个新的 String 空实例上。

        // 调用 io 库中的函数 stdin，stdin 函数返回一个 std::io::Stdin 的实例，这代表终端标准输入句柄的类型。
        // .read_line(&mut guess)，调用 read_line 方法从标准输入句柄获取用户输入。我们还向 read_line() 传递了一个参数：&mut guess。
        // read_line 的工作是，无论用户在标准输入中键入什么内容，都将其存入一个字符串中，因此它需要字符串作为参数。这个字符串参数应该是可变的，以便 read_line 将用户输入附加上去。
        // & 表示这个参数是一个 引用（reference），它允许多处代码访问同一处数据，而无需在内存中多次拷贝。
        // read_line 方法返回一个之 io::Result
        // io::Result 的实例拥有 expect 方法。如果 io::Result 实例的值是 Err，expect 会导致程序崩溃，并显示当做参数传递给 expect 的信息。
        // 如果 io::Result 实例的值是 Ok，expect 会获取 Ok 中的值并原样返回。
        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");

        // 这里创建了一个叫做 guess 的变量。不过等等，不是已经有了一个叫做 guess 的变量了吗？确实如此，
        // 不过 Rust 允许用一个新值来 隐藏 （shadow） guess 之前的值。
        // 这个功能常用在需要转换值类型之类的场景。它允许我们复用 guess 变量的名字，而不是被迫创建两个不同变量。
        // String 实例的 trim 方法会去除字符串开头和结尾的空白字符。
        // 字符串的 parse 方法 将字符串解析成数字。
        // 因为这个方法可以解析多种数字类型，这里通过 let guess: u32 指定。guess 后面的冒号（:）告诉 Rust 我们指定了变量的类型。
        //
        // 将 expect 调用换成 match 语句，是从遇到错误就崩溃转换到真正处理错误的惯用方法。
        // 须知 parse 返回一个 Result 类型，而 Result 是一个拥有 Ok 或 Err 成员的枚举。
        // 这里使用的 match 表达式，和之前处理 cmp 方法返回 Ordering 时用的一样。
        //
        // 如果 parse 能够成功的将字符串转换为一个数字，它会返回一个包含结果数字的 Ok。
        // 这个 Ok 值与 match 第一个分支的模式相匹配，该分支对应的动作返回 Ok 值中的数字 num，最后如愿变成新创建的 guess 变量。
        // 如果 parse 不 能将字符串转换为一个数字，它会返回一个包含更多错误信息的 Err。
        // Err 值不能匹配第一个 match 分支的 Ok(num) 模式，但是会匹配第二个分支的 Err(_) 模式：_ 是一个通配符值，本例中用来匹配所有 Err 值，不管其中有何种信息。
        // 所以程序会执行第二个分支的动作，continue 意味着进入 loop 的下一次循环，请求另一个猜测。这样程序就有效的忽略了 parse 可能遇到的所有错误！
        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };

        println!("You guessed: {}", guess); // 使用 println! 占位符打印值，里面的 {} 是预留在特定位置的占位符

        // cmp 方法用来比较两个值并可以在任何可比较的值上调用。
        // 它获取一个被比较值的引用：这里是把 guess 与 secret_number 做比较。
        // 然后它会返回一个刚才通过 use 引入作用域的 Ordering 枚举的成员。
        // 使用一个 match 表达式，根据对 guess 和 secret_number 调用 cmp 返回的 Ordering 成员来决定接下来做什么。
        match guess.cmp(&secret_number) {
            Ordering::Less => println!("Too small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal => {
                println!("You win!");
                break; // 猜测正确,退出循环
            }
        };
    }
}
