//! This module speicifically exists to test the [`regex_ha`](regex::regex_ha) module.
//! All unit tests and integration tests related to [`regex_ha`](regex::regex_ha) go here

#[test]
fn should_fail_test1() 
{
    let mut regex_obj = regex::regex_ha::new("haahahhaa");
    let (parse_status, parse_errors) = regex_obj.parse();
    std::println!("Parse results:: {parse_status}, {parse_errors}");
    std::println!("haahahhaa");
    assert_eq!(false, parse_status);
}

#[test]
fn should_fail_test2() 
{
    let mut regex_obj = regex::regex_ha::new("hhhhahhaa");
    let (parse_status, parse_errors) = regex_obj.parse();
    std::println!("Parse results:: {parse_status}, {parse_errors}");
    std::println!("haahahhaa");
    assert_eq!(false, parse_status);
}

#[test]
fn should_fail_test3() 
{
    let mut regex_obj = regex::regex_ha::new("hhaa");
    let (parse_status, parse_errors) = regex_obj.parse();
    std::println!("Parse results:: {parse_status}, {parse_errors}");
    std::println!("haahahhaa");
    assert_eq!(false, parse_status);
}

#[test]
fn should_fail_test4() 
{
    let mut regex_obj = regex::regex_ha::new("aahhaa");
    let (parse_status, parse_errors) = regex_obj.parse();
    std::println!("Parse results:: {parse_status}, {parse_errors}");
    std::println!("haahahhaa");
    assert_eq!(false, parse_status);
}

#[test]
fn should_pass_test1() 
{
    let mut regex_obj = regex::regex_ha::new("haahaahahaa");
    let (parse_status, parse_errors) = regex_obj.parse();
    std::println!("Parse results:: {parse_status}, {parse_errors}");
    std::println!("haahahhaa");
    assert_eq!(true, parse_status);
}

#[test]
fn should_pass_test2() 
{
    let mut regex_obj = regex::regex_ha::new("hahahahaaaha");
    let (parse_status, parse_errors) = regex_obj.parse();
    std::println!("Parse results:: {parse_status}, {parse_errors}");
    std::println!("haahahhaa");
    assert_eq!(true, parse_status);
}

#[test]
fn should_pass_test3() 
{
    let mut regex_obj = regex::regex_ha::new("haaahaahahahahaaaa");
    let (parse_status, parse_errors) = regex_obj.parse();
    std::println!("Parse results:: {parse_status}, {parse_errors}");
    std::println!("haahahhaa");
    assert_eq!(true, parse_status);
}

#[test]
fn should_pass_test4() 
{
    let mut regex_obj = regex::regex_ha::new("haaaaaaaaahaaaaahahahaaaaa");
    let (parse_status, parse_errors) = regex_obj.parse();
    std::println!("Parse results:: {parse_status}, {parse_errors}");
    std::println!("haahahhaa");
    assert_eq!(true, parse_status);
}
