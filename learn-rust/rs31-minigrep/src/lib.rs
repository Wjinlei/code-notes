use std::error::Error;
use std::fs;
use std::env;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn one_result() {
        let query = "duct";
        let contents = "\
Rust:
safe, fast, productive.
Pick three.";
        assert_eq!(vec!["safe, fast, productive."], search(query, contents))
    }

    #[test]
    fn case_insensitive() {
        let query = "rUsT";
        let contents = "\
Rust:
safe, fast, productive.
Pick three.
Trust me.";
        assert_eq!(
            vec!["Rust:", "Trust me."],
            search_case_insensitive(query, contents)
        )
    }
}

pub struct Config {
    pub query: String,
    pub filename: String,
    pub case_sensitive: bool, // 是否区分大小写
}

impl Config {
    // new函数返回一个 Result 值，它在成功时会包含一个 Config 的实例，而在错误时会描述问题。
    // 当 Config::new 与 main 交流时，可以使用 Result 类型来表明这里存在问题。
    pub fn new(args: &[String]) -> Result<Config, &'static str> {
        if args.len() < 3 {
            return Err("not enough arguments");
        }
        let query = args[1].clone();
        let filename = args[2].clone();
        // env::var 方法可以检查一个环境变量是否被设置
        let case_sensitive = env::var("CASE_INSENSITIVE").is_err(); // 如果没有错,is_err,会返回false
        Ok(Config {
            query,
            filename,
            case_sensitive,
        })
    }

    // 使用33学习的迭代器知识优化new函数
    pub fn new2(mut args: std::env::Args) -> Result<Config, &'static str> {
        args.next(); // 第一个参数是文件名,因此跳过

        let query = match args.next() {
            Some(arg) => arg,
            None => return Err("Didn 't get a query string"),
        };

        let filename = match args.next() {
            Some(arg) => arg,
            None => return Err("Didn 't get a filename"),
        };

        let case_sensitive = env::var("CASE_INSENSITIVE").is_err();
        Ok(Config {query, filename, case_sensitive})
    }
}

// 将 run 函数的返回类型变为 Result<(), Box<dyn Error>>。
// 对于错误类型，使用了 trait 对象 Box<dyn Error>。
// 目前只需知道 Box<dyn Error> 意味着函数会返回实现了 Error trait 的类型
// 无需指定具体将会返回的值的类型。
// 这提供了在不同的错误场景可能有不同类型的错误返回值的灵活性。
// 这也就是 dyn，它是 “动态的”（“dynamic”）的缩写。
// 说白了就是成功返回空,失败返回错误
pub fn run(config: Config) -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string(config.filename)?;

    let results = if config.case_sensitive {
        search(&config.query, &contents)
    } else {
        search_case_insensitive(&config.query, &contents)
    };
    for line in results {
        println!("{}", line);
    }
    Ok(())
}

pub fn search<'a>(query: &str, contents: &'a str) -> Vec<&'a str> {
    //let mut results = Vec::new();
    //for line in contents.lines() {
        //if line.contains(query) {
            //results.push(line);
        //}
    //}

    // 使用33学习的迭代器知识优化
    contents.lines().filter(|line| line.contains(query)).collect()
    //results
}

fn search_case_insensitive<'a>(query: &str, contents: &'a str) -> Vec<&'a str> {
    let query = query.to_lowercase(); // 转小写
    let mut results = Vec::new();

    for line in contents.lines() {
        if line.to_lowercase().contains(&query) {
            results.push(line);
        }
    }
    results
}
