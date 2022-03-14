// 哈希 map（hash map）。
// HashMap<K, V> 类型储存了一个键类型 K 对应一个值类型 V 的映射。
// 它通过一个 哈希函数（hashing function）来实现映射，决定如何将键和值放入内存中。
// 很多编程语言支持这种数据结构，不过通常有不同的名字：哈希、map、对象、哈希表或者关联数组，仅举几例。
// 哈希 map 可以用于需要任何类型作为键来寻找数据的情况，而不是像 vector 那样通过索引。
//
// 例如，在一个游戏中，你可以将每个团队的分数记录到哈希 map 中，其中键是队伍的名字而值是每个队伍的分数。
// 给出一个队名，就能得到他们的得分。

use std::collections::HashMap;

fn main() {
    // 可以使用 new 创建一个空的 HashMap，并使用 insert 增加元素。
    let mut scores1 = HashMap::new();
    scores1.insert(String::from("Blue"), 10);
    scores1.insert(String::from("Yellow"), 50);
    // 类似于 vector，哈希 map 是同质的：所有的键必须是相同类型，值也必须都是相同类型。
    // 这个 HashMap 的键类型是 String 而值类型是 i32。

    // 另一个构建哈希 map 的方法是使用一个元组的 vector 的 collect 方法
    // 但我觉得比较复杂,不推荐,了解下即可必要时再考虑
    let teams = vec![String::from("Blue"), String::from("Yellow")];
    let initial_scores = vec![10, 50];
    // collect 方法可以将数据收集进一系列的集合类型，包括 HashMap。
    let scores2: HashMap<_, _> = teams.iter().zip(initial_scores.iter()).collect();

    // 可以通过 get 方法并提供对应的键来从哈希 map 中获取值
    let team_name = String::from("Blue");
    println!("{:?}", scores2.get(&team_name));

    // 可以使用与 vector 类似的方式来遍历哈希 map 中的每一个键值对，也就是 for 循环
    for (key, value) in &scores2 {
        println!("{}: {}", key, value);
    }

    // 更新哈希 map
    // 尽管键值对的数量是可以增长的，不过任何时候，每个键只能关联一个值。
    // 当我们想要改变哈希 map 中的数据时，必须决定如何处理一个键已经有值了的情况。
    // 1.可以选择完全无视旧值并用新值代替旧值。
    // 2.可以选择保留旧值而忽略新值，并只在键 没有 对应值时增加新值。
    // 3.或者可以结合新旧两值。
    // 让我们看看这分别该如何处理！

    // 覆盖一个值
    // 如果我们插入了一个键值对，接着用相同的键插入一个不同的值，与这个键相关联的旧值将被替换。
    let mut scores3 = HashMap::new();
    scores3.insert(String::from("Red"), 10);
    scores3.insert(String::from("Red"), 20);
    println!("{:?}", scores3);

    // 只在键没有对应值时插入
    // 我们经常会检查某个特定的键是否有值，如果没有就插入一个值。
    // 为此哈希 map 有一个特有的 API，叫做 entry，它获取我们想要检查的键作为参数。
    // entry 函数的返回值是一个枚举，Entry，它代表了可能存在也可能不存在的值。
    // 比如说我们想要检查黄队的键是否关联了一个值。如果没有，就插入值 50，对于蓝队也是如此。
    let mut scores4 = HashMap::new();
    scores4.insert(String::from("Blue"), 10);
    scores4.entry(String::from("Yellow")).or_insert(50);
    scores4.entry(String::from("Blue")).or_insert(50); // 因为篮队已经有值,因此不会再插入值了
    println!("{:?}", scores4);
    // Entry 的 or_insert 方法在键对应的值存在时就返回这个值的可变引用。
    // 如果不存在则将参数作为新值插入并返回新值的可变引用。
    // 这比编写自己的逻辑要简明的多，另外也与借用检查器结合得更好。

    // 根据旧值更新一个值
    // 一个常见的哈希 map 的应用场景是找到一个键对应的值并根据旧的值更新它。
    // 例如，计数一些文本中每一个单词分别出现了多少次。
    // 我们使用哈希 map 以单词作为键并递增其值来记录我们遇到过几次这个单词。
    // 如果是第一次看到某个单词，就插入值 0。
    let text = "hello world wonderful world";
    let mut map = HashMap::new();
    for word in text.split_whitespace() {
        let count = map.entry(word).or_insert(0);
        *count += 1;
    }
    println!("{:?}", map);
    // 这个例子的最重要的部分就是entry会返回这个键的值的一个可变引用（&mut V）。
    // 这里我们将这个可变引用储存在 count 变量中。
    // 所以为了赋值必须首先使用星号（*）解引用 count。
    // 这个可变引用在 for 循环的结尾离开作用域，这样所有这些改变都是安全的并符合借用规则。

    // HashMap 实际上不是最快的算法
    // HashMap 默认使用一种 “密码学安全的”（“cryptographically strong” ）哈希函数。
    // 它可以抵抗拒绝服务（Denial of Service, DoS）攻击。
    // 然而这并不是可用的最快的算法，不过为了更高的安全性值得付出一些性能的代价。
    // 如果性能监测显示此哈希函数非常慢，以致于你无法接受，你可以指定一个不同的 hasher 来切换为其它函数。
    // hasher 是一个实现了 BuildHasher trait 的类型。
    // 第十章会讨论 trait 和如何实现它们。
    // 你并不需要从头开始实现你自己的 hasher；crates.io 有其他人分享的实现了许多常用哈希算法的 hasher 的库。
}
