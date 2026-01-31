# Calculator

## Description
Simple console calculator for UNIX
## How to install
- Clone repository
`git clone https://github.com/Vaturia/calculator.git`
- Install
```bash
~$ cd calculator
~$ cmake -B build
~$ cmake --build build
~$ sudo cmake --build build --target install
```
## How use
The calculator accepts a json file as input.
Has three operation mode:
- "help" - get help about program
- "version" - get version program
- "calculation" - mode for execute calculation

When use "help" mode, other fields can be empty. See [Example](#minimal-require-for-json-file).
When use "calculation" mode and use binary operation All fields must be filled in. See [Example](#format-example-json-file).
When use "calculation" mode and use unary operation field "second_num" can be empty. See
### Format examples json file
#### This example must for get help program
```json
{
    "mode": "help"
}
```
#### Binary operation
```json
{
    "mode": "calculation",
    "first_num": 5,
    "second_num": 3,
    "operation": "+"
}
```
#### Unary operation
```json
{
    "mode": "calculation",
    "first_num": 5,
    "operation": "!"
}
```
### Use
- For get help use:
```bash
~$ calculator file.json 
```
format `file.json` see [this](#this-example-must-for-get-help-program)

### Other
The project contains tests.
By default, tests are compiled with the project, but they can be disabled.
Edit `calculator/tests/CMakeLists.txt` for off
```cmake
option(ENABLE_TESTS "Enable tests" OFF)
```
#### How run tests
To run tests, execute 
```bash
./calculator/build/tests/run_tests
```