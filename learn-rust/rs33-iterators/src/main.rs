// 迭代器没啥好说的，学过java的都懂
// 值得一提的是Rust的迭代器是惰性的
// 这意味着在调用迭代方法前，它都不会有效果

fn main() {
    let v1 = vec![1, 2, 3];

    // iter 方法生成一个不可变引用的迭代器。
    // 如果我们需要一个获取 v1 所有权并返回拥有所有权的迭代器，则可以调用 into_iter 而不是 iter。
    // 类似的，如果我们希望迭代可变引用，则可以调用 iter_mut 而不是 iter。
    for val in v1.iter() {
        println!("Got: {}", val);
    }


    // 总结一下
    // 迭代器比for循环更高效，是不是更高效我也不清楚，至少rust官方说是
    // 我也懒得去求证了。
    // 参考: https://kaisery.github.io/trpl-zh-cn/ch13-04-performance.html
}

#[test]
fn iterator_demonstration() {
    let v1 = vec![1, 2, 3];

    // 注意 v1_iter 需要是可变的：在迭代器上调用 next 方法改变了迭代器中用来记录序列位置的状态。
    // 换句话说，代码 消费（consume）了，或使用了迭代器。
    // 每一个 next 调用都会从迭代器中消费一个项。
    // 使用 for 循环时无需使 v1_iter 可变因为 for 循环会获取 v1_iter 的所有权并在后台使 v1_iter 可变。
    let mut v1_iter = v1.iter();

    assert_eq!(v1_iter.next(), Some(&1));
    assert_eq!(v1_iter.next(), Some(&2));
    assert_eq!(v1_iter.next(), Some(&3));
    assert_eq!(v1_iter.next(), None);
}

// 这些调用 next 方法的方法被称为 消费适配器（consuming adaptors），因为调用他们会消耗迭代器。
// 一个消费适配器的例子是 sum 方法。
// 这个方法获取迭代器的所有权并反复调用 next 来遍历迭代器，因而会消费迭代器。
// 当其遍历每一个项时，它将每一个项加总到一个总和并在迭代完成时返回总和。
#[test]
fn iterator_sum() {
    let v1 = vec![1, 2, 3];

    let v1_iter = v1.iter();

    let total: i32 = v1_iter.sum();

    assert_eq!(total, 6);
}

// map 方法使用闭包来调用每个元素以生成新的迭代器。
// 这里的闭包创建了一个新的迭代器，对其中 vector 中的每个元素都被加 1。
// collect 方法消费迭代器并将结果收集到一个数据结构中。
#[test]
fn iterator_map() {
    let v1: Vec<i32> = vec![1, 2, 3];

    // 如果你不调用collect方法消费迭代器的话,光map方法是没有什么效果的
    // 因为迭代器是惰性的。
    let v2: Vec<_> = v1.iter().map(|x| x + 1).collect();

    assert_eq!(v2, vec![2, 3, 4]);
}

// 使用闭包获取环境
#[derive(PartialEq, Debug)]
struct Shoe {
    size: u32,
    style: String,
}

fn shoes_in_my_size(shoes: Vec<Shoe>, shoe_size: u32) -> Vec<Shoe> {
    // 迭代器的 filter 方法获取一个使用迭代器的每一个项并返回布尔值的闭包。
    // 如果闭包返回 true，其值将会包含在 filter 提供的新迭代器中。
    // 如果闭包返回 false，其值不会包含在结果迭代器中。
    shoes.into_iter().filter(|s| s.size == shoe_size).collect()
}

#[test]
fn filters_by_size() {
    let shoes = vec![
        Shoe {size: 10,style: String::from("sneaker")},
        Shoe {size: 13,style: String::from("sandal")},
        Shoe {size: 10,style: String::from("boot")},
    ];

    let in_my_size = shoes_in_my_size(shoes, 10);

    assert_eq!(
        in_my_size,
        vec![
            Shoe {size: 10,style: String::from("sneaker")},
            Shoe {size: 10,style: String::from("boot")},
        ]
    );
}

// 自定义迭代器
struct Counter {
    count: u32,
}

impl Counter {
    fn new() -> Counter {
        Counter { count: 0 }
    }
}

// 需要实现Iterator trait
// 注意这里有一个我们还未讲到的新语法：type Item 和 Self::Item，他们定义了 trait 的 关联类型（associated type）。
// 现在只需知道这段代码表明实现 Iterator trait 要求同时定义一个 Item 类型，这个 Item 类型被用作 next 方法的返回值类型。
// 换句话说，Item 类型将是迭代器返回元素的类型。
impl Iterator for Counter {
    type Item = u32;

    // next 是 Iterator 实现者被要求定义的唯一方法。
    // next 一次返回迭代器中的一个项，封装在 Some 中，当迭代器结束时，它返回 None。
    fn next(&mut self) -> Option<Self::Item> {
        self.count += 1;

        if self.count < 6 {
            Some(self.count)
        } else {
            None
        }
    }
}

#[test]
fn calling_next_directly() {
    let mut counter = Counter::new();

    assert_eq!(counter.next(), Some(1));
    assert_eq!(counter.next(), Some(2));
    assert_eq!(counter.next(), Some(3));
    assert_eq!(counter.next(), Some(4));
    assert_eq!(counter.next(), Some(5));
    assert_eq!(counter.next(), None);
}
