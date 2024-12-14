//! This is a binary impl of the [`regex`] crate/lib

fn main()
{
    let args_collected : Vec<String> = std::env::args().collect();
    if args_collected.len() <= 1
    {
        std::println!("Error: Too few args expected atleast 1 provided 0\n\
            Usage: {} <\"...\"> to check if its a part of (ha+)+ grammer or not", args_collected[0])
    }
    else
    {
        for i in &args_collected[1..]
        {
            let mut regex_obj = regex::regex_ha::new(i);
            let (parse_status, parse_errors) = regex_obj.parse();
            println!("Parse results: {}, {}", parse_status, parse_errors);
        }
    }
}
