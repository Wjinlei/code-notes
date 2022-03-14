// 执行cargo test 即可运行测试
//
// 就像 cargo run 会编译代码并运行生成的二进制文件一样
// cargo test 在测试模式下编译代码并运行生成的测试二进制文件。
// 可以指定命令行参数来改变 cargo test 的默认行为。
// cargo test 生成的二进制文件的默认行为是并行的运行所有测试
// 并截获测试运行过程中产生的输出，阻止他们被显示出来，使得阅读测试结果相关的内容变得更容易。
//
// 可以将一部分命令行参数传递给 cargo test，而将另外一部分传递给生成的测试二进制文件。
// 为了分隔这两种参数，需要先列出传递给 cargo test 的参数，接着是分隔符 --，再之后是传递给测试二进制文件的参数。
// 运行 cargo test --help 会提示 cargo test 的有关参数
// 而运行 cargo test -- --help 可以提示在分隔符 -- 之后使用的有关参数。
//
// 当运行多个测试时， Rust 默认使用线程来并行运行。
// 这意味着测试会更快地运行完毕，所以你可以更快的得到代码能否工作的反馈。
// 因为测试是在同时运行的，你应该确保测试不能相互依赖
// 或依赖任何共享的状态，包括依赖共享的环境，比如当前工作目录或者环境变量。
// 举个例子，每一个测试都运行一些代码，假设这些代码都在硬盘上创建一个 test-output.txt 文件并写入一些数据。
// 接着每一个测试都读取文件中的数据并断言这个文件包含特定的值，而这个值在每个测试中都是不同的。
// 因为所有测试都是同时运行的，一个测试可能会在另一个测试读写文件过程中修改了文件。
// 那么第二个测试就会失败，并不是因为代码不正确，而是因为测试并行运行时相互干扰。
// 一个解决方案是使每一个测试读写不同的文件；另一个解决方案是一次运行一个测试。
//
// 可以使用 cargo test -- --test-threads=1 将测试线程设置为 1，告诉程序不要使用任何并行机制。
// 这也会比并行运行花费更多时间，不过在有共享的状态时，测试就不会潜在的相互干扰了。
//
// 默认情况下，当测试通过时，Rust 的测试库会截获打印到标准输出的所有内容。
// 比如在测试中调用了 println! 而测试通过了，我们将不会在终端看到 println! 的输出。
// 只会看到说明测试通过的提示行。如果测试失败了，则会看到所有标准输出和其他错误信息。
// 如果你希望也能看到通过的测试中打印的值，截获输出的行为可以通过 --nocapture 参数来禁用
// cargo test -- --nocapture
//
// 有时运行整个测试集会耗费很长时间。
// 如果你负责特定位置的代码，你可能会希望只运行与这些代码相关的测试。
// 你可以向 cargo test 传递所希望运行的测试名称的参数来选择运行哪些测试。
// cargo test panic_test2 // 只测试panic_test2函数
// cargo test panic // 只测试所有名字中带有panic的函数
//
// 可以使用 cargo test -- --ignored 来测试被忽略了的函数

#[cfg(test)]
mod tests {
    // #[test] 注解用来表明这是一个测试函数
    #[test]
    fn it_works() {
        let a = true;
        assert_eq!(2 + 2, 4); // assert_eq! 宏用来判断值是否相等
        assert_ne!(2 + 2, 3); // assert_ne! 宏用来判断值是否不相等
        assert!(a); // assert! 宏用来判断bool值是否为true
    }

    #[test]
    #[should_panic] // #[should_panic] 注解用来指明该函数应该发生painc，如果没有painc则测试失败
    fn panic_test1() {
        let v = vec![1, 2, 3];
        println!("{:?}", v[10]);
    }

    // 然而 should_panic 测试结果可能会非常含糊不清，因为它只是告诉我们代码并没有产生 panic。
    // should_panic 甚至在一些不是我们期望的原因而导致 panic 时也会通过。
    // 为了使 should_panic 测试结果更精确，我们可以给 should_panic 属性增加一个可选的 expected 参数。
    // 测试工具会确保错误信息中包含其提供的文本。
    #[test]
    #[should_panic(expected = "v = 1")] // 确保panic信息中包含v = 1
    fn panic_test2() {
        let v = vec![1, 2, 3];
        //println!("{:?}", v[10]); // 虽然引发了panic,但由于错误中不包含 v = 1 因此不算
        if v[0] == 1 {
            panic!("v = 1")
        }
    }

    // 不能对这些使用 Result<T, E> 的测试使用 #[should_panic] 注解。
    // 相反应该在测试失败时直接返回 Err 值。
    // 这样编写测试来返回 Result<T, E> 就可以在函数体中使用问号运算符，如此可以方便的编写任何运算符会返回 Err 成员的测试。
    #[test]
    fn result_test() -> Result<(), String> {
        if 2 + 2 == 4 {
            Ok(())
        } else {
            Err(String::from("two plus two does not equal four"))
        }
    }

    #[test]
    #[ignore] // #[ignore] 注解表明该函数默认不会被测试
    fn ignore_test() {
        println!("ignore_test() is run...")
    }
}
