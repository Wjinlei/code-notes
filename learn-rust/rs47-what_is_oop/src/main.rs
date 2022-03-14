// 在一些定义下，Rust 是面向对象的；在其他定义下，Rust 不是。
// 也就是说看你自己怎么理解面向对象的定义
//
// 面向对象的特点
// 1.对象包含数据和行为
//     面向对象的程序是由对象组成的。一个 对象 包含数据和操作这些数据的过程。这些过程通常被称为 方法 或 操作。
// 2.封装隐藏了实现细节
//     另一个通常与面向对象编程相关的方面是 封装（encapsulation）的思想：对象的实现细节不能被使用对象的代码获取到。
//     所以唯一与对象交互的方式是通过对象提供的公有 API；使用对象的代码无法深入到对象内部并直接改变数据或者行为。
//     封装使得改变和重构对象的内部时无需改变使用对象的代码。
//     之前我们学习过可以使用 pub 关键字来决定模块、类型、函数和方法是公有的，而默认情况下其他一切都是私有的。
// 3.继承
//     继承（Inheritance）一个对象可以定义为继承另一个对象的定义，这使其可以获得父对象的数据和行为，而无需重新定义。
//     如果一个语言必须有继承才能被称为面向对象语言的话，那么 Rust 就不是面向对象的。
//     因为Rust 无法定义一个结构体继承父结构体的成员和方法。
//     不过Rust 为我们提供了其他解决方案，Rust 使用 trait 对象而不是继承。
//     选择继承有两个主要的原因:
//         3.1 为了重用代码：
//             一旦为一个类型实现了特定行为，继承可以对一个不同的类型重用这个实现。
//             Rust 代码可以使用默认 trait 方法实现来进行共享
//         3.2 与类型系统有关：
//             表现为子类型可以用于父类型被使用的地方。
//             这也被称为 多态（polymorphism），这意味着如果多种对象共享特定的属性，则可以相互替代使用。
//
// 近来继承作为一种语言设计的解决方案在很多语言中失宠了，因为其时常带有共享多于所需的代码的风险。
// 子类不应总是共享其父类的所有特征，但是继承却始终如此。
// 如此会使程序设计更为不灵活，并引入无意义的子类方法调用，或由于方法实际并不适用于子类而造成错误的可能性。
// 某些语言还只允许子类继承一个父类，进一步限制了程序设计的灵活性。
// 因为这些原因，Rust 选择了一个不同的途径，使用 trait 对象而不是继承。
//
// 总结一下：
//     如果你认为面向对象必须拥有继承和和多态的特性，那么Rust就不是面向对象的。


// 下面是一个例子
// 我们可以定义一个包含一个 i32 类型 vector 的结构体 AveragedCollection 。
// 结构体也可以有一个字段，该字段保存了 vector 中所有值的平均值。
// 这样，希望知道结构体中的 vector 的平均值的人可以随时获取它，而无需自己计算。
pub struct AveragedCollection {
    list: Vec<i32>,
    average: f64,
}

// 注意，结构体自身被标记为 pub，这样其他代码就可以使用这个结构体，但是在结构体内部的字段仍然是私有的。
// 这是非常重要的，因为我们希望保证变量被增加到列表或者被从列表删除时，也会同时更新平均值。
// 可以通过在结构体上实现 add、remove 和 average 方法来做到这一点
impl AveragedCollection {
    pub fn add(&mut self, value: i32) {
        self.list.push(value);
        self.update_average();
    }

    pub fn remove(&mut self) -> Option<i32> {
        let result = self.list.pop();
        match result {
            Some(value) => {
                self.update_average();
                Some(value)
            },
            None => None,
        }
    }

    pub fn average(&self) -> f64 {
        self.average
    }

    fn update_average(&mut self) {
        let total: i32 = self.list.iter().sum();
        self.average = total as f64 / self.list.len() as f64;
    }
}

fn main() {
    let list = Vec::new();
    let mut aver = AveragedCollection{list, average: 0.0};
    aver.add(1);
    aver.add(2);
    aver.add(3);
    aver.add(4);
    println!("aver avg is {}", aver.average);
}
