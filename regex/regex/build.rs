// build.rs

use std::path::PathBuf;
use std::env;
use std::fs;
use std::path::Path;

fn get_test_files(manifest_dir : &str) -> Vec<PathBuf>
{
    let cargo_toml_path = Path::new(&manifest_dir).join("Cargo.toml");

    let toml_contents = fs::read_to_string(&cargo_toml_path)
        .expect("Failed to read Cargo.toml");

    let mut inside_tst_blk : bool = false;
    let mut test_file_paths : Vec<PathBuf> = vec![];

    for line in toml_contents.lines()
    {
        let trimmed_line = line.trim();

        if inside_tst_blk && trimmed_line.starts_with("path =")
        {
            test_file_paths.push
            (
                Path::new(&manifest_dir)
                .join
                (
                    trimmed_line["path =".len()..]
                    .trim_matches(|c| c == '"' || c == '\'' || c == ' ')
                    .to_string()
                )
            );
        }
        else if inside_tst_blk && trimmed_line.starts_with('[')
        {
            inside_tst_blk = false;
        }

        if trimmed_line.starts_with("[[test]]")
        {
            inside_tst_blk = true;
        }
    }
    return test_file_paths;
}

fn get_fns_from_file(test_file_paths : &Vec<PathBuf>) -> (Vec<String>, Vec<String>, Vec<String>)
{
    let mut test_fail_fns : Vec<String> = vec![];
    let mut test_pass_fns : Vec<String> = vec![];
    let mut file_names : Vec<String> = vec![];

    for file_paths in test_file_paths
    {
        file_names.push
            (
                file_paths.file_stem()
                .expect("FileName not found")
                .to_str().expect("Some unknown shit happened")
                .to_string()
            );

        let test_file_contents = fs::read_to_string(file_paths)
            .expect("Failed to read Cargo.toml");

        for line in test_file_contents.lines()
        {
            let trimmed_line = line.trim();
            if trimmed_line.starts_with("fn should_fail_test")
            {
                test_fail_fns.push
                (
                    trimmed_line["fn".len()..]
                    .trim_end_matches(|c| c == '{' || c == '}')
                    .to_string()
                );
            }
            else if trimmed_line.starts_with("fn should_pass_test")
            {
                test_pass_fns.push
                (
                    trimmed_line["fn".len()..]
                    .trim_end_matches(|c| c == '{' || c == '}')
                    .to_string()
                );
            }
        }

    }
    return (test_fail_fns, test_pass_fns, file_names);
}

fn gen_code(test_file_paths : &Vec<PathBuf>) -> String
{
    let (test_fail_fns, test_pass_fns, file_names_noext) = get_fns_from_file(&test_file_paths);

    let mut gen_str_code : String = "".to_string();
    for file in file_names_noext
    {
        gen_str_code.push_str("use ");
        gen_str_code.push_str(&file);
        gen_str_code.push_str(";\n");
    }

    gen_str_code.push_str("pub fn should_fail_tests()\n{");
    for gen_fails in test_fail_fns
    {
        gen_str_code.push('\n');
        gen_str_code.push_str(&gen_fails);
        gen_str_code.push(';');
    }
    gen_str_code.push_str("\n};");

    gen_str_code.push_str("\npub fn should_pass_tests()\n{");
    for gen_pass in test_pass_fns
    {
        gen_str_code.push('\n');
        gen_str_code.push_str(&gen_pass);
        gen_str_code.push(';');
    }
    gen_str_code.push_str("\n};");

    return gen_str_code;
}

fn main() 
{
    // This code generates a file at compile time

    println!("cargo:rerun-if-changed=build.rs");

    let manifest_dir = 
        env::var("CARGO_MANIFEST_DIR")
        .expect("CARGO_MANIFEST_DIR is not set");
    let test_file_paths : Vec<PathBuf> = get_test_files(&manifest_dir);

    let out_dir = env::var("OUT_DIR").expect("OUT_DIR is not set");
    let dest_path = Path::new(&out_dir).join("generated.rs");

    let generated_code = gen_code(&test_file_paths);
    fs::write(dest_path, generated_code)
        .expect("Failed to write generated code!");
}
