fn main() {
    let number = 3;

    // if 表达式允许根据条件执行不同的代码分支。
    // 你提供一个条件并表示 “如果条件满足，运行这段代码；如果条件不满足，不运行这段代码。”
    if number < 5 {
        println!("condition was true");
    } else {
        println!("condition was false");
    }

    // else if 处理多重条件
    if number % 4 == 0 {
        println!("number is divisible by 4");
    } else if number % 3 == 0 {
        println!("number is divisible by 3");
    } else if number % 2 == 0 {
        println!("number is divisible by 2");
    } else {
        println!("number is not divisible by 4, 3, or 2");
    }

    // 因为 if 是一个表达式，我们可以在 let 语句的右侧使用它
    let condition = true;
    let number = if condition { 5 } else { 6 }; // 如果条件满足,变量number=5,如果条件不满足,number=6
    println!("This value of number is: {}", number);

    // loop,无条件循环
    let mut counter = 0;
    let result = loop {
        counter += 1;
        if counter == 10 {
            // counter = 10的时候,跳出循环
            break counter * 2;
        }
    };
    println!("The result is {}", result);

    // while,条件循环
    let mut number = 3;
    // 当number不等于0的时候进入循环
    while number != 0 {
        println!("{}!", number);
        number = number - 1; // 每次循环number-1,直到条件number!=0不满足,退出循环
    }
    println!("LIFTOFF!!!");

    // for 循环
    // 使用 for 循环来对一个集合的每个元素执行一些代码。
    let a = [10, 20, 30, 40, 50];
    for element in a.iter() {
        println!("the value is: {}", element);
    }
}
